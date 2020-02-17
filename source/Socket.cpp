//
// Created by Gaëtan Léandre on 15/10/2019.
//

#include        "Socket.hpp"
#include <iostream>

Socket::Socket() {}

Socket::Socket(SOCKET socket) {
    this->_socket = socket;
}

Socket::~Socket() {
    close(this->_socket);
}

SOCKET          Socket::getSocket() const {
    return (this->_socket);
}


void            Socket::fdSet(fd_set *value) const {
    FD_SET(this->_socket, value);
}

bool            Socket::fdIsSet(const fd_set *value) const {
    return (FD_ISSET(this->_socket, value));
}

std::string     Socket::read() const {
    std::string stringBuffer = "";
    char buffer[MAX_BUFF_SIZE + 1] = {0};
    int size;

    size = ::read(this->_socket, buffer, MAX_BUFF_SIZE);
    std::cout << "read " << size << "[" << buffer << "]" << std::endl;
    (void)size;
    return (std::string(buffer));
}

void            Socket::write(const std::string data) {
    ::write(this->_socket, data.c_str(), data.length());
}

bool            operator<(const Socket &a, const Socket &b) {
    return a._socket < b._socket;
}

bool            operator>(const Socket &a, const Socket &b) {
    return a._socket > b._socket;
}

bool            operator==(const Socket &a, const Socket &b) {
    return a._socket == b._socket;
}

bool            operator==(const Socket &a, fd_set *value) {
    return a.fdIsSet(value);
}

Socket          &operator<<(Socket &a, const std::string data) {
    a.write(data);
    return a;
}

std::string     &operator<<(std::string &data, const Socket &a) {
    data = a.read();
    return data;
}