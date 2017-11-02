# This makefile deals with all CI processing 
# of the gbpHome repository

.PHONY: test clean

# Set the KCov token
KCOV_TOKEN="74c531b7-23f1-4914-bd15-36b32a6bf144"

# This ensures that we use standard (what is used in interactive shells) version of echo.
ECHO = /bin/echo

# Determine what sort of environment we're in (eg. OSX or Linux)
# Set linux defaults
KCOV_DIR='.test/kcov-master'
KCOV_EXE=$(KCOV_DIR)'/build/src/kcov'
_MAC_BUILD=0
_TRAVIS_BUILD=0
ifdef TRAVIS_OS_NAME
    ifeq ($(TRAVIS_OS_NAME),'osx')
        KCOV_EXE=$(KCOV_DIR)'/build/src/Release/kcov'
        _MAC_BUILD=1
    endif
    _TRAVIS_BUILD=1
else
    ifeq ($(GBP_OS),Mac)
        KCOV_EXE=$(KCOV_DIR)'/build/src/Release/kcov'
        _MAC_BUILD=1
    endif
endif
export KCOV_EXE
export _MAC_BUILD
export _TRAVIS_BUILD

# Generate build tests for the CI service.  This assumes that
# all wanted build flags have been set in the environment
# variable $(USE_FLAGS)
test_build:
	@$(ECHO) "Performing build test:"
	@mkdir build_test      && \
	cd build_test          && \
	echo $(PWD)            && \
	echo $(USE_FLAGS)      && \
	cmake .. $(USE_FLAGS)  && \
	make install           && \
	cd ..                  && \
	rm -rf build_test 
	@echo "Build passed with USE_FLAGS={"$(USE_FLAGS)"}"

# Execution tests
EXE_TESTS = 
$(EXE_TESTS):
	@$(ECHO) -n "Running execution test: "$@
	@$@
	@$(ECHO) "Done."

# Run all tests
test: test_build $(EXE_TESTS)

# Generate coverage information for executable tests
.test/kcov.tgz:
	@$(ECHO) -n "Downloading kcov code..."
	@wget https://github.com/SimonKagstrom/kcov/archive/master.tar.gz -O .test/kcov.tgz
	@tar xfz .test/kcov.tgz -C .test
	@$(ECHO) "Done."
$(KCOV_EXE): .test/kcov.tgz
ifeq ($(_MAC_BUILD),1)
	@cd $(KCOV_DIR);mkdir build;cd build;cmake -G Xcode .. ;xcodebuild -configuration Release
else
	@cd $(KCOV_DIR);mkdir build;cd build;cmake .. ;make
endif
$(TEST_LIST): $(KCOV_EXE)
	@$(ECHO) -n "Generating coverage report for execution test: "$@"..."
	@$(KCOV_EXE) .test/coverage $@
	@$(ECHO) "Done."
kcov_exe: $(EXE_TESTS)

# Generate and upload all coverage information
kcov: kcov_exe
	@$(ECHO) -n "Finalizing Codecov integration..."
	@bash -c "bash <(curl -s https://codecov.io/bash) -t $(KCOV_TOKEN)"
	@$(ECHO) "Done."

# Clean-up
clean:
	@rm -rf build_test .test/kcov.tgz $(KCOV_DIR) .test/coverage
