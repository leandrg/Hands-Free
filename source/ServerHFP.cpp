//
// Created by Gaëtan Léandre on 17/02/2020.
//

#include                    "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel, int maxClients): _serviceServer(ServerHFPService(channel, maxClients)), _audioServer(ServerSCO()) {
}

ServerHFP::~ServerHFP() {
    this->stop();
}

void                        ServerHFP::start() {
    this->_serviceServer.start();
    this->_audioServer.start();
    this->_started = true;
}

void                        ServerHFP::listen() {
    std::thread threadService = std::thread(&ServerHFPService::listen, &this->_serviceServer);
    std::thread threadAudio = std::thread(&ServerSCO::listen, &this->_serviceServer);
    this->_serviceListenThread = threadService.native_handle();
    this->_audioListenThread = threadAudio.native_handle();
    threadService.detach();
    threadAudio.detach();
    this->_listening = true;
}

void                        ServerHFP::stopListening() {
    if (this->_listening == true) {
        pthread_cancel(this->_serviceListenThread);
        pthread_cancel(this->_audioListenThread);
        this->_listening = false;
    }
}

void                        ServerHFP::stop() {
    if (this->_started == true) {
        this->stopListening();
        this->_serviceServer.stop();
        this->_audioServer.stop();
        this->_started = false;
    }
}