//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include                "ServerTCP.hpp"

ServerTCP::ServerTCP(uint16_t port, int maxClients) : ServerSocket(maxClients) {
    this->_port = port;
}

ServerTCP::~ServerTCP() {
}

void                    ServerTCP::socket() {
    this->_socket = ::socket(AF_INET, SOCK_STREAM, 0);
}

int                     ServerTCP::bind() const {
    SOCKADDR_IN         sockaddrIn;

    sockaddrIn.sin_family = AF_INET;
    sockaddrIn.sin_addr.s_addr = INADDR_ANY;
    sockaddrIn.sin_port = htons(this->_port);
    return (::bind(this->_socket, (SOCKADDR*)&sockaddrIn, sizeof(sockaddrIn)));
}

ClientSocket            *ServerTCP::accept() {
    SOCKADDR_IN         sockaddrIn;
    socklen_t           size;
    SOCKET              newSocket;

    size = sizeof(sockaddrIn);
    newSocket = ::accept(this->_socket, (SOCKADDR*)&sockaddrIn, &size);
    if (newSocket == -1)
        return NULL;
    return new ClientSocket(newSocket, inet_ntoa(sockaddrIn.sin_addr));
}

void                    ServerTCP::actionClient(ClientSocket *client, std::string data) {
    std::cout << "New message from " << client->getStringId() << " : " << data << std::endl;
}