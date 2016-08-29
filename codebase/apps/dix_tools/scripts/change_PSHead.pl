#! /usr/local/bin/perl

#
# rm_wspace
#
# replaces any contiguous whitespace with a single space
#

while (<>) {

  s/PShead\s**/PShandle/g;
  print;

}

