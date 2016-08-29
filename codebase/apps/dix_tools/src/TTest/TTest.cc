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
// TTest.cc
//
// TTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// TTest is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "TTest.hh"
#include <string>
#include <cmath>
#include <malloc.h>
#include <iostream>
#include <toolsa/uusleep.h>
#include <toolsa/DateTime.hh>
#include <didss/DsInputPath.hh>
#include <didss/DataFileNames.hh>
#include <toolsa/DateTime.hh>
#include <toolsa/TaStr.hh>
#include <toolsa/TaFile.hh>
using namespace std;

// Constructor

TTest::TTest(int argc, char **argv) :
  _args("TTest")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("TTest");

  // get command line args
  
  if (_args.parse(argc, (const char **) argv)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    OK = FALSE;
    return;
  }

  // get TDRP params
  
  _paramsPath = (char *) "unknown";
  if (_params.loadFromArgs(argc, argv,
			   _args.override.list,
			   &_paramsPath)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with TDRP parameters" << endl;
    OK = FALSE;
    return;
  }

  return;

}

// destructor

TTest::~TTest()

{

  
}

//////////////////////////////////////////////////
// Run

int TTest::Run()
{

  
#ifdef __GLIBC__
  cerr << "Have __GLIBC__" << endl;
#else
  cerr << "No not have __GLIBC__" << endl;
#endif

#ifdef __APPLE__
  cerr << "Have __APPLE__" << endl;
#else
  cerr << "No not have __APPLE__" << endl;
#endif

  double xx = -59.999;
  double yy = 30;

  cerr << "fmod(" << xx << "," << yy << "): " << fmod(xx, yy) << endl;

  cerr << "25u - 50: " << 25u - 50 << endl;;

  return 0;

}

