//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel) : ServerBluetooth(channel), SdpHFP() {
    this->registerRecord(channel);
    this->addCommand(*this, HFP_COMMAND_SUCCESS, &ServerHFP::onSuccess);
    this->addCommand(*this, HFP_COMMAND_ERROR, &ServerHFP::onError);
    this->addCommand(*this, HFP_COMMAND_SUPPORTED_FEATURES, &ServerHFP::receiveSupportedFeatures);
    this->addCommand(*this, HFP_COMMAND_INDICATORS, &ServerHFP::receiveIndicatorsList);
};

ServerHFP::~ServerHFP(){}

void                    ServerHFP::onSuccess(ClientSocket *client, std::string const &str) {
    client->onSuccess(client, str);
}

void                    ServerHFP::onError(ClientSocket *client, std::string const &str) {
    std::cerr << "Error : " << str << std::endl;
    client->onError(client, str);
}

ClientSocket            *ServerHFP::createClient(SOCKET newSocket, std::string const &name) {
    return new ClientHFP(newSocket, name);
}

void                    ServerHFP::onClientConnect(ClientSocket *client) {
    this->sendSupportedFeatures(client);
}

void                    ServerHFP::actionClient(ClientSocket *client, std::string data) {
    this->parseCommand(client, data);
}

void                    ServerHFP::sendSupportedFeatures(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_SUPPORTED_FEATURES << "=" << std::to_string(this->_features) << "\n";
    client->onSuccess(*this, &ServerHFP::sendIndicatorsListQuestion); //TODO ADD CODECS?
}

void                    ServerHFP::sendIndicatorsListQuestion(ClientSocket *client, std::string const &question) {
    std::cout << "--" << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "=" << question << std::endl;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "=" << question << "\n";
    client->onSuccess(*this, &ServerHFP::sendIndicatorsListQuestion);
}


void                    ServerHFP::receiveSupportedFeatures(ClientSocket *client, std::string const &str) {
    ((ClientHFP *)client)->setFeatures(std::stoi(str));
}

void                    ServerHFP::receiveIndicatorsList(ClientSocket *client, std::string const &str) {
    (void)client;
    std::cout << "||" << str << "||" << std::endl;
}
