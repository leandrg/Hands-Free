//
// Created by Gaëtan Léandre on 17/02/2020.
//

#ifndef                     HANDS_FREE_SERVERHFP_HPP
#define                     HANDS_FREE_SERVERHFP_HPP

#include                    <thread>
#include                    "ServerHFPService.hpp"
#include                    "ServerSCO.hpp"
#include                    "Server.hpp"

class                       ServerHFP: public Server {
    bool                    _listening;
    ServerHFPService        _serviceServer;
    ServerSCO               _audioServer;
    pthread_t               _serviceListenThread;
    pthread_t               _audioListenThread;

public:
    ServerHFP(uint8_t channel = 1, int maxClients = 1);
    ~ServerHFP();
    void                    start();
    void                    listen();
    void                    stop();
    void                    stopListening();
};


#endif                      //HANDS_FREE_SERVERHFP_HPP
