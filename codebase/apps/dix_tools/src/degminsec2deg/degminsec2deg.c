/***********************************************************************
 * degminsec2deg.c
 *
 * Mike Dixon  RAP NCAR Boulder CO USA
 *
 * July 2001
 *
 * converts deg,min,sec to decimal deg
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>

static void usage()
{
  fprintf(stderr, "Usage: degminsec2deg deg min sec\n");
}

int main(int argc, char **argv)

{

  double deg, min, sec, dec_deg;

  if (argc != 4) {
    usage();
    return -1;
  }

  if (sscanf(argv[1], "%lg", &deg) != 1) {
    usage();
    return -1;
  }
  
  if (sscanf(argv[2], "%lg", &min) != 1) {
    usage();
    return -1;
  }
  
  if (sscanf(argv[3], "%lg", &sec) != 1) {
    usage();
    return -1;
  }

  dec_deg = deg + min / 60.0 + sec / 3600.0;

  fprintf(stderr, "%g deg %g min %g sec = %.6f deg\n",
	  deg, min, sec, dec_deg);

  return 0;

}
