// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/18/25.
//  apple_platform.h
//
//  Description:
//      Graphical user interface for OpenDAW
//
// ---------------------------------------------------------

/* This is Objective-C++ code not c code*/

#ifndef APPLE_PLATFORM_H
#define APPLE_PLATFORM_H

#import <Cocoa/Cocoa.h>
#include <cstdarg>
#include <cstdio>

/**
 * @brief This function shows a error message box for the apple platform
 * @param msg The message that will be displayed
 * @returns void
 */
extern "C" void merror_apple(const char* msg, ...);

#endif 