# This makefile deals with all CI processing 
# of the gbpHome repository

.PHONY: test clean

# Set the KCov token for this project
KCOV_TOKEN="74c531b7-23f1-4914-bd15-36b32a6bf144"

# List the executable tests that will be run
EXE_TESTS = 

# This ensures that we use standard (what is used in interactive shells) version of echo.
ECHO = /bin/echo

# Set the build directory
BUILD_DIR = $(PWD)/build-test

# Determine what sort of environment we're in (eg. OSX or Linux)
# Set linux defaults
KCOV_DIR='test/kcov-master'
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

# Set USE_XXX values
# There should be a block here for every optional
# environment variable affecting the build
USE_FLAGS := 

# USE_MPI
ifndef USE_MPI
	USE_MPI := ON
endif
ifeq ($(USE_MPI),ON)
	USE_FLAGS := $(USE_FLAGS) -DUSE_MPI=ON
else
	override USE_MPI := OFF
	USE_FLAGS := $(USE_FLAGS) -DUSE_MPI=OFF
endif

# USE_MPI_IO
ifndef USE_MPI_IO
	USE_MPI_IO := OFF
endif
ifeq ($(USE_MPI_IO),ON)
	USE_FLAGS := $(USE_FLAGS) -DUSE_MPI_IO=ON
else
	override USE_MPI_IO := OFF
	USE_FLAGS := $(USE_FLAGS) -DUSE_MPI_IO=OFF
endif

# USE_CUDA
ifndef USE_CUDA
	USE_CUDA := OFF
endif
ifeq ($(USE_CUDA),ON)
	USE_FLAGS := $(USE_FLAGS) -DUSE_CUDA=ON
else
	override USE_CUDA := OFF
	USE_FLAGS := $(USE_FLAGS) -DUSE_CUDA=OFF
endif

# USE_DOUBLE
ifndef USE_DOUBLE
	USE_DOUBLE := OFF
endif
ifeq ($(USE_DOUBLE),ON)
	USE_FLAGS := $(USE_FLAGS) -DUSE_DOUBLE=ON
else
	override USE_DOUBLE := OFF
	USE_FLAGS := $(USE_FLAGS) -DUSE_DOUBLE=OFF
endif

# Build mpi if needed and not found
mpi:
ifeq ($(USE_MPI),ON)
ifneq (, $(shell which mpicc))
	@$(ECHO) "mpicc found."
else
	@$(ECHO) "Building MPI..."
	@$(ECHO) -n "   Fetching MPI..."
	@wget http://www.mpich.org/static/downloads/3.2/mpich-3.2.tar.gz 
	@tar xfz mpich-3.2.tar.gz 
	@rm mpich-3.2.tar.gz 
	@$(ECHO) "Done."
	@$(ECHO) -n "   Configuring and building..."
	@cd mpich-3.2               && \
	./configure                    \
	   --prefix=`pwd`/../mpich     \
	   --enable-static=false       \
	   --enable-alloca=true        \
	   --disable-long-double       \
	   --enable-threads=single     \
	   --enable-fortran=no         \
	   --enable-fast=all           \
	   --enable-g=none             \
	   --enable-timing=none     && \
	make -j4                    && \
	make install                && \
	cd -                        && \
	rm -rf mpich-3.2
	@$(ECHO) "Done."
	@$(ECHO) "Done."
endif
endif

# Generate build tests for the CI service.  This assumes that
# all wanted build flags have been set in the environment
# variable $(USE_FLAGS)
test_build:
	@$(ECHO) "Performing build test:"
	@mkdir -p $(BUILD_DIR)                                    && \
	cd $(BUILD_DIR)                                           && \
	cmake .. $(USE_FLAGS) -DCMAKE_INSTALL_PREFIX=$(BUILD_DIR) && \
	make install 
	@$(ECHO) "Build passed with USE_FLAGS={"$(USE_FLAGS)"}"

# Execution tests
$(EXE_TESTS):
	@$(ECHO) "Running execution test: "$@
	@$(BUILD_DIR)/bin/$@
	@$(ECHO) "Done."

# Run all tests
tests: mpi test_build $(EXE_TESTS)

# Generate coverage information for executable tests
.test/kcov.tgz:
	@$(ECHO) -n "Downloading kcov code..."
	@wget https://github.com/SimonKagstrom/kcov/archive/master.tar.gz -O test/kcov.tgz
	@tar xfz test/kcov.tgz -C test
	@$(ECHO) "Done."
$(KCOV_EXE): test/kcov.tgz
ifeq ($(_MAC_BUILD),1)
	@cd $(KCOV_DIR);mkdir build;cd build;cmake -G Xcode .. ;xcodebuild -configuration Release
else
	@cd $(KCOV_DIR);mkdir build;cd build;cmake .. ;make
endif
$(TEST_LIST): $(KCOV_EXE)
	@$(ECHO) -n "Generating coverage report for execution test: "$@"..."
	@$(KCOV_EXE) test/coverage $@
	@$(ECHO) "Done."
kcov_exe: $(EXE_TESTS)

# Generate and upload all coverage information
kcov: kcov_exe
	@$(ECHO) -n "Finalizing Codecov integration..."
	@bash -c "bash <(curl -s https://codecov.io/bash) -t $(KCOV_TOKEN)"
	@$(ECHO) "Done."

# Clean-up
clean:
	@rm -rf $(BUILD_DIR) test/kcov.tgz $(KCOV_DIR) test/coverage mpich-3.2 

