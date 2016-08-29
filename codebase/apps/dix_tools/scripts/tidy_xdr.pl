#! /local/bin/perl

#
# tidy_xdr
#
# The xdr generation routines sometimes leave a ',}' sequence
# in an enum typedef.
#
# This script cleans those up.
#

while ($line = <STDIN>) {

  if ($line =~ m/^enum/) {

    $prev_line = $line;

    while ($enum_line = <STDIN>) {

      if ($enum_line =~ m/^\}\;/) {

        $prev_line =~ s/,$//;
	print $prev_line;
	print $enum_line;
	goto end_of_enum;
	
      } else {
	
	print $prev_line;
	
      } # if ($enum_line =~ m/^\};/)

      $prev_line = $enum_line;
      
    } # while ($enum_line = <STDIN>) 

    end_of_enum:

  } else {

    print $line;

  } # if ($line =~ m/^enum/) 


}

