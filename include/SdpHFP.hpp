//
// Created by Gaëtan Léandre on 03/02/2020.
//

#ifndef             HANDS_FREE_SDPHFP_HPP
#define             HANDS_FREE_SDPHFP_HPP

#include            "Sdp.hpp"

class SdpHFP : public Sdp {
    std::string     _serviceName;
    std::string     _serviceProvider;
    std::string     _serviceDescription;

public:
    SdpHFP(std::string serviceName = "HandFree", std::string serviceProvider = "leandrg", std::string serviceDescription = "");
    ~SdpHFP();
    void            registerRecord(uint8_t channel);
};


#endif //HANDS_FREE_SDPHFP_HPP
