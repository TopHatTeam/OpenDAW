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
#import <AVFAudio/AVFAudio.h>       // Because apple is such a shitty company for people like me


/*
    Apple has to make everything an API, no simple I/O interface, just like this 
    #define AudioPort 0x1F 
    nope, you must 'OWN' our overpirced Computers that comes with 256 GBs as standard
    when my fucking computer comes with 1 TB as standard, 
*/
#define FREQ(x) (x)
typedef double freq_t;      // Frequency in Hz
typedef double volume_t;    // Volume in range [0.0 to 1.0]
typedef double pan_t;       // Pan position in range [-10.0 to 10.0]
typedef double length_t;    // Length of the note in seconds
typedef double pitch_t;     // Pitch in semitones


// -- Music notes frequencies --
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


@interface MixerChannelInfo : NSObject 

@property (nonatomic, assign) uint32_t channelid;
@property (nonatomic, assign) uint32_t pluginid;       // primitive type
@property (nonatomic, assign) uint32_t numplugins;
@property (nonatomic, assign) pan_t panpos;
@property (nonatomic, assign) volume_t volume;
@property (nonatomic, assign) BOOL mute;
@property (nonatomic, assign) BOOL solo;
@property (nonatomic, copy) NSString* channelname;

- (instancetype)initWithName:(const char*)name channelID:(uint32_t)channelid;

@end

@interface AudioCore : NSObject

- (instancetype)initWithDevice:(const char*)device samplerate:(unsigned int)samplerate;

- (int)cleanup;

@end
