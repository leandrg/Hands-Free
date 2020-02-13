//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef                         HANDS_FREE_CLIENTHFP_HPP
#define                         HANDS_FREE_CLIENTHFP_HPP

#include                        <vector>
#include                        <iostream>
#include                        "ClientSocket.hpp"
#include                        "IndicatorHFP.hpp"

class ClientHFP : public ClientSocket {
    int                         _features = 0;
    std::vector<IndicatorHFP>   _indicators;

public:
    ClientHFP(SOCKET socket, std::string stringId);
    ~ClientHFP();
    void                        setFeatures(int features);
    bool                        supportFeature(int feature);
    void                        deleteIndicators();
    void                        pushIndicator(IndicatorHFP const &indicator);
    void                        setIndicatorsValue(std::vector<int> const &vector);
    void                        printIndicators() const;
};

#endif                  //HANDS_FREE_CLIENTHFP_HPP
