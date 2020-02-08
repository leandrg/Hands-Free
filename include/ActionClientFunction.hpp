//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef             HANDS_FREE_ACTIONCLIENTFUNCTION_HPP
#define             HANDS_FREE_ACTIONCLIENTFUNCTION_HPP

#include            "ClientSocket.hpp"

template<typename T>
using ActionClientFunction = void (T::*)(ClientSocket *clientSocket, std::string const &str);

#endif              //HANDS_FREE_ACTIONCLIENTFUNCTION_HPP
