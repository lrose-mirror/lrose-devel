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



//////////////////////////////////////////////////////////////
// Actor.h: Abstract base class for all "actor" objects
//////////////////////////////////////////////////////////////
#ifndef ACTOR_H
#define ACTOR_H
#include <Xm/Xm.h>
class Stage;

class Actor {
    
public:
    Actor ( Stage * );
    virtual ~Actor();
    
    // Must be implemented by derived classes
    
    virtual void nextFrame ( Drawable, Dimension, Dimension ) = 0;
    
protected:
    Stage *_stage;    // The Stage on which this object appears
};
#endif






















