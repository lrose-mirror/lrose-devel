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
//////////////////////////////////////////////////////////
// Args.cc : command line args
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Jan 2002
//
//////////////////////////////////////////////////////////

#include "Args.hh"
#include "Params.hh"
#include <string.h>

// Constructor

Args::Args (const char *prog_name) :
  _progName(prog_name)

{

  TDRP_init_override(&override);

}

// Destructor

Args::~Args ()

{

  TDRP_free_override(&override);

}
  
// Parse args

int Args::parse(int argc, char **argv)

{

  char tmp_str[BUFSIZ];

  // intialize

  int iret = 0;
  
  // loop through args
  
  for (int i =  1; i < argc; i++) {

    if (!strcmp(argv[i], "-h")) {
      
      _usage(cout);
      exit (0);
      
    } else if (!strcmp(argv[i], "-debug")) {
      
      sprintf(tmp_str, "debug = DEBUG_NORM;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-verbose")) {
      
      sprintf(tmp_str, "debug = DEBUG_VERBOSE;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-f")) {
      
      if (i < argc - 1) {
	mapFilePath = argv[++i];
      } else {
	iret = -1;
      }

    } // if
    
  } // i

  if (iret) {
    _usage(cerr);
  }

  return iret;
    
}

void Args::_usage(ostream &out)
{

  out << "Usage: " << _progName << " [options as below]\n"
      << "options:\n"
      << "       [ -h ] produce this list.\n"
      << "       [ -debug ] print debug messages\n"
      << "       [ -f ?] set station name\n"
      << "       [ -verbose ] print verbosedebug messages\n"
      << endl;

  Params::usage(cout);

}






