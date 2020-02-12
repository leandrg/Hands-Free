//
// Created by Gaëtan Léandre on 15/10/2019.
//

#include                "ClientSocket.hpp"

ClientSocket::ClientSocket(SOCKET socket, std::string stringId) : Socket(socket) {
    this->_stringId = stringId;
}

ClientSocket::~ClientSocket() {
    this->deleteSuccess();
    this->deleteError();
    close(this->_socket);
}

const std::string       ClientSocket::getStringId() const {
    return this->_stringId;
}

void                    ClientSocket::setStringId(const std::string stringId) {
    this->_stringId = stringId;
}

void                    ClientSocket::deleteSuccess() {
    if (this->success == NULL)
        return;
    delete this->success;
    this->success = NULL;
}

void                    ClientSocket::onSuccess(ClientSocket *clientSocket, std::string const &str) {
    std::cout << "called2" << std::endl;
    if (this->success == NULL)
        return;
    std::cout << "called3" << std::endl;
    this->success->launch(clientSocket, str);
    this->deleteSuccess();
}

void                    ClientSocket::deleteError() {
    if (this->error == NULL)
        return;
    delete this->error;
    this->error = NULL;
}

void                    ClientSocket::onError(ClientSocket *clientSocket, std::string const &str) {
    if (this->error == NULL)
        return;
    this->error->launch(clientSocket, str);
    this->deleteError();
}