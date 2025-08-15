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

/* God i must fucking hate myself
    well, let's cue the rocky theme
*/

#import "AudioCore.h"       // <-- Why change it to #import?


/* Who is the asshole that designed this language?*/
@implementation MixerChannelInfo

- (instancetype)initWithName:(const char*)name channelID:(uint32_t)channelid
{
    self = [super init];
    if (self) 
    {
        _channelid      = channelid;
        _channelname    = [NSString stringWithUTF8String:name];
        _numplugins     = 0;
        _pluginid       = NULL;   // <-- why not NONE? i guess null works
        _panpos         = 0.0;
        _volume         = 0.0;
        _mute           = NO;   
        _solo           = NO;     // <-- NO? well i guess it's straightforward
    }
    return self;
}
@end

@implementation AudioCore 
{
    AVAudioEngine       *audioengine; 
    AVAudioPlayerNode   *playernode;
}

- (instancetype)initWithDevice:(const char*)device samplerate:(unsigned int)samplerate
{
    self = [super init];
    if (self)
    {
        // Initialze the audio core with the device and samplerate
        // TODO: Implement the actual audio core initialized logic 
        NSLog(@"AudioCore initialized with device: %s at sampler rate: %u\n", device, samplerate);
        // For now, just the log message
    }

    return self;
}

@end 



