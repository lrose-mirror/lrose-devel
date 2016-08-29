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
// BitPrint.cc
//
// BitPrint object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// BitPrint is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "BitPrint.hh"
#include <string>
#include <malloc.h>
#include <iostream>
#include <toolsa/uusleep.h>
#include <toolsa/DateTime.hh>
#include <didss/DsInputPath.hh>
#include <didss/DataFileNames.hh>
#include <toolsa/DateTime.hh>
using namespace std;

// Constructor

BitPrint::BitPrint(int argc, char **argv) :
  _args("BitPrint")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("BitPrint");

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

BitPrint::~BitPrint()

{

  
}

//////////////////////////////////////////////////
// Run

int BitPrint::Run()
{

  cerr << "Val: " << _params.val << "  : ";

  int jj = 1;
  for (int ii = 15; ii >= 0; ii--) {

    int kk = jj << ii;

    // cerr << "ii, jj, kk: " << ii << ", " << jj << ", " << kk << endl;

    if (kk & _params.val) {
      cerr << "1";
    } else {
      cerr << "0";
    }

  }

  cerr << endl;

  return 0;

}

//////////////////////////////////////////////
// tokenize a string into a vector of strings.
// use this version if you have a string spacer
// e.g. TO that could have characters in common
// with other strings. Use tokenize() if you have
// a unique character

double BitPrint::_computePhase(time_t thisTime)
  
{
    
  double synodic = 29.53058867;
  double secsPerDay = 86400.0;

  DateTime fullMoonTime(1998, 12, 18, 22, 43, 00);
  double timeDiffSecs = (double) thisTime - (double) fullMoonTime.utime();
  double timeDiffDays = timeDiffSecs / secsPerDay;
  double nPhasesSinceFull = timeDiffDays / synodic;
  double sinPhase = fabs(sin(nPhasesSinceFull * M_PI));

  return sinPhase;

}

