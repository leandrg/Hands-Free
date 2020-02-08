//
// Created by Gaëtan Léandre on 04/02/2020.
//

#include                "CommandParser.hpp"

CommandParser::CommandParser() {
}

CommandParser::~CommandParser() {
    this->removeAllCommands();
}

void                CommandParser::removeCommand(std::string const &key) {
    std::unordered_map<std::string, CommandParent*>::iterator it = this->_mapCommands.find(key);

    if (it != this->_mapCommands.end()) {
        delete it->second;
        this->_mapCommands.erase(it->first);
    }
}

void                CommandParser::removeAllCommands() {
    std::unordered_map<std::string, CommandParent*>::iterator it = this->_mapCommands.begin();

    while (it != this->_mapCommands.end())
    {
        std::unordered_map<std::string, CommandParent*>::iterator tmp = it;
        it++;
        delete tmp->second;
        this->_mapCommands.erase(tmp->first);
    }
}

bool                CommandParser::parseCommand(ClientSocket *client, std::string const &str) {
    //TODO get key
    std::unordered_map<std::string, CommandParent*>::iterator it = this->_mapCommands.find(str);

    if (it != this->_mapCommands.end()) {
        it->second->launch(client, str);
        return true;
    }
    return false;
}