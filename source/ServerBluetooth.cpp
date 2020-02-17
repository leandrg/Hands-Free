//
// Created by Gaëtan Léandre on 16/02/2020.
//

#include                "ServerBluetooth.hpp"

ServerBluetooth::ServerBluetooth(int maxClients) : ServerSocket(maxClients) {
}

ServerBluetooth::~ServerBluetooth() {
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