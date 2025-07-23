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

#include "headers/AudioCore.h"
#include "headers/AudioError.h"
#include "headers/Common.h"

int AudioCore_Init(const char* device, unsigned int samplerate)
{
#if defined(__linux__)
    snd_pcm_t* handle;
    int err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0)
    {   
        fprintf(stderr, "Failed to open audio device: %s\n", snd_strerror(err));
        return -1;
    }

    snd_pcm_hw_params_t* params;
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 2); // stereo setup
    snd_pcm_hw_params_set_rate_near(handle, params, &sampelrate, 0);
    
    err = snd_pcm_hw_params(handle, params);
    if (err < 0)
    {
        fprintf(stderr, "Failed to set HW params: %s\n", snd_strerror(err));
        snd_pcm_close(handle);
        return -2;
    }

    // TODO: Store 'handle' somewhere for later use
#elif defined(_WIN32)
    // TODO: Create or make a AudioCore_Init functionality for cross-platform support for windows
#endif
    return 0;
}

MixerChannelInfo* CreateChannel(const char* name, uint32_t id)
{
    MixerChannelInfo* channel = malloc(sizeof(MixerChannelInfo));
    channel->channelid = id;
    channel->channelname = cstrdup(name);
    channel->mute = false;
    channel->panpos = 0.0f;
    channel->pluginid = NULL;
    channel->solo = false;
    channel->volume = 0.0f; // Normalized db
    channel->numplugins = 0;
    return channel;		// <-- added return function to avoid undefined behavior
}
