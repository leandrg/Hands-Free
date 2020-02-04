//
// Created by Gaëtan Léandre on 03/02/2020.
//

#ifndef                 HANDS_FREE_SDP_HPP
#define                 HANDS_FREE_SDP_HPP

#include                <iostream>
#include                <bluetooth/sdp.h>
#include                <bluetooth/sdp_lib.h>
#include <stdio.h>

class                   Sdp {
    sdp_session_t       *_session = NULL;

protected:
    sdp_record_t        _record = {};

public:
    Sdp();
    ~Sdp();
    void unregisterRecord();
    void registerRecord();
};

#endif                  //HANDS_FREE_SDP_HPP
