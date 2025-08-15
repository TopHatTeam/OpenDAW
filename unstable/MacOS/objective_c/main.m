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

#import "AudioCore.h" 

int main(int argc, const char* argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    // Initialze the AudioCore engine
    AudioCore *audiocore = [[AudioCore alloc] initWithDevice:"Default Device", samplerate:44100];

    NSLog(@"AudioCore initialized with %d argument(s)\n", argc);
    NSLog(@"Also, Hello, World! Nerds!\n");

    // Cleanup 
    int cleanupResult = [audiocore cleanup];
    if (cleanupResult != 0)
    {
        NSLog(@"Error during cleanup: %d", cleanupResult);
    }
    [pool drain];   
    [audiocore release];
    return 0;
}