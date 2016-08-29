/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright (c) 1992, UCAR
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 ** All rights reserved. Licenced use only.
 ** Do not copy or distribute without authorization
 ** 1993/3/5 16:31:9
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/****************************************************************************
 * set_derived_params()
 *
 * Sets those params which are derived from the main ones.
 *
 * Mike Dixon  RAP NCAR Boulder CO USA
 *
 * March 1997
 *
 ****************************************************************************/

#include "MDV_server.hh"

void set_derived_params(void)

{

  if (Glob->params.malloc_debug_level > 0) {
    umalloc_debug(Glob->params.malloc_debug_level);
  }

  if (!Glob->params.realtime_avail) {
    Glob->params.use_realtime_file = (tdrp_bool_t) FALSE;
  }

  if (Glob->params.projection == PROJ_LATLON) {
    Glob->params.projection = (MDV_server_projection) PJG_LATLON;
  } else {
    Glob->params.projection = (MDV_server_projection) PJG_FLAT;
  }

  return;

}
