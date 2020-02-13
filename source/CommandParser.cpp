//
// Created by Gaëtan Léandre on 04/02/2020.
//

#include                "CommandParser.hpp"

CommandParser::CommandParser() {
}

CommandParser::~CommandParser() {
    this->removeAllCommands();
}

std::vector<std::string>    CommandParser::split(std::string const &str, std::string const & delimiter, int maxSize) const {
    std::vector<std::string> strings;
    int                     i = 1;
    std::string::size_type  pos = 0;
    std::string::size_type  prev = 0;

    while ((maxSize == 0 || maxSize > i) && (pos = str.find(delimiter, prev)) != std::string::npos) {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
        i++;
    }
    std::string tmp = str.substr(prev);
    if (!tmp.empty())
        strings.push_back(tmp);
    return strings;
}

void                    CommandParser::clean(std::string &str) const {
    bool                space = false;
    auto                p = str.begin();

    for (auto ch : str) {
        if (std::isspace(ch)) {
            space = p != str.begin();
        }
        else {
            if (space) *p++ = ' ';
            *p++ = ch;
            space = false;
        }
    }
    str.erase(p, str.end());
}


void                    CommandParser::removeCommand(std::string const &key) {
    std::unordered_map<std::string, CommandParent*>::iterator it = this->_mapCommands.find(key);

    if (it != this->_mapCommands.end()) {
        delete it->second;
        this->_mapCommands.erase(it->first);
    }
}

void                    CommandParser::removeAllCommands() {
    std::unordered_map<std::string, CommandParent*>::iterator it = this->_mapCommands.begin();

    while (it != this->_mapCommands.end())
    {
        std::unordered_map<std::string, CommandParent*>::iterator tmp = it;
        it++;
        delete tmp->second;
        this->_mapCommands.erase(tmp->first);
    }
}

bool                    CommandParser::parseCommand(ClientSocket *client, std::string const &str) {
    std::vector<std::string>    strings = this->split(str, "\n");

    for (std::vector<std::string>::iterator it = strings.begin() ; it != strings.end(); ++it) {
        std::vector<std::string> command = this->split(*it, ":", 2);
        if (command.size() > 0)
            this->clean(command[0]);
        else
            continue;
        if (command.size() > 1)
            this->clean(command[1]);
        std::unordered_map<std::string, CommandParent*>::iterator mapIt = this->_mapCommands.find(command[0]);

        if (mapIt != this->_mapCommands.end()) {
            std::cout << "Command " << command[0] << " from " << client->getStringId() << " " << (command.size() > 1 ? command[1] : "") << std::endl;
            mapIt->second->launch(client, command.size() > 1 ? command[1] : "");
        }
    }
    return true;
}