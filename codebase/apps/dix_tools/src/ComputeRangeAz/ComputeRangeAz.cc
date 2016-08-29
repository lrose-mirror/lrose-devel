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
// ComputeRangeAz.cc
//
// ComputeRangeAz object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Nov 2005
//
///////////////////////////////////////////////////////////////
//
// ComputeRangeAz computes range and azimuth between two points
//
////////////////////////////////////////////////////////////////

#include "ComputeRangeAz.hh"
#include "Params.hh"
#include <string>
#include <iostream>
#include <toolsa/pjg.h>
#include <toolsa/toolsa_macros.h>
#include <dataport/bigend.h>

using namespace std;

// Constructor

ComputeRangeAz::ComputeRangeAz(int argc, char **argv) :
  _args("ComputeRangeAz")

{

  OK = 1;

  // set programe name

  _progName = strdup("ComputeRangeAz");
  
  // get command line args
  
  if (_args.parse(argc, (const char **) argv)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    OK = 0;
    return;
  }

  // load TDRP params from command line
  
  char *paramsPath = "unknown";
  if (_params.loadFromArgs(argc, argv,
			   _args.override.list,
			   &paramsPath)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with TDRP parameters." << endl;
    OK = false;
    return;
  }

  return;

}

// destructor

ComputeRangeAz::~ComputeRangeAz()

{

  
}

//////////////////////////////////////////////////
// Run

int ComputeRangeAz::Run()
{

  cerr << "Computing distance from:" << endl;
  cerr << "  (" << _params.lat1 << ", " << _params.lon1 << ")" << endl;
  cerr << "to:" << endl;
  cerr << "  (" << _params.lat2 << ", " << _params.lon2 << ")" << endl;
  cerr << endl;

  double range, theta;

  PJGLatLon2RTheta(_params.lat1, _params.lon1,
                   _params.lat2, _params.lon2,
                   &range, &theta);

  cerr << "  Distance in km: " << range << endl;
  cerr << "  Distance in nm: " << (range / KM_PER_NM) << endl;
  cerr << "  Bearing in deg T: " << theta << endl;
  
  return 0;

}


