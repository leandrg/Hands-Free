//
// Created by Gaëtan Léandre on 15/10/2019.
//

#ifndef HANDS_FREE_SOCKET_HPP
#define HANDS_FREE_SOCKET_HPP

#include            <stdio.h>
#include            <unistd.h>
#include            <sys/socket.h>
#include            <string>
#include            <string.h>

typedef int         SOCKET;
#define MAX_BUFF_SIZE 4096

typedef struct      s_package {
    int             size;
    char            buffer[MAX_BUFF_SIZE + 1] = {0};
}                   t_package;

class               Socket {
protected:
    SOCKET          _socket;

public:
    Socket();
    Socket(SOCKET socket);
    ~Socket();
    SOCKET          getSocket() const;
    void            fdSet(fd_set *value) const;
    bool            fdIsSet(const fd_set *value) const;
    t_package       read() const;
    void            write(t_package const &data);
    friend bool     operator<(const Socket &a, const Socket &b);
    friend bool     operator>(const Socket &a, const Socket &b);
    friend bool     operator==(const Socket &a, const Socket &b);
    friend bool     operator==(const Socket &a, fd_set *value);
    friend Socket   &operator<<(Socket &a, const std::string data);
    friend std::string &operator<<(std::string &data, const Socket &a);
    friend t_package &operator<<(t_package &data, const Socket &a);
};


#endif //HANDS_FREE_SOCKET_HPP
