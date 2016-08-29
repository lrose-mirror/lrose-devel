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
// ReformatMap.cc
//
// ReformatMap object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Jan 2002
//
///////////////////////////////////////////////////////////////
//
// ReformatMap reformats a map file, writes to stdout
//
///////////////////////////////////////////////////////////////

#include "ReformatMap.hh"
#include <errno.h>
#include <vector>

// Constructor

ReformatMap::ReformatMap(int argc, char **argv) :
  _args("ReformatMap")

{

  OK = TRUE;

  // set programe name

  _progName = "ReformatMap";

  // get command line args
  
  if (_args.parse(argc, argv)) {
    cerr << "ERROR - " << _progName << endl;
    cerr << "  Problem with command line args" << endl;
    OK = FALSE;
    return;
  }

  // get TDRP params

  _paramsPath = "unknown";
  if (_params.loadFromArgs(argc, argv,
			   _args.override.list,
			   &_paramsPath)) {
    cerr << "ERROR - " << _progName << endl;
    cerr << "  Problem with TDRP parameters" << endl;
    OK = FALSE;
    return;
  }

  return;

}

// destructor

ReformatMap::~ReformatMap()

{

  
}

//////////////////////////////////////////////////
// Run

int ReformatMap::Run()
{

  // open the map file

  FILE *in;
  if ((in = fopen(_args.mapFilePath.c_str(), "r")) == NULL) {
    int errNum = errno;
    cerr << "ERROR - ReformatMap::Run" << endl;
    cerr << "  Cannot open map file: " << _args.mapFilePath << endl;
    cerr << "  " << strerror(errNum) << endl;
    return -1;
  }

  // read through the file

  vector<map_point_t> points;
  map_point_t point;
  int mapNum = 0;

  while (!feof(in)) {

    bool goodLine = false;

    char line[1024];
    if (fgets(line, 1024, in)) {
      if (sscanf(line, "%lg,%lg", &point.lon, &point.lat) == 2) {
	points.push_back(point);
	goodLine = true;
      }
    }

    if (!goodLine) {
      if (points.size() > 0) {
	fprintf(stdout, "POLYLINE Island_%d %d\n",
		mapNum, points.size());
	for (size_t ii = 0; ii < points.size(); ii++) {
	  fprintf(stdout, "%12.6f %12.6f\n",
		  points[ii].lat, points[ii].lon);
	}
	fprintf(stdout, "\n");
	points.clear();
	mapNum++;
      }
    }

  } // while

  // close input file

  fclose(in);

  return 0;

}

