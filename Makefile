#==========================================================
#	 Environment setup
#==========================================================

# Program for compiling C programs; default ‘cc’. 
CC := gcc
# Program for compiling C++ programs; default ‘g++’. 
CXX := g++

# Parallelism
CPUS ?= $(shell nproc)
MAKEFLAGS += -j$(CPUS)

# Project structures
SRCDIR := src
HEADERDIR := include
TESTDIR := test
BUILDDIR := build
TARGET := bin/strix
TEST_TARGET := bin/test

# Filename (without the extension) of the file contaning the main function
# Used to be filtered out in the test build
MAIN := main

# C specifics
C_SOURCES := $(shell find $(SRCDIR) -type f -name *.c)
C_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(C_SOURCES:.c=.o))

# C++ specifics
CXX_SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
CXX_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(CXX_SOURCES:.cpp=.o))

# Test specifics
TEST_SOURCES := $(shell find $(TESTDIR) -type f -name *.cpp)
TEST_HEADERS := $(shell find $(TESTDIR) -type f -name *.hpp)
TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SOURCES:.cpp=.o))

# Aggregation of all the objects
OBJECTS := $(C_OBJECTS) $(CXX_OBJECTS)
TEST_OBJECTS := $(filter-out $(BUILDDIR)/$(MAIN).o, $(OBJECTS)) $(TEST_OBJECTS)

# Delete targets in case of error
.DELETE_ON_ERROR:


#==========================================================
#	 Special flags
#==========================================================

INCLUDES := \
	-I $(SRCDIR)
TEST_INCLUDES := 								\
	$(INCLUDES) 								\
	-I external/googletest/googletest/include 	\
	-I external/googletest/googlemock/include

# Extra flags to give to the C compiler. 
CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic -g
# Extra flags to give to the C++ compiler. 
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -g -DBOOST_LOG_DYN_LINK
# Thanks google test ! (cf. https://github.com/google/googletest/issues/2650)
CXXFLAGS_TEST := -std=c++17 -g -DBOOST_LOG_DYN_LINK
# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L. 
# Libraries (-lfoo) should be added to the LDLIBS variable instead. 
LDFLAGS := -Llib
# Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. 
# Non-library linker flags, such as -L, should go in the LDFLAGS variable
LDLIBS := -lboost_log_setup -lboost_log -lboost_thread -lpthread


#==========================================================
#	 Default rule
#==========================================================

.PHONY: all
all: build


#==========================================================
#	 Regular build
#==========================================================

.PHONY: build
build: external $(TARGET)

$(TARGET): $(OBJECTS)
	@echo -e "    \e[93m[artefact]\e[0m $@"
	@$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@echo -e "    \e[96m[object]\e[0m $@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo -e "    \e[96m[object]\e[0m $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: run
run: build
	$(TARGET)

#==========================================================
#	 Tests
#==========================================================

.PHONY: build-test
build-test: external $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	@echo -e "    \e[93m[artefact]\e[0m $@"
	@$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS) -lgtest -lgtest_main -lgmock

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(@D)
	@echo -e "    \e[96m[object]\e[0m $@"
	@$(CXX) $(CXXFLAGS_TEST) $(TEST_INCLUDES) -c -o $@ $<

.PHONY: test
test: build-test
	$(TEST_TARGET)

#==========================================================
#	 External dependencies
#==========================================================

.PHONY: external
external:
	@$(MAKE) -s --no-print-directory -C lib


#==========================================================
#	 Clean
#==========================================================

.PHONY: clean
clean:
	@echo "Cleaning..."; 
	@$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean-lib
clean-lib:
	@echo "Cleaning libs..."; 
	@$(MAKE) -s --no-print-directory -C lib clean

.PHONY: clean-all
clean-all: clean clean-lib


#==========================================================
#	 Rebuild
#==========================================================

.PHONY: rebuild
rebuild:
	@$(MAKE) -s --no-print-directory clean
	@$(MAKE) -s --no-print-directory build


#==========================================================
#	 Debug
#==========================================================

.PHONY: gdb
gdb: build
	gdb $(TARGET)
