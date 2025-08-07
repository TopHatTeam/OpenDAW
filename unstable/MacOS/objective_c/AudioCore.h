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

/* This is objective-c code not c code! */

#import <Foundation/Foundation.h>

@interface MixerChannelInfo : NSObject 

@property (nonatomic, assign) uint32_t channelid;
@property (nonatomic, assign) uint32_t pluginid;       // primitive type
@property (nonatomic, assign) uint32_t numplugins;
@property (nonatomic, assign) float panpos;
@property (nonatomic, assign) float volume;
@property (nonatomic, assign) BOOL mute;
@property (nonatomic, assign) BOOL solo;
@property (nonatomic, copy) NSString* channelname;

- (instancetype)initWithName:(const char*)name channelID:(uint32_t)channelid;

@end
