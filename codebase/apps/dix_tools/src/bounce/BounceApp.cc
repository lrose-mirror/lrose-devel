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


/////////////////////////////////////////////////////////////
// This version of main was created to work with the 
// Singleton-style Application class
/////////////////////////////////////////////////////////////

#include <MotifApp/Application.h>
#include <MotifApp/QuestionDialogManager.h>
#include "BounceWindow.h"

/////////////////////////////////////////////////////////////
// main()
/////////////////////////////////////////////////////////////


int main ( int argc, char **argv )

{

  // instantiate an Application object

  Application *app = Application::Instance("BounceApp",&argc,argv);
  
  // create the main window

  MainWindow *window = new BounceWindow ( "Bounce" );

  // initialize the application

  app->initialize ();

  // enter event loop

  app->handleEvents();

  // free up

  delete window;
  delete app;

}

