/*************************************************************************
 * client_test.cpp
 *
 * Summary: Tester file for simulating a zmq client
 ************************************************************************/

#include <iostream>
#include <string>
#include "zmqpp/zmqpp.hpp"

#define MDPC_CLIENT "MDPC01"
#define MDPW_WORKER "MDPW01"

//  MDP/Server commands, as strings
#define MDPW_READY "\001"
#define MDPW_REQUEST "\002"
#define MDPW_REPLY "\003"
#define MDPW_HEARTBEAT "\004"
#define MDPW_DISCONNECT "\005"

using namespace std;
using namespace zmqpp;

int main(int argc, char* argv[]) {
    cout << "Hello, World from client!" << endl;

    context ctx;
    socket_type type = socket_type::req;
    socket Request = socket(ctx, type);

    Request.connect("tcp://127.0.0.1:5426");

    message msg;
    msg.push_back("");
    msg.push_back(MDPC_CLIENT);
    msg.push_back(MDPW_REQUEST);
    msg.push_back("");
    msg.push_back("echo");

    Request.send(msg);

    message rec;
    Request.receive(rec);
    cout << "Message from server: " << rec.get(0) << endl;
}