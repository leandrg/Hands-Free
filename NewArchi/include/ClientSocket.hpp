//
// Created by Gaëtan Léandre on 15/10/2019.
//

#ifndef HANDS_FREE_CLIENTSOCKET_HPP
#define HANDS_FREE_CLIENTSOCKET_HPP

#include                "Socket.hpp"

class                   ClientSocket: public Socket {
    std::string          _stringId;

public:
    ClientSocket(SOCKET socket, std::string stringId);
    ~ClientSocket();
    const std::string   getStringId() const;
    void                setStringId(const std::string stringId);
};


#endif //HANDS_FREE_CLIENTSOCKET_HPP
