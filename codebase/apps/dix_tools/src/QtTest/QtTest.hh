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
/////////////////////////////////////////////////////////////
// QtTest.h
//
// QtTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// July 2006
//
///////////////////////////////////////////////////////////////

#ifndef QtTest_H
#define QtTest_H

#include <string>
#include <vector>

#include "Args.hh"
#include "Params.hh"

class QtTest {
  
public:

  // constructor

  QtTest (int argc, char **argv);

  // destructor
  
  ~QtTest();

  // run 

  int Run();

  // data members

  int OK;

protected:
  
private:

  string _progName;
  Params _params;
  Args _args;
  char *_paramsPath;
  int _argc;
  char **_argv;

  double _computeVisDay(double ee);
  double _computeVisNight(double ee);
  double _evFunc(double ee, double vv);

};

#endif
