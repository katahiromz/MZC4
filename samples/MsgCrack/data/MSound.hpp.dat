// MSound.hpp -- MZC4 sound                                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSOUND_HPP_
#define MZC4_MSOUND_HPP_        3       /* Version 3 */

class MSound;

////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msacm32.lib")

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif
#ifndef _INC_MMSYSTEM
    #include <mmsystem.h>
#endif
#ifndef _INC_MMREG
    #include <mmreg.h>
#endif
#ifndef _INC_MSACM
    #include <msacm.h>
#endif

////////////////////////////////////////////////////////////////////////////

#include "MByteStream.hpp"
#include "MFile.hpp"

class MSound
{
public:
    MSound();
    MSound(LPCTSTR pszName, BOOL bFile = FALSE, BOOL bMp3 = FALSE);
    virtual ~MSound();

    BOOL Load(LPCTSTR pszName, BOOL bFile = FALSE, BOOL bMP3 = FALSE);
    BOOL SaveToWaveFile(LPCTSTR pszFile);
    void Unload();

    BOOL LoadWaveFromFile(LPCTSTR pszFile);
    BOOL LoadWaveFromResource(LPCTSTR pszResource, HINSTANCE hInstance = NULL);
    BOOL LoadWaveFromResource(UINT nResourceID, HINSTANCE hInstance = NULL);
    BOOL LoadWaveFromMemory(LPVOID pv, DWORD cb);

    BOOL LoadMp3FromFile(LPCTSTR pszFile);
    BOOL LoadMp3FromResource(LPCTSTR pszResource, HINSTANCE hInstance = NULL);
    BOOL LoadMp3FromResource(UINT nResourceID, HINSTANCE hInstance = NULL);
    BOOL LoadMp3FromMemory(LPVOID pv, DWORD cb);

    BOOL Play(BOOL bRepeat = FALSE);
    BOOL PlayAndWait();
    void Stop();

    LPVOID GetPtr();

    static void SetSoundVolume(WORD left, WORD right);
    static void StopAll(void);

protected:
    MByteStream         m_binWave;
    LPVOID              m_pvWave;
    DWORD               m_cbWave;
    BOOL                m_bAlloc;
};

////////////////////////////////////////////////////////////////////////////

inline MSound::MSound() : m_pvWave(NULL), m_cbWave(0), m_bAlloc(FALSE)
{
}

inline void MSound::Unload()
{
    m_binWave.clear();
    m_pvWave = NULL;
    m_cbWave = 0;
    m_bAlloc = FALSE;
}

inline /*static*/ void SetSoundVolume(WORD left, WORD right)
{
    ::waveOutSetVolume(reinterpret_cast<HWAVEOUT>(WAVE_MAPPER), MAKELONG(left, right));
}

inline /*static*/ void MSound::StopAll(void)
{
    ::PlaySound(NULL, NULL, SND_PURGE);
    ::PlaySound(NULL, ::GetModuleHandle(NULL), SND_PURGE);
}

