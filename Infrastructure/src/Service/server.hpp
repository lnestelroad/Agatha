#ifndef ADP_SERVER_H
#define ADP_SERVER_H

#include <signal.h>
#include <iostream>
#include <sstream>
#include <string>
#include "zmqpp/zmqpp.hpp"
#define HEARTBEAT_LIVENESS 3  //  3-5 is reasonable

//  This is the version of ADP/Client we implement
#define ADPC_CLIENT "ADPC01"

//  This is the version of ADP/Service we implement
#define ADPS_SERVICE "ADPS01"

//  MDP/Server commands, as strings
#define ADPS_READY "\001"
#define ADPS_REQUEST "\002"
#define ADPS_REPLY "\003"
#define ADPS_HEARTBEAT "\004"
#define ADPS_DISCONNECT "\005"

// Command to terminate the broker loop
#define ADP_TERMINATE "\006"

class adserver {
   private:
    zmqpp::context ctx;
    std::string broker;
    zmqpp::socket* server;

    std::string service_name;

   public:
    adserver(std::string name);
    ~adserver();

    void register_with_broker();
    void start();
};

#endif