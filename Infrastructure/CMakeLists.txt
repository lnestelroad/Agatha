# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
        You should create a separate directory for build files.
")
endif()


cmake_minimum_required(VERSION 3.5...3.16)
project(Amon_Din)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Sets up the compling 
include(ctest)
enable_testing()

#------------------------------------------------------------------------------
# Setup cmake build paths
#------------------------------------------------------------------------------

# Where to lookup cmake modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set output paths
OPTION(LIB_PATH "path to put compiled libs" "${CMAKE_BINARY_DIR}/lib")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

# # Install Options
# SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")

#------------------------------------------------------------------------------
# Cmake modules
#------------------------------------------------------------------------------
INCLUDE(FindThirdParty)
INCLUDE(Version)
INCLUDE(BuildInfo)
INCLUDE(Package)

# Include source code directories
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)