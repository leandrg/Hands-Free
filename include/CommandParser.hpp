//
// Created by Gaëtan Léandre on 04/02/2020.
//

#ifndef                 HANDS_FREE_COMMANDPARSER_HPP
#define                 HANDS_FREE_COMMANDPARSER_HPP

#include                <string>
#include                <iostream>
#include                <unordered_map>

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
        void (T::*_f)(std::string const &str);

    public:
        Command(T &context, void (T::*f)(std::string const &str)) : _context(context), _f(f) {};
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
            void addCommand(T &context, std::string key, void (T::*f)(std::string const &str)) {
                Command<T> *tmp = new CommandParser::Command<T>(context, f);
                this->_mapCommands[key] = tmp;
            }

    void                removeCommand(std::string const &key);
    void                removeAllCommands();
    bool                parseCommand(std::string const &str);
};


#endif                  //HANDS_FREE_COMMANDPARSER_HPP