//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef                 HANDS_FREE_CLIENTHFP_HPP
#define                 HANDS_FREE_CLIENTHFP_HPP

#include                "ClientSocket.hpp"

class ClientHFP : public ClientSocket {
    int                 _features = 0;

public:
    ClientHFP(SOCKET socket, std::string stringId);
    ~ClientHFP();
    void                setFeatures(int features);
};

#endif                  //HANDS_FREE_CLIENTHFP_HPP
