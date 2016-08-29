/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright UCAR (c) 1992 - 1999
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** Do not copy or distribute without authorization
 ** 1999/03/14 14:18:54
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/////////////////////////////////////////////////////////////
// Threads.hh
//
// Mike Dixon, RAP, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// July 2007
//
///////////////////////////////////////////////////////////////
//
// Classes for dealing with threads
//
///////////////////////////////////////////////////////////////

#ifndef Threads_hh
#define Threads_hh

#include <pthread.h>
#include <radar/RadarFft.hh>
class BeamReader;
class OutputFmq;
class Beam;
class Iq2Dsr;
class Params;

using namespace std;

////////////////////////////
// Generic thread base class

class Thread {
public:

  Thread();
  ~Thread();

  // data

  pthread_t thread;

  pthread_mutex_t startMutex;
  pthread_mutex_t doneMutex;

  pthread_cond_t startCond;
  pthread_cond_t doneCond;

  bool startFlag;
  bool doneFlag;

  int threadNum;
   bool exitFlag;

  // Mutex handling for communication between caller and thread

  // Parent signals thread to start work

  void signalThreadToStart();
  
  // Thread waits for parent to signal start
  void waitForStartSignal();

  // Thread signals parent it is done
  void signalParentThreadIsDone();

  // Parent waits for thread to be done
  void waitForThreadIsDone();

  // create and destroy FFT objects in a thread safe manner

  static RadarFft *createFft(int nSamples);
  static void destroyFft(RadarFft *fft);

private:

  static pthread_mutex_t _fftMutex;

};

//////////////////////////////
// Moments computation thread

class MomentsThread : public Thread 

{

public:

  MomentsThread(const Params &params);
  ~MomentsThread();
  void initFfts(int nSamples);

  // data

  const Params &params;

  // start and end gates

  int startGate;
  int endGate;

  // FFT support
  
  int nSamplesFft;
  RadarFft *fft;
  RadarFft *fftHalf;

};

#endif

