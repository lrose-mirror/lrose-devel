#! /bin/env perl

#
# script to purge files in a target directory using an event list file
# to determine event start and end times
# 

sub print_usage {

  printf(STDERR "Usage : $prog event_list target_dir [-p]\n");
  printf(STDERR "[-p] - only prints list to be deleted, no deletion\n");

}

#
# check usage
#

($prog = $0) =~ s%.*/%%;
 
if (@ARGV < 2) {
  &print_usage();
  exit(-1);
}

$event_list = shift(@ARGV);
$target_dir = shift(@ARGV);

$mode = "delete";

if (@ARGV > 0) {
  $mode = shift(@ARGV);
  if ($mode ne "-p") {
    &print_usage();
    exit(-1);
  }
  $mode = "print";
}

#
# read in events
#

if (open (EVENTS, $event_list) == 0) {
  printf ("Cannot open $event_list\n");
  &print_usage();
  exit(-1);
}

$n_events = 0;

while ($line = <EVENTS>) {
  
#
# only process lines which conform to the params spec
#
# "start yyyy mm dd hh mm ss end yyyy mm dd hh mm ss"
#

  if (!($line =~ /^start\s+\d+\s+\d+\s+\d+\s+\d+\s+\d+\s+\d+\s+end\s+\d+\s+\d+\s+\d+\s+\d+\s+\d+\s+\d+/)) {
    next;
  }

#
# read in start and end times
#

  ($start_year[$n_events], $start_month[$n_events], $start_day[$n_events],
   $start_hour[$n_events], $start_min[$n_events], $start_sec[$n_events],
   $end_year[$n_events], $end_month[$n_events], $end_day[$n_events],
   $end_hour[$n_events], $end_min[$n_events], $end_sec[$n_events]) =
     ($line =~ m%^\s*\S*\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)\s*\S*\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)\s*(\S*)%);

  $start_str[$n_events] = ($start_year[$n_events] .
			   $start_month[$n_events] .
			   $start_day[$n_events] . "/" .
			   $start_hour[$n_events] .
			   $start_min[$n_events] .
			   $start_sec[$n_events]);

  $end_str[$n_events] = ($end_year[$n_events] .
			 $end_month[$n_events] .
			 $end_day[$n_events] . "/" .
			 $end_hour[$n_events] .
			 $end_min[$n_events] .
			 $end_sec[$n_events]);

  $n_events++;

} # while

close(EVENTS);

printf(STDOUT "\nEvent list in file %s\n\n", $event_list);

for ($i = 0; $i < $n_events; $i++) {
  printf(STDOUT "Event %d ", $i);
  printf(STDOUT "start %s %s %s %s %s %s ",
	 $start_year[$i], $start_month[$i], $start_day[$i],
	 $start_hour[$i], $start_min[$i], $start_sec[$i]);
  printf(STDOUT "end %s %s %s %s %s %s\n",
	 $end_year[$i], $end_month[$i], $end_day[$i],
	 $end_hour[$i], $end_min[$i], $start_sec[$i]);
  printf(STDOUT "start_str %s\n", $start_str[$i]);
  printf(STDOUT "end_str %s\n", $end_str[$i]);
}

#
# get list of files in target dirs
#

chdir $target_dir;

printf (STDOUT "%s\n", $target_dir);

open(TARGET_DIR_LIST, "ls |");

while ($sub_dir = <TARGET_DIR_LIST>) {

  if (length($sub_dir) == 9) {

    chop $sub_dir;

    open(TARGET_FILE_LIST, "ls $sub_dir/??????.* |");
    
    $n_target_files = 0;
    
    while ($target_file = <TARGET_FILE_LIST>) {
      
      chop $target_file;
      $target_file_list[$n_target_files] = $target_file;
      $target_purge[$n_target_files] = "false";
      $n_target_files++;
      
    }
    
    for ($i = 0; $i < $n_target_files; $i++) {

      $file_str = substr($target_file_list[$i], 0, 15);
      $delete_file = true;
      for ($j = 0; $j < $n_events; $j++) {
	if ($file_str ge $start_str[$j] && $file_str le $end_str[$j]) {
	  $delete_file = false;
	}
      }

      $target_file = $target_dir . "/" . $target_file_list[$i];

      if ($mode eq "delete") {
	
	if ($delete_file eq true) {
	  printf(STDOUT "Deleting: %s\n", $target_file);
	  $res = unlink($target_file);
	  print $res "\n";
	} else {
	  printf(STDOUT "Saving:   %s\n", $target_file);
	}

      } else {

	if ($delete_file eq true) {
	  printf(STDOUT "To be deleted: %s\n", $target_file);
	} else {
	  printf(STDOUT "To be saved:    %s\n", $target_file);
	}

      }
      
    }
    
    close (TARGET_FILE_LIST);

  } # if (length($sub_dir) == 9) 

} # while ($sub_dir = <TARGET_DIR_LIST>) 

close (TARGET_DIR_LIST);

exit (0);

