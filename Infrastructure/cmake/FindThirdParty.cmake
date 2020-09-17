# FindThirdParty.cmake
# -----------------------------------------------------------------------------
# This file contains cmake macros to used to find and include all of the zmq
# libs and include files
#
# To use these macros include this file in your CMakeLists.txt file:
# INCLUDE(FindThirdParty)
#
# https://stackoverflow.com/questions/28597351/how-do-i-add-a-library-path-in-cmake
# https://stackoverflow.com/questions/5971921/building-a-library-using-autotools-from-cmake
#------------------------------------------------------------------------------


include(ExternalProject)

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ REQUIRED ${Amon_Din_BINARY_DIR}/prefix/libzmq/lib64/pkgconfig/libzmq.pc)

ExternalProject_Add(
    libzmqpp
	SOURCE_DIR "${Amon_Din_SOURCE_DIR}/thirdparty-repos/zmqpp/"
	INSTALL_DIR "${Amon_Din_BINARY_DIR}/prefix/zmqpp"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DZEROMQ_INCLUDE=${PC_ZeroMQ_INCLUDEDIR} -DZEROMQ_LIBRARY_SHARED=${PC_ZeroMQ_LIBRARY_DIRS}64/libzmq.so -DZEROMQ_LIBRARY_STATIC=${PC_ZeroMQ_LIBRARY_DIRS}64/libzmq.so
)

add_library(zmqpp SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(zmqpp PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/zmqpp/lib/libzmqpp.so"
)


include_directories(${Amon_Din_SOURCE_DIR}/thirdparty-repos/toml11)