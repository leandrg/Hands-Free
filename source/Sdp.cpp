//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include                "Sdp.hpp"

Sdp::Sdp() {}

Sdp::~Sdp() {
    this->unregisterRecord();
}

void                    Sdp::unregisterRecord() {
    std::cout << "here" << std::endl;
    if (this->_session != NULL) {
        std::cout << "Close session" << std::endl;
        sdp_close(this->_session);
    }
    this->_session = NULL;
}

void                    Sdp::registerRecord() {
    bdaddr_t            bdaddr_any = {{0, 0, 0, 0, 0, 0}};
    bdaddr_t            bdaddr_local = {{0, 0, 0, 0xff, 0xff, 0xff}};

    this->unregisterRecord();
    this->_session = sdp_connect(&bdaddr_any, &bdaddr_local, SDP_RETRY_IF_BUSY);
    if (this->_session == NULL) {
        perror("sdp_connect");
        return;
    }
    std::cout << this->_session << std::endl;
    if (sdp_record_register(this->_session, &this->_record, 0) < 0)
        std::cerr << "Can't register record" << std::endl;
    else
        std::cout << "Record registered successfully!" << std::endl;
}