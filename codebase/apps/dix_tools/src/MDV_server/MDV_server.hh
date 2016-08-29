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

/************************************************************************
 * MDV_server.hh
 *
 */

#include <toolsa/umisc.h>
#include <toolsa/sockutil.h>
#include <toolsa/str.h>
#include <toolsa/pjg.h>
#include <toolsa/pmu.h>
#include <toolsa/smu.h>
#include <cidd/cdata_util.h>
#include <mdv/MdvRead.hh>
#include <rapmath/umath.h>
#include <tdrp/tdrp.h>
#include "MDV_server_tdrp.h"

/*
 * DATA INFO NOT AVAILABLE IN FILES - (IMPLIED)
 */

#define VALID_TIME 10         /* seconds that live data remains valid */

#define DATA_ORDER 1     /* 1 = Y increases UP, (right hand)
			  * 0 = Down (left hand) */
#define RADAR_CONST 1.0
#define NOISE_THRESH 5.0

/*
 * global data struct
 */

typedef struct {

  char *prog_name;                  /* the applications name */


  si32 time_last_request;        /* time at which last request for data
				  * was made */

  si32 n_data_requests;          /* number of data requests */

  si32 latest_data_time;

  double data_to_com_delta_x;    /* x diff between the data origin and
				  * the command origin */
  
  double data_to_com_delta_y;    /* y diff between the data origin and
				  * the command origin */
  
  TDRPtable *table;              /* TDRP parsing table */

  MDV_server_tdrp_struct params; /* parameter struct */

} global_t;


/*
 * declare the global structure locally in the main,
 * and as an extern in all other routines
 */

#ifdef MAIN

global_t *Glob = NULL;

#else

extern global_t *Glob;

#endif

/*
 * prototypes
 */

extern int find_best_file(si32 min_time,
			  si32 target_time,
			  si32 max_time,
			  si32 ntop_dir,
			  char **top_dir,
			  char *file_path);

extern void file_search_debug(int dflag);

extern ui08 *get_grid_data(cdata_comm_t *com,
			   cdata_reply_t *reply,
			   cdata_info_t *info,
			   MdvRead &mdv);

extern int get_latest_file(si32 ntop_dir,
			   char **top_dir,
			   char *file_path);

extern void operate(void);

extern void parse_args(int argc,
		       char **argv,
		       int *check_params_p,
		       int *print_params_p,
		       tdrp_override_t *override,
		       char **params_file_path_p);

extern int read_mdv(MdvRead &mdv,
		    cdata_comm_t *com);
     
extern void register_server_init(void);

extern void set_derived_params(void);

extern void tidy_and_exit(int sig);

extern void unregister_server(void);

