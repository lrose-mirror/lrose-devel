/***************
 * csu2class.c
 *
 * Program to convert German sounding files to class format.
 *
 * Mike Dixon, Bethany Hobson April 1995
 *
 * RAP, NCAR, Boulder, CO, 80307
 */

#include "german2class.h"

int main(int argc, char **argv)
     
{

  int nfiles;
  int i;
  int ret;
  char **apa_file_names;
  char *ext_pt;
  char cal_file_name[MAX_PATH_LEN];
  char class_file_name[MAX_PATH_LEN];

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [.apa file names]\n", argv[0]);
    exit (-1);
  }
  
  nfiles = argc - 1;
  apa_file_names = argv + 1;

  for (i = 0; i < nfiles; i++) {

    fprintf(stderr, "===============================================\n");

    fprintf(stderr, "Processing file %s\n", apa_file_names[i]);
    
    /*
     * compute cal file name
     */

    strncpy(cal_file_name, apa_file_names[i], MAX_PATH_LEN);
    ext_pt = strrchr(cal_file_name, '.');
    *ext_pt = '\0';
    strcat(cal_file_name, ".cal");
    
    fprintf(stderr, " ..... and file %s\n", cal_file_name);

    /*
     * compute class file name
     */

    strncpy(class_file_name, apa_file_names[i], MAX_PATH_LEN);
    ext_pt = strrchr(class_file_name, '.');
    *ext_pt = '\0';
    strcat(class_file_name, ".class");
    
    fprintf(stderr, " ..... and produce file %s\n", class_file_name);

    ret = process_file(apa_file_names[i], cal_file_name, class_file_name);

    if (ret == -1) {
      fprintf(stderr, "Cannot generate file %s\n", class_file_name);
    }

  } /* i */
  
  exit (0);

}

