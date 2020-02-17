//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFPService.hpp"

ServerHFPService::ServerHFPService(uint8_t channel, int maxClients) : ServerRFCOMM(channel, maxClients), SdpHFP() {
    this->registerRecord(channel);
    this->addCommand(*this, HFP_COMMAND_SUCCESS, &ServerHFPService::onSuccess);
    this->addCommand(*this, HFP_COMMAND_ERROR, &ServerHFPService::onError);
    this->addCommand(*this, HFP_COMMAND_SUPPORTED_FEATURES, &ServerHFPService::receiveSupportedFeatures);
    this->addCommand(*this, HFP_COMMAND_INDICATORS, &ServerHFPService::receiveIndicatorsList);
    this->addCommand(*this, HFP_COMMAND_INDICATOR_VALUE, &ServerHFPService::receiveIndicatorValue);
};

ServerHFPService::~ServerHFPService(){
}

void                    ServerHFPService::onSuccess(ClientSocket *client, std::string const &str) {
    client->onSuccess(client, str);
}

void                    ServerHFPService::onError(ClientSocket *client, std::string const &str) {
    std::cerr << "Error : " << str << std::endl;
    client->onError(client, str);
}

ClientSocket            *ServerHFPService::createClient(SOCKET newSocket, std::string const &name) {
    return new ClientHFP(newSocket, name);
}

void                    ServerHFPService::onClientConnect(ClientSocket *client) {
    this->sendSupportedFeatures(client);
}

void                    ServerHFPService::actionClient(ClientSocket *client, t_package &data) {
    this->parseCommand(client, std::string(data.buffer));
}

void                    ServerHFPService::sendSupportedFeatures(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_SUPPORTED_FEATURES << "=" << std::to_string(this->_features) << "\n";
    client->onSuccess(*this, &ServerHFPService::sendIndicatorsListQuestion); //TODO ADD CODECS?
}

void                    ServerHFPService::sendIndicatorsListQuestion(ClientSocket *client, std::string const &question) {
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "=" << (question.empty() ? "?" : question) << "\n";
    client->onSuccess(*this, &ServerHFPService::sendIndicatorsValueQuestion);
}

void                    ServerHFPService::sendIndicatorsValueQuestion(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "?" << "\n";
    client->onSuccess(*this, &ServerHFPService::sendStartListenIndicators);
}

void                    ServerHFPService::sendStartListenIndicators(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_LISTEN_INDICATORS << "=" << "3,0,0,1" "\n";
}


void                    ServerHFPService::receiveSupportedFeatures(ClientSocket *client, std::string const &str) {
    ((ClientHFP *)client)->setFeatures(std::stoi(str));
}

bool                    ServerHFPService::containAlpha(std::string const &str) const {
    for (auto ch : str) {
        if (std::isalpha(ch))
            return true;
    }
    return false;
}


void                    ServerHFPService::receiveIndicatorsList(ClientSocket *client, std::string const &str) {
    std::string::size_type  pos = 0;
    std::string::size_type  prev = 0;
    int                     parent = 0;

    if (this->containAlpha(str)) {
        ((ClientHFP *)client)->deleteIndicators();
        while (!str.empty() && pos <= str.length()) {
            if (parent == 0 && (pos == str.length() || str[pos] == ',')) {
                std::string tmp = str.substr(prev, (pos == str.length() ? pos - 1 : pos) - prev);
                this->clean(tmp);
                if (!tmp.empty() && tmp[0] == '(' && tmp[tmp.length() - 1] == ')') {
                    tmp = tmp.substr(1, tmp.length() - 2);
                    this->clean(tmp);
                }
                ((ClientHFP *)client)->pushIndicator(IndicatorHFP(tmp));
                prev = pos + 1;
            }
            else if (str[pos] == '(')
                parent++;
            else if (str[pos] == ')')
                parent--;
            pos++;
        }
    }
    else {
        std::vector<std::string> vectorStr = this->split(str, ",");
        std::vector<int> vectorInt;
        for (auto it = vectorStr.begin(); it != vectorStr.end(); it++) {
            try {vectorInt.push_back(std::stoi(*it));} catch (...) {vectorInt.push_back(0);}
        }
        ((ClientHFP *)client)->setIndicatorsValue(vectorInt);
    }
}

void                    ServerHFPService::receiveIndicatorValue(ClientSocket *client, std::string const &str) {
    std::vector<std::string> vectorStr = this->split(str, ",");
    std::vector<int> vectorInt;

    if (vectorStr.size() >= 2) {
        int feature = 0;
        int value = 0;
        try {feature = std::stoi(vectorStr[0]);} catch (...) {};
        try {value = std::stoi(vectorStr[1]);} catch (...) {};
        ((ClientHFP *)client)->setIndicatorValue(feature, value);
    }

}