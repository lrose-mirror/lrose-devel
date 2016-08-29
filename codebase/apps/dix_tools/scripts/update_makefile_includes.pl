#! /local/bin/perl
#
# ch_awpg_makerefs_inc.pl
#
# Function:
#	Perl script to change Makefile HEADER references to include
#       files. The change is mostly to add subdirectory paths but 
#       there are some name changes.
#
# Usage:
#       ch_awpg_makeinc_inc.pl [-m] [-h] <list of source files>
#
#       -h : help, print usage
#       -m : modify the files (default is just to check and print pattern matches)
#
# Input:
#       Makefiles
#
# Output:
#       Copies the input sourc file into <file>.bak and puts the 
#       filtered file into <file>.
#
# Dependencies:
#	Perl must be available in the location at the top of this file.
# 	
# Author: Deirdre Garvey - NCAR/RAP/ESG		19-NOV-1993
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
  # change include location text
  #

  # ... cidd ...

  &dochange('\$\(INCDIR\)/cdata_util.h', '$(INCDIR)/cidd/cdata_util.h');

  # ... gis ...

  &dochange('\$\(INCDIR\)/posloc.h', '$(INCDIR)/gis/posloc.h');

  # ... display interface ...

  &dochange('\$\(INCDIR\)/awpg_gui_mess.h', '$(INCDIR)/display_interface/awpg_gui_mess.h');
  &dochange('\$\(INCDIR\)/awpg_ds_mess.h', '$(INCDIR)/display_interface/awpg_ds_mess.h');

