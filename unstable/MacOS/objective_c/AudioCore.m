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
        _channelid = channelid;
        _channelname = [NSString stringWithUTF8String:name];
        _numplugins = 0;
        _pluginid = NULL;   // <-- why not NONE? i guess null works
        _panpos = 0.0f;
        _volume = 0.0f;
        _mute = NO;
        _solo = NO;     // <-- NO? well i guess it's straight
    }
    return self;
}
@end

