// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/15/25.
//  audiocore.m
//
//  Description:
//      Audio Core engine for the sound
//
// ---------------------------------------------------------


#import "audiocore.h"

@implementation AudioCore
{
    AVAudioEngine       *audioengine;
    AVAudioOutputNode   *audout_n;      /* The '_n' stands for node makes thing simplier*/
    AVAudioMixerNode    *audmixer_n;
    AVAudioPlayerNode   *audioplayer_n;
}

+ (AVAudioApplication *) sharedInstance API_AVAILABLE(macos(14.0))
{
    return AVAudioApplication.sharedInstance;
}

/* Configure AVAudioSession*/
- (void)configureAudioSession
{
    
}

- (instancetype)initWithDevice:(const char*)device samplerate:(unsigned int)samplerate
{
    self = [super init];
    
    if (self)
    {
        
        /* This is gonna be the default for the AudioCore for now*/
        device      = "Default Device";
        samplerate  = 44100;
        NSLog(@"Implementing AudioCore");
        /* Objective-c is one those languages that want to be unique by having @*/
        
        audioengine = [[AVAudioEngine alloc] init];
        
        audout_n    = audioengine.outputNode;
        audmixer_n  = audioengine.mainMixerNode;
        
        /* Connect the nodes*/
        
        /*Start the AudioCore*/
        NSError *err = nil;
        
        if (![audioengine startAndReturnError:&err])
        {
            /*This is meant to let us know our code has fucked up*/
            NSLog(@"Failed to start AudioCore engine: %@", err);
        }
        else
        {
            /*Now pat ourselves on the back because our code didn't fuck up*/
            NSLog(@"AudioCore has successfully started");
        }
    }
    
    return self;
}

@end

