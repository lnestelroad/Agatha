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

ExternalProject_Add(
    libsodium
    SOURCE_DIR ${Amon_Din_SOURCE_DIR}/
    INSTALL_DIR "${Amon_Din_BINARY_DIR}/prefix/libsodium"
    CONFIGURE_COMMAND ${Amon_Din_SOURCE_DIR}/thirdparty-repos/libsodium/configure --prefix=<INSTALL_DIR>
)

ExternalProject_Add(
    libzmq
	SOURCE_DIR "${Amon_Din_SOURCE_DIR}/thirdparty-repos/libzmq/"
	INSTALL_DIR "${Amon_Din_BINARY_DIR}/prefix/libzmq"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Add(
    libzmqpp
	SOURCE_DIR "${Amon_Din_SOURCE_DIR}/thirdparty-repos/zmqpp/"
	INSTALL_DIR "${Amon_Din_BINARY_DIR}/prefix/zmqpp"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)



# target_link_libraries(zmqpp INTERFACE zmq)
add_library(sodium STATIC IMPORTED)
set_target_properties(sodium PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/libsodium/lib/libsodium.a"    
)

add_library(zmq STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(zmq PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/libzmq/lib/libzmq.a"
)
add_library(zmqpp STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(zmqpp PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/zmqpp/lib/libzmqpp-static.a"
)

include_directories(${Amon_Din_SOURCE_DIR}/thirdparty-repos/toml11)