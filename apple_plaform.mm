// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/18/25.
//  apple_platform.mm
//
//  Description:
//      Apple platform specific stuff
//
// ---------------------------------------------------------

#include "headers/apple/apple_platform.h"

extern "C" void merror_apple(const char* msg, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);

    @autoreleasepool 
    {
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Error"];
        [alert setInformativeText:[NSString stringWithUTF8String:buffer]];
        [alert addButtonWithTitle:@"OK"];
        [alert runModal];
    }
}