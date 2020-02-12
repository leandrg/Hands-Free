//
// Created by Gaëtan Léandre on 15/10/2019.
//

#ifndef                 HANDS_FREE_CLIENTSOCKET_HPP
#define                 HANDS_FREE_CLIENTSOCKET_HPP

#include                "Socket.hpp"
#include                "ActionClientFunction.hpp"
#include                "Command.hpp"
#include <iostream>


class                   ClientSocket: public Socket {
    std::string          _stringId;
    CommandParent       *success = NULL;
    CommandParent       *error = NULL;

public:
    ClientSocket(SOCKET socket, std::string stringId);
    ~ClientSocket();
    const std::string   getStringId() const;
    void                setStringId(const std::string stringId);
    void deleteSuccess();
    template <class T>
        void onSuccess(T &context, ActionClientFunction<T> f) {
            this->deleteSuccess();
            this->success = new Command<T>(context, f);
        };
    void onSuccess(ClientSocket *clientSocket, std::string const &str);
    void deleteError();
    template <class T>
        void onError(T &context, ActionClientFunction<T> f) {
            this->deleteError();
            this->error = new Command<T>(context, f);
        };
    void onError(ClientSocket *clientSocket, std::string const &str);
};

#else

class                   ClientSocket;

#endif                  //HANDS_FREE_CLIENTSOCKET_HPP
