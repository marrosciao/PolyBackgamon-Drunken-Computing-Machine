#The Target Binary Program
TARGET        := PolyBackgammon
 
#Compiler
export CC            := gcc
 
#The Directories, Source, Includes, Objects, Binary and Resources
export SRCDIR        := src
export INCDIR        := include
export BUILDDIR      := obj
export TARGETDIR     := $(pwd)
export IADIR         := strategy
export GUIDIR        := interface
 
#Flags, Libraries and Includes
export CFLAGS        += -std=c11 -Wall -Wextra -pedantic -pipe -fdiagnostics-color=auto -rdynamic -fsanitize=address
export CFLAGS_DEBUG  += -Og -g -fsanitize=address
export CFLAGS_PROD   += -O2 -s -DNDEBUG
export CPPFLAGS      += -MMD -MP -I $(INCDIR)
LDFLAGS       +=
LDLIBS        +=

export green         := `tput setaf 2`
export reset         := `tput sgr0`
export blue          := `tput setaf 4`
export bold          := `tput bold`
 
 
#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES       := $(wildcard $(SRCDIR)/*.c)
SOURCES       += main.c
OBJECTS       := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))
DEBUG         ?= 1
 
ifeq ($(DEBUG), 1)
	CFLAGS += $(CFLAGS_DEBUG)
else
	CFLAGS += $(CFLAGS_PROD)
endif
export CFLAGS

all: GUI IA
	#@echo "${green}${bold}Compilation de l'interface graphique${reset}"

GUI: 
	@($(MAKE) -f $(GUIDIR)/makefile)

IA: 
	@($(MAKE) -f $(IADIR)/makefile)

clean:
	$(RM) -r $(BUILDDIR) *.o
	$(RM) $(TARGETDIR)/$(TARGET)
 
-include $(OBJECTS:.o=.d)
 
.PHONY: all clean check

