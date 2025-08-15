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
#include <math.h>

#if defined(__linux__)
#include <alsa/control.h>
#include <alsa/timer.h>
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
#define C8      FREQ(4186.00)
#define B7      FREQ(3951.05)
#define Bb7     FREQ(3729.30)
#define A7      FREQ(3519.99)
#define Ab7     FREQ(3322.43)
#define G7      FREQ(3135.95)
#define Gb7     FREQ(2959.95)
#define F7      FREQ(2793.82)
#define E7      FREQ(2637.01)
#define Eb7     FREQ(2489.01)
#define D7      FREQ(2349.31)
#define Db7     FREQ(2217.46)
#define C7      FREQ(2093.00)
#define B6      FREQ(1975.53)
#define Bb6     FREQ(1864.65)
#define A6      FREQ(1760.00)
#define Ab6     FREQ(1661.22)
#define G6      FREQ(1567.98)
#define Gb6     FREQ(1479.98)
#define F6      FREQ(1396.91)
#define E6      FREQ(1318.51)
#define Eb6     FREQ(1244.51)
#define D6      FREQ(1174.66)
#define Db6     FREQ(1108.73)
#define C6      FREQ(1046.50)
#define B5      FREQ(987.77)
#define Bb5     FREQ(932.33)
#define A5      FREQ(880.00)
#define Ab5     FREQ(830.61)
#define G5      FREQ(783.99)
#define Gb5     FREQ(739.99)
#define F5      FREQ(698.46)
#define E5      FREQ(659.25)
#define Eb5     FREQ(622.25)
#define D5      FREQ(587.33)
#define Db5     FREQ(554.37)
#define C5      FREQ(523.25)
#define B4      FREQ(493.88)
#define Bb4     FREQ(466.16)  // A#4 or Bb4 note
#define A4      FREQ(440.00) 
#define Ab4     FREQ(415.30)  // G#4 or Ab4 note
#define G4      FREQ(392.00)
#define Gb4     FREQ(369.99)  // F#4 or Gb4 note
#define F4      FREQ(349.23) 
#define E4      FREQ(329.63)
#define Eb4     FREQ(311.13)  // D#4 or Eb4 note
#define D4      FREQ(293.66)
#define Db4     FREQ(277.18)  // C#4 or Db4 note
#define C4      FREQ(261.63)
#define B3      FREQ(246.94)
#define Bb3     FREQ(233.08)
#define A3      FREQ(220.00)
#define Ab3     FREQ(207.65)
#define G3      FREQ(196.00)
#define Gb3     FREQ(185.00)
#define F3      FREQ(174.61)
#define E3      FREQ(164.81)
#define Eb3     FREQ(155.56)
#define D3      FREQ(146.83)
#define Db3     FREQ(138.59)
#define C3      FREQ(130.81)
#define B2      FREQ(123.47)
#define Bb2     FREQ(116.54)
#define A2      FREQ(110.00)
#define Ab2     FREQ(103.83)
#define G2      FREQ(98.00)
#define Gb2     FREQ(92.50)
#define F2      FREQ(87.31)
#define E2      FREQ(82.41)
#define Eb2     FREQ(77.78)
#define D2      FREQ(73.42)
#define Db2     FREQ(69.30)
#define C2      FREQ(65.41)
#define B1      FREQ(61.74)
#define Bb1     FREQ(58.27)
#define A1      FREQ(55.00)
#define Ab1     FREQ(51.91)
#define G1      FREQ(49.00)
#define Gb1     FREQ(46.25)
#define F1      FREQ(44.00)
#define E1      FREQ(41.20)
#define Eb1     FREQ(38.89)
#define D1      FREQ(36.71)
#define Db1     FREQ(34.65)
#define C1      FREQ(32.70)
#define B0      FREQ(30.87)
#define Bb0     FREQ(29.14)
#define A0      FREQ(27.50)

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

