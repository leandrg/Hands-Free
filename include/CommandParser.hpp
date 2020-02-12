//
// Created by Gaëtan Léandre on 04/02/2020.
//

#ifndef                         HANDS_FREE_COMMANDPARSER_HPP
#define                         HANDS_FREE_COMMANDPARSER_HPP

#include                        <string>
#include                        <iostream>
#include                        <unordered_map>
#include                        <vector>
#include                        "Command.hpp"

class                           CommandParser {
    std::unordered_map<std::string, CommandParent*> _mapCommands = {};

    void                        clean(std::string &str) const;
    std::vector<std::string>    split(std::string const &str, std::string const & delimiter, int maxSize = 0) const;


public:
    CommandParser();
    ~CommandParser();

    template <class T>
            void                    addCommand(T &context, std::string key, ActionClientFunction<T> f) {
                this->removeCommand(key);
                Command<T> *tmp = new Command<T>(context, f);
                this->_mapCommands[key] = tmp;
            };
    void                            removeCommand(std::string const &key);
    void                            removeAllCommands();
    bool                            parseCommand(ClientSocket *client, std::string const &str);
};


#endif                  //HANDS_FREE_COMMANDPARSER_HPP