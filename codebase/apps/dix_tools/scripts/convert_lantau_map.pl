#! /usr/local/bin/perl

while ($line = <>) {

  if ($line =~ /#/) {
    print(STDOUT "$line");
  } else {
    ($ilat, $ilon) = ($line =~ m%(\d+)\s(\d+).*%);
    $lat = ($ilat / 145.0) * 0.1666667 + 22.16666667;
    $lon = ($ilon / 135.0) * 0.1666667 + 113.8333333;
    printf(STDOUT "%.4f %.4f\n", $lat, $lon);
  }
    
}

