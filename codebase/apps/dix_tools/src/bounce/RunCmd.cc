///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//         This example code is from the book:
//
//           Object-Oriented Programming with C++ and OSF/Motif, 2nd Edition
//         by
//           Douglas Young
//           Prentice Hall, 1995
//           ISBN 0-13-20925507
//
//         Copyright 1995 by Prentice Hall
//         All Rights Reserved
//
//  Permission to use, copy, modify, and distribute this software for 
//  any purpose except publication and without fee is hereby granted, provided 
//  that the above copyright notice appear in all copies of the software.
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////
// RunCmd.C
//////////////////////////////////////////////////////////
#include "RunCmd.h"
#include <MotifApp/Clock.h>

RunCmd::RunCmd ( const char *name, int active, Clock *clock ) : 
Cmd ( name, active )
{
    _clock = clock;    // Store the Clock for later use 
}
void RunCmd::doit()
{
    _clock->start();     // Start the animation
}       
void RunCmd::undoit()
{
    _clock->stop();      // Stop the clock, and the animation
}       
























