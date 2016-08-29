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
// ControlPanel.C
//////////////////////////////////////////////////////////
#include "ControlPanel.h"
#include <MotifApp/ButtonInterface.h>
#include <MotifApp/Clock.h>
#include "RunCmd.h"
#include "StopCmd.h"
#include "StepCmd.h"
#include <Xm/RowColumn.h>

ControlPanel::ControlPanel ( const char *name, 
			     Widget parent, 
			     Clock *clock ) : UIComponent ( name )
{
    CmdInterface *runBtn, *stopBtn, *stepBtn;
    Cmd          *runCmd, *stopCmd, *stepCmd;
    
    // Manage all command buttons in a single horizontal row
    
    _w = XtVaCreateManagedWidget ( _name, xmRowColumnWidgetClass, 
				   parent, 
				   XmNnumColumns, 1,
				   XmNorientation, XmHORIZONTAL, 
				   NULL );
    installDestroyHandler();
    
    // Instantiate one object for each command 
    // The clock will initially be stopped, so activate the  
    // step and run commands, but deactivate the stop command
    
    runCmd  = new RunCmd  ( "Run",  TRUE,  clock );
    stopCmd = new StopCmd ( "Stop", FALSE, clock );
    stepCmd = new StepCmd ( "Step", TRUE,  clock );
    
    // Set up dependencies between the various commands
    // A running clock can be stopped, but not stepped
    // A stopped clock can be run, or stepped (It doesn't
    // make sense to stop a stopped clock, or to run a 
    // running  clock, so have these commands deactivate
    // themselves automatically)
    
    runCmd->addToActivationList ( stopCmd );
    runCmd->addToDeactivationList ( stepCmd );
    runCmd->addToDeactivationList ( runCmd );
    
    stopCmd->addToActivationList ( runCmd );
    stopCmd->addToActivationList ( stepCmd );
    stopCmd->addToDeactivationList ( stopCmd );
    
    stepCmd->addToActivationList ( runCmd );
    stepCmd->addToDeactivationList ( stopCmd );
    
    // Finally, create the user interface (buttons) for
    // each of the commands
    
    runBtn   = new ButtonInterface ( _w, runCmd );   
    stopBtn  = new ButtonInterface ( _w, stopCmd );
    stepBtn  = new ButtonInterface ( _w, stepCmd );
    
    runBtn->manage();
    stopBtn->manage();
    stepBtn->manage();
    
}












