//
// Created by Gaëtan Léandre on 16/02/2020.
//

#ifndef                         HANDS_FREE_SERVERBLUETOOTH_HPP
#define                         HANDS_FREE_SERVERBLUETOOTH_HPP

#include                        <bluetooth/bluetooth.h>
#include                        <bluetooth/hci.h>
#include                        <bluetooth/hci_lib.h>
#include                        "ServerSocket.hpp"

typedef struct sockaddr         SOCKADDR;

class                           ServerBluetooth: public ServerSocket {
public:
    ServerBluetooth(int maxClients = 1);
    ~ServerBluetooth();
    virtual const std::string   getServerName() const;

protected:
    virtual void                socket() = 0;
    virtual int                 bind() const = 0;
    virtual ClientSocket        *accept() = 0;
    virtual void                actionClient(ClientSocket *client, t_package &data) = 0;
};


#endif                          //HANDS_FREE_SERVERBLUETOOTH_HPP
