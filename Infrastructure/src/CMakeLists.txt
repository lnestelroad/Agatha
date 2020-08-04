add_executable(Amon_Server server.cpp)
target_link_libraries(Amon_Server PUBLIC zmq zmqpp sodium)

add_executable(Amon_Client client.cpp)
target_link_libraries(Amon_Client PUBLIC zmq zmqpp sodium)