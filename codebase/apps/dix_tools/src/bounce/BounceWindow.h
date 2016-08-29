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
// BounceWindow.h: 
/////////////////////////////////////////////////////////////
#ifndef BOUNCEWINDOW_H
#define BOUNCEWINDOW_H
#include <MotifApp/MenuWindow.h>
class Clock;
class Stage;
class ControlPanel;

class BounceWindow : public MenuWindow {
    
public:
    
    BounceWindow ( const char * );
    ~BounceWindow();
    
protected:
    
    virtual Widget createWorkArea ( Widget );
    virtual void   createMenuPanes();
    
private:
    
    Clock        *_clock;
    Stage        *_stage;
    ControlPanel *_controlPanel;
};
#endif
















































































































































































