inline INT GetMp3FrameHeaderDx(MPEGLAYER3WAVEFORMAT *pwf, LPBYTE& pb, DWORD& cb)
{
    BYTE head[4], byte;
    INT ver, layer, bitrate, samp, padding, empha, cbFrame;
    static const INT anMp3Freq_[3] = {44100, 48000, 32000};
    static const SHORT anMp3BitRate_[2][3][15] =
    {
        {
            {0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448}, 
            {0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384}, 
            {0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320}
        }, 
        {
            {0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256}, 
            {0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160}, 
            {0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160}
        }
    };
    static const INT anMp3SmpPerFrame_[3][3] =
    {
        {384, 1152, 1152}, {384, 1152, 576}, {384, 1152, 576}
    };

retry:
    if (cb < 2)
        return 0;
    CopyMemory(head, &pb[0], 2);
    pb += 2; cb -= 2;

    while (!(head[0] == 0xFF && (head[1] & 0xE0) == 0xE0))
    {
        if (cb < 1)
            return 0;
        byte = pb[0];
        pb++; cb--;
        head[0] = head[1];
        head[1] = byte;
    }

    if (cb < 2)
        return 0;
    CopyMemory(&head[2], &pb[0], 2);
    pb += 2; cb -= 2;

    ver = (head[1] >> 3) & 3;
    layer = (head[1] >> 1) & 3;
    bitrate = (head[2] >> 4) & 0xf;
    samp = (head[2] >> 2) & 3;
    empha = head[3] & 3;

    if (ver == 1 || layer == 0 || bitrate == 15 || samp == 3 || empha == 2)
    {
        pb -= 3; cb += 3;
        goto retry;
    }

    if (ver == 0) ver = 2;
    else if (ver == 2) ver = 1;
    else ver = 0;

    layer = 3 - layer;
    bitrate = anMp3BitRate_[(ver == 0) ? 0 : 1][layer][bitrate];
    samp = anMp3Freq_[samp] >> ver;
    padding = (head[2] >> 1) & 1;
    cbFrame = anMp3SmpPerFrame_[ver][layer] / 8 *
        bitrate * 1000 / samp + padding;

    if (pwf != NULL)
    {
        pwf->wfx.wFormatTag      = WAVE_FORMAT_MPEGLAYER3;
        pwf->wfx.nChannels       = WORD((((head[3] >> 6) & 3) == 3) ? 1 : 2);
        pwf->wfx.nSamplesPerSec  = (DWORD)samp;
        pwf->wfx.nAvgBytesPerSec = DWORD(bitrate * 1000 / 8);
        pwf->wfx.nBlockAlign     = 1;
        pwf->wfx.wBitsPerSample  = 0;
        pwf->wfx.cbSize          = MPEGLAYER3_WFX_EXTRA_BYTES;

        pwf->wID                 = MPEGLAYER3_ID_MPEG;
        pwf->nBlockSize          = (WORD)cbFrame; 
        pwf->nFramesPerBlock     = 1;
        pwf->nCodecDelay         = 1393;
        if (padding)
            pwf->fdwFlags = MPEGLAYER3_FLAG_PADDING_ON;
        else
            pwf->fdwFlags = MPEGLAYER3_FLAG_PADDING_OFF;
    }

    pb -= 4; cb += 4;

    return cbFrame;
}

