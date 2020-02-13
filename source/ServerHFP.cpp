//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "ServerHFP.hpp"

ServerHFP::ServerHFP(uint8_t channel) : ServerBluetooth(channel), SdpHFP() {
    this->registerRecord(channel);
    this->addCommand(*this, HFP_COMMAND_SUCCESS, &ServerHFP::onSuccess);
    this->addCommand(*this, HFP_COMMAND_ERROR, &ServerHFP::onError);
    this->addCommand(*this, HFP_COMMAND_SUPPORTED_FEATURES, &ServerHFP::receiveSupportedFeatures);
    this->addCommand(*this, HFP_COMMAND_INDICATORS, &ServerHFP::receiveIndicatorsList);
};

ServerHFP::~ServerHFP(){}

void                    ServerHFP::onSuccess(ClientSocket *client, std::string const &str) {
    client->onSuccess(client, str);
}

void                    ServerHFP::onError(ClientSocket *client, std::string const &str) {
    std::cerr << "Error : " << str << std::endl;
    client->onError(client, str);
}

ClientSocket            *ServerHFP::createClient(SOCKET newSocket, std::string const &name) {
    return new ClientHFP(newSocket, name);
}

void                    ServerHFP::onClientConnect(ClientSocket *client) {
    this->sendSupportedFeatures(client);
}

void                    ServerHFP::actionClient(ClientSocket *client, std::string data) {
    this->parseCommand(client, data);
}

void                    ServerHFP::sendSupportedFeatures(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_SUPPORTED_FEATURES << "=" << std::to_string(this->_features) << "\n";
    client->onSuccess(*this, &ServerHFP::sendIndicatorsListQuestion); //TODO ADD CODECS?
}

void                    ServerHFP::sendIndicatorsListQuestion(ClientSocket *client, std::string const &question) {
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "=" << (question.empty() ? "?" : question) << "\n";
    client->onSuccess(*this, &ServerHFP::sendIndicatorsValueQuestion);
}

void                    ServerHFP::sendIndicatorsValueQuestion(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_INDICATORS << "?" << "\n";
    client->onSuccess(*this, &ServerHFP::sendStartListenIndicators);
}

void                    ServerHFP::sendStartListenIndicators(ClientSocket *client, std::string const &_) {
    (void)_;
    *client << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_LISTEN_INDICATORS << "\n";
    std::cout << "sended : " << HFP_COMMAND_SEND_BY_HF << HFP_COMMAND_LISTEN_INDICATORS << "\n";
    ((ClientHFP *)client)->printIndicators();
}


void                    ServerHFP::receiveSupportedFeatures(ClientSocket *client, std::string const &str) {
    ((ClientHFP *)client)->setFeatures(std::stoi(str));
}

bool                    ServerHFP::containAlpha(std::string const &str) const {
    for (auto ch : str) {
        if (std::isalpha(ch))
            return true;
    }
    return false;
}


void                    ServerHFP::receiveIndicatorsList(ClientSocket *client, std::string const &str) {
    std::string::size_type  pos = 0;
    std::string::size_type  prev = 0;
    int                     parent = 0;

    if (this->containAlpha(str)) {
        ((ClientHFP *)client)->deleteIndicators();
        while (!str.empty() && pos < str.length()) {
            if (parent == 0 && str[pos] == ',') {
                std::string tmp = str.substr(prev, pos - prev);
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
        std::cout << "||" << str << std::endl;
        std::vector<std::string> vectorStr = this->split(str, ",");
        std::cout << vectorStr.size() << std::endl;
        std::vector<int> vectorInt;
        for (auto it = vectorStr.begin(); it != vectorStr.end(); it++) {
            try {vectorInt.push_back(std::stoi(*it));std::cout << *it << " " << std::stoi(*it) << std::endl;} catch (...) {vectorInt.push_back(0); std::cout << "hgfdhjhgfd" << std::endl;}
        }
    }
}
