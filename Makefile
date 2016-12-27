CC ?= gcc
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
TEST_DIR ?= ./test
TEST_BUILD_DIR ?= ${BUILD_DIR}/test
TEST_MAKEFILE = ${TEST_BUILD_DIR}/MakefileTestSupport
OBJ ?= ${BUILD_DIR}/obj
OBJ_DIR = ${OBJ}
CMOCK_DIR ?= ./CMock

default: all

all: test

${TEST_MAKEFILE}:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${OBJ}
	CMOCK_DIR=${CMOCK_DIR} ruby ${CMOCK_DIR}/scripts/create_makefile.rb

clean:
	rm -rf ${BUILD_DIR}

-include ${TEST_MAKEFILE}

