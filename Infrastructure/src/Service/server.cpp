#include "server.hpp"
using namespace std;
using namespace zmqpp;

adserver::adserver(string name) {
    ctx = context();
    server = new socket(ctx, socket_type::req);
    broker = "tcp://localhost:5555";
    service_name = name;
}

adserver::~adserver() {
    server->close();
    delete (server);

    ctx.terminate();
}

void adserver::register_with_broker() {
    server->close();
    delete (server);

    server = new socket(ctx, socket_type::req);
    server->connect(broker);

    message registration, confirmation;
    registration.push_back(ADPS_SERVICE);
    registration.push_back(service_name);
    registration.push_back("");

    server->send(registration);
    server->receive(confirmation);

    assert(confirmation.get(1) == "thx bro");
    cout << "Registration with broker successfull!" << endl;
}

void adserver::start() {
    register_with_broker();
    message ready;
    ready.push_back(ADPS_READY);
    ready.push_back(service_name);
    server->send(ready);

    message request, response;
    while (1) {
        server->receive(request);
        cout << "Message from client: " << request.get(request.parts() - 1)
             << endl;

        // cout << request.parts() << endl;
        // for (int i = 0; i < request.parts(); i++) {
        //     cout << request.get(i) << endl;
        // }

        if (request.get(request.parts() - 1) == "Exit") {
            cout << "Service Shutting Down" << endl;
            break;
        }

        stringstream ss;
        ss << "Shalom from " << service_name << "bro!";

        response.push_back(ADPS_REPLY);
        response.push_back(service_name);
        response.push_back(request.get(0));
        response.push_back(request.get(1));
        response.push_back("");
        response.push_back(ss.str());
        server->send(response);
    }
}