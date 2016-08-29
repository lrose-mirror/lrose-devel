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
// StepCmd.h
//////////////////////////////////////////////////////////
#ifndef STEPCMD_H
#define STEPCMD_H
#include <MotifApp/NoUndoCmd.h>

class Clock;

class StepCmd : public NoUndoCmd {
    
public:
    
    StepCmd (  const char *, int, Clock * );
    
protected:
    
    Clock *_clock;
    virtual void doit();
};
#endif























