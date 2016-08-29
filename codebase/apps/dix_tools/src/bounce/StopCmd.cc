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
// StopCmd.C
//////////////////////////////////////////////////////////
#include "StopCmd.h"
#include <MotifApp/Clock.h>

StopCmd::StopCmd ( const char *name, int active, Clock *clock ) : 
Cmd ( name, active )
{
    _clock = clock;     
}
void StopCmd::doit()
{
    _clock->stop();     // Stop the animation
}       
void StopCmd::undoit()
{
    _clock->start();    // Restart the animation
}       

























