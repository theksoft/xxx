# Default variables
BUILD ?= ./build
LIBNAME ?= xxx_lists

# Directories
SRCDIR := src
INCDIR := include

# Temporary directories
LIBDIR := $(BUILD)/lib
OBJDIR := $(BUILD)/obj/lists
DIRS := $(LIBDIR) $(OBJDIR)

# Library path
TARGET := $(LIBDIR)/lib$(LIBNAME)

# Source list
SRCS := xxx_sll_s xxx_list2d

# Flags
CFLAGS += -Wall -Wextra -Werror -Wpedantic --pedantic-errors -std=c17
CFLAGS += -I $(SRCDIR) $(INCDIR:%=-I %)
ARFLAGS := rcs

# Targets
all: dirs $(TARGET).a $(TARGET)d.a
	@echo "..... XXX LINKED LIBS BUILD DONE / lib = $(LIBNAME) ....."

# Dependencies management
DEPS := $(SRCS:%=$(OBJDIR)/%.d)

$(OBJDIR)/%.d: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) -MM -MP -MT $(OBJDIR)/$(basename $(<F)).o -MT $(OBJDIR)/$(basename $(<F))-g.o $(CFLAGS) $< > $@

# Target specificities
$(TARGET).a: CFLAGS += -O2 -DNDEBUG=1
$(TARGET)d.a: CFLAGS += -g -D__DEBUG

# Object files build rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%-g.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Libraries target
$(TARGET).a: $(SRCS:%=$(OBJDIR)/%.o)
	$(AR) $(ARFLAGS) $@ $^

$(TARGET)d.a: $(SRCS:%=$(OBJDIR)/%-g.o)
	$(AR) $(ARFLAGS) $@ $^

# Other targets

clean:
	@-$(RM) -r $(OBJDIR)
	@-$(RM) -f $(TARGET).a $(TARGET)d.a

cleanall:
	@-$(RM) -r $(BUILD)

dirs: $(DIRS)

$(DIRS):
	@mkdir -p $@

.PHONY: all clean dirs

# Dependencies

-include $(DEPS)