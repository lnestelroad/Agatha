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

add_library(zmq SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(zmq PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/libzmq/lib64/libzmq.so"
)

# target_link_libraries(zmqpp INTERFACE zmq)
add_library(sodium SHARED IMPORTED)
set_target_properties(sodium PROPERTIES
    IMPORTED_LOCATION "${Amon_Din_BINARY_DIR}/prefix/libsodium/lib64/libsodium.so"
)
