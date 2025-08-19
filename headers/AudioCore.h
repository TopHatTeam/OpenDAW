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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#if defined(__linux__)
    #include <alsa/asoundlib.h>
    #include <unistd.h>

#elif defined(_WIN32)
    #include <windows.h>
    #include <initguid.h>
    #include <mmdeviceapi.h>
    #include <audioclient.h>
    #include <functiondiscoverykeys_devpkey.h>
        #ifndef sleep
        #define sleep(x) Sleep(1000 * (x))
        #endif 
/* TOOK THE SDKS for MacOS Xcode*/
#elif defined(__APPLE__)
    #include <CoreFoundation/CoreFoundation.h>
    #include <CoreAudio/CoreAudio.h>
    #include <CoreAudio/AudioHardware.h>
    #include <AudioToolbox/AudioToolbox.h>
    #include <AudioUnit/AudioUnit.h>
#endif



// Check if compiler supports IEC 559 (IEEE 754) floating-point arithmetic
#if defined(__clang__)
    typedef double freq_t;      // Frequency in Hz
    typedef double volume_t;    // Volume in range [0.0 to 1.0]
    typedef double pan_t;       // Pan position in range [-10.0 to 10.0]
    typedef double length_t;    // Length of the note in seconds
    typedef double pitch_t;     // Pitch in semitones
    #define FREQ(x) x
    #pragma message("Using double precision: for musical notes frequencies")

#elif defined(__STDC_IEC_559__) && !defined(__STDC_IEC_559_DOUBLE__)
    typedef float freq_t;      // Frequency in Hz
    typedef float volume_t;    // Volume in range [0.0 to 1.0]
    typedef float pan_t;       // Pan position in range [-10.0 to 10.0]
    typedef float length_t;    // Length of the note in seconds
    typedef float pitch_t;     // Pitch in semitones
    #define FREQ(x) x##f
    #pragma message("Using float precision: for musical notes frequencies")

#else 
    typedef float freq_t;      // Frequency in Hz
    typedef float volume_t;    // Volume in range [0.0 to 1.0]
    typedef float pan_t;       // Pan position in range [-10.0 to 10.0]
    typedef float length_t;    // Length of the note in seconds
    typedef float pitch_t;     // Pitch in semitones
    #define FREQ(x) x##f
    #pragma message("Assuming no double support, falling back to float precision")
#endif

// -- Musical notes frequencies --
/* We had to add n to each musical note because it was fucking with fmt*/
#define nC8      FREQ(4186.00)
#define nB7      FREQ(3951.05)
#define nBb7     FREQ(3729.30)
#define nA7      FREQ(3519.99)
#define nAb7     FREQ(3322.43)
#define nG7      FREQ(3135.95)
#define nGb7     FREQ(2959.95)
#define nF7      FREQ(2793.82)
#define nE7      FREQ(2637.01)
#define nEb7     FREQ(2489.01)
#define nD7      FREQ(2349.31)
#define nDb7     FREQ(2217.46)
#define nC7      FREQ(2093.00)
#define nB6      FREQ(1975.53)
#define nBb6     FREQ(1864.65)
#define nA6      FREQ(1760.00)
#define nAb6     FREQ(1661.22)
#define nG6      FREQ(1567.98)
#define nGb6     FREQ(1479.98)
#define nF6      FREQ(1396.91)
#define nE6      FREQ(1318.51)
#define nEb6     FREQ(1244.51)
#define nD6      FREQ(1174.66)
#define nDb6     FREQ(1108.73)
#define nC6      FREQ(1046.50)
#define nB5      FREQ(987.77)
#define nBb5     FREQ(932.33)
#define nA5      FREQ(880.00)
#define nAb5     FREQ(830.61)
#define nG5      FREQ(783.99)
#define nGb5     FREQ(739.99)
#define nF5      FREQ(698.46)
#define nE5      FREQ(659.25)
#define nEb5     FREQ(622.25)
#define nD5      FREQ(587.33)
#define nDb5     FREQ(554.37)
#define nC5      FREQ(523.25)
#define nB4      FREQ(493.88)
#define nBb4     FREQ(466.16)  // A#4 or Bb4 note
#define nA4      FREQ(440.00) 
#define nAb4     FREQ(415.30)  // G#4 or Ab4 note
#define nG4      FREQ(392.00)
#define nGb4     FREQ(369.99)  // F#4 or Gb4 note
#define nF4      FREQ(349.23) 
#define nE4      FREQ(329.63)
#define nEb4     FREQ(311.13)  // D#4 or Eb4 note
#define nD4      FREQ(293.66)
#define nDb4     FREQ(277.18)  // C#4 or Db4 note
#define nC4      FREQ(261.63)
#define nB3      FREQ(246.94)
#define nBb3     FREQ(233.08)
#define nA3      FREQ(220.00)
#define nAb3     FREQ(207.65)
#define nG3      FREQ(196.00)
#define nGb3     FREQ(185.00)
#define nF3      FREQ(174.61)
#define nE3      FREQ(164.81)
#define nEb3     FREQ(155.56)
#define nD3      FREQ(146.83)
#define nDb3     FREQ(138.59)
#define nC3      FREQ(130.81)
#define nB2      FREQ(123.47)
#define nBb2     FREQ(116.54)
#define nA2      FREQ(110.00)
#define nAb2     FREQ(103.83)
#define nG2      FREQ(98.00)
#define nGb2     FREQ(92.50)
#define nF2      FREQ(87.31)
#define nE2      FREQ(82.41)
#define nEb2     FREQ(77.78)
#define nD2      FREQ(73.42)
#define nDb2     FREQ(69.30)
#define nC2      FREQ(65.41)
#define nB1      FREQ(61.74)
#define nBb1     FREQ(58.27)
#define nA1      FREQ(55.00)
#define nAb1     FREQ(51.91)
#define nG1      FREQ(49.00)
#define nGb1     FREQ(46.25)
#define nF1      FREQ(44.00)
#define nE1      FREQ(41.20)
#define nEb1     FREQ(38.89)
#define nD1      FREQ(36.71)
#define nDb1     FREQ(34.65)
#define nC1      FREQ(32.70)
#define nB0      FREQ(30.87)
#define nBb0     FREQ(29.14)
#define nA0      FREQ(27.50)

