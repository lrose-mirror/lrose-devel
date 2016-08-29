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
// InotifyTest.h
//
// InotifyTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// April 1998
//
///////////////////////////////////////////////////////////////

#ifndef InotifyTest_H
#define InotifyTest_H

#include <tdrp/tdrp.h>
#include <string>
#include <vector>
#include <map>
#include <sys/inotify.h>

#include "Args.hh"
#include "Params.hh"

class InotifyTest {
  
public:

  // constructor

  InotifyTest (int argc, char **argv);

  // destructor
  
  ~InotifyTest();

  // run 

  int Run();

  // data members

  int OK;

protected:
  
private:

  string _progName;
  Args _args;
  Params _params;
  char *_paramsPath;

  int _inotifyFd;
  map<int, string> _watchList;

  void _handleEvent(struct inotify_event *i);
  
  void _printEvent(struct inotify_event *event, ostream &out);

  void _loadSubDirs(const string &dir,
                    int depth,
                    vector<string> &dirList);
};

#endif
