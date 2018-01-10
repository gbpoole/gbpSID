# This makefile combines the targets of the various
# codes implemented in this project into a unified set

# Set the default build target
.PHONY: default
default: build

# Extract the project name from the parent directory
PRJ_DIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
PRJ_NAME=$(shell basename $(PRJ_DIR))

# Get git hash
GIT_HASH=$(shell git rev-parse --short HEAD)

# Fetch the version from the .version file
ifneq ($(wildcard .version),)
	PRJ_VERSION:=`cat .version`
	PRJ_VERSION:='v'$(PRJ_VERSION)
else
	PRJ_VERSION:=unset
endif

# This ensures that we use standard (what is used in interactive shells) version of echo.
ECHO = /bin/echo
export ECHO

# List of common targets requiring specialized action for each language separately
BUILD_LIST = 
DOCS_LIST = 
INSTALL_LIST = 
TEST_LIST = 
CLEAN_LIST = 

# Add appropriate targets if C/C++ is supported by this project
ifneq ($(wildcard .Makefile.c_cpp),)
	include .Makefile.c_cpp
	BUILD_LIST := $(BUILD_LIST) build.c_cpp
	DOCS_LIST := $(DOCS_LIST) docs.c_cpp
	INSTALL_LIST := $(INSTALL_LIST) install.c_cpp
	TEST_LIST := $(TEST_LIST) test.c_cpp
	CLEAN_LIST := $(CLEAN_LIST) clean.c_cpp
	USE_C_CPP := ON
endif

# Add appropriate targets if Python is supported by this project
ifneq ($(wildcard .Makefile.python),)
	include .Makefile.python
	BUILD_LIST := $(BUILD_LIST) build.python
	DOCS_LIST := $(DOCS_LIST) docs.python
	INSTALL_LIST := $(INSTALL_LIST) install.python
	TEST_LIST := $(TEST_LIST) test.python
	CLEAN_LIST := $(CLEAN_LIST) clean.python
	USE_PYTHON := ON
endif

################################
# TARGETS and RULES BEGIN HERE #
################################

.PHONY: all build docs test install clean
all:	 build docs
build:	 .print_status $(BUILD_LIST)
docs:	 .print_status $(DOCS_LIST)
test:	 .print_status $(TEST_LIST)
install: .print_status $(INSTALL_LIST)
clean:	 .print_status $(CLEAN_LIST)

# Print a status message
.print_status: .printed_status
	@$(ECHO)
	@$(ECHO) "Project information:"
	@$(ECHO) "-------------------"
	@$(ECHO) "Project name:     "$(PRJ_NAME)
	@$(ECHO) "Project version:  "$(PRJ_VERSION)
	@$(ECHO) "Git hash (short): "$(GIT_HASH)
ifeq ($(USE_C_CPP),ON)
	@$(ECHO) "C/C++  support:   ON"
else
	@$(ECHO) "C/C++  support:   OFF"
endif
ifeq ($(USE_PYTHON),ON)
	@$(ECHO) "Python support:   ON"
else
	@$(ECHO) "Python support:   OFF"
endif
	@$(ECHO)
	@rm -rf .printed_status
.printed_status:
	@touch .printed_status
