/***************
 * read_apa()
 *
 * Reads in the .apa header file
 *
 * Mike Dixon, Bethany Hobson April 1995
 *
 * RAP, NCAR, Boulder, CO, 80307
 */

#include "german2class.h"
#include <ctype.h>

static char *read_beyond_colon(FILE *apa, char *line);

int read_apa(char *apa_name,
	     double *lat, double *lon, double *ht,
	     char *NS, char *EW,
	     long *rs_number, long *computing_freq,
	     date_time_t *start_time,
	     double *ptu_identified,
	     char *gc_corr,
	     char *wind_mode,
	     char *excluded_sta)

{

  FILE *apa;

  char line[BUFSIZ];
  char *ptr;

  int i;

  /*
   * open apa file
   */

  if ((apa = fopen(apa_name, "r")) == NULL) {
    fprintf(stderr, "Cannot open apa file\n");
    perror(apa_name);
    return (-1);
  }

  /*
   * Line 1 - station position
   */

  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (-1);
  }

  if (sscanf(line, "Station: %lg %s %lg %s %lg m",
	     lat, NS, lon, EW, ht) != 5) {
    fprintf(stderr, "ERROR decoding apa line 1\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 2
   */

  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (-1);
  }

  /*
   * clear non-digits
   */

  for (i = 0; i < strlen(line) - 1; i++) {
    if(!isdigit(line[i])) {
      line[i] = ' ';
    }
  }

  if (sscanf(line, "%d %d %d %d %d",
	     &start_time->year,
	     &start_time->month,
	     &start_time->day,
	     &start_time->hour,
	     &start_time->min) != 5) {
    fprintf(stderr, "ERROR decoding apa line 2\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  start_time->sec = 0;
  
  /*
   * line 3
   */

  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (-1);
  }
  
  if (sscanf(line, "Rs-number: %ld", rs_number) != 1) {
    fprintf(stderr, "ERROR decoding apa line 3\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 4
   */

  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (-1);
  }
  
  if (sscanf(line, "Computing density: %ld", computing_freq) != 1) {
    fprintf(stderr, "ERROR decoding apa line 4\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 5
   */

  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (-1);
  }
  
  if (sscanf(line, "PTU identified: %lg", ptu_identified) != 1) {
    fprintf(stderr, "ERROR decoding apa line 5\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 6
   */

  ptr = read_beyond_colon(apa, line);
  
  if (ptr != NULL) {
    strncpy(gc_corr, ptr, LABLEN-1);
    gc_corr[LABLEN-1] = '\0';
    gc_corr[strlen(gc_corr)-1] = '\0';
  } else {
    fprintf(stderr, "ERROR decoding apa line 6\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 7
   */

  ptr = read_beyond_colon(apa, line);

  if (ptr != NULL) {
    strncpy(wind_mode, ptr, LABLEN-1);
    wind_mode[LABLEN-1] = '\0';
    wind_mode[strlen(wind_mode) - 1] = '\0';
  } else {
    fprintf(stderr, "ERROR decoding apa line 7\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * line 8
   */

  ptr = read_beyond_colon(apa, line);

  if (ptr != NULL) {
    strncpy(excluded_sta, ptr, LABLEN-1);
    excluded_sta[LABLEN-1] = '\0';
    excluded_sta[strlen(excluded_sta) - 1] = '\0';
  } else {
    fprintf(stderr, "ERROR decoding apa line 8\n");
    fprintf(stderr, ">> %s <<", line);
    fclose(apa);
    return (-1);
  }
  
  /*
   * close file
   */

  fclose(apa);
  return (0);

}

/*
 * read_beyond_colon()
 * 
 * gets a line, returns pointer to first non-space
 * character beyond colon. Also, strips C-M.
 */

static char *read_beyond_colon(FILE *apa, char *line)

{

  int i;
  char *ptr;
  
  /*
   * read in line
   */
  
  if (fgets(line, BUFSIZ, apa) == NULL) {
    fclose(apa);
    return (NULL);
  }

  /*
   * remove Ctrl-M
   */

  for (i = 0; i < strlen(line); i++) {
    if (line[i] == 13) {
      line[i] = ' ';
    }
  }
  
  /*
   * advance beyond colon
   */

  ptr = strchr(line, ':');
  ptr++;
  while (*ptr == ' ' || *ptr == '\t') {
    ptr++;
  }
  
  return (ptr);
  
}
