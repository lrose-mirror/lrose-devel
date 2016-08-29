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


////////////////////////////////////////////////////
// AddBallCmd.h
////////////////////////////////////////////////////
#ifndef ADDBALLCMD_H
#define ADDBALLCMD_H
#include <MotifApp/Cmd.h>
class Stage;
class Actor;

class AddBallCmd : public Cmd {
    
public:
    AddBallCmd ( const char *, int active, 
		 Stage*, char *color = ( char * ) 0 );
protected:
    Stage   *_stage;
    Actor   *_ball;
    char    *_color;
    virtual void doit();
    virtual void undoit();
};
#endif























