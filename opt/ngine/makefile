################################################################################
#                                                                              #
#                                                                              #
#                                   PART I                                     #
#                                                                              #
#                                                                              #
################################################################################
################################################################################
#                                                                              #
#                                  COMMON                                      #
#                                                                              #
################################################################################
VERSION         = 2.0.0
LICENSE        ?= no

ARCH_TYPE      ?= x32
OUTPUT_TYPE ?= STATIC
#OUTPUT_TYPE ?= SHARED
#OUTPUT_TYPE ?= BINARY
################################################################################
#                                                                              #
#                                                                              #
#                                 PART II                                      #
#                                                                              #
#                                                                              #
################################################################################
################################################################################
#                                                                              #
#                                 COMPILER                                     #
#                                                                              #
################################################################################
COPT = -O2 -no-integrated-cpp
#COPT = -g -ggdb -W -Wall -no-integrated-cpp -static-libgcc

ifeq ($(ARCH_TYPE), x32)
	TOOLCHAIN_PATH = /usr
	XCOMPILE- = 
	XTARGET   = x32
	COPT += -Dx32
	COPT += -m32
	COPT += -DPACKED
endif

ifeq ($(ARCH_TYPE), x64)
	TOOLCHAIN_PATH = /usr
	XCOMPILE- = 
	XTARGET   = x64
	COPT += -Dx64
	COPT += -m64
endif

ifeq ($(ARCH_TYPE), a32) #####
	COPT += -Da32
	ifeq ($(ABI), HARD)
		TOOLCHAIN_PATH = /usr
		XCOMPILE- = arm-linux-gnueabihf-
		XTARGET = hf.a32
		COPT += -DABI_HARD
		COPT += -mfloat-abi=hard
	endif
	ifeq ($(ABI), SOFT)
		TOOLCHAIN_PATH = /usr
		XCOMPILE- = arm-linux-gnueabi-
		XTARGET = a32
		COPT += -DABI_SOFT
		COPT += -mfloat-abi=soft
	endif
endif #####

ifeq ($(ARCH_TYPE), a64)
	COPT += -Da64
	TOOLCHAIN_PATH = /usr
	XCOMPILE- = aarch64-linux-gnu-
	ifeq ($(ABI), HARD)
		XTARGET   = hf.a64
		COPT += -DABI_SOFT
		COPT += -march=armv8-a
	endif
	ifeq ($(ABI), SOFT)
		XTARGET   = a64
		COPT += -DABI_HARD
		COPT += -march=armv8-a
	endif
endif

TOOLCHAIN_BIN  = $(TOOLCHAIN_PATH)/bin/
TOOLCHAIN_LIB = $(TOOLCHAIN_PATH)/lib
ifeq ($(ARCH_TYPE), x64)
TOOLCHAIN_LIB = $(TOOLCHAIN_PATH)/lib64
endif

CC     = $(TOOLCHAIN_BIN)$(XCOMPILE-)gcc
AR     = $(TOOLCHAIN_BIN)$(XCOMPILE-)ar
RANLIB = $(TOOLCHAIN_BIN)$(XCOMPILE-)ranlib
AR_OPT = rcs


################################################################################
#                                                                              #
#                                  SUFFIX                                      #
#                                                                              #
################################################################################
C_SUFFIX = .c
O_SUFFIX = .o

ifeq ($(OUTPUT_TYPE), SHARED)
	OUT_SUFFIX = .so
	COPT += -DSHARED_LIB
endif

ifeq ($(OUTPUT_TYPE), STATIC)
	OUT_SUFFIX = .a
	COPT += -DSTATIC_LIB
endif

ifeq ($(OUTPUT_TYPE), BINARY)
	OUT_SUFFIX = .out
endif

################################################################################
#                                                                              #
#                              COMPILE OPTIONS                                 #
#                                                                              #
################################################################################

COPT += -D__DRBG_CHECK__=0
COPT += -D__WEBSOCKET__=1
COPT += -D__HTTP__=1
COPT += -D__MIME__=1
COPT += -D__SHM__=1
COPT += -D__NIC__=0
COPT += -D__CGI__=0
COPT += -D__XML__=0
COPT += -D__SERIAL__=1
COPT += -D__SOCKET__=1
COPT += -D__PACKET__=1
COPT += -D__DBC__=0
COPT += -D__SHA1__=1
COPT += -D__LIST__=0
COPT += -D__QUEUE__=0
COPT += -D__STACK__=0
COPT += -D__JSON__=1
COPT += -D__SYSQUEUE__=0
COPT += -D__STATIC_LIB__=1
#COPT += -D__TRIGONOMETRIC__=1
COPT += -DLINUX
COPT += -DBSD_SOCKET
COPT += -DPOLLING
#COPT  += -DRTS
#COPT  += -DCONSOLE_PRINT

LIBS = -lnsl -lrt
RM = rm -rf
CP = cp -rf
MV = mv

################################################################################
#                                                                              #
#                                 DIRECTORIES                                  #
#                                                                              #
################################################################################
INC = .
SRC = .
LIB = lib
OBJ = obj
BIN = bin
OUT = out
COM = coms

################################################################################
################################################################################
#############################                 ##################################
#############################                 ##################################
#############################                 ##################################
#############################                 ##################################
##########################                       ###############################
###########################                     ################################
#############################                 ##################################
###############################             ####################################
#################################         ######################################
###################################     ########################################
##################################### ##########################################
################################################################################

