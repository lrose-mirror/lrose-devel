/***********************************************************************
 * swap_si32.c
 *
 * Mike Dixon  RAP NCAR Boulder CO USA
 *
 * April 1998
 *
 * Swaps a single si32 as input on the command line
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <toolsa/umisc.h>
#include <dataport/swap.h>

int main(int argc, char **argv)

{

  si32 unswapped, swapped;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s integer-to-swap\n", argv[0]);
    exit(-1);
  }

  unswapped = atoi(argv[1]);
  swapped = SWAP_si32(unswapped);

  fprintf(stdout, "Unswapped: %d, swapped %d\n",
	  (int) unswapped, (int) swapped);

  return (0);

}

