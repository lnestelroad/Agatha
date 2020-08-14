#include "server.hpp"
#include <assert.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include "zmqpp/zmqpp.hpp"

using namespace std;
using namespace zmqpp;

mdwrk::mdwrk(string broker, string service, int verbose) {
    ctx = context();
    broker = broker;
    service = service;
    verbose = verbose;
    heartbeat = 2500;
    reconnect = 2500;
    s_mdwrk_connect_to_broker();
}

mdwrk::~mdwrk() {
    ctx.terminate();
    worker->close();
}

void mdwrk::s_mdwrk_connect_to_broker() {
    if (worker) {
        worker->close();
    }
    *worker = socket(ctx, zmqpp::socket_type::dealer);
    worker->connect(broker);
    // TODO: log this if verbose on

    message* msg = new message();
    s_mdwrk_send_to_broker(MDPW_READY, service, msg);
    // liveness = heartbeat;
    // auto now = chrono::system_clock::now();
    // auto now_ms =
    // std::chrono::time_point_cast<std::chrono::milliseconds>(now); auto value
    // = now_ms.time_since_epoch(); heartbeat_at = value.count() + heartbeat;
}

//  Send message to broker
//  If no msg is provided, creates one internally
void mdwrk::s_mdwrk_send_to_broker(string command,
                                   string option,
                                   message* msg) {
    zmqpp::message reply;
    reply.push_back("");
    reply.push_back(MDPW_WORKER);
    reply.push_back(command);

    if (!option.empty())
        reply.push_back(option);

    if (msg->parts() != 0)
        reply.push_back(msg->get(0));

    worker->send(reply);
}

void mdwrk::mdwrk_set_heartbeat(int heartbeat) {
    heartbeat = heartbeat;
}

void mdwrk::mdwrk_set_reconnect(int reconnect) {
    reconnect = reconnect;
}

//  This is the recv method; it's a little misnamed because it first sends
//  any reply and then waits for a new request. If you have a better name
//  for this, let me know.

//  Send reply, if any, to broker and wait for next request.
message mdwrk::mdwrk_recv(message reply) {
    if (reply.parts() != 0) {
        s_mdwrk_send_to_broker(MDPW_REPLY, NULL, &reply);
    }

    message ret;
    auto ReqEvent = [this, &ret]() {
        message request;
        string command;
        worker->receive(request);
        ret.copy(request);

        // liveness = HEARTBEAT_LIVENESS;

        assert(request.parts() >= 3);
        assert(request.get(0).compare(""));
        assert(request.get(1).compare(MDPW_WORKER));
        command = request.get(2);

        // if (command == MDPW_REQUEST) {
        reply_to = request.get(3);
        return request;
        // } else if (command == MDPW_DISCONNECT) {
        //     s_mdwrk_connect_to_broker();
        // } else if (--liveness == 0) {
        //     zmq_sleep(reconnect);
        //     s_mdwrk_connect_to_broker();
        // }

        // auto now = chrono::system_clock::now();
        // auto now_ms =
        //     std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        // auto value = now_ms.time_since_epoch();

        // if (value.count() > heartbeat_at) {
        //     s_mdwrk_send_to_broker(MDPW_HEARTBEAT, NULL, NULL);
        //     auto now = chrono::system_clock::now();
        //     auto now_ms =
        //         std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        //     auto value = now_ms.time_since_epoch();
        //     heartbeat_at = value.count() + heartbeat;
        // }
    };
    reactor Reactor;
    Reactor.add(*worker, ReqEvent);
    Reactor.poll();

    return ret;
}