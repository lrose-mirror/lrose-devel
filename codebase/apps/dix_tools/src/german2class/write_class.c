/***************
 * write_class()
 *
 * Writes the class file
 *
 * Mike Dixon, Bethany Hobson April 1995
 *
 * RAP, NCAR, Boulder, CO, 80307
 */

#include "german2class.h"

int write_class(char *cal_name,
		char *class_name,
		double lat, double lon, double ht,
		char *NS, char *EW,
		long rs_number, long computing_freq,
		date_time_t *start_time,
		double ptu_identified,
		char *gc_corr,
		char *wind_mode,
		char *excluded_sta)

{

  FILE *class;

  int ilat, ilon;
  double lat_min, lon_min;

  /*
   * compute lat and lon params
   */

  ilat = (int) lat;
  ilon = (int) lon;

  lat_min = (lat - ilat) * 60.0;
  lon_min = (lon - ilon) * 60.0;

  if (!strcmp(NS, "S")) {
    lat *= -1.0;
  }

  if (!strcmp(EW, "W")) {
    lon *= -1.0;
  }

  /*
   * open class file
   */

  if ((class = fopen(class_name, "w")) == NULL) {
    fprintf(stderr, "Cannot open class file\n");
    perror(class_name);
    return (-1);
  }

  /*
   * write header
   */

  fprintf(class, "Data Type:                         "
	  "CLASS %ld SECOND DATA\n",
	  computing_freq);
  fprintf(class, "Project ID:                        "
	  "GERMAN MET SERVICE\n");
  fprintf(class, "Launch Site Type/Site ID:          "
	  "MOBILE, GERMAN [0]\n");
  fprintf(class, "Launch Location (lon,lat,alt):     "
	  "%d %.2f'%s, %d %.2f'%s, %g, %g, %g\n",
	  ilon, lon_min, EW, ilat, lat_min, NS, lon, lat, ht);
  fprintf(class, "GMT Launch Time (y,m,d,h,m,s):     "
	  "%d, %d, %d, %d:%d:%d\n",
	  start_time->year,
	  start_time->month,
	  start_time->day,
	  start_time->hour,
	  start_time->min,
	  start_time->sec);
  fprintf(class, "Sonde Type/ID/Sensor ID/Tx Freq:   "
	  "UNKNOWN, %ld, UNKNOWN, UNKNOWN\n", rs_number);
  fprintf(class, "Met Processor/Met Smoothing:       "
	  "UNKNOWN, %ld SECONDS\n", computing_freq); 
  fprintf(class, "Winds Type/Processor/Smoothing:    "
	  "%s, UNKNOWN, UNKNOWN\n", wind_mode);
  fprintf(class, "Pre-launch Surface Obs Source:     "
	  "UNKNOWN\n");
  fprintf(class, "System Operator/Comments:          "
	  "GC Corrections - %s, PTU identified - %g %%,"
	  " Excluded stations - %s\n",
	  gc_corr, ptu_identified, excluded_sta);
  fprintf(class, "/\n");
  fprintf(class, "/\n");
  fprintf(class, " Time  Press  Temp  Dewpt  RH    Uwind  Vwind  Wspd  Dir   dZ       Lon       Lat     Rng   Ang    Alt    Qp   Qt   Qh   Qu   Qv   Quv\n");
  fprintf(class, "  sec    mb     C     C     %%     m/s    m/s   m/s   deg   m/s      deg       deg      km   deg     m     mb   C    %%    m/s  m/s  m/s\n");
  fprintf(class, "------ ------ ----- ----- ----- ------ ------ ----- ----- ----- ---------- --------- ----- ----- ------- ---- ---- ---- ---- ---- ----\n");

  /*
   * read in cal data and write to class
   */

  copy_cal_to_class(cal_name, class);

  /*
   * close file
   */

  fclose(class);
  return (0);

}

