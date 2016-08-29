/*
 * Read 2-byte hex dump in ascii as stdin, put our chars as
 * stdout.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)

{

  int hex_val;
  int byte1;
  int byte2;

  if (argc != 1) {
    fprintf(stderr, "Usage: hex2char < stdin > stdout\n");
    fprintf(stderr, "hex2char converts 16 bit hex data to chars\n"
	    "  separated by spaces.\n");
    exit (-1);
  }

  while (fscanf(stdin, "%x", &hex_val) == 1) {

    byte1 = hex_val & 0xff;
    byte2 = (hex_val >> 8) & 0xff;

    fprintf(stdout, "%c %c ", byte2, byte1);
    
  }

  return (0);

}
