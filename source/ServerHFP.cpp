//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel) : ServerBluetooth(channel), SdpHFP() {
    this->registerRecord(channel);
    this->addCommand(*this, "testttt", &ServerHFP::test);
    this->addCommand(*this, "tuust", &ServerHFP::test);
    this->parseCommand("tuust");

};

ServerHFP::~ServerHFP(){}

void ServerHFP::test(std::string const &hum) {
    std::cout << hum << " yees" << std::endl;
    std::cout << this->getServerName() << std::endl;
}
