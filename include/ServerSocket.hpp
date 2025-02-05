//
// Created by Gaëtan Léandre on 15/10/2019.
//

#ifndef                         HANDS_FREE_SERVER_SOCKET_HPP
#define                         HANDS_FREE_SERVER_SOCKET_HPP

#include                        <list>
#include                        <iostream>
#include                        "ClientSocket.hpp"
#include                        "CommandParser.hpp"
#include                        "Server.hpp"

class                           ServerSocket : public Socket, public Server, public CommandParser {
    int                         _maxClients;
    std::list<ClientSocket*>    _clients;

    void                        addClient();
    void                        receiveClient(fd_set value);

public:
    ServerSocket(int maxClients = 1);
    ~ServerSocket();
    void                        start();
    void                        listen();
    void                        stop();
    void                        stopAllClients();
    void                        disconnectClient(ClientSocket *client);

protected:
    virtual void                socket() = 0;
    virtual int                 bind() const = 0;
    virtual ClientSocket        *accept() = 0;
    virtual void                actionClient(ClientSocket *client, t_package &package) = 0;
    virtual ClientSocket        *createClient(SOCKET newSocket, std::string const & name);
    virtual void                onClientConnect(ClientSocket *client);
};


#endif                          //HANDS_FREE_SERVER_SOCKET_HPP