// -- AudioCore API definitions --

typedef enum
{
    PST_PAUSED,
    PST_PLAYING,
    PST_UNDEFINED
} PlaybackState;

typedef enum 
{
    N_C8,
    N_B7,
    N_Bb7,
    N_A7,
    N_Ab7,
    N_G7,
    N_Gb7,
    N_F7,
    N_E7,
    N_Eb7,
    N_D7,
    N_Db7,
    N_C7,
    N_B6,
    N_Bb6,
    N_A6,
    N_Ab6,
    N_G6,
    N_Gb6,
    N_F6,
    N_E6,
    N_Eb6,
    N_D6,
    N_Db6,
    N_C6,
    N_B5,
    N_Bb5,
    N_A5,
    N_Ab5,
    N_G5,
    N_Gb5,
    N_F5,
    N_E5,
    N_Eb5,
    N_D5,
    N_Db5,
    N_C5,
    N_B4,
    N_Bb4,
    N_A4,
    N_Ab4,
    N_G4,
    N_Gb4,
    N_F4,
    N_E4,
    N_Eb4,
    N_D4,
    N_Db4,
    N_C4,
    N_B3,
    N_Bb3,
    N_A3,
    N_Ab3,
    N_G3,
    N_Gb3,
    N_F3,
    N_E3,
    N_Eb3,
    N_D3,
    N_Db3,
    N_C3,
    N_B2,
    N_Bb2,
    N_A2,
    N_Ab2,
    N_G2,
    N_Gb2,
    N_F2,
    N_E2,
    N_Eb2,
    N_D2,
    N_Db2,
    N_C2,
    N_B1,
    N_Bb1,
    N_A1,
    N_Ab1,
    N_G1,
    N_Gb1,
    N_F1,
    N_E1,
    N_Eb1,
    N_D1,
    N_Db1,
    N_C1,
    N_B0,
    N_Bb0,
    N_A0,
    N_UNDEFINED,
} Note;

