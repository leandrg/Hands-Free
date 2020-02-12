//
// Created by Gaëtan Léandre on 08/02/2020.
//

#include                "ClientHFP.hpp"

ClientHFP::ClientHFP(SOCKET socket, std::string stringId) : ClientSocket(socket, stringId) {
}

ClientHFP::~ClientHFP() {
}

void                    ClientHFP::setFeatures(int features) {
    this->_features = features;
}

bool                    ClientHFP::supportFeature(int feature) {
    return ((this->_features & feature) > 0);
}

void                    ClientHFP::deleteIndicators() {
    this->_indicators.clear();
}

void                    ClientHFP::pushIndicator(IndicatorHFP const &indicator) {
    this->_indicators.push_back(indicator);
}

void                    ClientHFP::printIndicators() const {
    for (auto it = this->_indicators.begin(); it != this->_indicators.end(); ++it)
        std::cout << ' ' << it->getName() << std::endl;
}