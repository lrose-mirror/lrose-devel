/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright UCAR (c) 1992 - 1997
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** Do not copy or distribute without authorization
 ** 1997/9/26 13:58:59
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/////////////////////////////////////////////////////////////
// Args.h: Command line object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Jan 2002
//
/////////////////////////////////////////////////////////////

#ifndef ARGS_HH
#define ARGS_HH

#include <string>
#include <ostream.h>
#include <tdrp/tdrp.h>

class Args {
  
public:

  // constructor

  Args (const char *prog_name);

  // Destructor

  ~Args();

  // parse

  int parse(int argc, char **argv);

  // public data

  tdrp_override_t override;
  string mapFilePath;

protected:
  
private:

  string _progName;
  void _usage(ostream &out);
  
};

#endif



