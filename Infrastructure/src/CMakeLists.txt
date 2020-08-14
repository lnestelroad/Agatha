set(SOURCE
    server.cpp
    client.cpp
    broker.cpp
)

add_library(Amon_Din ${SOURCE})
target_link_libraries(Amon_Din PUBLIC zmq zmqpp sodium)
target_include_directories(Amon_Din PUBLIC
    "${Amon_Din_BINARY_DIR}/prefix/libzmq/include"
    "${Amon_Din_BINARY_DIR}/prefix/zmqpp/include"
    "${Amon_Din_BINARY_DIR}/prefix/libsodium/include"
)

add_executable(client main.cpp)
target_link_libraries(client Amon_Din)
target_include_directories(client PUBLIC ${CMAKE_SOURCE_DIR}/src/client.hpp)


add_executable(broker mainBroker.cpp)
target_link_libraries(broker Amon_Din)
target_include_directories(broker PUBLIC ${CMAKE_SOURCE_DIR}/src/broker.hpp)