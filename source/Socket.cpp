//
// Created by Gaëtan Léandre on 15/10/2019.
//

#include        "Socket.hpp"

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

t_package       Socket::read() const {
    t_package   package;

    package.size = ::read(this->_socket, package.buffer, MAX_BUFF_SIZE);
    return (package);
}

void            Socket::write(t_package const &package) {
    ::write(this->_socket, package.buffer, package.size);
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
    t_package   package;

    package.size = data.length();
    ::strncpy(package.buffer, data.c_str(), package.size);
    a.write(package);
    return a;
}

std::string     &operator<<(std::string &data, const Socket &a) {
    t_package   package = a.read();
    data = std::string(package.buffer);
    return data;
}

t_package       &operator<<(t_package &data, const Socket &a) {
    t_package   package = a.read();

    data.size = package.size;
    ::strncpy(data.buffer, package.buffer, package.size);
    return data;
}