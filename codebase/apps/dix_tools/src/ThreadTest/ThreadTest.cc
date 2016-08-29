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
// ThreadTest.cc
//
// ThreadTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// ThreadTest is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "ThreadTest.hh"
#include <sys/time.h>
#include <string>
#include <malloc.h>
#include <iostream>
#include <toolsa/uusleep.h>
#include <toolsa/DateTime.hh>
#include <didss/DsInputPath.hh>
#include <didss/DataFileNames.hh>
#include <toolsa/DateTime.hh>
using namespace std;

vector<MomentsThread *> ThreadTest::_threads;
int ThreadTest::_count = 0;

// Constructor

ThreadTest::ThreadTest(int argc, char **argv) :
  _args("ThreadTest")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("ThreadTest");

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

ThreadTest::~ThreadTest()

{
  cleanUpThreads();
}

//////////////////////////////////////////////////
// Run

int ThreadTest::Run()
{
  
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double startTime = tv.tv_sec + tv.tv_usec / 1.0e6;

  _nSamples = 64;
  _nGates = _params.n_gates;

  // clean up threads which already exist
  
  cleanUpThreads();

  // set up new threads

  for (int ii = 0; ii < _params.n_threads; ii++) {
    MomentsThread *thread = new MomentsThread(_params);
    pthread_t pth = 0;
    pthread_create(&pth, NULL, _runThread, thread);
    thread->thread = pth;
    thread->threadNum = ii;
    _threads.push_back(thread);
  } // ii

  // run

  for (int ii = 0; ii < _params.n_iterations; ii++) {
    _triggerComputeThreads();
  }

  gettimeofday(&tv, NULL);
  double endTime = tv.tv_sec + tv.tv_usec / 1.0e6;

  cerr << "final count: " << _count << endl;
  cerr << "elapsed secs: " << endTime - startTime << endl;

  return 0;

}


//////////////////////////////////////////////
// Manage compute threads for this xmitRcvMode

void ThreadTest::cleanUpThreads()
  
{

  if (_threads.size() > 0) {

    // allow threads to exit by setting done flag
    
    for (int ii = 0; ii < (int) _threads.size(); ii++) {
      // set done flags so threads will exit
      MomentsThread *thread = _threads[ii];
      _threads[ii]->exitFlag = true;
      thread->signalThreadToStart();
    }
    
    // wait for threads to exit, clean up thread memory
    
    for (int ii = 0; ii < (int) _threads.size(); ii++) {
      _threads[ii]->waitForThreadIsDone();
    }

    _threads.clear();
    
  } // if (_threads.size() > 0)

}

///////////////////////////////////////////////////////////
// Trigger threads for computing at each gate

void ThreadTest::_triggerComputeThreads()

{

  int nThreads = (int) _threads.size();
  if (nThreads == 0) {
    return;
  }

  // initialize the FFT objects on the threads
  // this is done before the threads are used because 
  // fftw initialization is not thread safe

  //   for (int ii = 0; ii < nThreads; ii++) {
  //     _threads[ii]->initFfts(_nSamples);
  //   }
  
  // single threaded operation
  
  //   if (nThreads < 2) {
  //     MomentsThread *thread = _threads[0];
  //     thread->startGate = 0;
  //     thread->endGate = _nGates - 1;
  //     thread->signalThreadToStart();
  //     thread->waitForThreadIsDone();
  //     return;
  //   }
  
  // initialize thread state
  
  int ngatesThread = (_nGates / nThreads) + 1;
  int startGate = 0;
  for (int ii = 0; ii < nThreads; ii++) {
    int endGate = startGate + ngatesThread - 1;
    if (endGate > _nGates - 1) {
      endGate = _nGates - 1;
    }
    MomentsThread *thread = _threads[ii];
    thread->startGate = startGate;
    thread->endGate = endGate;
    startGate = endGate + 1;
  }

  // start threads
  
  for (int ii = 0; ii < nThreads; ii++) {
    _threads[ii]->signalThreadToStart();
  }

  // wait for threads to complete

  for (int ii = 0; ii < nThreads; ii++) {
    _threads[ii]->waitForThreadIsDone();
  }
  
}

//////////////////////////////////////////////
// Thread runner

void* ThreadTest::_runThread(void *thread_data)
  
{

  // get thread data from args
  
  MomentsThread *thread = (MomentsThread *) thread_data;
  
  while (true) {
    
    // wait for start signal from main thread
    
    thread->waitForStartSignal();
    
    // if exitFlag is set, app is done, exit now
    
    if (thread->exitFlag) {
      thread->signalParentThreadIsDone();
      return NULL;
    }
    
    // perform computations
    
    for (int igate = thread->startGate; igate <= thread->endGate; igate++) {

      double ang = fmod((igate / 1000.0), 3.0);
      double sinVal = sin(ang);
      double cosVal = cos(ang);
      double rr = 99.0;
      double xx = rr * cosVal;
      double yy = rr * sinVal;
      double ang2 = atan2(yy, xx);
      if (fabs(ang2 - ang) > 0.0001) {
        cerr << "ERROR - ang, ang2: " << ang << ", " << ang2 << endl;
      }
      _count++;
      
    } // igate
    
    // signal parent that we are done

    thread->signalParentThreadIsDone();
    
  } // while

  return NULL;

}

