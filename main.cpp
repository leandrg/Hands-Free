//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include       "ServerHFP.hpp"

int main() {
    ServerHFP hfp = ServerHFP();
    hfp.start();
    std::cout << hfp.getServerName() << std::endl;
//    hfp.listen();
    hfp.stop();
    return 0;
}