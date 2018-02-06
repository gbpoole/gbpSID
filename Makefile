# This makefile combines the targets of the various
# codes implemented in this project into a unified set

# Set the default build target
.PHONY: default
default: build

# Extract the project name from the parent directory
PRJ_DIR=$(PWD)
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
INIT_LIST = 
BUILD_LIST = 
DOCS_LIST = 
INSTALL_LIST = 
TEST_LIST = 
CLEAN_LIST = 
LINT_LIST = 

# Add appropriate targets if C/C++ is supported by this project
ifneq ($(wildcard .Makefile-c),)
	include .Makefile-c
	BUILD_LIST := $(BUILD_LIST) build-c
	DOCS_LIST := $(DOCS_LIST) build docs-c
	INSTALL_LIST := $(INSTALL_LIST) install-c
	TEST_LIST := $(TEST_LIST) tests-c
	CLEAN_LIST := $(CLEAN_LIST) clean-c
	LINT_LIST := $(LINT_LIST) lint-c
endif

# Add appropriate targets if Python is supported by this project
ifneq ($(wildcard .Makefile-py),)
	include .Makefile-py
	INIT_LIST := $(INIT_LIST) init-py
	BUILD_LIST := $(BUILD_LIST) build-py
	DOCS_LIST := $(DOCS_LIST) docs-py
	INSTALL_LIST := $(INSTALL_LIST) install-py
	TEST_LIST := $(TEST_LIST) tests-py
	CLEAN_LIST := $(CLEAN_LIST) clean-py
	LINT_LIST := $(LINT_LIST) lint-py
endif

################################
# TARGETS and RULES BEGIN HERE #
################################

.PHONY: init build tests lint install clean
init:	 .print_status submodules $(INIT_LIST)
build:	 .print_status $(BUILD_LIST)
tests:	 .print_status build $(TEST_LIST)
lint:	 .print_status $(LINT_LIST)
install: .print_status $(INSTALL_LIST)
clean:	 .print_status $(CLEAN_LIST)

# Update API documentation
#
# Note that 'build' is a dependancy
# because a build needs to be in place
# in order to generate executable
# syntax documentation.
.PHONY: docs-update
docs-update: build
	@$(ECHO) "Updating API documenation..."
	@python python/$(PRJ_NAME)_dev/$(PRJ_NAME)_dev/scripts/update_$(PRJ_NAME)_docs.py
	@$(ECHO) "Done."

.PHONY: docs
docs: $(DOCS_LIST) docs-update
	@$(ECHO) "Building documenation..."
	@cd docs;sphinx-build . build
	@$(ECHO) "Done."

# Make sure all submodules are up-to-date
.PHONY: submodules
submodules:
	@$(ECHO) "Checking that all git submodules are up-to-date..."
	@git submodule update --recursive
	@$(ECHO) "Done."

# Print a status message
.print_status: .printed_status
	@$(ECHO)
	@$(ECHO) "Project information:"
	@$(ECHO) "-------------------"
	@$(ECHO) "Project name:     "$(PRJ_NAME)
	@$(ECHO) "Project version:  "$(PRJ_VERSION)
	@$(ECHO) "Git hash (short): "$(GIT_HASH)
	@$(ECHO)
	@rm -rf .printed_status
.printed_status:
	@touch .printed_status
