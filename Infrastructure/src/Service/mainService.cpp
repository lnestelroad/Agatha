#include "server.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello, Server!" << endl;

    string ServiceName;
    if (argc == 1) {
        cout << "Enter a name for this service: ";
        cin >> ServiceName;
    } else {
        ServiceName = argv[1];
        cout << "Registering as " << ServiceName << endl;
    }
    adserver* test = new adserver(ServiceName);
    test->start();
}