###########################################################################
#
# Makefile for MDV_server program
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# March 1997
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGET_FILE = MDV_server

LOC_INCLUDES =
LOC_CFLAGS =
LOC_LDFLAGS =
LOC_LIBS = \
	-lcdata_util -lmdv -lrapformats -ltoolsa \
	-lrapmath -ldataport -ltdrp -lbz2 \
	-lm

HDRS = MDV_server.hh

C_SRCS = \
	$(TDRP_C)

CPPC_SRCS = \
	MDV_server.cc \
	file_search.cc \
	get_grid_data.cc \
	operate.cc \
	parse_args.cc \
	read_mdv.cc \
	register_server.cc \
	set_derived_params.cc \
	tidy_and_exit.cc

#
# tdrp support
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_macros

#
# standard targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_c++_targets

#
# local targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_targets

depend: depend_generic

# DO NOT DELETE THIS LINE -- make depend depends on it.

