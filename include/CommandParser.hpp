//
// Created by Gaëtan Léandre on 04/02/2020.
//

#ifndef                 HANDS_FREE_COMMANDPARSER_HPP
#define                 HANDS_FREE_COMMANDPARSER_HPP

#include                <string>
#include                <iostream>
#include                <unordered_map>
#include                "ClientSocket.hpp"

template<typename T>
using ActionFunction = void (T::*)(ClientSocket *clientSocket, std::string const &str);

class                   CommandParser {
    class                   CommandParent {
    public:
        virtual ~CommandParent(){};
        virtual void        launch(std::string const &str) {
            (void)str;
        };
    };

    template <class T>
    class                   Command : public CommandParent {
        T                   &_context;
        ActionFunction<T>   _f;

    public:
        Command(T &context, ActionFunction<T> f) : _context(context), _f(f) {};
        ~Command(){};
        void                launch(std::string const &str) {
            (this->_context.*(this->_f))(str);
        };
    };

    std::unordered_map<std::string, CommandParser::CommandParent*> _mapCommands = {};

public:
    CommandParser();
    ~CommandParser();

    template <class T>
            void        addCommand(T &context, std::string key, ActionFunction<T> f) {
                this->removeCommand(key);
                Command<T> *tmp = new CommandParser::Command<T>(context, f);
                this->_mapCommands[key] = tmp;
            };
    void                removeCommand(std::string const &key);
    void                removeAllCommands();
    bool                parseCommand(ClientSocket *client, std::string const &str);
};


#endif                  //HANDS_FREE_COMMANDPARSER_HPP