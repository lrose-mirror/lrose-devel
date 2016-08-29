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
// "Main" program for multiple animation windows
//////////////////////////////////////////////////////////
#include <MotifApp/Application.h>
#include "BounceWindow.h"

Application *bounceApp = new Application  ( "Bounce" );
MainWindow *window     = new BounceWindow ( "Bounce" );
MainWindow *window2    = new BounceWindow ( "Bounce 2" );
