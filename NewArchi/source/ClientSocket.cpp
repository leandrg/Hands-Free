//
// Created by Gaëtan Léandre on 15/10/2019.
//

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(SOCKET socket, std::string stringId) : Socket(socket) {
    this->_stringId = stringId;
}

ClientSocket::~ClientSocket() {
    close(this->_socket);
}

const std::string       ClientSocket::getStringId() const {
    return this->_stringId;
}

void                    ClientSocket::setStringId(const std::string stringId) {
    this->_stringId = stringId;
}