#! /local/bin/perl
#
# ch_awpg_inc.pl
#
# Function:
#	Perl script to change source file references to AWPG include
#       files. The change is mostly to add subdirectory paths but 
#       there are some name changes. The include file references will
#       also be changed to use angle brackets (<>) instead of quotes
#       ("").
#
# Usage:
#       ch_awpg_inc.pl [-m] [-h] <list of source files>
#
#       -h : help, print usage
#       -m : modify the files (default is just to check and print pattern matches)
#
# Input:
#       Source files (.c and .h)
#
# Output:
#       Copies the input sourc file into <file>.bak and puts the 
#       filtered file into <file>.
#
# Dependencies:
#	Perl must be available in the location at the top of this file.
# 	
# Author: Deirdre Garvey - NCAR/RAP/ESG		17-NOV-1993
#
##
#---------------------------------------------------------------------------------
#
# Need the Perl getopts library routine
#

require 'getopts.pl';

#
# Get command line options
#

&Getopts('hmd'); 

if ($opt_h) {
   die "Usage: $0 [-m] <files> ...\n";
}

$checkonly = 1;
if ($opt_m) {
   $checkonly = 0;
}

#
# Echo the current directory
#

print STDERR "Current directory: $ENV{'PWD'}\n";

#
# Go through each file on the command line
#

