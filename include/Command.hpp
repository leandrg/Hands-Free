//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef                         HANDS_FREE_COMMAND_HPP
#define                         HANDS_FREE_COMMAND_HPP

#include                        "ClientSocket.hpp"

class                           CommandParent {
public:
    virtual ~CommandParent(){};
    virtual void                launch(ClientSocket *client, std::string const &str) {
        (void)client;
        (void)str;
    };
};

template <class T>
class                           Command : public CommandParent {
    T                           &_context;
    ActionClientFunction<T>     _f;

public:
    Command(T &context, ActionClientFunction<T> f) : _context(context), _f(f) {};
    ~Command(){};
    void                        launch(ClientSocket *client, std::string const &str) {
        (this->_context.*(this->_f))(client, str);
    };
};

#else

class                           CommandParent;
template <class T>
    class                           Command;

#endif                          //HANDS_FREE_COMMAND_HPP
