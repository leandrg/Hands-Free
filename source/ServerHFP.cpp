//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel) : ServerBluetooth(channel), SdpHFP() {
    this->registerRecord(channel);
};

ServerHFP::~ServerHFP(){}