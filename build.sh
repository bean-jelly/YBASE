#!/bin/sh

set -x

SOURCE_DIR = pwd
BUILD_DIR=${BUILD_DIR:-../build}
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install-cpp11}
BUILD_NO_EXAMPLES=${BUILD_NO_EXAMPLES:-0}