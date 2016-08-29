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



///////////////////////////////////////////////////////////////////
// BounceClock.C: The clock that controls the animation in bounce
//////////////////////////////////////////////////////////////////
#include "BounceClock.h"
#include "Stage.h"

BounceClock::BounceClock ( const char *name, Widget parent, Stage *stage ) :
Clock ( name, parent, 1, 60 )
{
    _stage = stage;
}
void BounceClock::tick()
{
    _stage->nextFrame();
}





























