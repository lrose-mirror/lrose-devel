/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright (c) 1992, UCAR
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** Do not copy or distribute without authorization
 ** 1993/3/6 19:43:44
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*****************************************************************
 * TIDY_AND_EXIT : Traps signals so as to die gracefully 
 *
 * Mike Dixon, RAP, NCAR, Boulder, Co, USA, 80307
 *
 * March 1997
 */

#include "MDV_server.hh"

void tidy_and_exit(int sig)

{

  /*
   * unregister with mappers
   */

  unregister_server();
  PMU_auto_unregister();

  exit(sig);
  
}

