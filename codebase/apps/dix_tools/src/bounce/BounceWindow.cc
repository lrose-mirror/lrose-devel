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
// BounceWindow.C
/////////////////////////////////////////////////
#include <MotifApp/Application.h>
#include "BounceWindow.h"
#include "Stage.h"
#include "ControlPanel.h"
#include "BounceClock.h"
#include <MotifApp/QuitCmd.h>
#include <MotifApp/UndoCmd.h>
#include <MotifApp/CmdList.h>
#include "AddBallCmd.h"
#include <MotifApp/MenuBar.h>
#include <Xm/Form.h>
#include <Xm/Separator.h>
BounceWindow::BounceWindow ( const char *name ) : MenuWindow ( name )
{
    _clock         = NULL;
    _stage         = NULL;
    _controlPanel  = NULL;
}
BounceWindow::~BounceWindow ()
{
    delete _clock;
    delete _stage;
    delete _controlPanel;
}
Widget BounceWindow::createWorkArea ( Widget parent )
{
    // The BounceWindow work area is implemented as a form widget
    // that contains the other components of the bounce interface
    
    Widget form =  XtCreateWidget ( "workArea", xmFormWidgetClass,
				    parent, NULL, 0 );
    
    // Create each major component of the bounce window
    
    _stage        = new Stage ( "stage", form );
    _clock        = new BounceClock ( "clock", form, _stage );
    _controlPanel = new ControlPanel ( "control", form, _clock );
    
    // Set up the attachments to achieve the layout shown in Figure 12.1
    
    XtVaSetValues ( _controlPanel->baseWidget(),
		    XmNtopWidget,        _clock->baseWidget(),
		    XmNtopAttachment,    XmATTACH_OPPOSITE_WIDGET,
		    XmNleftAttachment,   XmATTACH_FORM,
		    XmNrightPosition,    50,
		    XmNrightAttachment,  XmATTACH_POSITION,
		    XmNbottomAttachment, XmATTACH_NONE,
		    NULL );
    
    XtVaSetValues ( _clock->baseWidget(), 
		    XmNtopAttachment,    XmATTACH_NONE,
		    XmNleftPosition,     50,
		    XmNleftAttachment,   XmATTACH_POSITION,
		    XmNrightAttachment,  XmATTACH_FORM,
		    XmNbottomAttachment, XmATTACH_FORM,
		    NULL );
    
    Widget sep =  
	XtVaCreateManagedWidget ( "sep", 
				  xmSeparatorWidgetClass,
				  form,
				  XmNleftAttachment,   XmATTACH_FORM,
				  XmNrightAttachment,  XmATTACH_FORM,
				  XmNtopAttachment,    XmATTACH_NONE,
				  XmNbottomWidget, _clock->baseWidget(),
				  XmNbottomAttachment, XmATTACH_WIDGET,
				  NULL );
    
    XtVaSetValues ( _stage->baseWidget(),
		    XmNtopAttachment,    XmATTACH_FORM,
		    XmNleftAttachment,   XmATTACH_FORM,
		    XmNrightAttachment,  XmATTACH_FORM,
		    XmNbottomWidget,     sep,
		    XmNbottomAttachment, XmATTACH_WIDGET,
		    NULL );
    
    // Manage all child widgets and return the form
    
    _controlPanel->manage();
    _stage->manage();
    _clock->manage();    
    
    return ( form );        
}
void BounceWindow::createMenuPanes ()
{
    
    // Create the main application menu, with just a quit and undo cmd
    
    CmdList *cmdList  = new CmdList ( "Application" );
    Cmd     *quit     = new QuitCmd ( "Quit" );
    
    cmdList->add ( UndoCmd::Instance() );        
    cmdList->add ( quit );
    _menuBar->addCommands ( cmdList );
    
    // Create a menu for adding actors to the screen
    
    CmdList *actorList = new CmdList ( "Actors" );
    
    Cmd *addRed   = new AddBallCmd ( "Add Red Ball",   TRUE, 
				     _stage,  "Red"  );
    Cmd *addGreen = new AddBallCmd ( "Add Green Ball", TRUE, 
				     _stage, "Green" );
    Cmd *addBlue  = new AddBallCmd ( "Add Blue Ball",  TRUE,
				     _stage, "Blue"  ); 
    Cmd *addAny   = new AddBallCmd ( "Add Ball...",    TRUE,
				     _stage );    
    
    actorList->add ( addRed );
    actorList->add ( addGreen );
    actorList->add ( addBlue );
    actorList->add ( addAny );
    
    _menuBar->addCommands ( actorList );
    
}





















































































































