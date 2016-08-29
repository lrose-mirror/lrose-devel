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
// WordSizeCheck.cc
//
// WordSizeCheck object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// WordSizeCheck is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "WordSizeCheck.hh"
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <cstddef>

using namespace std;

// Constructor

WordSizeCheck::WordSizeCheck(int argc, char **argv)

{

  OK = 1;

  return;

}

// destructor

WordSizeCheck::~WordSizeCheck()

{

  
}

//////////////////////////////////////////////////
// Run

int WordSizeCheck::Run()
{

  cerr << "sizeof(bool): " << sizeof(bool) << endl;
  cerr << "sizeof(short): " << sizeof(short) << endl;
  cerr << "sizeof(int): " << sizeof(int) << endl;
  cerr << "sizeof(long): " << sizeof(long) << endl;
  cerr << "sizeof(float): " << sizeof(float) << endl;
  cerr << "sizeof(double): " << sizeof(double) << endl;
  cerr << "sizeof(time_t): " << sizeof(time_t) << endl;
  cerr << "sizeof(long long int): " << sizeof(long long int) << endl;
  cerr << "sizeof(long double): " << sizeof(long double) << endl;

  cerr << "sizeof(dev_t): " << sizeof(dev_t) << endl;
  cerr << "sizeof(ino_t): " << sizeof(ino_t) << endl;
  cerr << "sizeof(mode_t): " << sizeof(mode_t) << endl;
  cerr << "sizeof(nlink_t): " << sizeof(nlink_t) << endl;
  cerr << "sizeof(uid_t): " << sizeof(uid_t) << endl;
  cerr << "sizeof(gid_t): " << sizeof(gid_t) << endl;
  cerr << "sizeof(off_t): " << sizeof(off_t) << endl;
  cerr << "sizeof(blksize_t): " << sizeof(blksize_t) << endl;
  cerr << "sizeof(blkcnt_t): " << sizeof(blkcnt_t) << endl;
  cerr << "sizeof(time_t): " << sizeof(time_t) << endl;

  cerr << "offsetof(char_field_1): "
       << offsetof(test_struct_t, char_field_1) << endl;
  cerr << "offsetof(short_field_1): "
       << offsetof(test_struct_t, short_field_1) << endl;
  cerr << "offsetof(char_field_2): "
       << offsetof(test_struct_t, char_field_2) << endl;
  cerr << "offsetof(int_field_1): "
       << offsetof(test_struct_t, int_field_1) << endl;
  cerr << "offsetof(long_field_1): "
       << offsetof(test_struct_t, long_field_1) << endl;
  cerr << "offsetof(char_field_3): "
       << offsetof(test_struct_t, char_field_3) << endl;
  cerr << "offsetof(double_field_1): "
       << offsetof(test_struct_t, double_field_1) << endl;

  return 0;

}


