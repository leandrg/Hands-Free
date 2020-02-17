//
// Created by Gaëtan Léandre on 03/02/2020.
//

#ifndef                     HANDS_FREE_SERVERHFPSERVICE_HPP
#define                     HANDS_FREE_SERVERHFPSERVICE_HPP

#include                    "ServerRFCOMM.hpp"
#include                    "SdpHFP.hpp"
#include                    "ClientHFP.hpp"
#include                    "IndicatorHFP.hpp"
#include                    "HFPDefine.hpp"

class ServerHFPService : public ServerRFCOMM, protected SdpHFP {
    int                     _features = 0;

    bool                    containAlpha(std::string const &str) const;

public:
    ServerHFPService(uint8_t channel = 1, int maxClients = 1);
    ~ServerHFPService();
    void                    onSuccess(ClientSocket *client, std::string const &str);
    void                    onError(ClientSocket *client, std::string const &str);

    void                    sendSupportedFeatures(ClientSocket *client, std::string const &features = "0");
    void                    sendIndicatorsListQuestion(ClientSocket *client, std::string const &question = "?");
    void                    sendIndicatorsValueQuestion(ClientSocket *client, std::string const &_ = "");
    void                    sendStartListenIndicators(ClientSocket *client, std::string const &_ = "");

    void                    receiveSupportedFeatures(ClientSocket *client, std::string const &str);
    void                    receiveIndicatorsList(ClientSocket *client, std::string const &str);
    void                    receiveIndicatorValue(ClientSocket *client, std::string const &str);

protected:
    virtual ClientSocket    *createClient(SOCKET newSocket, std::string const &name);
    virtual void            onClientConnect(ClientSocket *client);
    virtual void            actionClient(ClientSocket *client, t_package &data);

};


#endif                      //HANDS_FREE_SERVERHFPSERVICE_HPP
