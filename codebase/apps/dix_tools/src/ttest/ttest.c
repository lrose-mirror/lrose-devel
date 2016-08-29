/***********************************************************************
 * ttest.c
 *
 * Mike Dixon  RAP NCAR Boulder CO USA
 *
 * August 1996
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <toolsa/udatetime.h>

#ifdef SUNOS4
#define RAND_MAX 0x7fffffff
#endif

#define JAN_1_1970 2440587

static void _uconvert_from_utime(date_time_t *date_time)
{

  time_t unix_time;
  long day;
  int time_of_day;
  
  unix_time = date_time->unix_time;

  time_of_day = (unix_time % 86400);
  day = (unix_time / 86400);
  if (unix_time < 0 && time_of_day != 0) {
    day--;
    time_of_day += 86400;
  }
  
  ucalendar_date((JAN_1_1970 + day),
		 &date_time->day,
		 &date_time->month,
		 &date_time->year);
  
  date_time->hour = time_of_day / 3600;
  date_time->min = (time_of_day / 60) - (date_time->hour * 60);
  date_time->sec = time_of_day % 60;

}
 
int main(int argc, char **argv)

{

  date_time_t dtime;

  if (argc != 7) {
    fprintf(stderr, "Usage: ttest year month day hour min sec\n");
    exit (-1);
  }

  dtime.year = atoi(argv[1]);
  dtime.month = atoi(argv[2]);
  dtime.day = atoi(argv[3]);
  dtime.hour = atoi(argv[4]);
  dtime.min = atoi(argv[5]);
  dtime.sec = atoi(argv[6]);

  uconvert_to_utime(&dtime);
  _uconvert_from_utime(&dtime);

  fprintf(stderr, "%.4d %.2d %.2d %.2d %.2d %.2d %d\n",
	  dtime.year,
	  dtime.month,
	  dtime.day,
	  dtime.hour,
	  dtime.min,
	  dtime.sec,
	  dtime.unix_time);

}

