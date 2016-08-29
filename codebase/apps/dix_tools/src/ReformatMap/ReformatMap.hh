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
// ReformatMap.h
//
// ReformatMap object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Jan 2002
//
///////////////////////////////////////////////////////////////

#ifndef ReformatMap_H
#define ReformatMap_H

#include <string>
#include "Args.hh"
#include "Params.hh"

typedef struct {
  double lat, lon;
} map_point_t;

class ReformatMap {
  
public:

  // constructor

  ReformatMap (int argc, char **argv);
  
  // destructor
  
  ~ReformatMap();

  // run 

  int Run();

  // data members

  int OK;

protected:
  
private:

  string _progName;
  char *_paramsPath;
  Args _args;
  Params _params;

};

#endif
