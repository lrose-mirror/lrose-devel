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
// TimeCheck.cc
//
// TimeCheck object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// TimeCheck is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "TimeCheck.hh"
#include <string>
#include <malloc.h>
#include <iostream>
#include <toolsa/uusleep.h>
#include <toolsa/DateTime.hh>
#include <didss/DsInputPath.hh>
#include <didss/DataFileNames.hh>
#include <toolsa/DateTime.hh>
#include <ctime>
using namespace std;

// Constructor

TimeCheck::TimeCheck(int argc, char **argv) :
  _args("TimeCheck")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("TimeCheck");

  // get command line args
  
  if (_args.parse(argc, (const char **) argv)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    OK = FALSE;
    return;
  }

  // get TDRP params
  
  _paramsPath = "unknown";
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

TimeCheck::~TimeCheck()

{

  
}

//////////////////////////////////////////////////
// Run

int TimeCheck::Run()
{

  int prevSec = 0;

  while (true) {

    struct timeval tv;
    gettimeofday(&tv, NULL);
    DateTime now(tv.tv_sec);
    
    if (tv.tv_sec != prevSec) {
      cerr << "==================" << endl;
      prevSec = tv.tv_sec;
    }
    cerr << now.getSec() << "."
         << tv.tv_usec / 1000 << endl;

    int next = (tv.tv_usec / 100000) * 100000 + 100000;
    int diff = next - tv.tv_usec;
    uusleep(diff);

  }

  return 0;

}