##  &dochange('\$\(INCDIR\)/awpg_gui_mess.h', '$(INCDIR)/gui/awpg_gui_mess.h');
##  &dochange('\$\(INCDIR\)/awpg_ds_mess.h', '$(INCDIR)/ds/awpg_ds_mess.h');

  # ... data servers ...

  &dochange('\$\(INCDIR\)/ds.h', '$(INCDIR)/ds/ds.h');
  &dochange('\$\(INCDIR\)/dsc.h', '$(INCDIR)/ds/dsc.h');
  &dochange('\$\(INCDIR\)/dsu.h', '$(INCDIR)/ds/dsu.h');
  &dochange('\$\(INCDIR\)/gds.h', '$(INCDIR)/ds/gds.h');
  &dochange('\$\(INCDIR\)/gds_xdr.h', '$(INCDIR)/ds/gds_xdr.h');
  &dochange('\$\(INCDIR\)/kav_pack.h', '$(INCDIR)/ds/kav_pack.h');
  &dochange('\$\(INCDIR\)/xdru.h', '$(INCDIR)/ds/xdru.h');

  # ... product server ...

  &dochange('\$\(INCDIR\)/awps.h', '$(INCDIR)/prodserv/awps.h');
  &dochange('\$\(INCDIR\)/pdb.h', '$(INCDIR)/prodserv/pdb.h');

  # ... dixon ...

  &dochange('\$\(INCDIR\)/coord_export.h', '$(INCDIR)/display_interface/coord_export.h');
  &dochange('\$\(INCDIR\)/flight_track.h', '$(INCDIR)/display_interface/flight_track.h');
  &dochange('\$\(INCDIR\)/time_hist_shmem.h', '$(INCDIR)/display_interface/time_hist_shmem.h');
  &dochange('\$\(INCDIR\)/dix_config.h', '$(INCDIR)/dix_util/dix_config.h');
  &dochange('\$\(INCDIR\)/dix_gutil.h', '$(INCDIR)/dix_util/dix_gutil.h');
  &dochange('\$\(INCDIR\)/dix_mutil.h', '$(INCDIR)/dix_util/dix_mutil.h');
  &dochange('\$\(INCDIR\)/dix_psutil.h', '$(INCDIR)/dix_util/dix_psutil.h');
  &dochange('\$\(INCDIR\)/dix_rfutil.h','$(INCDIR)/dix_util/dix_rfutil.h');
  &dochange('\$\(INCDIR\)/dix_util.h', '$(INCDIR)/dix_util/dix_util.h');
  &dochange('\$\(INCDIR\)/dix_xutil.h', '$(INCDIR)/dix_util/dix_xutil.h');
  &dochange('\$\(INCDIR\)/track_verify.h', '$(INCDIR)/storm_tracking/track_verify.h');
  &dochange('\$\(INCDIR\)/dix_storm.h', '$(INCDIR)/storm_tracking/dix_storm.h');
  &dochange('\$\(INCDIR\)/dix_track.h', '$(INCDIR)/storm_tracking/dix_track.h');
  &dochange('\$\(INCDIR\)/dix_radar.h', '$(INCDIR)/radar/dix_radar.h');
  &dochange('\$\(INCDIR\)/radial_file.h', '$(INCDIR)/radar/radial_file.h');
  &dochange('\$\(INCDIR\)/chill.h', '$(INCDIR)/radar/chill.h');
  &dochange('\$\(INCDIR\)/gate_data.h', '$(INCDIR)/radar/gate_data.h');
  &dochange('\$\(INCDIR\)/lincoln.h', '$(INCDIR)/radar/lincoln.h');
  &dochange('\$\(INCDIR\)/rp7.h', '$(INCDIR)/radar/rp7.h');
  &dochange('\$\(INCDIR\)/tdata_server.h', '$(INCDIR)/ds/tdata_server.h');
  &dochange('\$\(INCDIR\)/tdata_util.h', '$(INCDIR)/ds/tdata_util.h');
  &dochange('\$\(INCDIR\)/dix_gds.h', '$(INCDIR)/ds/dix_gds.h');
  &dochange('\$\(INCDIR\)/mcidas.h', '$(INCDIR)/ds/mcidas.h');

  # ... toolsa ...

  &dochange('\$\(INCDIR\)/toolsa_globals.h', '$(INCDIR)/toolsa/globals.h');
  &dochange('\$\(INCDIR\)/dlm.h', '$(INCDIR)/toolsa/dlm.h');
  &dochange('\$\(INCDIR\)/err.h', '$(INCDIR)/toolsa/err.h');
  &dochange('\$\(INCDIR\)/font.h', '$(INCDIR)/toolsa/font.h');
  &dochange('\$\(INCDIR\)/mem.h', '$(INCDIR)/toolsa/mem.h');
  &dochange('\$\(INCDIR\)/pjg.h', '$(INCDIR)/toolsa/pjg.h');
  &dochange('\$\(INCDIR\)/port.h', '$(INCDIR)/toolsa/port.h');
  &dochange('\$\(INCDIR\)/servmap.h','$(INCDIR)/toolsa/servmap.h');
  &dochange('\$\(INCDIR\)/smu.h', '$(INCDIR)/toolsa/smu.h');
  &dochange('\$\(INCDIR\)/sockutil.h', '$(INCDIR)/toolsa/sockutil.h');
  &dochange('\$\(INCDIR\)/sok2.h', '$(INCDIR)/toolsa/sok2.h');
  &dochange('\$\(INCDIR\)/str.h', '$(INCDIR)/toolsa/str.h');
  &dochange('\$\(INCDIR\)/toolsa.h', '$(INCDIR)/toolsa/toolsa.h');
  &dochange('\$\(INCDIR\)/utim.h', '$(INCDIR)/toolsa/utim.h');

  # ... xutils ...

  &dochange('\$\(INCDIR\)/xrs.h', '$(INCDIR)/xutils/xrs.h');
  &dochange('\$\(INCDIR\)/xudr.h', '$(INCDIR)/xutils/xudr.h');
  &dochange('\$\(INCDIR\)/xutils.h', '$(INCDIR)/xutils/xutils.h');
  &dochange('\$\(INCDIR\)/rascon.h', '$(INCDIR)/xutils/rascon.h');

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
            print(STDERR "\tFound: $searchstr\n");
	}
        else {
            print(STDERR "\tChanging: $searchstr \tto: $replacestr\n");
  	    $line =~ s/$searchstr/$replacestr/;
	}
    } #endif $line
}

