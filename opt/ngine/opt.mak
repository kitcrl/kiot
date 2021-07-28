################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
CODEX_PATH = ..

COPT += -D__SSL_TLS__=1
COPT += -D__CUSTOM_X_SOCKET__=1
COPT += -D__CUSTOM_X_HTTP__=1
COPT += -D__CUSTOM_X_HTTPD__=0
COPT += -D__CUSTOM_X_HTTPSD__=0
COPT += -D__CUSTOM_X_WS__=1
COPT += -D__CUSTOM_X_SERIAL__=0
COPT += -D__CUSTOM_X_SIFR__=0

SRC  = .
SRC += n
SRC += z

INC  = -I.
INC += -In
INC += -Iz
INC += -I$(CODEX_PATH)/
INC += -I$(CODEX_PATH)/h

xLIB += -Xlinker --start-group
xLIB += $(CODEX_PATH)/lib/$(XTARGET)/icode.xr.a
xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group
