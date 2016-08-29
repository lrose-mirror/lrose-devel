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
// BouncingBall.C
//////////////////////////////////////////////////////////
#include <MotifApp/Application.h>
#include "Stage.h"
#include "BouncingBall.h"
#include <MotifApp/ColorChooser.h>
#include <MotifApp/InfoDialogManager.h>
#include "libc.h"
#define SIZE 25

BouncingBall::BouncingBall ( const char *colorName, 
			     Stage * stage ) : Actor ( stage )
{
    // Get an initial velocity at random
    
    _delta.x = ( int ) ( (SIZE * drand48()) / 3 );
    _delta.y = ( int ) ( (SIZE * drand48()) / 3 );
    
    // Initialize the current location and bounding box of the object
    
    _bounds.width = _bounds.height = SIZE;
    _bounds.x     = _bounds.width  + 1;
    _bounds.y     = _bounds.height + 1;
    _gc = NULL;
    
    // If a color name has been specified, try to allocate a color
    // Otherwise, use the ColorChooser to let the user pick a color
    
    if ( colorName )    
    {
	XGCValues  gcv;
	Display   *dpy  = Application::Instance()->display();
	int        scr  = DefaultScreen ( dpy );
	Colormap   cmap = DefaultColormap ( dpy, scr );
	XColor     color, ignore;
	
	// If color allocation fails, use the default black pixel
	
	if ( XAllocNamedColor ( dpy, cmap, colorName, 
				&color, &ignore ) )
	    gcv.foreground = color.pixel;
	else
	    gcv.foreground = BlackPixel ( dpy, scr );
	
	// Create a graphics context used to draw this object
	_gc = XtGetGC ( _stage->baseWidget(),  GCForeground,  &gcv ); 
    }
    else
    {
	ColorChooser *colorChooser =  new ColorChooser ( "colorChooser",
							 Application::Instance()->baseWidget() );
	
	colorChooser->pickColor ( &BouncingBall::colorSelectedCallback, 
				  &BouncingBall::canceledCallback, 
				  ( void * ) this );
    }
}
void BouncingBall::nextFrame ( Drawable  d, 
			       Dimension width, 
			       Dimension height )
{
    if ( !_gc)   // Return if no color has been chosen yet
	return;
    
    // Update the current position
    
    _bounds.x += _delta.x; _bounds.y += _delta.y;
    
    // If we have hit the right wall, reposition and
    // reverse the x component of the  velocity
    
    if ( _bounds.x + _bounds.width >= width )
    {
	_bounds.x = width - _bounds.width;
	_delta.x  = -_delta.x;
    }
    else if ( _bounds.x <= 0 )  // Check for hitting the left wall
    {
	_bounds.x = 0;
	_delta.x  = -_delta.x;
    }
    
    // If we have hit the floor, reposition and 
    // reverse the y component of the velocity
    
    if ( _bounds.y + _bounds.height >= height )
    {
	_bounds.y = height - _bounds.height;
	_delta.y  = -_delta.y;
    }
    else if ( _bounds.y <= 0 )  // Check for bouncing off the top
    {
	_bounds.y = 0;
	_delta.y  = -_delta.y;
    }
    
    // 	Draw the object at the new location
    XFillArc ( Application::Instance()->display(), d, _gc, 
	       _bounds.x, _bounds.y, _bounds.width, _bounds.height, 
	       0, 360 * 64 );
}
void BouncingBall::colorSelectedCallback ( int   red, 
					   int   green, 
					   int   blue, 
					   void *clientData )
{
    BouncingBall *obj = ( BouncingBall * ) clientData;
    obj->colorSelected ( red, green, blue );
}
void BouncingBall::colorSelected ( int red, int green, int blue )
{
    XGCValues  gcv;
    Display   *dpy  = Application::Instance()->display();
    int        scr  = DefaultScreen ( dpy );
    Colormap   cmap = DefaultColormap ( dpy, scr );
    XColor     color;           
    color.red   = red   * 256;
    color.green = green * 256;
    color.blue  = blue  * 256 ;
    
    if ( XAllocColor ( dpy, cmap, &color ) )
	gcv.foreground = color.pixel;
    else
	gcv.foreground = BlackPixel ( dpy, scr );
    
    _gc = XtGetGC ( _stage->baseWidget(), GCForeground,  &gcv ); 
}
void BouncingBall::canceledCallback ( void *clientData )
{
    BouncingBall *obj = ( BouncingBall * ) clientData;
    InfoDialogManager::Instance()->post ( "Using Black as the default color" );
    obj->colorSelected ( 0, 0, 0 );
}







































































































