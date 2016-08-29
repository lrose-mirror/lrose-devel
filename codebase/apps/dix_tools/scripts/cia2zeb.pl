#! /usr/local/bin/perl

$| = 1;

while ($line = <>) {

  ($id1, $id2, $npoints, $id3) = ($line =~ m%(\d+)\s*(\d+)\s*(\d+)\s*(\d+).*%);

  $min_lat = 1000;
  $max_lat = -1000;
  $min_lon = 1000;
  $max_lon = -1000;

  for ($i = 0; $i < $npoints; $i++) {

    $line = <>;
  
    ($lat_deg, $lat_min, $lat_sec, $lon_deg, $lon_min, $lon_sec) = ($line =~ m%(..)(..)(..)\D(...)(..)(..).*%);
    $lat = $lat_deg + $lat_min / 60.0 + $lat_sec / 3600.0;
    $lon = $lon_deg + $lon_min / 60.0 + $lon_sec / 3600.0;

    if ($lat < $min_lat) {
      $min_lat = $lat;
    }
  
    if ($lat > $max_lat) {
      $max_lat = $lat;
    }
  
    if ($lon < $min_lon) {
      $min_lon = $lon;
    }
  
    if ($lon > $max_lon) {
      $max_lon = $lon;
    }
  
    $lat_array[$i] = $lat;
    $lon_array[$i] = $lon;

  }

  printf(STDOUT "%d %.4f %.4f %.4f %.4f\n",
	 $npoints * 2, $min_lat, $max_lat, $min_lon, $max_lon);

  $line_count = 0;

  for ($i = 0; $i < $npoints; $i++) {

    printf(STDOUT " %.4f %.4f", $lat_array[$i], $lon_array[$i]);

    $line_count++;

    if ($line_count == 4) {
      printf(STDOUT "\n");
      $line_count = 0;
    }

  }

  if ($line_count != 0) {
    printf(STDOUT "\n");
  }

}

