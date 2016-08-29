#! /usr/local/bin/perl

#*************************************************************************
# JULIAN_DATE: Calc the Julian calendar Day Number
# As Taken from Computer Language- Dec 1990, pg 58
#

sub ujulian_date {

  local($year) = $_[0];
  local($month) = $_[1];
  local($day) = $_[2];
  
#
# correct for negative year
#

  if ($year > 0) {
    $yr_corr = 0.0;
  } else {
    $yr_corr = 0.75;
  }

  if($month <= 2) {
    $year--;
    $month += 12;
  }

  $b = 0;

#
# Cope with Gregorian Calendar reform
#

  if($year * 10000.0 + $month * 100.0 + $day >= 15821015.0) {
    $a = $year / 100;
    $b = 2 - $a + $a / 4;
  }
	
  $jul_day = int ((365.25 * $year - $yr_corr) +
		  int ((30.6001 * ($month + 1))) + 
		  $day + 1720994 + $b);

}

sub uunix_time {

  local($year) = $_[0];
  local($month) = $_[1];
  local($day) = $_[2];
  local($hour) = $_[3];
  local($min) = $_[4];
  local($sec) = $_[5];

  $jday = &ujulian_date($year, $month, $day);

  $jdays = $jday - 2440587;

  $u_time = ($jdays * 86400) + ($hour * 3600) + ($min * 60) + $sec;

  return ($u_time);

}

#
# main routine
#

#
# main routine
#
# check usage
#

($prog = $0) =~ s%.*/%%;

$usage = "Usage : $prog file_path. Must be run from cdata dir";
 
if (@ARGV != 1) {

  print("$usage\n");
  exit(-1);

}

$active_file_name = shift(@ARGV);

#
# get previous seq num
#

if (open (CURR, "current_file_index") == 0) {
  printf ("Cannot open 'current_file_index'\n");
  print("$usage\n");
  exit(-1);
}

$prev_seq = <CURR>;
$seq = $prev_seq + 1;

printf (STDOUT "prev_seq, seq: %d, %d\n", $prev_seq, $seq);

close (CURR);

#
# get the date and time of the file to be touched
#

($year, $month, $day, $hour, $min, $sec, $ext) = $active_file_name =~ m%(....)(..)(..)/(..)(..)(..)\.(...)%;

printf (STDOUT "date: %.4d/%.2d/%.2d_%.2d:%.2d:%.2d_%s\n",
       $year, $month,  $day, $hour, $min, $sec, $ext);

$unix_time = &uunix_time($year, $month, $day, $hour, $min, $sec);

printf (STDOUT "date: %.4d/%.2d/%.2d_%.2d:%.2d:%.2d_%s\n",
       $year, $month,  $day, $hour, $min, $sec, $ext);

printf (STDOUT "unix_time: %d\n", $unix_time);

#
# create backup file
#

system ('/bin/mv', "current_file_index", "current_file_index.old");

#
# write new file
#

if (open (CURR, ">tmp") == 0) {
  printf ("Cannot open 'current_file_index' for writing\n");
  exit(-1);
}

$exact_time = 1;
$n_forecasts = 0;

printf (CURR "%d\n", $seq);
printf (CURR "%d\n", $year);
printf (CURR "%d\n", $month);
printf (CURR "%d\n", $day);
printf (CURR "%d\n", $hour);
printf (CURR "%d\n", $min);
printf (CURR "%d\n", $sec);
printf (CURR "%d\n", $unix_time);
printf (CURR "%d\n", $exact_time);
printf (CURR "%s\n", $ext);
printf (CURR "%s\n", "unknown");
printf (CURR "%s\n", "unknown");
printf (CURR "%d\n", "$n_forecasts");

close (CURR);

#
# rename
#

system ('/bin/mv', "tmp", "current_file_index");

exit(0);