################################################################################
#                                                                              #
#                                                                              #
#                            DIRECTORY INFORMATION                             #
#                                                                              #
#                                                                              #
################################################################################
OUTPUT_NAME = $(notdir $(shell pwd))

_NAME = $(OUTPUT_NAME)
TARGET_OBJ = $(OUT)/$(_NAME).$(OBJ).$(XTARGET)
TARGET_NAME = $(OUTPUT_NAME).$(XTARGET)

include opt.mak
#                                                                              #
#                                                                              #
################################################################################
##################################### ##########################################
###################################     ########################################
#################################         ######################################
###############################             ####################################
#############################                 ##################################
###########################                     ################################
##########################                       ###############################
#############################                 ##################################
#############################                 ##################################
#############################                 ##################################
#############################                 ##################################
################################################################################
################################################################################

################################################################################
#                                                                              #
#                            SOURCE CONVERTING                                 #
#                                                                              #
################################################################################
C_SRCS  = $(foreach dir, $(SRC), $(wildcard $(dir)/*$(C_SUFFIX)))
CXX_SRCS = $(foreach dir, $(SRC), $(wildcard $(dir)/*$(CXX_SUFFIX)))
OBJS = $(foreach dir, . $(TARGET_OBJ), $(wildcard $(dir)/*$(O_SUFFIX)))
OXXS = $(foreach dir, . $(TARGET_OBJ), $(wildcard $(dir)/*$(OXX_SUFFIX)))

################################################################################
#                                                                              #
#                             COMPILE OBJECT                                   #
#                                                                              #
################################################################################
%$(O_SUFFIX) :
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#  compile "$@
	@echo "#                                                                              #"
	@echo "################################################################################"
	$(RM) $(TARGET_OBJ)/$@;
	$(CC) $(INC) $(COPT) -static -o $(addprefix $(TARGET_OBJ)/, $(notdir $@)) \
	-fPIC -c $(subst $(O_SUFFIX),$(C_SUFFIX), $@) -lm;
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "################################################################################"

%$(OXX_SUFFIX) :
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#  compile CXX "$@
	@echo "#                                                                              #"
	@echo "################################################################################"
	$(CXX) $(INC) $(COPT) -static -o $(addprefix $(TARGET_OBJ)/, $(notdir $@)) \
	-fpermissive -fPIC -c $(subst $(OXX_SUFFIX),$(CXX_SUFFIX), $@) -lm;
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "################################################################################"

################################################################################
#                                                                              #
#                                    BUILD                                     #
#                                                                              #
################################################################################
% :
ifeq ($(OUTPUT_TYPE), SHARED)
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#  shared object "$@$(OUT_SUFFIX)
	@echo "#                                                                              #"
	@echo "################################################################################"
	$(CC) -fPIC -shared $(COPT) -o $(OUT)/$@$(OUT_SUFFIX) $(OBJS) $(xLIB);
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "################################################################################"
endif
ifeq ($(OUTPUT_TYPE), STATIC)
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#  archive "$@$(OUT_SUFFIX)
	@echo "#                                                                              #"
	@echo "################################################################################"
	$(AR) $(AR_OPT) $(OUT)/$@$(OUT_SUFFIX) $(OBJS) $(xLIB);
	$(RANLIB) $(OUT)/$@$(OUT_SUFFIX);
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "################################################################################"
endif
ifeq ($(OUTPUT_TYPE), BINARY)
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#  binary "$@$(OUT_SUFFIX)
	@echo "#                                                                              #"
	@echo "################################################################################"
	$(CC) -o $(OUT)/$@$(OUT_SUFFIX) $(OBJS) $(INC) $(COPT) $(xLIB);
	@echo "################################################################################"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "#                                                                              #"
	@echo "################################################################################"
endif

all:
	@echo "################################################################################"
	@echo "#"
	@echo "#"
	@echo "#  Build Start "$(TARGET_NAME)"  ("$(ARCH_TYPE)")"
	@echo "#  "$(addsuffix $(O_SUFFIX),$(basename $(C_SRCS)))
	@echo "#"
	@echo "#"
	@echo "################################################################################"
	make $(addsuffix $(O_SUFFIX),$(basename $(C_SRCS)));
	@echo "################################################################################"
	@echo "#"
	@echo "#"
	@echo "#  link "$(TARGET_NAME)
	@echo "#"
	@echo "#"
	@echo "################################################################################"
	make $(TARGET_NAME);
	@echo "################################################################################"
	@echo "#"
	@echo "#"
	@echo "#  Build Complete "$(TARGET_NAME)"  ("$(ARCH_TYPE)")"
	@echo "#"
	@echo "#"
	@echo "################################################################################"
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "
	@echo " "

################################################################################
#                                                                              #
#                                 BUILD PREFIX                                 #
#                                                                              #
################################################################################
dir:
	mkdir -p $(OUT);
	mkdir -p $(TARGET_OBJ);

clean :
	$(RM)  *.o core;
	$(RM)  $(TARGET_OBJ)/*.o;
	$(RM)  $(OUT)/$(TARGET_NAME)$(OUT_SUFFIX);

distclean:
	$(RM)  *.o core;
	$(RM)  $(OUT)/*;
	$(RM)  $(TARGET_OBJ)/*.o;
	$(RM)  $(OUT)/*.$(OUT_SUFFIX);