inline BOOL ConvertMp3ToWaveDx(MByteStream& bin, LPBYTE& pb, DWORD& cb)
{
    MPEGLAYER3WAVEFORMAT wfmp3;
    WAVEFORMATEX wfwav;
    HACMSTREAM has;
    ACMSTREAMHEADER ash;
    DWORD cbTemp, cbWavBuf, cbData, /*cFrames,*/ cbFrame;
    const DWORD cbMp3Buf = 131072;

    bin.clear();
    GetMp3FrameHeaderDx(&wfmp3, pb, cb);

    ZeroMemory(&wfwav, sizeof(wfwav));
    wfwav.wFormatTag = WAVE_FORMAT_PCM;

    if (::acmFormatSuggest(NULL, (WAVEFORMATEX *)&wfmp3, &wfwav, 
            sizeof(WAVEFORMATEX), ACM_FORMATSUGGESTF_WFORMATTAG))
    {
        assert(FALSE);
        return FALSE;
    }

    if (::acmStreamOpen(&has, NULL, (WAVEFORMATEX *)&wfmp3, &wfwav, 
            NULL, 0, 0, ACM_STREAMOPENF_NONREALTIME))
    {
        assert(FALSE);
        return FALSE;
    }

    ::acmStreamSize(has,
        DWORD(wfmp3.nBlockSize + 1), &cbWavBuf, ACM_STREAMSIZEF_SOURCE);

    MByteStream     mp3_buf(cbMp3Buf);
    MByteStream     wav_buf(cbWavBuf);

    ZeroMemory(&ash, sizeof(ash));
    ash.cbStruct        = sizeof(ash);
    ash.pbSrc           = &mp3_buf[0];
    ash.cbSrcLength     = DWORD(wfmp3.nBlockSize + 1);
    ash.pbDst           = &wav_buf[0];
    ash.cbDstLength     = cbWavBuf;

    if (::acmStreamPrepareHeader(has, &ash, 0))
    {
        assert(FALSE);
        ::acmStreamClose(has, 0);
        return FALSE;
    }

    bin.WriteData("RIFF????WAVEfmt ", 16);
    cbTemp = sizeof(WAVEFORMATEX);
    bin.WriteData(&cbTemp, 4);
    bin.WriteData(&wfwav, (INT)cbTemp);
    bin.WriteData("data????", 8);

    for(cbData = /*cFrames =*/ 0; ; /*cFrames++*/)
    {
        cbFrame = static_cast<DWORD>(GetMp3FrameHeaderDx(NULL, pb, cb));
        if (cbFrame == 0)
        {
            break;
        }

        if (cb < cbFrame)
        {
            assert(FALSE);
            break;
        }

        CopyMemory(&mp3_buf[0], pb, cbFrame);
        pb += cbFrame; cb -= cbFrame;

        ash.cbSrcLength = cbFrame;
        if (::acmStreamConvert(has, &ash, 0))
        {
            assert(FALSE);
            break;
        }

        if (ash.cbDstLengthUsed)
        {
            bin.WriteData(&wav_buf[0], (INT)ash.cbDstLengthUsed);
            cbData += ash.cbDstLengthUsed;
        }
    }
    //MzcTrace(TEXT("cFrames: %d\r\n"), cFrames);

    cbTemp = 20 + sizeof(WAVEFORMATEX) + 4 + cbData;
    CopyMemory(&bin[4], &cbTemp, 4);
    CopyMemory(&bin[16 + 4 + sizeof(WAVEFORMATEX) + 4], &cbData, 4);

    ::acmStreamUnprepareHeader(has, &ash, 0);
    ::acmStreamClose(has, 0);

    return TRUE;
}

inline
MSound::MSound(LPCTSTR pszName, BOOL bFile/* = FALSE*/, BOOL bMp3/* = FALSE*/)
    : m_pvWave(NULL), m_cbWave(0), m_bAlloc(FALSE)
{
    Load(pszName, bFile, bMp3);
}

inline /*virtual*/ MSound::~MSound()
{
}

inline BOOL
MSound::Load(LPCTSTR pszName, BOOL bFile/* = FALSE*/, BOOL bMP3/* = FALSE*/)
{
    if (bMP3)
    {
        if (bFile)
            return LoadMp3FromFile(pszName);
        else
            return LoadMp3FromResource(pszName);
    }
    else
    {
        if (bFile)
            return LoadWaveFromFile(pszName);
        else
            return LoadWaveFromResource(pszName);
    }
}

inline BOOL MSound::LoadWaveFromFile(LPCTSTR pszFile)
{
    using namespace std;
    size_t cb;
    LPBYTE pb = MFile_GetContents(pszFile, &cb);
    assert(pb);
    assert(cb);
    if (cb > 12 &&
        pb[0] == 'R' && pb[1] == 'I' && pb[2] == 'F' && pb[3] == 'F' &&
        pb[8] == 'W' && pb[9] == 'A' && pb[10] == 'V' && pb[11] == 'E')
    {
        m_bAlloc = TRUE;
        m_pvWave = NULL;
        m_cbWave = 0;
        m_binWave.assign(pb, pb + cb);
        free(pb);
        return TRUE;
    }
    assert(FALSE);
    free(pb);
    return FALSE;
}

inline BOOL
MSound::LoadWaveFromResource(LPCTSTR pszResource, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    HRSRC hRsrc = ::FindResource(hInstance, pszResource, TEXT("WAVE"));
    if (hRsrc != NULL)
    {
        DWORD cb = ::SizeofResource(hInstance, hRsrc);
        HGLOBAL hGlobal = ::LoadResource(hInstance, hRsrc);
        if (hGlobal != NULL)
        {
            LPVOID pv = ::LockResource(hGlobal);
            if (pv != NULL)
            {
                m_pvWave = pv;
                m_cbWave = cb;
                m_bAlloc = FALSE;
                m_binWave.clear();
                return TRUE;
            }
        }
    }
    assert(FALSE);
    return FALSE;
}

