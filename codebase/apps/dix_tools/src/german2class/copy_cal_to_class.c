/***************
 * copy_cal_to_class()
 *
 * Copies data from .cal file to .class file
 *
 * Mike Dixon, Bethany Hobson April 1995
 *
 * RAP, NCAR, Boulder, CO, 80307
 */

#include "german2class.h"
#include <rapmath/umath.h>

double pr_uwnd(double v, double dir);
double pr_vwnd(double v, double dir);
double pr_dewpt(double tdry, double rh_perc);
double pr_relh(double t, double td);

int copy_cal_to_class(char *cal_name, FILE *class)

{

  FILE *cal;

  char line[BUFSIZ];
  int minute, second;
  int secs_since_launch;
  
  double alt, pres, tdry, dewpt, rh, wspd, wdirn;
  double u, v;

  /*
   * open cal file
   */

  if ((cal = fopen(cal_name, "r")) == NULL) {
    fprintf(stderr, "Cannot open cal file\n");
    perror(cal_name);
    return (-1);
  }

  while (!feof(cal)) {
    
    if (fgets(line, BUFSIZ, cal) != NULL) {
      
      if (sscanf(line, "%d%d%lg%lg%lg%lg%lg%lg",
		 &minute, &second,
		 &alt, &pres, &tdry, &rh, &wdirn, &wspd) != 8) {
	fprintf(stderr, "ERROR scanning .cal line\n");
	perror(line);
	fclose(cal);
	return (-1);
      }

      secs_since_launch = minute * 60 + second;

      if (wspd == 9999.9) {
	u = 999.0;
	v = 999.0;
	wspd = 999.0;
	wdirn = 999.0;
      } else {
	u = pr_uwnd(wspd, wdirn);
	v = pr_vwnd(wspd, wdirn);
      }

      dewpt = pr_dewpt(tdry, rh);

      fprintf(class,
	      "%d  %.1f  %.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %g  "
	      "99.0  999.0  999.0  999.0  999.0  %g  "
	      "99.0  99.0  99.0  99.0  99.0  99.0\n", 
	      secs_since_launch, pres, tdry, dewpt, rh, u, v, wspd, wdirn,
	      alt);

    }

  }

  /*
   * close file
   */

  fclose(cal);
  return (0);

}

