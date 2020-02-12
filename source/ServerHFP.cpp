//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel) : ServerBluetooth(channel), SdpHFP() {
    this->registerRecord(channel);
    this->addCommand(*this, HFP_COMMAND_SUCCESS, &ServerHFP::onSuccess);
    this->addCommand(*this, HFP_COMMAND_ERROR, &ServerHFP::onError);
    this->addCommand(*this, HFP_COMMAND_SUPPORTED_FEATURES, &ServerHFP::receiveSupportedFeatures);
};

ServerHFP::~ServerHFP(){}

void                    ServerHFP::onSuccess(ClientSocket *client, std::string const &str) {
    client->onSuccess(client, str);
}

void                    ServerHFP::onError(ClientSocket *client, std::string const &str) {
    client->onError(client, str);
}

ClientSocket            *ServerHFP::createClient(SOCKET newSocket, std::string const &name) {
    return new ClientHFP(newSocket, name);
}

void                    ServerHFP::onClientConnect(ClientSocket *client) {
    this->sendSupportedFeatures(client);
}

void                    ServerHFP::sendSupportedFeatures(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_SUPPORTED_FEATURES << "=" << std::to_string(this->_features) << "\n";
    client->onSuccess(*this, &ServerHFP::sendSupportedFeatures);
}


void                    ServerHFP::receiveSupportedFeatures(ClientSocket *client, std::string const &str) {
    ((ClientHFP *)client)->setFeatures(std::stoi(str));
}