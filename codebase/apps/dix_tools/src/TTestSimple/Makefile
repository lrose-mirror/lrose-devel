###########################################################################
#
# Makefile for TTest program
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# Sept 1998
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGET_FILE = TTestSimple

## The following are needed for PGI compiles, the -fPIC for PGI links
## with the shared object lib

LOC_INCLUDES = -I/opt/netcdf/include
LOC_LDFLAGS = -L/opt/netcdf/lib -fPIC

## Testing load libraries. None are actually needed for this app.
LOC_LIBS = 
LOC_LIBS = -lnetcdf
LOC_LIBS = -lnetcdf_c++ -lnetcdf

HDRS = \
	TTest.hh

CPPC_SRCS = \
	Main.cc \
	TTest.cc

#
# tdrp macros
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_macros

#
# C++ targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_c++_targets

#
# tdrp targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_c++_targets

#
# local targets
#

depend: depend_generic

# DO NOT DELETE THIS LINE -- make depend depends on it.
