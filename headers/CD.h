// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      CD functionality
//
// ---------------------------------------------------------

#ifndef CD_H
#define CD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

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

/*These are based on the rust functions*/
int read_cd_sector(const char* device_path, uint32_t sector, uint8_t* buffer);

int burn_cd(const char* device_path, const uint8_t* buffer, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif 