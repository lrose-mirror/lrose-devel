###########################################################################
#
# Makefile for german2class
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# April 1995
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

MODULE_TYPE = program

TARGET_FILE = german2class

LOC_INCLUDES =
LOC_CFLAGS =
LOC_LDFLAGS =
LOC_LIBS = \
	-ltitan -ltoolsa -lbz2 -lm

HDRS = german2class.h

SRCS = \
	copy_cal_to_class.c \
	german2class.c \
	process_file.c \
	read_apa.c \
	write_class.c \
	wx_routines.c

#
# standard targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_targets

#
# local targets
#

depend: depend_generic

# DO NOT DELETE THIS LINE -- make depend depends on it.