const freq_t MusicNote[] =
{
    [N_C8]      = nC8,
    [N_B7]      = nB7,
    [N_Bb7]     = nBb7,
    [N_A7]      = nA7,
    [N_Ab7]     = nAb7,
    [N_G7]      = nG7,
    [N_Gb7]     = nGb7,
    [N_F7]      = nF7, 
    [N_E7]      = nE7,
    [N_Eb7]     = nEb7,
    [N_D7]      = nD7,
    [N_Db7]     = nDb7,
    [N_C7]      = nC7,
    [N_B6]      = nB6,
    [N_Bb6]     = nBb6,
    [N_A6]      = nA6,
    [N_Ab6]     = nAb6,
    [N_G6]      = nG6,
    [N_Gb6]     = nGb6,
    [N_F6]      = nF6,
    [N_E6]      = nE6,
    [N_Eb6]     = nEb6,
    [N_D6]      = nD6,
    [N_Db6]     = nDb6,
    [N_C6]      = nC6,
    [N_B5]      = nB5,
    [N_Bb5]     = nBb5,
    [N_A5]      = nA5,
    [N_Ab5]     = nAb5,
    [N_G5]      = nG5,
    [N_Gb5]     = nGb5,
    [N_F5]      = nF5,
    [N_E5]      = nE5,
    [N_Eb5]     = nEb5,
    [N_D5]      = nD5,
    [N_Db5]     = nDb5,
    [N_C5]      = nC5,
    [N_B4]      = nB4,
    [N_Bb4]     = nBb4,
    [N_A4]      = nA4,
    [N_Ab4]     = nAb4,
    [N_G4]      = nG4,
    [N_Gb4]     = nGb4,
    [N_F4]      = nF4,
    [N_E4]      = nE4,
    [N_Eb4]     = nEb4,
    [N_D4]      = nD4,
    [N_Db4]     = nDb4,
    [N_C4]      = nC4,
    [N_B3]      = nB3,
    [N_Bb3]     = nBb3,
    [N_A3]      = nA3,
    [N_Ab3]     = nAb3,
    [N_G3]      = nG3,
    [N_Gb3]     = nGb3,
    [N_F3]      = nF3,
    [N_E3]      = nE3,
    [N_Eb3]     = nEb3,
    [N_D3]      = nD3,
    [N_Db3]     = nDb3,
    [N_C3]      = nC3,
    [N_B2]      = nB2,
    [N_Bb2]     = nBb2,
    [N_A2]      = nA2,
    [N_Ab2]     = nAb2,
    [N_G2]      = nG2,
    [N_Gb2]     = nGb2,
    [N_F2]      = nF2,
    [N_E2]      = nE2,
    [N_Eb2]     = nEb2,
    [N_D2]      = nD2,
    [N_Db2]     = nDb2,
    [N_C2]      = nC2,
    [N_B1]      = nB1,
    [N_Bb1]     = nBb1,
    [N_A1]      = nA1,
    [N_Ab1]     = nAb1,
    [N_G1]      = nG1,
    [N_Gb1]     = nGb1,
    [N_F1]      = nF1,
    [N_E1]      = nE1,
    [N_Eb1]     = nEb1,
    [N_D1]      = nD1,
    [N_Db1]     = nDb1,
    [N_C1]      = nC1,
    [N_B0]      = nB0,
    [N_Bb0]     = nBb0,
    [N_A0]      = nA0,
} ;

typedef struct PlaybackInfo
{
    uint32_t        samplerate;    // The sample rate of the playback (e.g 44100 Hz, 48000 Hz)
    uint32_t        bitdepth;      // The bit depth of the playback (e.g 8-bit, 16-bit, 32-bit)
    uint64_t        currentpos;    // Current position of the playhead for playback in samples
    uint32_t        channels;      // How many channels for playback (e.g mono, stereo or surround)
    PlaybackState   status;        // What's the current status of playback
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

// -- Instrument API -- 
typedef struct InstrumentInfo
{
    uint32_t    instrumentid;       // The ID of the instrument
    uint32_t    midiport;           // The MIDI port of the instrument
    uint32_t    midipattenid;       // The MIDI pattern ID the instrument is in
    uint32_t    midichannel;        // The MIDI channel the instrument is on
    char*       instrumentname;
    bool        solo;
    bool        mute;
    float       instrumentvolume;
} InstrumentInfo;

typedef struct wave_t
{
    float frequency;    // Frequency of the wave in Hz
    float amplitude;    // Amplitude of the wave
    float phase;        // Phase of the wave in radians
    float samplerate;   // Sample rate of the wave in Hz
} wave_t;


typedef struct 
{
    
} noteinfo_t;

typedef struct audio_clip_t
{
    float start;
    float length;
    bool selected;
} audio_clip_t;


// -- AudioCore API platform specific variables --

#if defined(__linux__)
    extern snd_pcm_t* handle;
#elif defined(_WIN32)
    extern HRESULT hr;
    extern IMMDeviceEnumerator* deviceEnumerator;
    extern IMMDevice* audiodev;
#elif defined(__apple__)

#endif

// -- AudioCore API function declarations --


int AudioCore_Config();

/**
 * @brief initializes the Audio backend for AudioCore
 * @param device the audio device for output
 * @param samplerate the sample rate for the Audio backend to run at
 * @returns 0 if successfully and 1 if unsuccessful
 */
int AudioCore_Init(const char* device, unsigned int samplerate);

/** 
*@brief Cleans up the AudioCore resources.
*@note This function supports both Linux and Windows platforms.
*@returns void
*/
int AudioCore_Cleanup(void);

/** 
*@brief Creates a new mixer channel with the specified name and ID.
*@param name The name of the channel.
*@param id The ID of the channel.
*@returns A pointer to the newly created mixer channel
*@note For more information on MixerChannelInfo, see 'AudioCore.h'
*/
MixerChannelInfo* CreateChannel(const char* name, uint32_t id);

InstrumentInfo* CreateInstrument(const char* name, uint32_t id);
    
#ifdef __cplusplus
}
#endif

#endif