//
// Created by Gaëtan Léandre on 17/02/2020.
//

#ifndef HANDS_FREE_SERVER_HPP
#define HANDS_FREE_SERVER_HPP


class Server {
protected:
    bool                        _started = false;

public:
    virtual void                start() = 0;
    virtual void                listen() = 0;
    virtual void                stop() = 0;
};


#endif //HANDS_FREE_SERVER_HPP
