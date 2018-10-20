// MWavFile --- Linear PCM sound reader/writer
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>.
// This file is public domain software.
///////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWAVFILE_HPP_
#define MZC4_MWAVFILE_HPP_      1   // Version 1

#ifdef _WIN32
    #ifndef _INC_WINDOWS
        #include <windows.h>
    #endif
    #ifndef _INC_MMSYSTEM
        #include <mmsystem.h>
    #endif
#endif

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

class MWavFile
{
public:
    MWavFile();
    MWavFile(const char *filename);
    virtual ~MWavFile();

    uint32_t    m_file_size;            // the size of contents
    uint32_t    m_fmt_size;             // 16 for linear PCM
    uint16_t    m_format_id;            // 1 for PCM
    uint16_t    m_num_channels;         // the number of channels
    uint32_t    m_samples_per_second;   // the sampling rate
    uint32_t    m_bytes_per_second;
    uint16_t    m_bits_per_sample;

    bool load(const char *filename);
    bool is_loaded() const;
    bool is_stereo() const;
    bool save(const char *filename) const;
    void clear();

    typedef std::vector<uint8_t> data_type;
    data_type   m_contents;
    data_type   m_wave_data;
    void build();   // build m_contents

    size_t size() const;
    size_t info_size() const;
    size_t data_size() const;

    void dump_info() const;

#ifdef _WIN32
    void play(DWORD dwFlags = SND_MEMORY | SND_SYNC | SND_NODEFAULT) const;
#endif

protected:
    bool        m_loaded;
    bool read(FILE *fp);
    uint16_t get_u16(const void *data) const;
    uint32_t get_u32(const void *data) const;

    bool write(FILE *fp) const;
    void set_u16(void *data, uint16_t value) const;
    void set_u32(void *data, uint32_t value) const;
};

///////////////////////////////////////////////////////////////////////////////

inline void MWavFile::clear()
{
    m_loaded = false;
    m_file_size = 0;
    m_fmt_size = 0;
    m_format_id = 0;
    m_num_channels = 0;
    m_samples_per_second = 0;
    m_bytes_per_second = 0;
    m_bits_per_sample = 0;
    m_contents.clear();
    m_wave_data.clear();
}

inline size_t MWavFile::size() const
{
    return m_contents.size();
}

inline size_t MWavFile::info_size() const
{
    return 44;
}

inline size_t MWavFile::data_size() const
{
    return m_wave_data.size();
}

inline MWavFile::MWavFile()
{
    clear();
}

inline MWavFile::MWavFile(const char *filename)
{
    load(filename);
}

inline MWavFile::~MWavFile()
{
}

inline bool MWavFile::is_loaded() const
{
    return m_loaded;
}

inline bool MWavFile::is_stereo() const
{
    return m_num_channels == 2;
}

inline bool MWavFile::load(const char *filename)
{
    bool ret = false;
    clear();
    if (FILE *fp = fopen(filename, "rb"))
    {
        ret = read(fp);
        fclose(fp);
    }
    m_loaded = ret;
    return ret;
}

inline bool MWavFile::save(const char *filename) const
{
    bool ret = false;
    if (FILE *fp = fopen(filename, "wb"))
    {
        ret = write(fp);
        fclose(fp);
    }
    if (!ret)
    {
        printf("ERROR: Cannot write.\n");
    }
    return ret;
}

