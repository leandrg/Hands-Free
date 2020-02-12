//
// Created by Gaëtan Léandre on 08/02/2020.
//

#ifndef             HANDS_FREE_HFPDEFINE_HPP
#define             HANDS_FREE_HFPDEFINE_HPP

#define             HFP_COMMAND_SEND_BY_HF              "AT"


//RECEIVED COMMANDS
#define             HFP_COMMAND_SUCCESS                 "OK"
#define             HFP_COMMAND_ERROR                   "ERROR"
#define             HFP_COMMAND_SUPPORTED_FEATURES      "+BRSF"
#define             HFP_COMMAND_INDICATORS              "+CIND"

//AT+BRSF FEATURES
#define             HFP_AT_BRSF_FEATURE_RNEC            0
#define             HFP_AT_BRSF_FEATURE_THREE_WAY_CALL  1
#define             HFP_AT_BRSF_FEATURE_CLI             2
#define             HFP_AT_BRSF_FEATURE_VOICE_RECO      3
#define             HFP_AT_BRSF_FEATURE_REMOTE_VOL      4
#define             HFP_AT_BRSF_FEATURE_CALL_STATUS     5
#define             HFP_AT_BRSF_FEATURE_CALL_CONTROL    6
#define             HFP_AT_BRSF_FEATURE_CODEC           7
#define             HFP_AT_BRSF_FEATURE_HF_IND          8
#define             HFP_AT_BRSF_FEATURE_ESCO            9

//+BRSF FEATURES
#define             HFP_BRSF_FEATURE_THREE_WAY_CALL     0
#define             HFP_BRSF_FEATURE_RNEC               1
#define             HFP_BRSF_FEATURE_VOICE_RECO         2
#define             HFP_BRSF_FEATURE_RING_TONE          3
#define             HFP_BRSF_FEATURE_ATTACH_NUMBER      4
#define             HFP_BRSF_FEATURE_REJECT_CALL        5
#define             HFP_BRSF_FEATURE_CALL_STATUS        6
#define             HFP_BRSF_FEATURE_CALL_CONTROL       7
#define             HFP_BRSF_FEATURE_ERROR_RESULT       8
#define             HFP_BRSF_FEATURE_CODEC              9
#define             HFP_BRSF_FEATURE_HF_IND             10
#define             HFP_BRSF_FEATURE_ESCO               11

#endif              //HANDS_FREE_HFPDEFINE_HPP
