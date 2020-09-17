#include "broker.hpp"
using namespace std;

int main() {
    cout << "Hello, Broker!" << endl;
    Broker* test = new Broker();
    test->mediate();
}