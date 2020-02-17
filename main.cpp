//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include       "ServerHFP.hpp"
#include <iostream>

int main() {
    ServerHFP hfp = ServerHFP();

    hfp.start();
    hfp.listen();
    getchar();
    hfp.stop();
    return 0;
}