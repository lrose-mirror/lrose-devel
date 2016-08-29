#! /bin/csh -f

############################################################################
#
# This script kills any programs with the path as argument
#

while ($#argv > 0) 

  set ppids =  ` ps -x | grep -v grep | grep $argv[1] | awk ' {print $1 } ' `

  foreach ppid ($ppids)

    foreach sig (INT QUIT TERM KILL)

      kill -$sig $ppid >& /dev/null

    end ## foreach sig INT QUIT TERM KILL

  end ## foreach ppid ($ppids)

  shift

end ## while

