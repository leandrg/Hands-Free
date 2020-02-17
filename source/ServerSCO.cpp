//
// Created by Gaëtan Léandre on 16/02/2020.
//

#include                "ServerSCO.hpp"

ServerSCO::ServerSCO() {
}

ServerSCO::~ServerSCO() {
}

void                    ServerSCO::socket() {
    this->_socket = ::socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_SCO);
}

int                     ServerSCO::bind() const {
    SOCKADDR_SCO        sock_addr;
    bdaddr_t            bdaddr_any =  {{0, 0, 0, 0, 0, 0}};

    sock_addr.sco_family = AF_BLUETOOTH;
    sock_addr.sco_bdaddr = bdaddr_any;
    return (::bind(this->_socket, (SOCKADDR*)&sock_addr, sizeof(sock_addr)));
}

ClientSocket            *ServerSCO::accept() {
    SOCKADDR_SCO        sock_addr;
    SOCKET              newSocket;
    socklen_t		    size;
    char                tmpName[1024] = {0};

    size = sizeof(sock_addr);
    newSocket = ::accept(this->_socket, (SOCKADDR *)&sock_addr, &size);
    ba2str(&sock_addr.sco_bdaddr, tmpName);
    return this->createClient(newSocket, tmpName);
}

void                    ServerSCO::actionClient(ClientSocket *client, t_package &data) {
    (void)client;
    (void)data;
//    std::cout << "Received data from " << client->getStringId() << " : [" << data.buffer << "] (" << std::to_string(data.size) << ")" << std::endl;
}