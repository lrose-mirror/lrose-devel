/***********************************************************************
 * chaos.c
 *
 * Mike Dixon  RAP NCAR Boulder CO USA
 *
 * August 1996
 *
 ************************************************************************/

#include <stdio.h>

static void print_usage(void)

{
  fprintf(stderr, "Usage: chaos u x\n");
}

int main(int argc, char **argv)

{

  int forever = 1;
  int count = 0;
  double u, x, z;

  if (argc != 3) {
    print_usage();
    return (-1);
  }
  
  if (sscanf(argv[1], "%lg", &u) != 1) {
    print_usage();
    return (-1); 
  }

  if (sscanf(argv[2], "%lg", &x) != 1) {
    print_usage();
    return (-1);
  }

  fprintf(stderr, "u, x: %g, %g\n", u, x);

  while (forever) {

    fprintf(stderr, "%8d %20g\n", count, x);
    x = (u * x) * (1.0 - x);
    count++;
    
  }

  return (0);

}

