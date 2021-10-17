mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))


APPL_CXXOBJS += \
	InstructionMethod.o \
	LineTraceMethod.o \
	PID.o \
	RatioRotationMethod.o \
	RunMethod.o \
	Condition.o \
	DirectionCondition.o \
	AllDirectionCondition.o\
	DistanceCondition.o \
	LineCondition.o \
	WhiteCondition.o \
	LineoutCondition.o \
	ColorCondition.o \
	BlockplaceCondition.o \
	CheckRGBCondition.o \
	MultiCondition.o \
	ObstacleCondition.o \
	StepCondition.o \
	TimeDetectionCondition.o \
	Communication.o \
	LogData.o \
	Sound.o \
	SonarMeter.o \
	Brightness.o \
	Calibration.o \
	DistanceMeasure.o \
	SpeedoMeter.o \
	TrainReader.o \
	StarReader.o \
	RunArea.o \
	DynamicRunArea.o\
	BlockLineRunArea.o\
	RunBlock.o \
	LookblockRunBlock.o\
	EscapeRunBlock.o \
	StarWatchRunBlock.o \
	RouteSearchRunBlock.o \
	CrossRunBlock.o \
	ResetRunBlock.o \
	RunCourse.o \
	Mode.o \
	Solution.o \
	Block.o \
	ColorDistinguish.o \
	Route.o \
	Place.o \
	Placegroup.o \
	Field.o \
	RouteInfo.o


SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

srcpath = $(mkfile_path)RunMethod $(mkfile_path)RouteGuide $(mkfile_path)Measure $(mkfile_path)Device $(mkfile_path)Condition $(mkfile_path)Communication $(mkfile_path)Mode $(mkfile_path)BlockLined

ifdef app
  APPL_DIR += $(srcpath)
endif

ifdef mod
  SRCDIRS += $(srcpath)
endif

INCLUDES += \
	-I$(mkfile_path)RunMethod \
	-I$(mkfile_path)RouteGuide \
	-I$(mkfile_path)Measure \
	-I$(mkfile_path)Device \
	-I$(mkfile_path)Condition \
	-I$(mkfile_path)Communication \
	-I$(mkfile_path)Mode \
	-I$(mkfile_path)BlockLined 

COPTS += -fno-use-cxa-atexit