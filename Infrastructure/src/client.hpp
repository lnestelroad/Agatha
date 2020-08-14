#ifndef ADP_CLIENT_H
#define ADP_CLIENT_H

#include <signal.h>
#include <iostream>
#include <map>
#include <string>
#include "zmqpp/zmqpp.hpp"

#define MDPC_CLIENT "MDPC01"

// static volatile bool interrupted = false;

// void my_signal_handler(int) {
//     std::cout << "signal" << std::endl;
//     interrupted = true;
// }

// signal(SIGINT, my_signal_handler);

class mdcli {
   public:
    mdcli();
    mdcli(std::string broker, int verbose);
    ~mdcli();
    void s_mdcli_connect_to_broker();
    void mdcli_set_timeout(int timeout);
    void mdcli_set_retries(int retries);
    zmqpp::message mdcli_send(std::string service, zmqpp::message* request_p);

   private:
    zmqpp::context ctx;  //  Our context
    std::string broker;
    zmqpp::socket* client;  //  Socket to broker
    int verbose;            //  Print activity to stdout
    int timeout;            //  Request timeout
    int retries;            //  Request retries
};

#endif