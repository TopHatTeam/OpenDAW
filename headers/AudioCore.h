// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Audio Core engine for the sound
//
// ---------------------------------------------------------

#ifndef AUDIOCORE_H
#define AUDIOCORE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__linux__)
#include <alsa/control.h>
#include <alsa/timer.h>
#include <alsa/asoundlib.h>
#include <unistd.h>

#elif defined(_WIN32)
#include <windows.h>
#include <io.h>
    #ifndef sleep
    #define sleep(x) Sleep(1000 * (x))
    #endif 
#endif


// -- Include CD-DA global definitions -- 
#define CD_SAMPLERATE 44100 
#define CD_CHANNELS 2
#define CD_BITDEPTH 16
#define CD_SAMPLES_PER_SECTOR 588
#define CD_SECTOR_SIZE (CD_SAMPLES_PER_SECTOR * (CD_BITDEPTH / 8) * CD_CHANNELS)

/*
This compiles with the Red Book standard for CD audio.
The Red Book standard defines the audio format for CDs, which are the following:
- Sample Rate: 44.1 kHz
- Channels: Stereo (2 Channels)
- Bit Depth: 16 bits per sample
*/

typedef int16_t cd_sample_t; // signed 16-bit PCM

typedef struct cd_pcm_frame_t
{
    cd_sample_t left;   // Left channel sample
    cd_sample_t right;  // Right channel sample
} cd_pcm_frame_t;

// -- AudioCore API definitions --

typedef enum
{
    PST_PAUSED,
    PST_PLAYING,
    PST_UNDEFINED
} PlaybackState;

typedef struct PlaybackInfo
{
    uint32_t        samplerate;    // The sample rate of the playback (e.g 44100 Hz, 48000 Hz)
    uint32_t        bitdepth;      // The bit depth of the playback (e.g 8-bit, 16-bit, 32-bit)
    uint64_t        currentpos;    // Current position of the playhead for playback in samples
    uint32_t        channels;      // How many channels for playback (e.g mono, stereo or surround)
    PlaybackState   status;        // What's the current status of 
} PlaybackInfo;

typedef struct MixerChannelInfo
{
    uint32_t    numplugins;       // Number of plugins
    uint32_t*   pluginid;         // The ID of the plugin 
    uint32_t    channelid;        // The ID of the channel
    float       panpos;           // The position of the channels pan (e.g right or left speaker)
    float       volume;           // The volume of the channel
    bool        mute;             // Is the channel muted?
    bool        solo;             // Is the channel solo'd?
    char*       channelname;      // The channel's name
} MixerChannelInfo;

#ifdef __cplusplus
extern "C" {
#endif

int AudioCore_Init(const char* device, unsigned int samplerate);

MixerChannelInfo* CreateChannel(const char* name, uint32_t id);
    
#ifdef __cplusplus
}
#endif

#endif
