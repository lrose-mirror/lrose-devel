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

TARGET_FILE = TTest

LOC_INCLUDES = -I../include
LOC_CFLAGS =
LOC_LDFLAGS = -L..
LOC_LIBS = \
	-ltoolsa -ltdrp -lboost_thread -lbz2 \
	-lpthread

HDRS = \
	$(PARAMS_HH) \
	CircBuffer.h \
	Params.hh \
	TTest.hh

CPPC_SRCS = \
	$(PARAMS_CC) \
	Args.cc \
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

