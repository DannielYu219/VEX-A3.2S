# VEXcode mkenv.mk 2022_06_26_01

# macros to help with paths that include spaces
sp = $() $()
qs = $(subst ?, ,$1)
sq = $(subst $(sp),?,$1)

# default platform and build location
PLATFORM  = vexv5
BUILD     = build

# version for clang headers
ifneq ("$(origin HEADERS)", "command line")
HEADERS = 8.0.0
endif

# Project name passed from app
ifeq ("$(origin P)", "command line")
PROJECT  := $(P)
else
PROJECT  := $(call qs,$(notdir $(call sq,${CURDIR})))
endif

# check if the PROJECT name contains any whitespace
ifneq (1,$(words $(PROJECT)))
$(error Project name cannot contain whitespace: $(PROJECT))
endif

# SDK path passed from app
# if not set then environmental variabled used
ifeq ("$(origin T)", "command line")
VEX_SDK_PATH = $(T)
endif
# backup if still not set
VEX_SDK_PATH ?= ${HOME}/sdk

# printf_float flag name passed from app (not used in this version)
ifeq ("$(origin PRINTF_FLOAT)", "command line")
PRINTF_FLAG = -u_printf_float
endif

# Verbose flag passed from app
ifeq ("$(origin V)", "command line")
BUILD_VERBOSE=$(V)
endif

# allow verbose to be set by makefile if not set by app
ifndef VERBOSE
BUILD_VERBOSE ?= 0
else
BUILD_VERBOSE ?= $(VERBOSE)
endif

# use verbose flag
ifeq ($(BUILD_VERBOSE),0)
Q = @
else
Q =
endif

# compile and link tools
CC      = clang
CXX     = clang
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
LINK    = arm-none-eabi-ld
ARCH    = arm-none-eabi-ar
ECHO    = @echo
DEFINES = -DVexV5

# platform specific macros
ifeq ($(OS),Windows_NT)
$(info windows build for platform $(PLATFORM))
SHELL = cmd.exe
MKDIR = md "$(@D)" 2> nul || :
RMDIR = rmdir /S /Q
CLEAN = $(RMDIR) $(BUILD) 2> nul || :
else
# which flavor of linux
UNAME := $(shell sh -c 'uname -sm 2>/dev/null || Unknown')
$(info unix build for platform $(PLATFORM) on $(UNAME))
MKDIR = mkdir -p "$(@D)" 2> /dev/null || :
RMDIR = rm -rf
CLEAN = $(RMDIR) $(BUILD) 2> /dev/null || :
endif

# toolchain include and lib locations
TOOL_INC  = -I"$(SDK_ROOT)/clang/$(HEADERS)/include" -I"$(SDK_ROOT)/gcc/include/c++/4.9.3"  -I"$(SDK_ROOT)/gcc/include/c++/4.9.3/arm-none-eabi/armv7-ar/thumb" -I"$(SDK_ROOT)/gcc/include"
TOOL_LIB  = -L"$(SDK_ROOT)/gcc/libs"

# 工具链路径检测
# 定义可能的SDK根目录
ORIGINAL_SDK_PATH := $(VEX_SDK_PATH)
# 打印原始SDK路径
$(info Original VEX_SDK_PATH: $(ORIGINAL_SDK_PATH))
# 使用shell命令检查vexv5子目录是否存在，以处理包含空格的路径
VEXV5_DIR_EXISTS := $(shell if [ -d "$(ORIGINAL_SDK_PATH)/vexv5" ]; then echo "yes"; else echo "no"; fi)
ifneq ($(VEXV5_DIR_EXISTS),no)
    # 如果存在，将SDK_ROOT设置为包含vexv5子目录的路径
    SDK_ROOT := $(ORIGINAL_SDK_PATH)/vexv5
    $(info Using SDK_ROOT with vexv5 subdirectory: $(SDK_ROOT))
else
    # 否则，使用原始的SDK路径
    SDK_ROOT := $(ORIGINAL_SDK_PATH)
    $(info Using SDK_ROOT without vexv5 subdirectory: $(SDK_ROOT))
endif

# compiler flags
CFLAGS_CL = -target thumbv7-none-eabi -fshort-enums -Wno-unknown-attributes -U__INT32_TYPE__ -U__UINT32_TYPE__ -D__INT32_TYPE__=long -D__UINT32_TYPE__='unsigned long' 
CFLAGS_V7 = -march=armv7-a -mfpu=neon -mfloat-abi=softfp
CFLAGS    = ${CFLAGS_CL} ${CFLAGS_V7} -Os -Wall -Werror=return-type -ansi -std=gnu99 $(DEFINES)
CXX_FLAGS = ${CFLAGS_CL} ${CFLAGS_V7} -Os -Wall -Werror=return-type -fno-rtti -fno-threadsafe-statics -fno-exceptions  -std=gnu++11 -ffunction-sections -fdata-sections $(DEFINES)

# linker flags
LNK_FLAGS = -nostdlib -T "$(SDK_ROOT)/lscript.ld" -R "$(SDK_ROOT)/stdlib_0.lib" -Map="$(BUILD)/$(PROJECT).map" --gc-section -L"$(SDK_ROOT)" ${TOOL_LIB}

# future statuc library
PROJECTLIB = lib$(PROJECT)
ARCH_FLAGS = rcs

# libraries
LIBS =  --start-group -lv5rt -lstdc++ -lc -lm -lgcc --end-group

# include file paths
INC += $(addprefix -I, ${INC_F})
INC += -I"$(SDK_ROOT)/include"
INC += ${TOOL_INC}
