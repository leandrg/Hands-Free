//
// Created by Gaëtan Léandre on 03/02/2020.
//

#ifndef                     HANDS_FREE_SERVERHFP_HPP
#define                     HANDS_FREE_SERVERHFP_HPP

#include                    "ServerBluetooth.hpp"
#include                    "SdpHFP.hpp"
#include                    "ClientHFP.hpp"
#include                    "HFPDefine.hpp"

class ServerHFP : public ServerBluetooth, protected SdpHFP {
    int                     _features = 0;

public:
    ServerHFP(uint8_t channel = 1);
    ~ServerHFP();
    void                    onSuccess(ClientSocket *client, std::string const &str);
    void                    onError(ClientSocket *client, std::string const &str);

    void                    sendSupportedFeatures(ClientSocket *client, std::string const &features = "0");
    void                    sendIndicatorsListQuestion(ClientSocket *client, std::string const &question);

    void                    receiveSupportedFeatures(ClientSocket *client, std::string const &str);
    void                    receiveIndicatorsList(ClientSocket *client, std::string const &str);

protected:
    virtual ClientSocket    *createClient(SOCKET newSocket, std::string const &name);
    virtual void            onClientConnect(ClientSocket *client);
    virtual void            actionClient(ClientSocket *client, std::string data);

};


#endif                      //HANDS_FREE_SERVERHFP_HPP
