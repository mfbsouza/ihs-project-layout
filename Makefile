# Makefile by Matheus Souza (github.com/mfbsouza)

# project name
PROJECT  := app

# paths
BUILDDIR := ./app/build
DBGDIR   := $(BUILDDIR)/debug
RELDIR   := $(BUILDDIR)/release
INCDIR   := ./app/include

# compiler
PREFIX :=
CC     := $(PREFIX)gcc
AS     := $(PREFIX)nasm
CXX    := $(PREFIX)g++
LD     := $(PREFIX)g++
OD     := $(PREFIX)objdump

# flags
CFLAGS   := -Wall -I $(INCDIR) -MMD -MP
CXXFLAGS := -Wall -I $(INCDIR) -MMD -MP
ASMFLAGS := -f elf
LDFLAGS  :=

ifeq ($(DEBUG),1)
	BINDIR    := $(DBGDIR)
	OBJDIR    := $(DBGDIR)/obj
	CFLAGS    += -g -O0 -DDEBUG
	CXXFLAGS  += -g -O0 -DDEBUG
else
	BINDIR    := $(RELDIR)
	OBJDIR    := $(RELDIR)/obj
	CFLAGS    += -g -O3
	CXXFLAGS  += -g -O3
endif

# sources to compile
ALLCSRCS += $(shell find ./app/src ./app/include -type f -name *.c)
ALLCXXSRCS += $(shell find ./app/src ./app/include -type f -name *.cpp)
ALLASMSRCS += $(shell find ./app/src ./app/include -type f -name *.asm)

# objects settings
COBJS   := $(addprefix $(OBJDIR)/, $(notdir $(ALLCSRCS:.c=.o)))
CXXOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ALLCXXSRCS:.cpp=.o)))
ASMOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ALLASMSRCS:.asm=.o)))
OBJS    := $(COBJS) $(CXXOBJS) $(ASMOBJS)
DEPS    := $(OBJS:.o=.d)

# paths where to search for sources
SRCPATHS := $(sort $(dir $(ALLCSRCS)) $(dir $(ALLCXXSRCS)) $(dir $(ALLASMSRCS)))
VPATH     = $(SRCPATHS)

# output
OUTFILES := $(BINDIR)/$(PROJECT) $(BUILDDIR)/$(PROJECT).lst

# targets
.PHONY: all clean

all: $(OBJDIR) $(BINDIR) $(OBJS) $(OUTFILES)

# targets for the dirs
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# target for c objects
$(COBJS) : $(OBJDIR)/%.o : %.c
ifeq ($(VERBOSE),1)
	$(CC) -c $(CFLAGS) $< -o $@
else
	@echo -e "[CC]\t$<"
	@$(CC) -c $(CFLAGS) $< -o $@
endif

# target for cpp objects
$(CXXOBJS) : $(OBJDIR)/%.o : %.cpp
ifeq ($(VERBOSE),1)
	$(CXX) -c $(CXXFLAGS) $< -o $@
else
	@echo -e "[CXX]\t$<"
	@$(CXX) -c $(CXXFLAGS) $< -o $@
endif

# target for asm objects
$(ASMOBJS) : $(OBJDIR)/%.o : %.asm
ifeq ($(VERBOSE),1)
	$(AS) $(ASMFLAGS) $< -o $@
else
	@echo -e "[AS]\t$<"
	@$(AS) $(ASMFLAGS) $< -o $@
endif

# target for ELF file
$(BINDIR)/$(PROJECT): $(OBJS)
ifeq ($(VERBOSE),1)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
else
	@echo -e "[LD]\t./$@"
	@$(LD) $(LDFLAGS) $(OBJS) -o $@
endif

# target for disassembly and sections header info
$(BUILDDIR)/$(PROJECT).lst: $(BINDIR)/$(PROJECT)
ifeq ($(VERBOSE),1)
	$(OD) -h -S $< > $@
else
	@echo -e "[OD]\t./$@"
	@$(OD) -h -S $< > $@
endif

# target for cleaning files
clean:
	rm -rf $(BUILDDIR)

# include the dependency files, should be the last of the makefile
-include $(DEPS)
