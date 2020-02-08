//
// Created by Gaëtan Léandre on 08/02/2020.
//

#include                "ClientHFP.hpp"

ClientHFP::ClientHFP(SOCKET socket, std::string stringId) : ClientSocket(socket, stringId) {
}

ClientHFP::~ClientHFP() {
}