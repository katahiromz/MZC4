// MWavFile --- PCM sound reader/writer
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>.
// This file is public domain software.
///////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWAVFILE_HPP_
#define MZC4_MWAVFILE_HPP_      3   // Version 3

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
#include <cassert>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

class MWavFile
{
public:
    MWavFile();
    MWavFile(const char *filename);
    virtual ~MWavFile();

    uint32_t    m_file_size;            // the size of contents
    uint32_t    m_fmt_size;             // 16 for PCM
    uint16_t    m_audio_format;         // 1 for PCM
    uint16_t    m_num_channels;         // the number of channels
    uint32_t    m_samples_per_second;   // the sampling rate
    uint32_t    m_bytes_per_second;     // bytes per second
    uint16_t    m_block_size;           // m_num_channels * m_bits_per_sample / 8
    uint16_t    m_bits_per_sample;      // bits per sample

    bool load(const char *filename);
    bool is_loaded() const;
    bool is_stereo() const;
    bool save(const char *filename) const;
    void clear();

    typedef std::vector<uint8_t> data_type;
    data_type   m_contents;

    bool empty() const;
    size_t size() const;
    size_t info_size() const;
    size_t data_size() const;
          uint8_t *ptr(size_t index = 0);
    const uint8_t *ptr(size_t index = 0) const;

    bool get_info(void *info, size_t siz) const;
    bool get_data(void *data, size_t siz) const;

    void drop_data();
    void add_data(const void *data, size_t siz);

    void dump_info() const;
    void dump_data() const;

#ifdef _WIN32
    void play(DWORD dwFlags = SND_MEMORY | SND_SYNC | SND_NODEFAULT) const;
#endif

    int16_t get_i16(const void *data) const;
    int32_t get_i32(const void *data) const;
    uint16_t get_u16(const void *data) const;
    uint32_t get_u32(const void *data) const;

    void set_i16(void *data, int16_t value) const;
    void set_i32(void *data, int32_t value) const;
    void set_u16(void *data, uint16_t value) const;
    void set_u32(void *data, uint32_t value) const;

protected:
    bool m_loaded;
    bool read(FILE *fp);
    bool write(FILE *fp) const;
};

///////////////////////////////////////////////////////////////////////////////

inline void MWavFile::clear()
{
    m_loaded = false;
    m_file_size = 0;
    m_fmt_size = 0;
    m_audio_format = 0;
    m_num_channels = 0;
    m_samples_per_second = 0;
    m_bytes_per_second = 0;
    m_block_size = 0;
    m_bits_per_sample = 0;
    m_contents.clear();
}

inline bool MWavFile::empty() const
{
    return size() == 0;
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
    assert(size() >= info_size());
    return size() - info_size();
}

inline uint8_t *MWavFile::ptr(size_t index)
{
    if (index > size())
        return NULL;
    uint8_t *ret = &m_contents[0];
    return &ret[index];
}

inline const uint8_t *MWavFile::ptr(size_t index) const
{
    if (index >= size())
        return NULL;
    const uint8_t *ret = &m_contents[0];
    return &ret[index];
}

inline bool MWavFile::get_info(void *info, size_t siz) const
{
    if (siz < info_size())
        return false;

    memcpy(info, ptr(), info_size());
    return true;
}

inline bool MWavFile::get_data(void *data, size_t siz) const
{
    if (siz < data_size())
        return false;

    memcpy(data, ptr(info_size()), data_size());
    return true;
}

inline void MWavFile::drop_data()
{
    m_contents.resize(info_size());
}

inline void MWavFile::add_data(const void *data, size_t siz)
{
    if (siz == 0)
        return;

    size_t old_size = size();
    m_contents.resize(old_size + siz);
    memcpy(ptr(old_size), data, siz);
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
    if (!ret)
    {
        printf("ERROR: Cannot read.\n");
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
        return false;

    long real_file_size = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0)
        return false;

    if (real_file_size < info_size())
        return false;

    m_contents.resize(real_file_size);
    if (!fread(ptr(), real_file_size, 1, fp))
        return false;

    if (memcmp(ptr(), "RIFF", 4) != 0)
        return false;

    m_file_size = get_u32(ptr(4)) + 8;
    if (memcmp(ptr(8), "WAVEfmt ", 8) != 0)
        return false;

    m_fmt_size = get_u32(ptr(16));
    m_audio_format = get_u16(ptr(20));
    m_num_channels = get_u16(ptr(22));
    m_samples_per_second = get_u32(ptr(24));
    m_bytes_per_second = get_u32(ptr(28));
    m_block_size = get_u16(ptr(32));
    m_bits_per_sample = get_u16(ptr(34));
    if (memcmp(ptr(36), "data", 4) != 0)
        return false;

    uint32_t data_size = get_u32(ptr(40));

    if (m_file_size > real_file_size ||
        m_fmt_size != 16 ||
        m_audio_format != 1 ||
        m_file_size < info_size() + data_size)
    {
        m_contents.clear();
        return false;
    }

    return true;
}

inline bool MWavFile::write(FILE *fp) const
{
    if (empty())
        return false;

    if (!fwrite(ptr(), m_contents.size(), 1, fp))
        return false;

    return true;
}

inline int16_t MWavFile::get_i16(const void *data) const
{
    return (int16_t)get_u16(data);
}

inline uint16_t MWavFile::get_u16(const void *data) const
{
    const uint8_t *pb = (const uint8_t *)data;
    return pb[0] | (pb[1] << 8);
}

inline int32_t MWavFile::get_i32(const void *data) const
{
    return (int32_t)get_u32(data);
}

inline uint32_t MWavFile::get_u32(const void *data) const
{
    const uint8_t *pb = (const uint8_t *)data;
    return pb[0] | (pb[1] << 8) | (pb[2] << 16) | (pb[3] << 24);
}

inline void MWavFile::set_i16(void *data, int16_t value) const
{
    set_u16(data, (uint16_t)value);
}

inline void MWavFile::set_u16(void *data, uint16_t value) const
{
    uint8_t *pb = (uint8_t *)data;
    pb[0] = (uint8_t)value;
    pb[1] = (uint8_t)(value >> 8);
}

inline void MWavFile::set_i32(void *data, int32_t value) const
{
    set_u16(data, (uint32_t)value);
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
    PA_DUMP(m_audio_format);
    PA_DUMP(m_num_channels);
    PA_DUMP(m_samples_per_second);
    PA_DUMP(m_bytes_per_second);
    PA_DUMP(m_block_size);
    PA_DUMP(m_bits_per_sample);
#undef PA_DUMP
}

inline void MWavFile::dump_data() const
{
    size_t siz = data_size();
    if (empty() || siz == 0)
        return;

    const uint8_t *pb = ptr(info_size());
    for (size_t i = 0; i < siz; ++i)
    {
        printf("0x%02X, ", (int)pb[i]);
        if (i % 8 == 7)
            puts("");
    }
}

#ifdef _WIN32
    inline void MWavFile::play(DWORD dwFlags) const
    {
        if (empty())
            return;

        PlaySound((LPCTSTR)ptr(), NULL, dwFlags);
    }
#endif

///////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MWAVFILE_HPP_
