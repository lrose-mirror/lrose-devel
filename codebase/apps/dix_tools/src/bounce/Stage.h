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


/////////////////////////////////////////////////
// Stage.h
/////////////////////////////////////////////////
#ifndef STAGE_H
#define STAGE_H
#include <MotifApp/UIComponent.h>
#include <MotifApp/SimpleList.h>

class Actor;

class Stage : public UIComponent {
    
public:
    
    Stage ( const char *, Widget );    
    ~Stage ();    
    
    virtual void nextFrame();   // Move all actors to the next frame
    
    void addActor ( Actor * );       
    void removeActor ( Actor * );
    
    virtual const char *const className() { return ( "Stage" ); }
    
protected:
    
    GC          _gc;               // Used to clear and copy pixmaps
    Dimension   _width, _height;   // Current window/buffer size
    Pixmap      _front, _back;     // Buffers (Always draw to _back)
    SimpleList<Actor*> _cast;   // List of Actor objects on the Stage
    
    virtual void resize();
    virtual void redisplay();
    virtual void swapBuffers();
    
private:
    
    static void resizeCallback ( Widget, XtPointer, XtPointer );
    static void redisplayCallback ( Widget, XtPointer, XtPointer );
};
#endif