// -- MIDI definitions -- 
#define MIDI_NOTE_ON            0x90
#define MIDI_NOTE_OFF           0x80
#define MIDI_AFTERTOUCH         0xA0
#define MIDI_CONTROL_CHANGE     0xB0
#define MIDI_PROGRAM_CHANGE     0xC0
#define MIDI_PITCH_BEND         0xE0


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
    [N_C8]      = C8,
    [N_B7]      = B7,
    [N_Bb7]     = Bb7,
    [N_A7]      = A7,
    [N_Ab7]     = Ab7,
    [N_G7]      = G7,
    [N_Gb7]     = Gb7,
    [N_F7]      = F7, 
    [N_E7]      = E7,
    [N_Eb7]     = Eb7,
    [N_D7]      = D7,
    [N_Db7]     = Db7,
    [N_C7]      = C7,
    [N_B6]      = B6,
    [N_Bb6]     = Bb6,
    [N_A6]      = A6,
    [N_Ab6]     = Ab6,
    [N_G6]      = G6,
    [N_Gb6]     = Gb6,
    [N_F6]      = F6,
    [N_E6]      = E6,
    [N_Eb6]     = Eb6,
    [N_D6]      = D6,
    [N_Db6]     = Db6,
    [N_C6]      = C6,
    [N_B5]      = B5,
    [N_Bb5]     = Bb5,
    [N_A5]      = A5,
    [N_Ab5]     = Ab5,
    [N_G5]      = G5,
    [N_Gb5]     = Gb5,
    [N_F5]      = F5,
    [N_E5]      = E5,
    [N_Eb5]     = Eb5,
    [N_D5]      = D5,
    [N_Db5]     = Db5,
    [N_C5]      = C5,
    [N_B4]      = B4,
    [N_Bb4]     = Bb4,
    [N_A4]      = A4,
    [N_Ab4]     = Ab4,
    [N_G4]      = G4,
    [N_Gb4]     = Gb4,
    [N_F4]      = F4,
    [N_E4]      = E4,
    [N_Eb4]     = Eb4,
    [N_D4]      = D4,
    [N_Db4]     = Db4,
    [N_C4]      = C4,
    [N_B3]      = B3,
    [N_Bb3]     = Bb3,
    [N_A3]      = A3,
    [N_Ab3]     = Ab3,
    [N_G3]      = G3,
    [N_Gb3]     = Gb3,
    [N_F3]      = F3,
    [N_E3]      = E3,
    [N_Eb3]     = Eb3,
    [N_D3]      = D3,
    [N_Db3]     = Db3,
    [N_C3]      = C3,
    [N_B2]      = B2,
    [N_Bb2]     = Bb2,
    [N_A2]      = A2,
    [N_Ab2]     = Ab2,
    [N_G2]      = G2,
    [N_Gb2]     = Gb2,
    [N_F2]      = F2,
    [N_E2]      = E2,
    [N_Eb2]     = Eb2,
    [N_D2]      = D2,
    [N_Db2]     = Db2,
    [N_C2]      = C2,
    [N_B1]      = B1,
    [N_Bb1]     = Bb1,
    [N_A1]      = A1,
    [N_Ab1]     = Ab1,
    [N_G1]      = G1,
    [N_Gb1]     = Gb1,
    [N_F1]      = F1,
    [N_E1]      = E1,
    [N_Eb1]     = Eb1,
    [N_D1]      = D1,
    [N_Db1]     = Db1,
    [N_C1]      = C1,
    [N_B0]      = B0,
    [N_Bb0]     = Bb0,
    [N_A0]      = A0,
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

#ifdef __cplusplus
extern "C" {
#endif

// -- AudioCore API platform specific variables --

#if defined(__linux__)

#elif defined(_WIN32)
    extern HRESULT hr;
    extern IMMDeviceEnumerator* deviceEnumerator;
    extern IMMDevice* audiodev;
#endif

// -- AudioCore API function declarations --

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
