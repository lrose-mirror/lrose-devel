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
#include "CircBuffer.h"
#include <pthread.h>
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

TTest::TTest(int argc, char **argv) :
  _args("TTest")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("TTest");

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

TTest::~TTest()

{

  
}

//////////////////////////////////////////////////
// Run

int TTest::Run()
{

  CircBuffer<int> buf(100000);

  pthread_t write_thread, read_thread;
  pthread_create(&write_thread, NULL, run_write_thread, &buf);
  pthread_create(&read_thread, NULL, run_read_thread, &buf);

  pthread_join(write_thread, NULL);
  pthread_join(read_thread, NULL);

  return 0;

}

// threads

void *TTest::run_write_thread(void * arg)

{

  CircBuffer<int> *buf = (CircBuffer<int> *) arg;

  int count = 0;
  int *val = new int;

  while (true) {

    *val = count;
    count++;
    val = buf->write(val);

    if (count > 20000000) {
      break;
    }

    // usleep(10);

  }

  return NULL;

}

void *TTest::run_read_thread(void * arg)

{

  CircBuffer<int> *buf = (CircBuffer<int> *) arg;
  int *val = new int;

  int prevCount = 0;
  
  while (true) {

    int *tmp = buf->read(val);
    if (tmp != NULL) {
      val = tmp;
      // cerr << "val: " << *val << endl;
      if (*val != prevCount + 1) {
        cerr << "=========== MISSING =============" << endl;
        cerr << "  prevCount: " << prevCount << endl;
        cerr << "  val: " << *val << endl;
        cerr << "  nMiss: " << *val - prevCount << endl;
        cerr << "=================================" << endl;
      }
      prevCount = *val;
      if (*val > 10000000) {
        break;
      }
    } else {
      // cerr << "----------------------" << endl;
      usleep(1000);
    }

  }

  return NULL;

}

