#include <iostream>
#include <string>
#include "client.hpp"

using namespace std;
using namespace zmqpp;

int main(int argc, char* argv[]) {
    cout << "Hello, Client!" << endl;

    adcli* client = new adcli();
    client->connect_broker();

    string ServiceName, Payload;

    if (argc == 1) {
        cout << "Enter service to send to: ";
        cin >> ServiceName;

        cout << "What would you like to say?: ";
        cin >> Payload;
    } else {
        ServiceName = argv[1];
        Payload = argv[2];
    }
    client->adcli_send(ADPC_CLIENT, ServiceName, Payload);
}