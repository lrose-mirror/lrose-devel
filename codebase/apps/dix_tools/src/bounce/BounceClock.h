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



///////////////////////////////////////////////////////////////
// BounceClock.h
///////////////////////////////////////////////////////////////
#ifndef BOUNCECLOCK_H
#define BOUNCECLOCK_H
#include <MotifApp/Clock.h>
class Stage;

class BounceClock : public Clock {
    
public:
    BounceClock ( const char *, Widget, Stage *stage );    
    virtual const char *const className() { return ( "BounceClock" ); }
    
protected:
    virtual void tick();  // Called by base class
    
private:
    Stage *_stage;    // The Stage controlled by this clock
};
#endif























