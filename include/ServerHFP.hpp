//
// Created by Gaëtan Léandre on 03/02/2020.
//

#ifndef         HANDS_FREE_SERVERHFP_HPP
#define         HANDS_FREE_SERVERHFP_HPP

#include        "ServerBluetooth.hpp"
#include        "SdpHFP.hpp"

class ServerHFP : public ServerBluetooth, protected SdpHFP {

public:
    void test(std::string const &hum);
    ServerHFP(uint8_t channel = 1);
    ~ServerHFP();
};


#endif          //HANDS_FREE_SERVERHFP_HPP
