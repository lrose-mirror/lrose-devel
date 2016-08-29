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
// SunTest.cc
//
// SunTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 1999
//
///////////////////////////////////////////////////////////////
//
// SunTest is a test shell for C++
//
///////////////////////////////////////////////////////////////

#include "SunTest.hh"
#include <string>
#include <iostream>
#include <toolsa/uusleep.h>
#include <toolsa/DateTime.hh>
#include <didss/DsInputPath.hh>
#include <didss/DataFileNames.hh>
#include <toolsa/DateTime.hh>
#include <rvp8_rap/SunPosn.hh>
using namespace std;

// Constructor

SunTest::SunTest(int argc, char **argv)

{

  OK = TRUE;

  // set programe name

  _progName = strdup("SunTest");

  return;

}

// destructor

SunTest::~SunTest()

{

  
}

//////////////////////////////////////////////////
// Run

int SunTest::Run()
{

  SunPosn spos;

  for (double lat = -90.0; lat <= 90.0; lat++) {
    for (double lon = 0.0; lon <= 360.0; lon++) {

      time_t tnow = time(NULL);
      DateTime dnow(tnow);
      double now = (double) tnow;
      
      spos.setLocation(lat, lon, 0.0);

      double el0, az0;
      double el1, az1;
      double el2, az2;
      spos.computePosn(now, el0, az0);
      spos.computePosnNova(now, el1, az1);
      spos.computePosnOld(now, el2, az2);
      
      fprintf(stderr,
              "%.4d %.2d %.2d %.2d %.2d %.2d || %7.3f %7.3f || "
              "%7.3f %7.3f || %7.3f %7.3f || %7.3f %7.3f\n",
              dnow.getYear(),
              dnow.getMonth(),
              dnow.getDay(),
              dnow.getHour(),
              dnow.getMin(),
              dnow.getSec(),
              lat, lon,
              el0, az0,
              el1, az1,
              el2, az2);
              


    }
  }

  return 0;

}


