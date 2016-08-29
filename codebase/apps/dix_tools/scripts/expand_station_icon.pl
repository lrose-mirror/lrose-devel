#! /usr/local/bin/perl

#
# Expands station pos value to diamond icon in ZEB map format
#

$delta = 0.002;
$ncoords = 10;

while ($line = <>) {

  ($ref_lat, $ref_lon) = ($line =~ m%\s*(\S+)\s+(\S+).*%);

  printf(STDOUT "  %d  %.4f  %.4f  %.4f  %.4f ! station icon\n",
	 $ncoords,
	 $ref_lat - $delta,
	 $ref_lat + $delta,
	 $ref_lon - $delta,
	 $ref_lon + $delta);
	 
  printf(STDOUT "    %.4f  %.4f  ",
	 $ref_lat + $delta, $ref_lon);

  printf(STDOUT "%.4f  %.4f  ",
	 $ref_lat, $ref_lon + $delta);

  printf(STDOUT "%.4f  %.4f  ",
	 $ref_lat - $delta, $ref_lon);

  printf(STDOUT "%.4f  %.4f  ",
	 $ref_lat, $ref_lon - $delta);

  printf(STDOUT "\n");

  printf(STDOUT "    %.4f  %.4f  ",
	 $ref_lat + $delta, $ref_lon);

  printf(STDOUT "\n");

}

