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
// AddBallCmd.C
//////////////////////////////////////////////////////////
#include "AddBallCmd.h"
#include "BouncingBall.h"

AddBallCmd::AddBallCmd ( const char  *name, 
			 int    active,  
			 Stage *stage,
			 char  *color ) : Cmd ( name, active )
{ 
    _stage = stage;
    _color = color;     
    _ball  = NULL;
}
void AddBallCmd::doit()
{
    _ball = new BouncingBall ( _color, _stage );
} 
void AddBallCmd::undoit()
{
    delete _ball;       
    _ball = NULL;
} 




















