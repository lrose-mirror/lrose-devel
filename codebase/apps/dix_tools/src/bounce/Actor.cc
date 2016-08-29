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
// Actor.C: Abstract base class for all "actor" objects
///////////////////////////////////////////////////////////////
#include "Actor.h"
#include "Stage.h"

Actor::Actor ( Stage *stage ) 
{
    _stage = stage;      
    
    _stage->addActor ( this );   // Add this object to the Stage
}
Actor::~Actor() 
{
    _stage->removeActor ( this );  // Remove this object from the Stage
}





























