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

#if defined(__linux__)
    snd_pcm_t* handle;
#elif defined(_WIN32)
    HRESULT hr = S_OK;
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    IMMDevice* audiodev = NULL;
#endif

int AudioCore_Config()
{
    
}

int AudioCore_Init(const char* device, unsigned int samplerate)
{
#if defined(__linux__)
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
    snd_pcm_hw_params_set_rate_near(handle, params, &samplerate, 0);
    
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

    // Initialize COM 
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        merror_win32(NULL, "AudioCore Error", "Failed to initialize COM: %Lx", hr);
        return -1;
    }

    // Create the device enumerator
    hr = CoCreateInstance(&CLSID_MMDeviceEnumerator,
    NULL,
    CLSCTX_INPROC_SERVER,
    &IID_IMMDeviceEnumerator,
    (void**)&deviceEnumerator 
    );

    if (FAILED(hr))
    {
        merror_win32(NULL, "AudioCore Error", "Failed to create device enumerator: %Lx", hr);
        CoUninitialize();
        return -2;
    }

    // Get the default audio endpoint
    hr = deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(
        deviceEnumerator,
        eRender, 
        eConsole,
        &audiodev
    );

    if (FAILED(hr))
    {
        merror_win32(NULL, "AudioCore Error", "Failed to get default audio endpoint: %Lx", hr);
        deviceEnumerator->lpVtbl->Release(deviceEnumerator);
        CoUninitialize();
        return -3;
    }
#endif
    return 0;
}

int AudioCore_Cleanup(void)
{
#if defined(__linux__)
    if (handle)
    {
        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        handle = NULL;
    }
#elif defined(_WIN32)
    audiodev->lpVtbl->Release(audiodev);
    deviceEnumerator->lpVtbl->Release(deviceEnumerator);
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

InstrumentInfo* CreateInstrument(const char* name, uint32_t id)
{
    
}