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
// BouncingBall.h
//////////////////////////////////////////////////////////
#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H

#include "Actor.h"
#include <Xm/Xm.h>

class Stage;

class BouncingBall : public Actor {
    
public:
    
    BouncingBall ( const char *, Stage *);
    void nextFrame ( Drawable, Dimension, Dimension );  // Draw one frame
    
protected:
    
    GC         _gc;      // GC needed to draw the object
    XPoint     _delta;   // The velocity in terms of dx,dy 
    XRectangle _bounds;  // The bounding box of the ball
    
    // Called from the ColorChooser when the user has picked a color 
    
    static void colorSelectedCallback ( int   red, 
					int   green, 
					int   blue, 
					void *clientData );
    
    // Called from the ColorChooser if no color has been selected 
    
    static void canceledCallback ( void *);
    virtual void colorSelected ( int red, int green, int blue );
};
#endif









