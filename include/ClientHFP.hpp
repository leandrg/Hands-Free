//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef                 HANDS_FREE_CLIENTHFP_HPP
#define                 HANDS_FREE_CLIENTHFP_HPP

#include                "ClientSocket.hpp"

class ClientHFP : public ClientSocket {
public:
    ClientHFP(SOCKET socket, std::string stringId);
    ~ClientHFP();
};

#endif                  //HANDS_FREE_CLIENTHFP_HPP
