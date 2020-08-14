#include <iostream>
#include <string>
#include "client.hpp"
#include "zmqpp/zmqpp.hpp"

using namespace std;
using namespace zmqpp;

int main(int argc, char* argv[]) {
    cout << "Hello, World!" << endl;

    mdcli* test = new mdcli();
    message* msg = new message;

    msg->push_back("ADPC01");
    msg->push_back("Hello form the first client");
    test->mdcli_send("blah", msg);
}