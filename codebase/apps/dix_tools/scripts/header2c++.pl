#! /usr/local/bin/perl

#
# filter to add c++ directives to header files
#
# Added at start:
#
# #ifdef __cplusplus
#  extern "C" {
# #endif
#
# Added at end:
#
# #ifdef __cplusplus
# }
# #endif


#
# loop through all the args as filenames
#

 FILE:
foreach $filename (@ARGV) {

  print(STDERR "\n");
  print(STDERR "$filename\n");

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

  print(STDOUT "#ifdef __cplusplus\n");
  print(STDOUT " extern \"C\" {\n");
  print(STDOUT "#endif\n");

  #
  # loop through the lines in the file
  #

  while ($line = <SRCFILE>) {

    print(STDOUT $line);

  }

  print(STDOUT "#ifdef __cplusplus\n");
  print(STDOUT "}\n");
  print(STDOUT "#endif\n");

  close(STDOUT);

} # foreach

