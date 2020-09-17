/**
 * Server_test.cpp
 *
 * Summary: Tester file for simulating a zmq server
 */

#include <assert.h>
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
    cout << "Hello, World from server!" << endl;

    context ctx;
    socket_type type = socket_type::router;
    socket* Reply = new socket(ctx, type);
    Reply->close();
    delete (Reply);

    Reply = new socket(ctx, type);
    Reply->bind("tcp://*:5555");
    // Reply.close();

    message msg;

    while (1) {
        // receive the message
        zmqpp::message message;
        zmqpp::message reply;
        // decompose the message
        Reply->receive(message);

        for (int i = 0; i < message.parts(); i++)
            cout << message.get(i) << endl;

        reply.push_back(message.get(0));
        reply.push_back("");
        reply.push_back("Thx bro");

        Reply->send(reply);
    }
}

// reactor Reactor;
// string data;

// auto RepListener = [&Reply, &data]() {
//     message payload;
//     Reply.receive(payload);

//     assert(payload.parts() >= 3);
//     assert(payload.get(0) == "");
//     assert(payload.get(1) == MDPC_CLIENT);
//     message rep_msg;
//     if (payload.get(2) == MDPW_REQUEST) {
//         data = payload.get(4);
//         rep_msg.push_back(data);

//     } else if (payload.get(2) == MDPW_HEARTBEAT) {
//         rep_msg.push_back(MDPW_HEARTBEAT);
//     }

//     Reply.send(rep_msg);
// };

// Reactor.add(Reply, RepListener);
// Reactor.poll();

// cout << "Message from client: " << data << endl;
