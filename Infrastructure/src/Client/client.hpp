#ifndef ADP_CLIENT_H
#define ADP_CLIENT_H

#include <signal.h>
#include <iostream>
#include <map>
#include <string>
#include "zmqpp/zmqpp.hpp"

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

class adcli {
   public:
    adcli();
    adcli(std::string broker, int verbose);
    ~adcli();
    void connect_broker();
    zmqpp::message adcli_send(std::string command,
                              std::string service,
                              std::string payload);

   private:
    zmqpp::context ctx;  //  Our context
    std::string broker;
    zmqpp::socket* client;  //  Socket to broker
};

// class mdcli {
//    public:
//     mdcli();
//     mdcli(std::string broker, int verbose);
//     ~mdcli();
//     void s_mdcli_connect_to_broker();
//     void mdcli_set_timeout(int timeout);
//     void mdcli_set_retries(int retries);
//     zmqpp::message mdcli_send(std::string service, zmqpp::message*
//     request_p);

//    private:
//     zmqpp::context ctx;  //  Our context
//     std::string broker;
//     zmqpp::socket* client;  //  Socket to broker
//     int verbose;            //  Print activity to stdout
//     int timeout;            //  Request timeout
//     int retries;            //  Request retries
// };

#endif