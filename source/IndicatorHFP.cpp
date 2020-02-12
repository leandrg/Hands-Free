//
// Created by Gaëtan Léandre on 12/02/2020.
//

#include                "IndicatorHFP.hpp"

IndicatorHFP::IndicatorHFP(std::string const &str) {
    this->_name = this->parseName(str);
    std::pair<int, int> pair = parseRange(str);
    this->_downRange = pair.first;
    this->_upRange = pair.second;
}

IndicatorHFP::~IndicatorHFP() {
}

std::string             IndicatorHFP::parseName(std::string const &str) const {
    std::string::size_type  start = 0;
    std::string::size_type  end = 0;

    if ((start = str.find("\"")) != std::string::npos && (end = str.find("\"", start + 1)) != std::string::npos) {
        return str.substr(start + 1, end - start - 1);
    } else {
        return "";
    }
}

std::pair<int, int>     IndicatorHFP::parseRange(std::string const &str) const {
    std::string::size_type  start = 0;
    std::string::size_type  end = 0;
    int down = 0;
    int up = 0;

    try {
        if ((start = str.find("(")) != std::string::npos && (end = str.find(")")) != std::string::npos) {
            std::string couple = str.substr(start + 1, end - start - 1);
            down = std::stoi(couple);
            if ((start = couple.find(",")) != std::string::npos || (start = couple.find("-")) != std::string::npos) {
                up = std::stoi(couple.substr(start + 1));
            }
        }
    } catch (...) {}
    return std::make_pair(down, up);
}

std::string             IndicatorHFP::getName() const {
    return this->_name;
}
