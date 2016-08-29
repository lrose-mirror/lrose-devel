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
// ComputeRangeAz.h
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

#ifndef ComputeRangeAz_H
#define ComputeRangeAz_H

#include <string>
#include <vector>

#include "Args.hh"
#include "Params.hh"

class ComputeRangeAz {
  
public:

  // constructor

  ComputeRangeAz (int argc, char **argv);

  // destructor
  
  ~ComputeRangeAz();

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

  double _computePhase(time_t thisTime);

};

#endif