FILE: foreach $filename (@ARGV) {

  # ----- open each file -----

  print(STDERR "\n");
  print(STDERR "Checking file: $filename\n");

  # open file for reading only

  if ($checkonly == 1) {
     if (!open(SRCFILE, $filename)) {
         print(STDERR "Cannot open source file $filename - continuing ... \n");
         next FILE;
     }
  } #endif

  # copy file to .bak file then read .bak file and write to file

  else {

     $bakfile = $filename . ".bak";
     system ('/bin/mv', $filename, $bakfile);

     if (!open(SRCFILE, $bakfile)) {
         print(STDERR "Cannot open source file $bakfile - continuing ... \n");
         next FILE;
     }

    if (!open(STDOUT, ">$filename")) {
         print(STDERR "Cannot open file $filename - continuing ... \n");
         next FILE;
     }
  } #end else

  #
  # ----- loop through the lines in the file -----
  #

  while ($line = <SRCFILE>) {

  # 
  # get the next line unless this line has an include directive
  #

  if ($line !~ /^#include/) {
     if ($checkonly != 1) {
         print(STDOUT $line);
     }
     next
  }

##  next unless ($line =~ /^#include/);

  #
  # change include location text
  #

  # ... cidd ...

  &dochange('"cdata_util.h"', '<cidd/cdata_util.h>');
  &dochange('<cdata_util.h>', '<cidd/cdata_util.h>');

  # ... display interface ...

  &dochange('"awpg_gui_mess.h"', '<display_interface/awpg_gui_mess.h>');
  &dochange('<awpg_gui_mess.h>', '<display_interface/awpg_gui_mess.h>');
  &dochange('"awpg_ds_mess.h"', '<display_interface/awpg_ds_mess.h>');
  &dochange('<awpg_ds_mess.h>', '<display_interface/awpg_ds_mess.h>');

  # ... data servers ...

  &dochange('"ds.h"', '<ds/ds.h>');
  &dochange('<ds.h>', '<ds/ds.h>');
  &dochange('"dsc.h"', '<ds/dsc.h>');
  &dochange('<dsc.h>', '<ds/dsc.h>');
  &dochange('"dsu.h"', '<ds/dsu.h>');
  &dochange('<dsu.h>', '<ds/dsu.h>');
  &dochange('"gds.h"', '<ds/gds.h>');
  &dochange('<gds.h>', '<ds/gds.h>');
  &dochange('"gds_xdr.h"', '<ds/gds_xdr.h>');
  &dochange('<gds_xdr.h>', '<ds/gds_xdr.h>');
  &dochange('"kav_pack.h"', '<ds/kav_pack.h>');
  &dochange('<kav_pack.h>', '<ds/kav_pack.h>');
  &dochange('"xdru.h"', '<ds/xdru.h>');
  &dochange('<xdru.h>', '<ds/xdru.h>');

  # ... product server ...

  &dochange('"awps.h"', '<prodserv/awps.h>');
  &dochange('<awps.h>', '<prodserv/awps.h>');
  &dochange('"pdb.h"', '<prodserv/pdb.h>');
  &dochange('<pdb.h>', '<prodserv/pdb.h>');

  # ... dixon ...

  &dochange('"coord_export.h"', '<display_interface/coord_export.h>');
  &dochange('<coord_export.h>', '<display_interface/coord_export.h>');
  &dochange('"flight_track.h"', '<display_interface/flight_track.h>');
  &dochange('<flight_track.h>', '<display_interface/flight_track.h>');
  &dochange('"time_hist_shmem.h"', '<display_interface/time_hist_shmem.h>');
  &dochange('<time_hist_shmem.h>', '<display_interface/time_hist_shmem.h>');
  &dochange('"dix_config.h"', '<dix_util/dix_config.h>');
  &dochange('<dix_config.h>', '<dix_util/dix_config.h>');
  &dochange('"dix_gutil.h"', '<dix_util/dix_gutil.h>');
  &dochange('<dix_gutil.h>', '<dix_util/dix_gutil.h>');
  &dochange('"dix_mutil.h"', '<dix_util/dix_mutil.h>');
  &dochange('<dix_mutil.h>', '<dix_util/dix_mutil.h>');
  &dochange('"dix_psutil.h"', '<dix_util/dix_psutil.h>');
  &dochange('<dix_psutil.h>', '<dix_util/dix_psutil.h>');
  &dochange('"dix_rfutil.h"','<dix_util/dix_rfutil.h>');
  &dochange('<dix_rfutil.h>','<dix_util/dix_rfutil.h>');
  &dochange('"dix_util.h"', '<dix_util/dix_util.h>');
  &dochange('<dix_util.h>', '<dix_util/dix_util.h>');
  &dochange('"dix_xutil.h"', '<dix_util/dix_xutil.h>');
  &dochange('<dix_xutil.h>', '<dix_util/dix_xutil.h>');
  &dochange('"track_verify.h"', '<storm_tracking/track_verify.h>');
  &dochange('<track_verify.h>', '<storm_tracking/track_verify.h>');
  &dochange('"dix_storm.h"', '<storm_tracking/dix_storm.h>');
  &dochange('<dix_storm.h>', '<storm_tracking/dix_storm.h>');
  &dochange('"dix_track.h"', '<storm_tracking/dix_track.h>');
  &dochange('<dix_track.h>', '<storm_tracking/dix_track.h>');
  &dochange('"dix_radar.h"', '<radar/dix_radar.h>');
  &dochange('<dix_radar.h>', '<radar/dix_radar.h>');
  &dochange('"radial_file.h"', '<radar/radial_file.h>');
  &dochange('<radial_file.h>', '<radar/radial_file.h>');
  &dochange('"chill.h"', '<radar/chill.h>');
  &dochange('<chill.h>', '<radar/chill.h>');
  &dochange('"gate_data.h"', '<radar/gate_data.h>');
  &dochange('<gate_data.h>', '<radar/gate_data.h>');
  &dochange('"lincoln.h"', '<radar/lincoln.h>');
  &dochange('<lincoln.h>', '<radar/lincoln.h>');
  &dochange('"rp7.h"', '<radar/rp7.h>');
  &dochange('<rp7.h>', '<radar/rp7.h>');
  &dochange('"tdata_server.h"', '<ds/tdata_server.h>');
  &dochange('<tdata_server.h>', '<ds/tdata_server.h>');
  &dochange('"tdata_util.h"', '<ds/tdata_util.h>');
  &dochange('<tdata_util.h>', '<ds/tdata_util.h>');
  &dochange('"dix_gds.h"', '<ds/dix_gds.h>');
  &dochange('<dix_gds.h>', '<ds/dix_gds.h>');
  &dochange('"mcidas.h"', '<ds/mcidas.h>');
  &dochange('<mcidas.h>', '<ds/mcidas.h>');

  # ... toolsa ...

  &dochange('"toolsa_globals.h"', '<toolsa/globals.h>');
  &dochange('<toolsa_globals.h>', '<toolsa/globals.h>');
  &dochange('"dlm.h"', '<toolsa/dlm.h>');
  &dochange('<dlm.h>', '<toolsa/dlm.h>');
  &dochange('"err.h"', '<toolsa/err.h>');
  &dochange('<err.h>', '<toolsa/err.h>');
  &dochange('"font.h"', '<toolsa/font.h>');
  &dochange('<font.h>', '<toolsa/font.h>');
  &dochange('"mem.h"', '<toolsa/mem.h>');
  &dochange('<mem.h>', '<toolsa/mem.h>');
  &dochange('"pjg.h"', '<toolsa/pjg.h>');
  &dochange('<pjg.h>', '<toolsa/pjg.h>');
  &dochange('"port.h"', '<toolsa/port.h>');
  &dochange('<port.h>', '<toolsa/port.h>');
  &dochange('"servmap.h"','<toolsa/servmap.h>');
  &dochange('<servmap.h>','<toolsa/servmap.h>');
  &dochange('"smu.h"', '<toolsa/smu.h>');
  &dochange('<smu.h>', '<toolsa/smu.h>');
  &dochange('"sockutil.h"', '<toolsa/sockutil.h>');
  &dochange('<sockutil.h>', '<toolsa/sockutil.h>');
  &dochange('"sok2.h"', '<toolsa/sok2.h>');
  &dochange('<sok2.h>', '<toolsa/sok2.h>');
  &dochange('"str.h"', '<toolsa/str.h>');
  &dochange('<str.h>', '<toolsa/str.h>');
  &dochange('"toolsa.h"', '<toolsa/toolsa.h>');
  &dochange('<toolsa.h>', '<toolsa/toolsa.h>');
  &dochange('"utim.h"', '<toolsa/utim.h>');
  &dochange('<utim.h>', '<toolsa/utim.h>');

  # ... xutils ...

  &dochange('"xrs.h"', '<xutils/xrs.h>');
  &dochange('<xrs.h>', '<xutils/xrs.h>');
  &dochange('"xudr.h"', '<xutils/xudr.h>');
  &dochange('<xudr.h>', '<xutils/xudr.h>');
  &dochange('"xutils.h"', '<xutils/xutils.h>');
  &dochange('<xutils.h>', '<xutils/xutils.h>');
  &dochange('"rascon.h"', '<xutils/rascon.h>');
  &dochange('<rascon.h>', '<xutils/rascon.h>');

  #
  # print line to output file
  #

  if ($checkonly != 1) {
     print(STDOUT $line);
  }

  } # end while

  close(SRCFILE);

} # end foreach

#
#--------------------------------------------------------------------------------
#

sub dochange {
    local($searchstr, $replacestr) = @_;
##    print STDERR "search for: $searchstr and replace with: $replacestr\n";
    
   # search for string and change it if we are in modify mode

    if ($line =~ /$searchstr/) {

        if ($checkonly == 1) {
            print(STDERR "  Found: $searchstr\n");
	}
        else {
            print(STDERR "  Changing: '$searchstr' to: '$replacestr'\n");
  	    $line =~ s/$searchstr/$replacestr/;
	}
    } #endif $line
}

