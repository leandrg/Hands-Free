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
#define             HFP_COMMAND_LISTEN_INDICATORS       "+CMER"
#define             HFP_COMMAND_INDICATOR_VALUE         "+CIEV"
#define             HPP_COMMAND_ERROR_CODE              "+CMEE"

//AT+BRSF FEATURES
#define             HFP_AT_BRSF_FEATURE_RNEC            (1 << 0)
#define             HFP_AT_BRSF_FEATURE_THREE_WAY_CALL  (1 << 1)
#define             HFP_AT_BRSF_FEATURE_CLI             (1 << 2)
#define             HFP_AT_BRSF_FEATURE_VOICE_RECO      (1 << 3)
#define             HFP_AT_BRSF_FEATURE_REMOTE_VOL      (1 << 4)
#define             HFP_AT_BRSF_FEATURE_CALL_STATUS     (1 << 5)
#define             HFP_AT_BRSF_FEATURE_CALL_CONTROL    (1 << 6)
#define             HFP_AT_BRSF_FEATURE_CODEC           (1 << 7)
#define             HFP_AT_BRSF_FEATURE_HF_IND          (1 << 8)
#define             HFP_AT_BRSF_FEATURE_ESCO            (1 << 9)

//+BRSF FEATURES
#define             HFP_BRSF_FEATURE_THREE_WAY_CALL     (1 << 0)
#define             HFP_BRSF_FEATURE_RNEC               (1 << 1)
#define             HFP_BRSF_FEATURE_VOICE_RECO         (1 << 2)
#define             HFP_BRSF_FEATURE_RING_TONE          (1 << 3)
#define             HFP_BRSF_FEATURE_ATTACH_NUMBER      (1 << 4)
#define             HFP_BRSF_FEATURE_REJECT_CALL        (1 << 5)
#define             HFP_BRSF_FEATURE_CALL_STATUS        (1 << 6)
#define             HFP_BRSF_FEATURE_CALL_CONTROL       (1 << 7)
#define             HFP_BRSF_FEATURE_ERROR_RESULT       (1 << 8)
#define             HFP_BRSF_FEATURE_CODEC              (1 << 9)
#define             HFP_BRSF_FEATURE_HF_IND             (1 << 10)
#define             HFP_BRSF_FEATURE_ESCO               (1 << 11)

#endif              //HANDS_FREE_HFPDEFINE_HPP
