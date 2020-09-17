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

Broker::Broker() {
    ctx = context();
    Reactor = new reactor();
    entry_point = new socket(ctx, socket_type::router);
    entry_point->bind("tcp://*:5555");
}

Broker::~Broker() {
    delete Reactor;
    delete entry_point;

    ctx.terminate();
}

void Broker::bind() {
    // Close the sockets if they already exist
    close();

    // Make new socket connections
    entry_point = new socket(ctx, socket_type::router);
    entry_point->bind("tcp://*:5555");
}

void Broker::close() {
    entry_point->close();
    delete (entry_point);
}

void Broker::mediate() {
    cout << "Broker is now listening on port 5555" << endl;
    while (true) {
        message msg;
        entry_point->receive(msg);

        // cout << msg.parts() << endl;
        // for (int i = 0; i < msg.parts(); i++) {
        //     cout << msg.get(i) << endl;
        // }

        if (msg.get(2) == ADPC_CLIENT) {
            process_client(&msg);
            cout << "[LOG] Message Received" << endl;
        } else if (msg.get(2) == ADPS_SERVICE) {
            register_service(&msg);
            cout << "[LOG] Service Registered." << endl;
        } else if (msg.get(2) == ADPS_READY) {
            // TODO: Make the service avaliable again.
            // service* worker = find_service(msg.get(3));
            // worker->busy = false;
        } else if (msg.get(2) == ADPS_REPLY) {
            process_service(&msg);
        } else if (msg.get(2) == ADP_TERMINATE) {
            cout << "Shutting down. Good bye!" << endl;
            entry_point->send(msg);
            break;
        } else {
            cout << "Not command provided" << endl;
        }
    }
}

void Broker::process_client(message* msg) {
    message rep;

    // Needed to get the return address of client
    rep.push_back(msg->get(0));
    rep.push_back(msg->get(1));

    // Empty frame needed for spacing between hearder. Otherwise
    // message dropped
    rep.push_back("");
    // rep.push_back("Broker");

    service Test;
    Test.name = "TestService";
    Test.address = "127.0.0.1:5555";
    Test.busy = false;

    // services.push_back(Test);
    string requested_service = msg->get(3);
    service* found = find_service(requested_service);

    if (found != nullptr && found->busy != true) {
        rep.push_front(found->address);
        rep.push_front(found->label);

        // TODO: make sure to iterate through the whole message until the
        // delimiter is found. Then push the payload on the the request message.
        rep.push_back(msg->get(5));
        // found->busy = true;
        if (msg->get(5) == "Exit") {
            message Exit;
            Exit.push_back(msg->get(0));
            Exit.push_back(msg->get(1));
            Exit.push_back("");
            Exit.push_back("Service Terminated");
            entry_point->send(Exit);
        }

    } else if (found->busy == true) {
        // TODO: Implement a queue for each service to stack up requests rather
        // than dropping.
        rep.push_back("Service is currently occupied. Please try again later");
    } else {
        rep.push_back("Requested service is not currently registered");
    }

    entry_point->send(rep);
}

void Broker::process_service(message* msg) {
    message to_client;

    to_client.push_back(msg->get(4));
    to_client.push_back(msg->get(5));
    to_client.push_back("");
    to_client.push_back(msg->get(7));

    entry_point->send(to_client);
}

void Broker::register_service(message* msg) {
    message rep;
    service NS;

    NS.label = msg->get(0);
    NS.address = msg->get(1);
    NS.name = msg->get(3);  // Frame which will hold the services name.
    services.push_back(NS);

    // Needed to get the return address of client
    rep.push_back(msg->get(0));
    rep.push_back(msg->get(1));

    // Empty frame needed for spacing between hearder. Otherwise
    // message dropped
    rep.push_back("");
    rep.push_back("thx bro");

    entry_point->send(rep);
}

service* Broker::find_service(string requested_service) {
    stringstream ss;
    bool serviceFound = false;
    deque<service>::iterator it;

    for (it = services.begin(); it != services.end(); ++it) {
        // cout << it->name << endl;
        if (it->name == requested_service) {
            serviceFound = true;
            break;
        }
    }
    if (serviceFound == true) {
        return &*it;
    } else {
        return nullptr;
    }
}