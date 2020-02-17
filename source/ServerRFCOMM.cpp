//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include                "ServerRFCOMM.hpp"

ServerRFCOMM::ServerRFCOMM(uint8_t channel, int maxClients) : ServerBluetooth(maxClients) {
    this->_channel = channel;
}

ServerRFCOMM::~ServerRFCOMM() {
}

void                    ServerRFCOMM::socket() {
    this->_socket = ::socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
}

int                     ServerRFCOMM::bind() const {
    SOCKADDR_RC         sock_addr;
    bdaddr_t            bdaddr_any =  {{0, 0, 0, 0, 0, 0}};


    sock_addr.rc_family = AF_BLUETOOTH;
    sock_addr.rc_bdaddr = bdaddr_any;
    sock_addr.rc_channel = this->_channel;
    return (::bind(this->_socket, (SOCKADDR*)&sock_addr, sizeof(sock_addr)));
}

ClientSocket            *ServerRFCOMM::accept() {
    SOCKADDR_RC		    sock_addr;
    SOCKET              newSocket;
    socklen_t		    size;
    char                tmpName[1024] = {0};

    size = sizeof(sock_addr);
    newSocket = ::accept(this->_socket, (SOCKADDR *)&sock_addr, &size);
    if (newSocket == -1)
        return NULL;
    ba2str(&sock_addr.rc_bdaddr, tmpName);
    return this->createClient(newSocket, tmpName);
}

void                    ServerRFCOMM::actionClient(ClientSocket *client, t_package &data) {
    std::cout << "New message from " << client->getStringId() << " : " << data.buffer << std::endl;
}