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
// Stage.C
//////////////////////////////////////////////////////////
#include <MotifApp/Application.h>
#include "Stage.h"
#include "Actor.h"
#include <Xm/DrawingA.h>

Stage::Stage ( const char *name, Widget parent ) : UIComponent( name )
{
    XGCValues  gcv;
    
    // Initialize all data members 
    
    _front   = 0;
    _back    = 0;
    
    // Create the visible drawing canvas, and set 
    // up the destruction handler
    
    _w =  XtCreateWidget ( _name, xmDrawingAreaWidgetClass,
			   parent, NULL, 0 );
    installDestroyHandler();
    
    // Add callbacks to handle resizing and exposures
    
    XtAddCallback ( _w, XmNresizeCallback, 
		    &Stage::resizeCallback, ( XtPointer ) this );
    XtAddCallback ( _w, XmNexposeCallback, 
		    &Stage::redisplayCallback, ( XtPointer ) this );
    
    // A graphics context is needed for copying the pixmap buffers and
    // erasing the back pixmap. Use the background color of 
    // the base widget for the fill color.
    
    XtVaGetValues ( _w, XmNbackground, &gcv.foreground, NULL );
    
    _gc = XtGetGC ( _w, GCForeground, &gcv ); 
    
    // Call resize to create the first pixmaps
    
    resize();
}
Stage::~Stage()
{
    // Free the pixmaps and GC, if they still exist
    
    if ( _front )       
	XFreePixmap ( XtDisplay ( _w ), _front );
    
    if ( _back )        
	XFreePixmap ( XtDisplay ( _w ), _back );
    
    if ( _w && _gc )
	XtReleaseGC ( _w, _gc );
}

void Stage::resizeCallback ( Widget, 
			     XtPointer clientData, 
			     XtPointer )
{
    Stage *obj = ( Stage * ) clientData;
    
    obj->resize();
}    

void Stage::resize()
{
    
    // Get the current size of the drawing area
    
    XtVaGetValues ( _w, XmNwidth,  &_width,
		    XmNheight, &_height,
		    NULL );
    
    if(!_width || !_height)
	return;
    
    // Pixmaps can't be resized, so just destroy the old ones
    
    if ( _front )       
	XFreePixmap ( XtDisplay ( _w ), _front );
    
    if ( _back )        
	XFreePixmap ( XtDisplay ( _w ), _back );
    
    // Create new pixmaps to match the new size of the window
    
    _back = XCreatePixmap ( XtDisplay ( _w ),
			    DefaultRootWindow ( XtDisplay ( _w ) ),
			    _width, _height, 
			    DefaultDepthOfScreen ( XtScreen ( _w ) ) );
    
    _front = XCreatePixmap ( XtDisplay ( _w ),
			     DefaultRootWindow ( XtDisplay ( _w ) ),
			     _width, _height, 
			     DefaultDepthOfScreen ( XtScreen ( _w ) ) );
    
    // Erase both pixmaps
    
    XFillRectangle ( XtDisplay ( _w ), _back, 
		     _gc, 0, 0, _width, _height );
    
    XFillRectangle ( XtDisplay ( _w ), _front, 
		     _gc, 0, 0, _width, _height );
}
void  Stage::nextFrame()
{
    // For each new frame, simply swap buffers and have each
    // Actor object draw its next frame in the back buffer
    
    swapBuffers();
    
    for ( int i = 0; i < _cast.size(); i++)
	_cast[i]->nextFrame ( _back, _width, _height );
}
void Stage::swapBuffers()
{
    // Switch the front and back buffers
    
    if ( XtIsRealized ( _w ) )
    {
	Pixmap tmp;
	
	// Do the swap
	
	tmp    = _front;
	_front = _back;
	_back  = tmp;
	
	// Copy the new front buffer to the drawing area
	
	XCopyArea ( XtDisplay ( _w ), _front, XtWindow ( _w ),
		    _gc, 0, 0, _width, _height, 0, 0 );
	
	// Erase the new back buffer to get ready for the next scene
	
	XFillRectangle ( XtDisplay ( _w ), _back, 
			 _gc, 0, 0, _width, _height );
    }
}
void Stage::redisplayCallback ( Widget, 
				XtPointer clientData, 
				XtPointer )
{
    Stage *obj = ( Stage * ) clientData;
    obj->redisplay();
}    
void Stage::redisplay ( )
{
    // Copy the contents of the front pixmap
    // to restore the window
    
    XCopyArea ( Application::Instance()->display(), _front, 
		XtWindow ( _w ), _gc, 0, 0, 
		_width, _height, 0, 0 );
}    
void Stage::addActor ( Actor *newActor )
{
    _cast.add ( newActor );
}
void Stage::removeActor ( Actor *oldActor )
{
    _cast.remove ( oldActor );   
}








