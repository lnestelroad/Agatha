// Broker.hpp
//=============================================================================
//  Broker header file for the messages bus infrastructure
//
// $Revision$
//
// Author: Liam Nestelroad
//=============================================================================

#ifndef ADP_BROKER_H
#define ADP_BROKER_H

// #include <ctime>
#include <assert.h>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include "zmqpp/zmqpp.hpp"

#define endpoint "tcp://*:5426"

//  We'd normally pull these from config data

#define HEARTBEAT_LIVENESS 3     //  3-5 is reasonable
#define HEARTBEAT_INTERVAL 2500  //  msecs
#define HEARTBEAT_EXPIRY HEARTBEAT_INTERVAL* HEARTBEAT_LIVENESS

//  This is the version of MDP/Client we implement
#define ADPC_CLIENT "ADPC01"

//  This is the version of MDP/Worker we implement
#define ADPS_SERVICE "ADPS01"

//  MDP/Server commands, as strings
#define ADPS_READY "\001"
#define ADPS_REQUEST "\002"
#define ADPS_REPLY "\003"
#define ADPS_HEARTBEAT "\004"
#define ADPS_DISCONNECT "\005"

// Internal broker commands
#define ADP_TERMINATE "\006"
#define ADP_INTERNAL "\007"

typedef struct service {
    std::string address;
    std::string label;
    std::string name;
    // int expiry;
    bool busy;

    // TODO: Add queue structure here for multiple requests.
} service;

class Broker {
   private:
    zmqpp::reactor* Reactor;
    std::deque<service> services;

    zmqpp::context ctx;
    zmqpp::socket* entry_point;

   public:
    Broker();
    ~Broker();

    void bind();
    void close();

    void mediate();
    void process_client(zmqpp::message* msg);
    void process_service(zmqpp::message* msg);
    void register_service(zmqpp::message* msg);
    void delete_service(zmqpp::message* msg);

    service* find_service(std::string name);

    // void service_internal(service service, zmqpp::message msg);
    // void send_heartbeat();
};

//  The broker class defines a single broker instance:

// typedef struct service_t {
//     std::string name;
//     std::string IP;
//     std::string port;

//     bool occupied;
//     int heartbeat;
// } service_t;

// class MajorDomoBroker {
//    private:
//     zmqpp::context ctx;
//     zmqpp::socket* client_side;
//     zmqpp::socket* service_side;
//     zmqpp::reactor Reactor;

//     // std::list<service_t> services;

//     // uint64_t heartbeat_at;

//    public:
//     MajorDomoBroker();
//     ~MajorDomoBroker();

//     void bind();
//     void close();

//     void mediate();
//     // void process_client(std::string sender, zmqpp::message msg);
//     // void process_service(std::string sender, zmqpp::message msg);

//     // void send_to_service(service_t service,
//     //                      std::string command,
//     //                      std::string option,
//     //                      zmqpp::message msg);

//     // void delete_service(bool timout);
//     // void send_heartbeats();
// };

#endif