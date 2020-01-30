//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include       "ServerTCP.hpp"

int main() {
    ServerTCP tcp = ServerTCP(8083);
    tcp.start();
    tcp.listen();
    tcp.stop();
    return 0;
}