inline BOOL
MSound::LoadWaveFromResource(UINT nResourceID, HINSTANCE hInstance/* = NULL*/)
{
    return LoadWaveFromResource(MAKEINTRESOURCE(nResourceID), hInstance);
}

inline BOOL MSound::LoadMp3FromFile(LPCTSTR pszFile)
{
    using namespace std;
    size_t cb;
    BOOL bOK = FALSE;
    LPBYTE pb = MFile_GetContents(pszFile, &cb);
    if (pb)
    {
        bOK = LoadMp3FromMemory(pb, cb);
        free(pb);
    }
    assert(bOK);
    return bOK;
}

inline BOOL
MSound::LoadMp3FromResource(LPCTSTR pszResource, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    HRSRC hRsrc = ::FindResource(hInstance, pszResource, TEXT("MP3"));
    if (hRsrc != NULL)
    {
        DWORD cb = ::SizeofResource(hInstance, hRsrc);
        HGLOBAL hGlobal = ::LoadResource(hInstance, hRsrc);
        if (hGlobal != NULL)
        {
            LPVOID pv = ::LockResource(hGlobal);
            if (pv != NULL)
                return LoadMp3FromMemory(pv, cb);
        }
    }
    assert(FALSE);
    return FALSE;
}

inline BOOL
MSound::LoadMp3FromResource(UINT nResourceID, HINSTANCE hInstance/* = NULL*/)
{
    return LoadMp3FromResource(MAKEINTRESOURCE(nResourceID), hInstance);
}

inline BOOL MSound::LoadMp3FromMemory(LPVOID pv, DWORD cb)
{
    LPBYTE pb = (LPBYTE)pv;
    BOOL b = ConvertMp3ToWaveDx(m_binWave, pb, cb);
    assert(b);
    if (b)
        m_bAlloc = TRUE;
    return b;
}

inline BOOL MSound::Play(BOOL bRepeat/* = FALSE*/)
{
    if (m_bAlloc)
    {
        if (bRepeat)
            return ::PlaySound((LPTSTR)&m_binWave[0], NULL, SND_LOOP |
                SND_ASYNC | SND_MEMORY | SND_NODEFAULT | SND_NOSTOP);
        else
            return ::PlaySound((LPTSTR)&m_binWave[0], NULL,
                SND_ASYNC | SND_MEMORY | SND_NODEFAULT | SND_NOSTOP);
    }
    else
    {
        if (bRepeat)
            return ::PlaySound((LPCTSTR)m_pvWave, NULL, SND_LOOP |
                SND_ASYNC | SND_MEMORY | SND_NODEFAULT | SND_NOSTOP);
        else
            return ::PlaySound((LPCTSTR)m_pvWave, NULL,
                SND_ASYNC | SND_MEMORY | SND_NODEFAULT | SND_NOSTOP);
    }
}

inline LPVOID MSound::GetPtr()
{
    if (m_bAlloc)
        return &m_binWave[0];
    else
        return m_pvWave;
}

inline BOOL MSound::PlayAndWait()
{
    return ::PlaySound((LPCTSTR)GetPtr(), NULL,
        SND_SYNC | SND_MEMORY | SND_NODEFAULT | SND_NOSTOP);
}

inline BOOL MSound::SaveToWaveFile(LPCTSTR pszFile)
{
    BOOL b = MFile_PutContents(pszFile, &m_binWave[0], m_binWave.size());
    assert(b);
    return b;
}

inline void MSound::Stop()
{
    ::PlaySound(reinterpret_cast<LPCTSTR>(GetPtr()), NULL, SND_PURGE);
}

#endif  // ndef MZC4_MSOUND_HPP_
