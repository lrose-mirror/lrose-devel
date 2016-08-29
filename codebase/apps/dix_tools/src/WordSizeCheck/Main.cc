/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright UCAR (c) 1992 - 1997
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** Do not copy or distribute without authorization
 ** 1997/9/26 14:18:54
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
///////////////////////////////////////////////////////////////
//
// main for WordSizeCheck
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Sept 1998
//
///////////////////////////////////////////////////////////////
//
// WordSizeCheck checks size of various words on a host
//
////////////////////////////////////////////////////////////////

#include "WordSizeCheck.hh"

// file scope

static void tidy_and_exit (int sig);
static WordSizeCheck *Prog;

// main

int main(int argc, char **argv)

{

  // create program object

  WordSizeCheck *Prog;
  Prog = new WordSizeCheck(argc, argv);
  if (!Prog->OK) {
    return(-1);
  }

  // run it

  int iret = Prog->Run();

  // clean up

  tidy_and_exit(iret);
  return (iret);
  
}

// tidy up on exit

static void tidy_and_exit (int sig)

{
  delete(Prog);
}
