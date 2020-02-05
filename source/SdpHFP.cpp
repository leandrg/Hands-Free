//
// Created by Gaëtan Léandre on 03/02/2020.
//

#include            "SdpHFP.hpp"


SdpHFP::SdpHFP(std::string const &serviceName, std::string const &serviceProvider, std::string const &serviceDescription) {
    this->_serviceName = serviceName;
    this->_serviceProvider = serviceProvider;
    this->_serviceDescription = serviceDescription;
}

SdpHFP::~SdpHFP() {}

void                SdpHFP::registerRecord(uint8_t channel) { //TODO OMG sdp_list_insert_sorted can't be free
    uuid_t          rootID,
                    handFreeServiceClassID, genericAudioServiceClassID,
                    l2capID, rfcommID;

    sdp_list_t      *rootList,
                    *classList,
                    *l2capList, *rfcommList, *commonList, *parentList,
                    *profileList;

    sdp_data_t      *_channel, *features;

    sdp_profile_desc_t profile;

    //INIT public group browser
    sdp_uuid16_create(&rootID, PUBLIC_BROWSE_GROUP);
    rootList = sdp_list_append(0, &rootID);

    //INIT Service Class ID LIST
    sdp_uuid16_create(&handFreeServiceClassID, HANDSFREE_SVCLASS_ID);
    sdp_uuid16_create(&genericAudioServiceClassID, GENERIC_AUDIO_SVCLASS_ID);
    classList = sdp_list_append(0, &handFreeServiceClassID);
    sdp_list_append(classList, &genericAudioServiceClassID);

    //INIT Protocol List
    sdp_uuid16_create(&l2capID, L2CAP_UUID);
    l2capList = sdp_list_append(0, &l2capID);
    commonList = sdp_list_append(0, l2capList);
    sdp_uuid16_create(&rfcommID, RFCOMM_UUID);
    rfcommList = sdp_list_append(0, &rfcommID);
    _channel = sdp_data_alloc(SDP_UINT8, &channel);
    sdp_list_append(rfcommList, _channel);
    sdp_list_append(commonList, rfcommList);
    parentList = sdp_list_append(0, commonList);

    //INIT Profile description
    sdp_uuid16_create(&profile.uuid, HANDSFREE_PROFILE_ID);
    profile.version = 0x0107;
    profileList = sdp_list_append(0, &profile);

    //INIT features
    uint16_t tmp = 0;
    features = sdp_data_alloc(SDP_UINT16, &tmp);

    sdp_set_browse_groups(&this->_record, rootList);
    sdp_set_service_classes(&this->_record, classList);
    sdp_set_access_protos(&this->_record, parentList);
    sdp_set_profile_descs(&this->_record, profileList);
    sdp_set_info_attr(&this->_record, this->_serviceName.c_str(), this->_serviceProvider.c_str(), this->_serviceDescription.c_str());
    sdp_attr_add(&this->_record, SDP_ATTR_SUPPORTED_FEATURES, features);

    this->Sdp::registerRecord();

    //FREE everything
    sdp_data_free(_channel);
    sdp_data_free(features);
    sdp_list_free(rootList, 0);
    sdp_list_free(classList, 0);
    sdp_list_free(l2capList, 0);
    sdp_list_free(rfcommList, 0);
    sdp_list_free(commonList, 0);
    sdp_list_free(parentList, 0);
    sdp_list_free(profileList, 0);
}