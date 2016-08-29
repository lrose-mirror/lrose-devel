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
// WordSizeCheck.h
//
// WordSizeCheck object
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// April 1998
//
///////////////////////////////////////////////////////////////

#ifndef WordSizeCheck_H
#define WordSizeCheck_H

typedef struct {
  char char_field_1;
  short short_field_1;
  char char_field_2;
  int int_field_1;
  long long_field_1;
  char char_field_3;
  double double_field_1;
} test_struct_t;

class WordSizeCheck {
  
public:

  // constructor

  WordSizeCheck (int argc, char **argv);

  // destructor
  
  ~WordSizeCheck();

  // run 

  int Run();

  // data members

  int OK;

protected:
  
private:


};

#endif
