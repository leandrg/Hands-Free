//
// Created by Gaëtan Léandre on 15/10/2019.
//

#include        "ServerSocket.hpp"

ServerSocket::ServerSocket(int maxClients) {
    this->_maxClients = maxClients;
    this->_started = false;
}

ServerSocket::~ServerSocket() {
    this->stop();
}

void            ServerSocket::start() {
    if (this->_started == false) {
        this->socket();
        if (this->_socket == -1) {
            std::cerr << "Error socket connection" << std::endl;
            throw std::exception();
        } else if (this->bind() == -1) {
            std::cerr << "Error in socket bind" << std::endl;
            throw std::exception();
        } else if (::listen(this->_socket, this->_maxClients) == -1) {
            std::cerr << "Error in socket listen." << std::endl;
            throw std::exception();
        }
        std::cout << "Server started." << std::endl;
        this->_started = true;
    }
}

void            ServerSocket::listen() {
    fd_set      fdSet;
    Socket      *biggestSocket;

    while (1) {
        FD_ZERO(&fdSet);
        this->fdSet(&fdSet);
        biggestSocket = this;
        for(ClientSocket *ptr : this->_clients) {
            ptr->fdSet(&fdSet);
            biggestSocket = (*ptr > *biggestSocket ? ptr : biggestSocket);
        }
        if (select(biggestSocket->getSocket() + 1, &fdSet, NULL, NULL, NULL) == -1)
            return;
        if (*this == &fdSet)
            this->addClient();
        else
            this->receiveClient(fdSet);
    }
}

void            ServerSocket::stop() {
    if (this->_started == true) {
        this->stopAllClients();
        close(this->_socket);
        this->_started = false;
    }
}

void            ServerSocket::stopAllClients() {
    for (ClientSocket *ptr : this->_clients) {
        delete ptr;
    }
    this->_clients.clear();
}

void            ServerSocket::disconnectClient(ClientSocket *client) {
    std::cout << "Client " << client->getStringId() << " disconnect." << std::endl;
    this->_clients.remove(client);
    delete client;
}

void            ServerSocket::addClient() {
    ClientSocket *client = this->accept();
    if (client == NULL) {
        std::cerr << "Error while adding client." << std::endl;
        return;
    }
    std::cout << "New client : " << client->getStringId() << std::endl;
    this->_clients.push_back(client);
    this->onClientConnect(client);
}

void            ServerSocket::receiveClient(fd_set value) {
    std::string data;

    for (ClientSocket *ptr : this->_clients) {
        if (*ptr == &value) {
            data << *ptr;
            if (data.empty())
                this->disconnectClient(ptr);
            else
                this->actionClient(ptr, data);
            break;
        }
    }
}

ClientSocket    *ServerSocket::createClient(SOCKET newSocket, std::string const & name) {
    return new ClientSocket(newSocket, name);
}

void            ServerSocket::onClientConnect(ClientSocket *client) {
    (void)client;
}