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
// kakuro.cc
//
// kakuro object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// july 2011
//
///////////////////////////////////////////////////////////////
//
// kakuro prints out a table of possible kakuro numbers
//
///////////////////////////////////////////////////////////////

#include "kakuro.hh"
#include <string>
#include <sys/time.h>
#include <cmath>
#include <iostream>
using namespace std;

// Constructor

kakuro::kakuro(int argc, char **argv) :
  _args("kakuro")

{

  OK = TRUE;

  // set programe name

  _progName = strdup("kakuro");

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

kakuro::~kakuro()

{

  
}

//////////////////////////////////////////////////
// Run

int kakuro::Run()
{

  if (_params.debug) {
    cerr << "Kakuro list, max_size: " << _params.max_size << endl;
  }

  for (int isize = 2; isize <= _params.max_size; isize++) {
    _printPossibilities(isize);
  } 

  return 0;

}

//////////////////////////////////////////
// print out possibilities for given size

void kakuro::_printPossibilities(int size)

{
  
  cout << "=============================" << endl;
  cout << "Kakuro possibilities, size: " << size << endl;

  // clear solutions vector

  _solutions.clear();

  // create a trial solution for this size

  _trial.clear();
  for (int ii = 0; ii < size; ii++) {
    _trial.push_back(0);
  }
  _maxSum = 0;

  // recursively process each column in the solution, going up through
  // the columns

  _processColumn(0, size);

  // print out solutions in order

  for (int isum = 0; isum <= _maxSum; isum++) {

    bool headingPrinted = false;
    
    for (size_t ii = 0; ii < _solutions.size(); ii++) {
      
      const vector<int> &trial = _solutions[ii];
      int sum = 0;
      for (size_t jj = 0; jj < trial.size(); jj++) {
        sum += trial[jj];
      }

      if (sum == isum) {
        if (!headingPrinted) {
          cout << sum << "/" << size << ":";
          headingPrinted = true;
        }
        cout << " ";
        for (size_t jj = 0; jj < trial.size(); jj++) {
          cout << trial[jj];
        }
      } // if (sum == isum)
     
    } // ii

    if (headingPrinted) {
      cout << endl;
    }

  } // isum

}

void kakuro::_processColumn(int col, int size)

{

  if (col == size) {
    int sum = 0;
    // cout << "trial: <";
    for (int ii = 0; ii < size; ii++) {
      // cout << _trial[ii];
      sum += _trial[ii];
    }
    // cout << ">, sum: " << sum << endl;
    if (sum > _maxSum) {
      _maxSum = sum;
    }
    _solutions.push_back(_trial);
    return; // done
  }
  
  int maxVal = 9 - ((size - 1) - col);
  int minVal = 1;
  for (int ii = 0; ii < col; ii++) {
    if (_trial[ii] >= minVal) {
      minVal = _trial[ii] + 1;
    }
  }

  // cerr << "col, size, minVal, maxVal: "
  //      << col << ", "
  //      << size << ", "
  //      << minVal << ", "
  //      << maxVal << endl;

  for (int ival = minVal; ival <= maxVal; ival++) {
    _trial[col] = ival;
    // recursively call next column
    _processColumn(col + 1, size);
  }

}

