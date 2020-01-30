//
// Created by Gaëtan Léandre on 30/01/2020.
//

#ifndef                     HANDS_FREE_SERVERBLUETOOTH_HPP
#define                     HANDS_FREE_SERVERBLUETOOTH_HPP

#include                    <bluetooth/bluetooth.h>
#include                    <bluetooth/rfcomm.h>
#include                    <arpa/inet.h>
#include                    "ServerSocket.hpp"

typedef struct sockaddr_rc  SOCKADDR_RC;
typedef struct sockaddr     SOCKADDR;

class                       ServerBluetooth : public ServerSocket {
public:
    ServerBluetooth(int maxClients = 1);
    ~ServerBluetooth();

protected:
    virtual void            socket();
    virtual int             bind() const;
    virtual ClientSocket    *accept();
    virtual void            actionClient(ClientSocket *client, std::string data);
};


#endif //HANDS_FREE_SERVERBLUETOOTH_HPP
