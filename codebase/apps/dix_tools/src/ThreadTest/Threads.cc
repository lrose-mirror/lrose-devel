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
// Threads.cc
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

#include "Params.hh"
#include "Threads.hh"

pthread_mutex_t Thread::_fftMutex = PTHREAD_MUTEX_INITIALIZER;

/////////////////////////////////
// Generic thread

Thread::Thread()

{

  pthread_mutex_init(&startMutex, NULL);
  pthread_mutex_init(&doneMutex, NULL);

  pthread_cond_init(&startCond, NULL);
  pthread_cond_init(&doneCond, NULL);

  startFlag = false;
  doneFlag = false;

  exitFlag = false;

}

Thread::~Thread()

{

  pthread_mutex_destroy(&startMutex);
  pthread_mutex_destroy(&doneMutex);

  pthread_cond_destroy(&startCond);
  pthread_cond_destroy(&doneCond);

}

/////////////////////////////////////////////////////////////
// Mutex handling for communication between caller and thread

// Parent signals thread to start work

void Thread::signalThreadToStart() 
{
  pthread_mutex_lock(&startMutex);
  startFlag = true;
  pthread_cond_signal(&startCond);
  pthread_mutex_unlock(&startMutex);
}

// Thread waits for parent to signal start

void Thread::waitForStartSignal() 
{
  pthread_mutex_lock(&startMutex);
  while (!startFlag) {
    pthread_cond_wait(&startCond, &startMutex);
  }
  startFlag = false;
  pthread_mutex_unlock(&startMutex);
}

// Thread signals parent it is done
 
void Thread::signalParentThreadIsDone() 
{
  pthread_mutex_lock(&doneMutex);
  doneFlag = true;
  pthread_cond_signal(&doneCond);
  pthread_mutex_unlock(&doneMutex);
}

// Parent waits for thread to be done

void Thread::waitForThreadIsDone() 
{
  pthread_mutex_lock(&doneMutex);
  while (!doneFlag) {
    pthread_cond_wait(&doneCond, &doneMutex);
  }
  doneFlag = false;
  pthread_mutex_unlock(&doneMutex);
}

// create and destroy FFT objects in a thread safe manner

RadarFft *Thread::createFft(int nSamples)

{
  pthread_mutex_lock(&_fftMutex);
  RadarFft *fft = new RadarFft(nSamples);
  pthread_mutex_unlock(&_fftMutex);
  return fft;
}

void Thread::destroyFft(RadarFft *fft)

{
  pthread_mutex_lock(&_fftMutex);
  delete fft;
  pthread_mutex_unlock(&_fftMutex);
}


/////////////////////////////////
// Threads for computing moments

MomentsThread::MomentsThread(const Params &params) :
        Thread(),
        params(params)

{

  startGate = 0;
  endGate = -1;

  nSamplesFft = 0;
  fft = NULL;
  fftHalf = NULL;

}

MomentsThread::~MomentsThread()
{

  if (fft) {
    delete fft;
  }

  if (fftHalf) {
    delete fftHalf;
  }

}

// initialize the FFTs

void MomentsThread::initFfts(int nSamples)
{
  
  if (nSamplesFft == nSamples) {
    return;
  }

  // delete old objects
  
  if (fft) {
    delete fft;
  }
  if (fftHalf) {
    delete fftHalf;
  }
  
  // create new objects for correct size
  
  fft = new RadarFft(nSamples);
  fftHalf = new RadarFft(nSamples / 2);
  nSamplesFft = nSamples;

}
  

