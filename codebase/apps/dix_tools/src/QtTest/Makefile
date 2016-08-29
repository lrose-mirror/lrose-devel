###########################################################################
#
# Makefile for QtTest program
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# Sept 1998
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGET_FILE = QtTest

LOC_INCLUDES = -I/usr/include/qt4 \
		-I/usr/include/qt4/Qt \
		-I/usr/include/qt4/QtCore \
		-I/usr/include/qt4/QtGui
LOC_CFLAGS =
LOC_LDFLAGS =
LOC_LIBS = \
	-lMdv -lRadx -ldsserver -ldidss -lrapformats \
	-ltoolsa -ldataport -ltdrp -lQtGui \
	-lQtCore $(NETCDF4_LIB_LIST) -lbz2 -lz

HDRS = \
	Params.hh \
	QtTest.hh

CPPC_SRCS = \
	Params.cc \
	Args.cc \
	Main.cc \
	QtTest.cc \
	CannonField.cc \
	GameBoard.cc \
	LcdRange.cc

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

# sufixes 

CannonField.hh: CannonField.h
	moc $< -o $@

GameBoard.hh: GameBoard.h
	moc $< -o $@

LcdRange.hh: LcdRange.h
	moc $< -o $@

.h.hh:
	moc $<

#
# local targets
#

depend: depend_generic

# DO NOT DELETE THIS LINE -- make depend depends on it.

