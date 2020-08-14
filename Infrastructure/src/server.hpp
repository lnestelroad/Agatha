
#include <signal.h>
#include <iostream>
#include <map>
#include <string>
#include "zmqpp/zmqpp.hpp"
#define HEARTBEAT_LIVENESS 3  //  3-5 is reasonable

#define MDPW_WORKER "MDPW01"

//  MDP/Server commands, as strings
#define MDPW_READY "\001"
#define MDPW_REQUEST "\002"
#define MDPW_REPLY "\003"
#define MDPW_HEARTBEAT "\004"
#define MDPW_DISCONNECT "\005"

class mdwrk {
   public:
    // mdwrk();
    mdwrk(std::string broker, std::string service, int verbose);
    ~mdwrk();
    void s_mdwrk_connect_to_broker();
    void s_mdwrk_send_to_broker(std::string command,
                                std::string option,
                                zmqpp::message* msg);
    void mdwrk_set_heartbeat(int heartbeat);
    void mdwrk_set_reconnect(int reconnect);
    zmqpp::message mdwrk_recv(zmqpp::message);

   private:
    zmqpp::context_t ctx;  //  Our context
    std::string broker;
    std::string service;
    zmqpp::socket* worker;  //  Socket to broker
    int verbose;            //  Print activity to stdout

    //  Heartbeat management
    uint64_t heartbeat_at;  //  When to send HEARTBEAT
    size_t liveness;        //  How many attempts left
    int heartbeat;          //  Heartbeat delay, msecs
    int reconnect;          //  Reconnect delay, msecs

    std::string reply_to;  //  Return identity, if any
};

//  This is the recv method; it's a little misnamed because it first sends
//  any reply and then waits for a new request. If you have a better name
//  for this, let me know.

//  Send reply, if any, to broker and wait for next request.

// zmsg_t* mdwrk_recv(mdwrk_t* self, zmsg_t** reply_p) {
//     //  Format and send the reply if we were provided one
//     assert(reply_p);
//     zmsg_t* reply = *reply_p;
//     assert(reply || !self->expect_reply);
//     if (reply) {
//         assert(self->reply_to);
//         zmsg_wrap(reply, self->reply_to);
//         s_mdwrk_send_to_broker(self, MDPW_REPLY, NULL, reply);
//         zmsg_destroy(reply_p);
//     }
//     self->expect_reply = 1;

//     while (true) {
//         zmq_pollitem_t items[] = {{self->worker, 0, ZMQ_POLLIN, 0}};
//         int rc = zmq_poll(items, 1, self->heartbeat * ZMQ_POLL_MSEC);
//         if (rc == -1)
//             break;  //  Interrupted

//         if (items[0].revents & ZMQ_POLLIN) {
//             zmsg_t* msg = zmsg_recv(self->worker);
//             if (!msg)
//                 break;  //  Interrupted
//             if (self->verbose) {
//                 zclock_log("I: received message from broker:");
//                 zmsg_dump(msg);
//             }
//             self->liveness = HEARTBEAT_LIVENESS;

//             //  Don't try to handle errors, just assert noisily
//             assert(zmsg_size(msg) >= 3);

//             zframe_t* empty = zmsg_pop(msg);
//             assert(zframe_streq(empty, ""));
//             zframe_destroy(&empty);

//             zframe_t* header = zmsg_pop(msg);
//             assert(zframe_streq(header, MDPW_WORKER));
//             zframe_destroy(&header);

//             zframe_t* command = zmsg_pop(msg);
//             if (zframe_streq(command, MDPW_REQUEST)) {
//                 //  We should pop and save as many addresses as there are
//                 //  up to a null part, but for now, just save one…
//                 self->reply_to = zmsg_unwrap(msg);
//                 zframe_destroy(&command);
//                 //  Here is where we actually have a message to process; we
//                 //  return it to the caller application:

//                 return msg;  //  We have a request to process
//             } else if (zframe_streq(command, MDPW_HEARTBEAT))
//                 ;  //  Do nothing for heartbeats
//             else if (zframe_streq(command, MDPW_DISCONNECT))
//                 s_mdwrk_connect_to_broker(self);
//             else {
//                 zclock_log("E: invalid input message");
//                 zmsg_dump(msg);
//             }
//             zframe_destroy(&command);
//             zmsg_destroy(&msg);
//         } else if (--self->liveness == 0) {
//             if (self->verbose)
//                 zclock_log("W: disconnected from broker - retrying…");
//             zclock_sleep(self->reconnect);
//             s_mdwrk_connect_to_broker(self);
//         }
//         //  Send HEARTBEAT if it's time
//         if (zclock_time() > self->heartbeat_at) {
//             s_mdwrk_send_to_broker(self, MDPW_HEARTBEAT, NULL, NULL);
//             self->heartbeat_at = zclock_time() + self->heartbeat;
//         }
//     }
//     if (zctx_interrupted)
//         printf("W: interrupt received, killing worker…\n");
//     return NULL;
// }
