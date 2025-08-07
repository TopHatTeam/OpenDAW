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

// Unstable MacOS AudioCore version

import Foundation

typealias freq      = Double 
typealias volume    = Double
typealias pan       = Double
typealias length    = Double
typealias pitch     = Double
typealias cdsample  = Int16

// Instead of #define FREQ(x) x, we just assign the Double directly
let C8:  freq = 4186.00
let B7:  freq = 3951.05
let Bb7: freq = 3729.30
let A7:  freq = 3519.99
let Ab7: freq = 3322.43
let G7:  freq = 3135.95
let Gb7: freq = 2959.95
let F7:  freq = 2793.82
let E7:  freq = 2637.01
let Eb7: freq = 2489.01
let D7:  freq = 2349.31
let Db7: freq = 2217.46
let C7:  freq = 2093.00
let B6:  freq = 1975.53
let Bb6: freq = 1864.65
let A6:  freq = 1760.00
let Ab6: freq = 1661.22
let G6:  freq = 1567.98
let Gb6: freq = 1479.98
let F6:  freq = 1396.91
let E6:  freq = 1318.51
let Eb6: freq = 1244.51
let D6:  freq = 1174.66
let Db6: freq = 1108.73
let C6:  freq = 1046.50
let B5:  freq = 987.77
let Bb5: freq = 932.33
let A5:  freq = 880.00
let Ab5: freq = 830.61
let G5:  freq = 783.99
let Gb5: freq = 739.99
let F5:  freq = 698.46
let E5:  freq = 659.25
let Eb5: freq = 622.25
let D5:  freq = 587.33
let Db5: freq = 554.37
let C5:  freq = 523.25
let B4:  freq = 493.88
let Bb4: freq = 466.16 // A#4 or Bb4
let A4:  freq = 440.00
let Ab4: freq = 415.30 // G#4 or Ab4
let G4:  freq = 392.00
let Gb4: freq = 369.99 // F#4 or Gb4
let F4:  freq = 349.23
let E4:  freq = 329.63
let Eb4: freq = 311.13 // D#4 or Eb4
let D4:  freq = 293.66
let Db4: freq = 277.18 // C#4 or Db4
let C4:  freq = 261.63
let B3:  freq = 246.94
let Bb3: freq = 233.08
let A3:  freq = 220.00
let Ab3: freq = 207.65
let G3:  freq = 196.00
let Gb3: freq = 185.00
let F3:  freq = 174.61
let E3:  freq = 164.81
let Eb3: freq = 155.56
let D3:  freq = 146.83
let Db3: freq = 138.59
let C3:  freq = 130.81
let B2:  freq = 123.47
let Bb2: freq = 116.54
let A2:  freq = 110.00
let Ab2: freq = 103.83
let G2:  freq = 98.00
let Gb2: freq = 92.50
let F2:  freq = 87.31
let E2:  freq = 82.41
let Eb2: freq = 77.78
let D2:  freq = 73.42
let Db2: freq = 69.30
let C2:  freq = 65.41
let B1:  freq = 61.74
let Bb1: freq = 58.27
let A1:  freq = 55.00
let Ab1: freq = 51.91
let G1:  freq = 49.00
let Gb1: freq = 46.25
let F1:  freq = 44.00
let E1:  freq = 41.20
let Eb1: freq = 38.89
let D1:  freq = 36.71
let Db1: freq = 34.65
let C1:  freq = 32.70
let B0:  freq = 30.87
let Bb0: freq = 29.14
let A0:  freq = 27.50

enum note: Int, CaseIterable 
{
    case C8, B7, Bb7, A7, Ab7, G7, Gb7, F7, E7, Eb7, D7, Db7
    case C7, B6, Bb6, A6, Ab6, G6, Gb6, F6, E6, Eb6, D6, Db6
    case C6, B5, Bb5, A5, Ab5, G5, Gb5, F5, E5, Eb5, D5, Db5
    case C5, B4, Bb4, A4, Ab4, G4, Gb4, F4, E4, Eb4, D4, Db4
}

enum MidiMessage: UInt8 
{
    case noteon         = 0x90
    case noteoff        = 0x80
    case aftertouch     = 0xA0
    case controlchange  = 0xB0
    case programchange  = 0xC0
    case pitchbend      = 0xE0
}

struct cd_pcm_frame 
{
    var left: cdsample 
    var right: cdsample 
}

struct MixerChannelInfo 
{
    var channelid: UInt32 
    var channelname: String
    var pluginid: String? 
    var mute: Bool 
    var solo: Bool
    var panpos: Float 
    var volume: Float 
    var numplugins: Int 

    init(name: String, id: UInt32)
    {
        self.channelid = id 
        self.channelname = name 
        self.pluginid = nil 
        self.mute = false 
        self.panpos = 0.0 
        self.volume = 0.0 
        self.numplugins = 0
        self.solo = false
    }
}

class AudioCore 
{
    public func AudioCore_init()
    {
        /* INCLUDE WORKING CODE :) */
        print("AudioCore initialized")
    }   
}