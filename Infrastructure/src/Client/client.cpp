//  Hello World client

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <thread>

#include "client.hpp"

using namespace std;
using namespace zmqpp;

adcli::adcli() {
    ctx = context();
    broker = "tcp://localhost:5555";  //  Before we abandon
    client = new socket(ctx, socket_type::req);

    connect_broker();
}

adcli::adcli(string broker, int verbose) {
    ctx = context();
    broker = broker;
    verbose = verbose;

    connect_broker();
}

adcli::~adcli() {
    client->close();
    delete (client);

    ctx.terminate();
}

void adcli::connect_broker() {
    client->close();
    delete (client);

    client = new socket(ctx, socket_type::req);
    client->connect(broker);
}

message adcli::adcli_send(string command, string service, string payload) {
    message request;

    // message header
    request.push_back(command);
    request.push_back(service);

    // delimeter frame: end of header
    request.push_back("");

    // actual message
    request.push_back(payload);

    client->send(request);

    cout << "Wating for response ..." << endl;
    zmqpp::message response;
    client->receive(response);
    cout << response.get(1) << endl;

    return request;
}

// mdcli::mdcli() {
//     ctx = context();
//     broker = "tcp://127.0.0.1:5426";
//     verbose = 1;
//     timeout = 2500;  //  msecs
//     retries = 3;     //  Before we abandon
//     client = new socket(ctx, socket_type::req);

//     s_mdcli_connect_to_broker();
// }

// mdcli::mdcli(string broker, int verbose) {
//     ctx = context();
//     broker = broker;
//     verbose = verbose;
//     timeout = 2500;  //  msecs
//     retries = 3;     //  Before we abandon

//     s_mdcli_connect_to_broker();
//     // signal(SIGINT, my_signal_handler);
// }

// mdcli::~mdcli() {
//     client->close();
//     delete (client);

//     ctx.terminate();
// }

// void mdcli::s_mdcli_connect_to_broker() {
//     client->close();
//     delete (client);

//     client = new socket(ctx, socket_type::req);
//     client->connect(broker);
//     // TODO: Add logging event here if verbose
// }

// void mdcli::mdcli_set_timeout(int _timeout) {
//     timeout = _timeout;
// }

// void mdcli::mdcli_set_retries(int _retries) {
//     retries = _retries;
// }

// //  Here is the send method. It sends a request to the broker and gets
// //  a reply even if it has to retry several times. It takes ownership of
// //  the request message, and destroys it when sent. It returns the reply
// //  message, or NULL if there was no reply after multiple attempts:
// message mdcli::mdcli_send(string service, message* request) {
//     //  Prefix request with protocol frames
//     //  Frame 1: "MDPCxy" (six bytes, MDP/Client x.y)
//     //  Frame 2: Service name (printable string)

//     client->send(*request);

//     cout << "Wating for response ..." << endl;
//     zmqpp::message response;
//     client->receive(response);
//     cout << "Response from " << response.get(0) << endl;

//     return request;
// }