/***************
 * process_file()
 *
 * Processes a set of .apa and .cal files to
 * producs a .class file
 *
 * Mike Dixon, Bethany Hobson April 1995
 *
 * RAP, NCAR, Boulder, CO, 80307
 */

#include "german2class.h"

int process_file(char *apa_name, char *cal_name, char *class_name)

{

  long rs_number;
  long computing_freq;

  double lat, lon, ht;
  double ptu_identified;
  char NS[32], EW[32];
  char gc_corr[LABLEN];
  char wind_mode[LABLEN];
  char excluded_sta[LABLEN];

  date_time_t start_time;

  /*
   * read in header
   */

  if (read_apa(apa_name,
	       &lat, &lon, &ht, NS, EW,
	       &rs_number, &computing_freq, &start_time,
	       &ptu_identified, gc_corr, wind_mode, excluded_sta)) {
    return (-1);
  }

  fprintf(stderr, "Lat, lon, ht: %g %s, %g %s, %g m\n",
	  lat, NS, lon, EW, ht);
  fprintf(stderr, "Start_time: %s\n", utimestr(&start_time));
  fprintf(stderr, "rs_number: %ld\n", rs_number);
  fprintf(stderr, "computing_freq: %ld\n", computing_freq);
  fprintf(stderr, "ptu_identified: %g\n", ptu_identified);
  fprintf(stderr, "Gc_corr: %s\n", gc_corr);
  fprintf(stderr, "Wind mode: %s\n", wind_mode);
  fprintf(stderr, "Excluded stations: %s\n", excluded_sta);

  /*
   * write class file
   */

  if (write_class(cal_name, class_name,
		  lat, lon, ht, NS, EW,
		  rs_number, computing_freq, &start_time,
		  ptu_identified, gc_corr, wind_mode, excluded_sta)) {
    return (-1);
  }
  
  return (0);

}

