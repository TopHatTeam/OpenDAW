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
        // TODO: come up with the DAW initializing
    }
#elif defined(_WIN32)

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

}