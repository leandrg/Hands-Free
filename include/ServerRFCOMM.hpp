//
// Created by Gaëtan Léandre on 30/01/2020.
//

#ifndef                     HANDS_FREE_SERVERRFCOMM_HPP
#define                     HANDS_FREE_SERVERRFCOMM_HPP

#include                    "ServerBluetooth.hpp"
#include                    <bluetooth/rfcomm.h>
#include                    <arpa/inet.h>

typedef struct sockaddr_rc  SOCKADDR_RC;

class                       ServerRFCOMM : public ServerBluetooth {
    uint8_t                 _channel;

public:
    ServerRFCOMM(uint8_t channel = 1, int maxClients = 1);
    ~ServerRFCOMM();

protected:
    virtual void            socket();
    virtual int             bind() const;
    virtual ClientSocket    *accept();
    virtual void            actionClient(ClientSocket *client, std::string data);
};


#endif //HANDS_FREE_SERVERRFCOMM_HPP
