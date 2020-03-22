### MAC OS X ONLY OpenGL/SDL Makefile ! Tested on Yosemite
# adapted by Lucas Horand - http://luhof.fr - from a random chunk of code by Laurent Noël
# / ! \ You need a basic architecture with src, obj, includes folders / ! \
# app will be created in bin folder.
###

### FRIENDLY REMINDERS :
# 	Use homebrew to install libs : http://brew.sh
#	before including OpenGL check #ifdef __APPLE__ !
###

APP_BIN = sloppy

LIBS =
CC = gcc
#CFLAGS = -Wall
CFLAGS = -Wall -DSLOPPY_RENDER
INCLUDES =  -I`sdl2-config --cflags --libs`


SRC_PATH = source
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
DATA		:= ../data

SRC_FILES = $(shell find $(SRC_PATH) $(GBC_SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
export OFILES_BIN := $(addsuffix .o,$(BINFILES))
export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LIBS) $(INCLUDES) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)
	@echo cleaned .o files and executable !


$(OFILES_SOURCES) : $(HFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	%_bin.h :	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPSDIR)/*.d
