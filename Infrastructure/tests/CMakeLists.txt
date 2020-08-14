add_executable(Amon_Din_client client_test.cpp)
target_link_libraries(Amon_Din_client PUBLIC zmq zmqpp sodium)
target_include_directories(Amon_Din_client PUBLIC
    "${Amon_Din_BINARY_DIR}/prefix/libzmq/include"
    "${Amon_Din_BINARY_DIR}/prefix/zmqpp/include"
    "${Amon_Din_BINARY_DIR}/prefix/libsodium/include"
)

add_executable(Amon_Din_server server_test.cpp)
target_link_libraries(Amon_Din_server PUBLIC zmq zmqpp sodium)
target_include_directories(Amon_Din_server PUBLIC
    "${Amon_Din_BINARY_DIR}/prefix/libzmq/include"
    "${Amon_Din_BINARY_DIR}/prefix/zmqpp/include"
    "${Amon_Din_BINARY_DIR}/prefix/libsodium/include"
)

