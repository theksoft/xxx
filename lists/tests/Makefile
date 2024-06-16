BUILD ?= ./build
APP ?= tests-lists

# Predefined folders
SRCDIR := src
INCDIR := ../include

# Temporary folders
LIBDIR := $(BUILD)/lib
BINDIR := $(BUILD)/bin
OBJDIR := $(BUILD)/obj/lists
DIRS := $(LIBDIR) $(BINDIR) $(OBJDIR)

# Library and test exe path base
LIBTGT := $(LIBDIR)/lib$(APP)
TARGET := $(BINDIR)/$(APP)

# Source list
SRCS := main tests tests_list1d tests_list2d

# Flags
CFLAGS += -Wall -Wextra -Werror -Wpedantic --pedantic-errors -std=c17
CFLAGS += -I $(SRCDIR) $(INCDIR:%=-I %)
LDFLAGS += -fPIC -lcunit -L$(LIBDIR)

# Main target
all: dirs $(LIBTGT).a $(LIBTGT)d.a $(TARGET) $(TARGET)-d

# Dependencies management
DEPS := $(SRCS:%=$(OBJDIR)/%.d)

$(OBJDIR)/%.d: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) -MM -MP -MT $(OBJDIR)/$(basename $(<F)).o -MT $(OBJDIR)/$(basename $(<F))-g.o $(CFLAGS) $< > $@

# Target specificities
$(TARGET): CFLAGS += -O2 -DNDEBUG=1
$(TARGET): LDFLAGS += -l$(APP)
$(TARGET)-d: CFLAGS += -g -D__DEBUG
$(TARGET)-d: LDFLAGS += -l$(APP)d

# Object files build rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%-g.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Executable targets
$(TARGET): $(SRCS:%=$(OBJDIR)/%.o)
	$(CC) $^ $(LDFLAGS) -o $@

$(TARGET)-d: $(SRCS:%=$(OBJDIR)/%-g.o)
	$(CC) $^ $(LDFLAGS) -o $@

# Library targets
$(LIBTGT).a $(LIBTGT)d.a:
	@$(MAKE) -C .. BUILD=./tests/$(BUILD) LIBNAME=$(APP)

# Other targets

clean:
	@-$(RM) -r $(BUILD)

dirs: $(DIRS)

$(DIRS):
	@mkdir -p $@

.PHONY: all clean dirs

# Dependencies
-include $(DEPS)
