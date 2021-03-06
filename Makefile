# This makefile combines the targets of the various
# codes implemented in this project into a unified set

# Set the default target to 'build'
.PHONY: default
default: build

# This ensures that we use standard (what is used in interactive shells) version of echo.
ECHO = /bin/echo
export ECHO

# Extract the project name from the parent directory
PRJ_DIR=$(PWD)
PRJ_NAME=`grep "\- name:" .project.yml | awk '{print $$3}'`

# Get git hash
GIT_HASH=$(shell git rev-parse --short HEAD)

# Fetch the version from the .version file
ifneq ($(wildcard .version),)
	PRJ_VERSION:=`cat .version`
	PRJ_VERSION:='v'$(PRJ_VERSION)
else
	PRJ_VERSION:=unset
endif

# The build directory for documentation ('_build' to avoid breaking Readthedocs builds)
BUILD_DIR_DOCS:=$(PRJ_DIR)/docs/_build

# List of common targets (potentially) requiring specialized action for each language separately
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
	LINT_CHECK_LIST := $(LINT_CHECK_LIST) lint-check-c
	LINT_FIX_LIST := $(LINT_FIX_LIST) lint-fix-c
endif

# Add appropriate targets if Python is supported by this project
ifneq ($(wildcard .Makefile-py),)
	include .Makefile-py
	BUILD_LIST := $(BUILD_LIST) build-py
	INSTALL_LIST := $(INSTALL_LIST) install-py
	TEST_LIST := $(TEST_LIST) tests-py
	CLEAN_LIST := $(CLEAN_LIST) clean-py
	LINT_CHECK_LIST := $(LINT_CHECK_LIST) lint-check-py
	LINT_FIX_LIST := $(LINT_FIX_LIST) lint-fix-py
endif

#############################
# Targets for project users #
#############################

# Help
help:
	@$(ECHO) 
	@$(ECHO) "The following targets are available:"
	@$(ECHO) "	build   - build all software for this project"
	@$(ECHO) "	install - install all software for this project"
	@$(ECHO) "	etc.  ... finish this help"
	@$(ECHO) 

# One-time initialization
.PHONY: init
init:	 .print_status submodules requirements

# Build project
.PHONY: build
build:	 .print_status $(BUILD_LIST)

# Install project
.PHONY: install
install: .print_status $(INSTALL_LIST)

# Full-build
.PHONY: all
all:	.print_status init build install

# Clean project
.PHONY: clean
clean:	 .print_status docs-clean $(CLEAN_LIST)

# Make sure all submodules are installed
.PHONY: submodules
submodules:
	@$(ECHO) "Checking that all git submodules are up-to-date..."
	@git submodule update --recursive
	@$(ECHO) "Done."

# Make sure all needed Python code has been installed into the current environment
.PHONY: requirements
requirements:
	@$(ECHO) "Making sure that all needed Python modules are present..."
ifeq ($(shell which python),)
	@$(error "'python' not in path.  Please install it or fix your environment and try again.)
endif
ifeq ($(shell which pip),)
	@$(error "'pip' not in path.  Please install it or fix your environment and try again.)
endif
	@pip -q install -r .requirements.txt
	@pip -q install -r .requirements_dev.txt
	@$(ECHO) "Done."

########################################
# Targets for generating documentation #
########################################

# Build the project documentation
.PHONY: docs
docs: $(DOCS_LIST) docs-update
	@$(ECHO) "Building documenation..."
	@cd docs;sphinx-build . _build
	@$(ECHO) "Done."

# Update API documentation
# n.b.: 'build' is a dependancy because a build needs to be in place
#       in order to generate executable syntax documentation.
.PHONY: docs-update
docs-update: build $(BUILD_DIR_DOCS)
	@$(ECHO) "Updating API documenation..."
	@update_gbpBuild_docs $(PWD)
	@$(ECHO) "Done."

# Make the documentation build directory
$(BUILD_DIR_DOCS):
ifeq (,$(wildcard $@))
	@$(ECHO) -n "Making docs build directory {"$@"}..."
	@mkdir $@
	@$(ECHO) "Done."
endif

# Remove the documenation build directory
.PHONY: docs-clean
docs-clean:
	@rm -rf docs/__pycache__
	@rm -rf $(BUILD_DIR_DOCS)

##################################
# Targets for project developers #
##################################

# Run tests
tests:	.print_status build $(TEST_LIST)

# Make liniting suggestions
lint-check:	.print_status $(LINT_CHECK_LIST)

# Apply all linting suggestions
lint-fix:	.print_status $(LINT_FIX_LIST)

# Update the pip python requirements files for the project.
.PHONY: requirements-update
requirements-update: .print_status
	@$(ECHO) "Updating project Python requirements..."
ifeq ($(shell which pigar),)
	@$(error "'pigar' not in path.  Please install it with 'pip install pigar' and try again.)
else
	@pigar -p .requirements.txt
endif
	@$(ECHO) "Done."

##########################
# Print a status message #
##########################
.print_status: .printed_status
# Fetch the version from the .version file
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
