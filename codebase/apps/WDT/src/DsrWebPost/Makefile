###########################################################################
#
# Makefile for Dsr2Mdv program
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# May 1998
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGET_FILE = DsrWebPost

LOC_INCLUDES =
LOC_CFLAGS =
LOC_LDFLAGS =
LOC_LIBS = -lFmq -ldsserver -lrapformats -lrapmath \
		-ldidss -ltoolsa -ldataport -ltdrp -lpthread -lbz2 -lz

HDRS = \
	$(PARAMS_HH) \
	Args.hh \
	rda_rpg_message_header.h \
	basedata.h \
	generic_basedata.h \
	Swap.h \
	DsrWebPost.hh \

CPPC_SRCS = \
	$(PARAMS_CC) \
	Args.cc \
	Main.cc \
	Swap.cpp \
	DsrWebPost.cc

#
# tdrp macros
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_macros

#
# standard C++ targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_c++_targets

#
# tdrp targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_tdrp_c++_targets

#
# local targets
#

# print native-endian UF file

cpbin:
	cp DsrWebPost ~/rap/bin/

# DO NOT DELETE THIS LINE -- make depend depends on it.
