//
// Created by my_fl on 2021-06-07.
//

#ifndef SCARD_LOCK_MAIN_H
#define SCARD_LOCK_MAIN_H

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


#include "main_include.h"

#include "main_fn.h"


//####################################################
// 금융 공동망 정의
//####################################################
//애플릿을 선택
#ifndef COMMAND_DO_SELECT_FILE
#define COMMAND_DO_SELECT_FILE 0x00, 0xa4, 0x04, 0x00, 0x07
#endif

//카드 시리얼 가지기
#ifndef COMMAND_GET_CARD_SERIAL
#define COMMAND_GET_CARD_SERIAL 0x00, 0xCA, 0x01, 0x11
#endif
//####################################################
//####################################################


//####################################################
// 금융 공동망 정의
//####################################################
//금융 공동망 RID
#ifndef KO_FN_AID_RID
#define KO_FN_AID_RID 0Xd4, 0x10, 0x65, 0x09, 0x90
#endif

//직블
#ifndef KO_FN_AID_PIX_DF_DIRECT
#define KO_FN_AID_PIX_DF_DIRECT 0X30, 0x10
#endif

//금융 공동망
#ifndef KO_FN_AID_PIX_DF_FN
#define KO_FN_AID_PIX_DF_FN 0X00, 0x10
#endif

//전자 화폐
#ifndef KO_FN_AID_PIX_DF_CYBER
#define KO_FN_AID_PIX_DF_CYBER 0X00, 0x20
#endif

//인증서(서명용)
#ifndef KO_FN_AID_PIX_DF_SIGN
#define KO_FN_AID_PIX_DF_SIGN 0X00, 0x30
#endif

//인증서(키 분배용)
#ifndef KO_FN_AID_PIX_DF_DISTRIBUTE
#define KO_FN_AID_PIX_DF_DISTRIBUTE 0X00, 0x40
#endif
//####################################################
//####################################################

#endif //SCARD_LOCK_MAIN_H
