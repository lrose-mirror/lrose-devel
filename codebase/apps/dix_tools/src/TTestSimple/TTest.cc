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
#include <malloc.h>
#include <iostream>
#include <cmath>
using namespace std;

// Constructor

TTest::TTest(int argc, char **argv)

{

  OK = 1;

  // set programe name

  _progName = strdup("TTest");

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

  // calculate moon phase

  for (int iday = 0; iday < 14000; iday++) {
    time_t thisTime = iday * 86400 + 12 * 3600;
    double phase = _computePhase(thisTime);
    cout << thisTime << ": " << phase << endl;
  }

  return 0;

}

//////////////////////////////////////////////
// tokenize a string into a vector of strings.
// use this version if you have a string spacer
// e.g. TO that could have characters in common
// with other strings. Use tokenize() if you have
// a unique character

double TTest::_computePhase(time_t thisTime)
  
{
    
  double synodic = 29.53058867;
  double secsPerDay = 86400.0;

  double timeDiffSecs = (double) thisTime;
  double timeDiffDays = timeDiffSecs / secsPerDay;
  double nPhasesSinceFull = timeDiffDays / synodic;
  double sinPhase = fabs(sin(nPhasesSinceFull * M_PI));

  return sinPhase;

}

