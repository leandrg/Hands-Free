//
// Created by Gaëtan Léandre on 30/01/2020.
//

#ifndef                     HANDS_FREE_SERVERTCP_HPP
#define                     HANDS_FREE_SERVERTCP_HPP

#include                    <arpa/inet.h>
#include                    "ServerSocket.hpp"

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class                       ServerTCP : public ServerSocket {
    uint16_t                _port;

public:
    ServerTCP(uint16_t port = 8080, int maxClients = 1);
    ~ServerTCP();

protected:
    virtual void            socket();
    virtual int             bind() const;
    virtual ClientSocket    *accept();
    virtual void            actionClient(ClientSocket *client, t_package &data);
};


#endif //HANDS_FREE_SERVERTCP_HPP
