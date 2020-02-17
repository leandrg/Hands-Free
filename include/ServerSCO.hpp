//
// Created by Gaëtan Léandre on 16/02/2020.
//

#ifndef                     HANDS_FREE_SERVERSCO_HPP
#define                     HANDS_FREE_SERVERSCO_HPP

#include                    "ServerBluetooth.hpp"
#include                    <bluetooth/sco.h>

typedef struct sockaddr_sco SOCKADDR_SCO;

class                       ServerSCO: public ServerBluetooth {
public:
    ServerSCO();
    ~ServerSCO();

protected:
    virtual void            socket();
    virtual int             bind() const;
    virtual ClientSocket    *accept();
    virtual void            actionClient(ClientSocket *client, t_package &data);
};


#endif                      //HANDS_FREE_SERVERSCO_HPP
