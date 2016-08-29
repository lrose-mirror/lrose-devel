###########################################################################
#
# Makefile for bounce test program
#
# Mike Dixon, RAP, NCAR, Boulder, CO, 80307, USA
#
# Dec 1996
#
###########################################################################

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGET_FILE = bounce

LOC_INCLUDES = $(SYS_X_INCLUDES)
LOC_CFLAGS =
LOC_LDFLAGS = $(SYS_X_LDFLAGS)
LOC_LIBS = -lMotifApp -lXext -lXm -lXpm -lXt  -lX11

MODULE_TYPE = progcpp

HDRS =

CPPC_SRCS = \
	Actor.cc \
	AddBallCmd.cc \
	BounceApp.cc \
	BounceClock.cc \
	BounceWindow.cc \
	BouncingBall.cc \
	ControlPanel.cc \
	RunCmd.cc \
	Stage.cc \
	StepCmd.cc \
	StopCmd.cc

#
# standard targets
#

include $(RAP_MAKE_INC_DIR)/rap_make_targets

#
# local targets
#

depend: depend_generic

# DO NOT DELETE THIS LINE -- make depend depends on it.
