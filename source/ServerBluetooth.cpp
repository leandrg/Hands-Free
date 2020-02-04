//
// Created by Gaëtan Léandre on 30/01/2020.
//

#include                "ServerBluetooth.hpp"

ServerBluetooth::ServerBluetooth(uint8_t channel, int maxClients) : ServerSocket(maxClients) {
    this->_channel = channel;
}

ServerBluetooth::~ServerBluetooth() {
}

void                    ServerBluetooth::socket() {
    this->_socket = ::socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
}

const std::string       ServerBluetooth::getServerName() const {
    struct hci_dev_info di;
    char                *name;
    std::string         tmp;

    if(hci_devinfo(0, &di) < 0)
        return std::string();
    name = batostr(&di.bdaddr);
    tmp = std::string(name);
    free(name);
    return tmp;
}


int                     ServerBluetooth::bind() const {
    SOCKADDR_RC         sock_addr;
    bdaddr_t            bdaddr_any =  {{0, 0, 0, 0, 0, 0}};


    sock_addr.rc_family = AF_BLUETOOTH;
    sock_addr.rc_bdaddr = bdaddr_any;
    sock_addr.rc_channel = this->_channel;
    return (::bind(this->_socket, (SOCKADDR*)&sock_addr, sizeof(sock_addr)));
}

ClientSocket            *ServerBluetooth::accept() {
    SOCKADDR_RC		    sock_addr;
    SOCKET              newSocket;
    socklen_t		    size;
    char                tmpName[1024] = {0};
    ClientSocket        *tmpClient;

    size = sizeof(sock_addr);
    newSocket = ::accept(this->_socket, (SOCKADDR *)&sock_addr, &size);
    if (newSocket == -1)
        return NULL;
    ba2str(&sock_addr.rc_bdaddr, tmpName);
    tmpClient = new ClientSocket(newSocket, tmpName);
    return tmpClient;
}

void                    ServerBluetooth::actionClient(ClientSocket *client, std::string data) {
    std::cout << "New message from " << client->getStringId() << " : " << data << std::endl;
}