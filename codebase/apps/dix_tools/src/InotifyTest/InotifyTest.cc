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
// InotifyTest.cc
//
// InotifyTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// InotifyTest is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "InotifyTest.hh"
#include <string>
#include <malloc.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <sys/stat.h>
#include <dirent.h>
#include <toolsa/uusleep.h>
#include <toolsa/file_io.h>
#include <toolsa/DateTime.hh>
#include <toolsa/TaStr.hh>
using namespace std;

// Constructor

InotifyTest::InotifyTest(int argc, char **argv) :
        _args("InotifyTest")
        
{
  
  OK = TRUE;
  
  // set programe name

  _progName = strdup("InotifyTest");

  // get command line args

  if (_args.parse(argc, (const char **) argv)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    OK = FALSE;
    return;
  }

  // get TDRP params

  _paramsPath = (char *) "unknown";
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

InotifyTest::~InotifyTest()

{


}

//////////////////////////////////////////////////
// Run

int InotifyTest::Run()
{
   
  // load up list of dirs to watch

  vector<string> dirList;
  _loadSubDirs(_params.dir_to_watch, 0, dirList);

  // create inotify instance

  _inotifyFd = inotify_init();
  if (_inotifyFd == -1) {
    cerr << "ERROR in inotify_init()" << endl;
    return -1;
  }

  for (size_t ii = 0; ii < dirList.size(); ii++) {
    int wd = inotify_add_watch(_inotifyFd, dirList[ii].c_str(),
                               IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE_SELF | IN_CREATE);
    if (wd >= 0) {
      if (_params.debug) {
        cerr << "==>> watching dir: " << dirList[ii] << ", using wd: " << wd << endl;
      }
      _watchList[wd] = dirList[ii];
    }
  }
   
  int bufLen = (10 * (sizeof(struct inotify_event) + 1024 + 1));
  char *buf = new char[bufLen];

  while (true) {    /* Read events forever */

    if (ta_fd_read_select(_inotifyFd, _params.time_between_checks_secs * 1000) == -1) {
      if (_params.debug) {
        cerr << "==>> timeout ..., reg with procmap" << endl;
      }
      continue;
    }
     
    ssize_t numRead = read(_inotifyFd, buf, bufLen);
    if (numRead == 0) {
      perror("ERROR in inotify read()");
      return -1;
    }
     
    if (numRead == -1) {
      cerr << "ERROR in read()" << endl;
      return -1;
    }

    if (_params.debug >= Params::DEBUG_VERBOSE) {
      cerr << "==>> Read " << numRead << " bytes from inotify fd: " << _inotifyFd << endl;
    }
     
    /* Process all of the events in buffer returned by read() */
     
    for (char *p = buf; p < buf + numRead; ) {
      struct inotify_event *event = (struct inotify_event *) p;
      _handleEvent(event);
      p += sizeof(struct inotify_event) + event->len;
    }
     
  } // while
 
  return 0;

}

void InotifyTest::_handleEvent(struct inotify_event *event)

{

  if (_params.debug >= Params::DEBUG_VERBOSE) {
    _printEvent(event, cerr);
  }

  // new file?

  if ((event->mask & IN_CLOSE_WRITE) || (event->mask & IN_MOVED_TO)) {
    
    string dir(_watchList[event->wd]);
    string fileName(event->name);
    string newFilePath(dir);
    newFilePath += PATH_DELIM;
    newFilePath += fileName;

    if (_params.debug) {
      cerr << "Created file: " << newFilePath << endl;
    }
    
    // exclude dirs that start with _

    if (fileName[0] == '_') {
      
      if (_params.debug) {
        cerr << "Ignoring file starting with '_': " << fileName << endl;
      }
      
    } else {

      // handle new file

      cerr << "Handle new file: " << newFilePath << endl;
      
    }
    
  } // if ((event->mask & IN_CLOSE_WRITE) ...

  // new dir?

  if ((event->mask & IN_CREATE) && (event->mask & IN_ISDIR)) {
    
    string dir(_watchList[event->wd]);
    string subDir(event->name);
    string newDirPath(dir);
    newDirPath += PATH_DELIM;
    newDirPath += subDir;
    
    if (_params.debug) {
      cerr << "Created dir: " << newDirPath << endl;
    }
    
    // exclude dirs that start with _
    
    if (subDir[0] == '_') {
      
      if (_params.debug) {
        cerr << "Ignoring dir starting with '_': " << subDir << endl;
      }

    } else {
      
      int wd = inotify_add_watch(_inotifyFd, newDirPath.c_str(),
                                 IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE_SELF | IN_CREATE);
      if (wd >= 0) {
        if (_params.debug) {
          cerr << "==>> watching dir: " << newDirPath << ", using wd: " << wd << endl;
        }
        _watchList[wd] = newDirPath;
      }
      
    }
    
  } // if ((event->mask & IN_CREATE) ...

  // dir deleted?

  if (event->mask & IN_DELETE_SELF) {
    
    string deletedDir(_watchList[event->wd]);
    
    if (_params.debug) {
      cerr << "Deleted dir: " << deletedDir << endl;
    }

    inotify_rm_watch(_inotifyFd, event->wd);
    _watchList.erase(event->wd);
    
  } // if ((event->mask & IN_DELETE_SELF)

  
}

void InotifyTest::_printEvent(struct inotify_event *event, ostream &out)

{

  out << "    wd = " << event->wd << endl;
  if (event->cookie > 0) {
    out << "  cookie = " << event->cookie << endl;
  }
  
  out << "  mask = ";
  if (event->mask & IN_ACCESS)        out << "IN_ACCESS ";
  if (event->mask & IN_ATTRIB)        out << "IN_ATTRIB ";
  if (event->mask & IN_CLOSE_NOWRITE) out << "IN_CLOSE_NOWRITE ";
  if (event->mask & IN_CLOSE_WRITE)   out << "IN_CLOSE_WRITE ";
  if (event->mask & IN_CREATE)        out << "IN_CREATE ";
  if (event->mask & IN_DELETE)        out << "IN_DELETE ";
  if (event->mask & IN_DELETE_SELF)   out << "IN_DELETE_SELF ";
  if (event->mask & IN_IGNORED)       out << "IN_IGNORED ";
  if (event->mask & IN_ISDIR)         out << "IN_ISDIR ";
  if (event->mask & IN_MODIFY)        out << "IN_MODIFY ";
  if (event->mask & IN_MOVE_SELF)     out << "IN_MOVE_SELF ";
  if (event->mask & IN_MOVED_FROM)    out << "IN_MOVED_FROM ";
  if (event->mask & IN_MOVED_TO)      out << "IN_MOVED_TO ";
  if (event->mask & IN_OPEN)          out << "IN_OPEN ";
  if (event->mask & IN_Q_OVERFLOW)    out << "IN_Q_OVERFLOW ";
  if (event->mask & IN_UNMOUNT)       out << "IN_UNMOUNT ";
  out << endl;
  
  out << "    dir: " << _watchList[event->wd] << endl;
  if (event->len > 0) {
    out << "        name = " << event->name << endl;
  }

}

////////////////////////////////////////////////////////////
// load list of directories to watch
//

void InotifyTest::_loadSubDirs(const string &dir,
                               int depth,
                               vector<string> &dirList)
  
{
  
  // initialize with depth 0 dir
  
  if (depth == 0) {
    dirList.push_back(dir);
  }
  
  // check we don't recurse too far
  
  if (depth > _params.max_recursion_depth) {
    return;
  }
  
  DIR *dirp;
  if ((dirp = opendir(dir.c_str())) == NULL) {
    if (_params.debug) {
      int errNum = errno;
      cerr << "ERROR: InotifyTest::_findSubDirs" << endl;
      cerr << "  Cannot open dir: " << dir << endl;
      cerr << "  " << strerror(errNum) << endl;
    }
    return;
  }
  
  // read directory looking for sub dirs
  
  struct dirent *dp;
  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    
    // exclude dir entries and files beginning with '.'
    
    if (dp->d_name[0] == '.') {
      continue;
    }

    // exclude entries that start with _

    if (dp->d_name[0] == '_') {
      if (_params.debug) {
        cerr << "Ignoring entries starting with '_': " << dp->d_name << endl;
      }
      continue;
    }

    // check file type
    
    char entryPath[MAX_PATH_LEN];
    sprintf(entryPath, "%s%s%s", dir.c_str(), PATH_DELIM, dp->d_name);
    struct stat fileStat;
    if (ta_stat(entryPath, &fileStat)) {
      if (_params.debug) {
	int errNum = errno;
	cerr << "WARNING: InotifyTest::_findSubDirs" << endl;
	cerr << "  Cannot stat file: " << entryPath << endl;
	cerr << "  " << strerror(errNum) << endl;
      }
      continue;
    }
    
    // for directories, search recursively
    
    if (S_ISDIR(fileStat.st_mode)) {
      dirList.push_back(entryPath);
      _loadSubDirs(entryPath, depth + 1, dirList);
    }
    
  } // dp
  
  closedir(dirp);

  
}

