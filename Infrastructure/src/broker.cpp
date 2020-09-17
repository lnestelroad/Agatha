// Broker.cpp
//=============================================================================
//  Broker implementation file for the messages bus infrastructure
//
// $Revision$
//
// Author: Liam Nestelroad
//=============================================================================

#include "broker.hpp"
using namespace std;
using namespace zmqpp;
































// MajorDomoBroker::MajorDomoBroker() {
//     ctx = context();
//     client_side = new socket(ctx, socket_type::router);
//     service_side = new socket(ctx, socket_type::dealer);

//     bind();
//     Reactor = reactor();
// }

// MajorDomoBroker::~MajorDomoBroker() {
//     close();
// }

// void MajorDomoBroker::bind() {
//     // Close the sockets if they already exist
//     close();

//     // Make new socket connections
//     client_side = new socket(ctx, socket_type::reply);
//     service_side = new socket(ctx, socket_type::dealer);

//     client_side->bind("tcp://*:5426");
//     service_side->bind("tcp://*:5427");
// }

// void MajorDomoBroker::close() {
//     client_side->close();
//     service_side->close();

//     delete (client_side);
//     delete (service_side);
// }

// void MajorDomoBroker::mediate() {
//     auto client_callback = [this] {
//         // Get message from client side socket
//         message msg;
//         client_side->receive(msg);

//         // TODO: Check for proper message structure
//         // TODO: log this event if verbose

//         cout << "The message is: " << to_string(msg.parts()) << endl;
//         for (int i = 0; i < msg.parts(); i++) {
//             cout << "Part " << i << ": " << msg.get(i) << endl;
//         }

//         message response;
//         response.push_back("thx");
//         client_side->send(response);
//         cout << "Message sent back to client" << endl;
//     };

//     Reactor.add(*client_side, client_callback);
//     while (Reactor.poll()) {
//     }
// }