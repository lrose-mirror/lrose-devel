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
// QtTest.cc
//
// QtTest object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// July 2006
//
///////////////////////////////////////////////////////////////
//
// QtTest is a simple test app for Qt
//
///////////////////////////////////////////////////////////////

#include "QtTest.hh"
#include "Params.hh"
#include <string>
#include <iostream>
#include <toolsa/pjg.h>
#include <toolsa/toolsa_macros.h>
#include <dataport/bigend.h>
#include <rapformats/Edr.hh>
#include <Mdv/MdvxProj.hh>
#include <QApplication>
#include <QPushButton>
#include <QFont>
#include "GameBoard.hh"

using namespace std;

// Constructor

QtTest::QtTest(int argc, char **argv) :
  _args("QtTest"),
  _argc(argc),
  _argv(argv)

{

  OK = 1;

  // set programe name

  _progName = strdup("QtTest");
  
  // get command line args
  
  if (_args.parse(argc, (const char **) argv)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with command line args" << endl;
    OK = 0;
    return;
  }

  // load TDRP params from command line
  
  char *paramsPath = (char *) "unknown";
  if (_params.loadFromArgs(argc, argv,
			   _args.override.list,
			   &paramsPath)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "Problem with TDRP parameters." << endl;
    OK = false;
    return;
  }

}

// destructor

QtTest::~QtTest()

{

  
}

//////////////////////////////////////////////////
// Run

int QtTest::Run()
{
  
  QApplication app(_argc, _argv);
  GameBoard board;
  board.setGeometry(100, 100, 500, 355);
  board.show();
  return app.exec();

//   QApplication app(_argc, _argv);
  
//   QPushButton quit("Quit");
//   quit.resize(75, 30);
//   quit.setFont(QFont("Times", 18, QFont::Bold));
  
//   QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));
  
//   quit.show();
//   return app.exec();
  
}

