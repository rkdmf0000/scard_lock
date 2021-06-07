//
// Created by my_fl on 2021-06-07.
//
#ifndef MAIN_CPP_MAIN_FN_H
#define MAIN_CPP_MAIN_FN_H
#include "main_include.h"
void FN_SLEEP(unsigned int milli_sec);
const DWORD getAttr(LPBYTE* txt, DWORD* size, SCARDHANDLE* handle, ULONG type);
void printSWForTransmitRequest(BYTE aSide, BYTE bSide);
#endif //MAIN_CPP_MAIN_FN_H