inline bool MWavFile::read(FILE *fp)
{
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        printf("ERROR: Cannot seek.\n");
        return false;
    }
    long real_file_size = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        printf("ERROR: Cannot seek.\n");
        return false;
    }

    if (real_file_size < info_size())
        return false;

    m_contents.resize(real_file_size);
    if (!fread(&m_contents[0], real_file_size, 1, fp))
    {
        printf("ERROR: Cannot read.\n");
        return false;
    }

    if (memcmp(&m_contents[0], "RIFF", 4) != 0)
        return false;
    if (memcmp(&m_contents[8], "WAVE", 4) != 0)
        return false;
    if (memcmp(&m_contents[12], "fmt ", 4) != 0)
        return false;
    if (memcmp(&m_contents[36], "data", 4) != 0)
        return false;

    m_file_size = get_u32(&m_contents[4]) + 8;
    m_fmt_size = get_u32(&m_contents[16]);
    m_format_id = get_u16(&m_contents[20]);
    m_num_channels = get_u16(&m_contents[22]);
    m_samples_per_second = get_u32(&m_contents[24]);
    m_bytes_per_second = get_u32(&m_contents[28]);
    m_bits_per_sample = get_u16(&m_contents[34]);
    uint32_t data_size = get_u32(&m_contents[40]);

    if (m_file_size > real_file_size ||
        m_fmt_size != 16 ||
        m_format_id != 1 ||
        m_file_size < info_size() + data_size)
    {
        m_contents.clear();
        printf("ERROR: Not supported format.\n");
        return false;   // not linear PCM
    }

    m_wave_data.resize(data_size);
    memcpy(&m_wave_data[0], &m_contents[info_size()], data_size);

    return true;
}

inline bool MWavFile::write(FILE *fp) const
{
    if (m_contents.empty())
        return false;

    if (!fwrite(&m_contents[0], m_contents.size(), 1, fp))
        return false;

    return true;
}

inline void MWavFile::build()
{
    m_contents.resize(info_size());
    m_file_size = info_size() + m_wave_data.size();

    memcpy(&m_contents[0], "RIFF", 4);
    memcpy(&m_contents[8], "WAVE", 4);
    memcpy(&m_contents[12], "fmt ", 4);
    memcpy(&m_contents[36], "data", 4);

    set_u32(&m_contents[4], m_file_size - 8);
    set_u32(&m_contents[16], m_fmt_size);
    set_u16(&m_contents[20], m_format_id);
    set_u16(&m_contents[22], m_num_channels);
    set_u32(&m_contents[24], m_samples_per_second);
    set_u32(&m_contents[28], m_bytes_per_second);
    set_u16(&m_contents[34], m_bits_per_sample);
    set_u32(&m_contents[40], m_wave_data.size());

    m_contents.insert(m_contents.end(), m_wave_data.begin(), m_wave_data.end());
}

inline uint16_t MWavFile::get_u16(const void *data) const
{
    const uint8_t *pb = (const uint8_t *)data;
    return pb[0] | (pb[1] << 8);
}

inline uint32_t MWavFile::get_u32(const void *data) const
{
    const uint8_t *pb = (const uint8_t *)data;
    return pb[0] | (pb[1] << 8) | (pb[2] << 16) | (pb[3] << 24);
}

inline void MWavFile::set_u16(void *data, uint16_t value) const
{
    uint8_t *pb = (uint8_t *)data;
    pb[0] = (uint8_t)value;
    pb[1] = (uint8_t)(value >> 8);
}

inline void MWavFile::set_u32(void *data, uint32_t value) const
{
    uint8_t *pb = (uint8_t *)data;
    pb[0] = (uint8_t)value;
    pb[1] = (uint8_t)(value >> 8);
    pb[2] = (uint8_t)(value >> 16);
    pb[3] = (uint8_t)(value >> 24);
}

inline void MWavFile::dump_info() const
{
#define PA_DUMP(x) do { \
    if (sizeof(x) == 1) printf(#x ": %d (0x%02X)\n", (int)(x), (int)(x)); \
    else if (sizeof(x) == 2) printf(#x ": %d (0x%04X)\n", (int)(x), (int)(x)); \
    else if (sizeof(x) == 4) printf(#x ": %d (0x%08X)\n", (int)(x), (int)(x)); \
} while (0)
    PA_DUMP(m_file_size);
    PA_DUMP(m_fmt_size);
    PA_DUMP(m_format_id);
    PA_DUMP(m_num_channels);
    PA_DUMP(m_samples_per_second);
    PA_DUMP(m_bytes_per_second);
    PA_DUMP(m_bits_per_sample);
#undef PA_DUMP
}

#ifdef _WIN32
    inline void MWavFile::play(DWORD dwFlags) const
    {
        if (m_contents.empty())
            return;
        PlaySound((LPCTSTR)&m_contents[0], NULL, dwFlags);
    }
#endif

///////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MWAVFILE_HPP_
