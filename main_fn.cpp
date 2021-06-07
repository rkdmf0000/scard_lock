//
// Created by my_fl on 2021-06-07.
//

#include "main_fn.h"


void FN_SLEEP(unsigned int milli_sec) {
    clock_t start_clk = clock();
    milli_sec--;
    while(1) {
        if( (clock()- start_clk) > milli_sec )
            break;
    };
};

const DWORD getAttr(LPBYTE* txt, DWORD* size, SCARDHANDLE* handle, ULONG type) {
    LPBYTE* ref_txt = (LPBYTE*)txt;
    DWORD* ref_size = (DWORD*)size;
    SCARDCONTEXT* ref_handle = (SCARDCONTEXT*)handle;
    LONG res;
    DWORD resultSize = SCARD_AUTOALLOCATE;
    res = SCardGetAttrib(*ref_handle, type, (LPBYTE)ref_txt, &resultSize);
    if (res == SCARD_S_SUCCESS) {
        *ref_size = resultSize;
    } else {
        txt = nullptr;
        *ref_size = 0;
    };
    return res;
};


void printSWForTransmitRequest(BYTE aSide, BYTE bSide) {
    bool flag(false);

    //정상처리 코드1
    if (aSide == 0x90) {
        switch(bSide) {
            case 0x00:
                std::cout << "0x90 * Process Completed!" << '\n';
                break;
            default:
                std::cout << "0x90 * Undefined `0x6a` error" << '\n';
                break;
        };
        flag = true;
    };

    //정상처리 코드2
    if (aSide == 0x61) {
        switch(bSide) {
            default:
                std::cout << "0x61 * Process Completed! and you can use " << (int)bSide << " byte" << '\n';
                break;
        };
        flag = true;
    };

    //파라미터 오류
    if (aSide == 0x6a) {
        switch(bSide) {
            case 0x00:
                std::cout << "0x6a * There is notting" << '\n';
                break;
            case 0x80:
                std::cout << "0x6a * Parameter error of data field" << '\n';
                break;
            case 0x81:
                std::cout << "0x6a * Not supported action" << '\n';
                break;
            case 0x82:
                std::cout << "0x6a * Does not exist file" << '\n';
                break;
            case 0x83:
                std::cout << "0x6a * Does not exist record" << '\n';
                break;
            case 0x84:
                std::cout << "0x6a * File memory dose not enough" << '\n';
                break;
            case 0x85:
                std::cout << "0x6a * It is mismatch Lc to TLV Structure" << '\n';
                break;
            case 0x86:
                std::cout << "0x6a * Parameter1 , Parameter2 Internal error" << '\n';
                break;
            case 0x87:
                std::cout << "0x6a * Parameter1, Parameter2, they are mismatch of Lc" << '\n';
                break;
            case 0x88:
                std::cout << "0x6a * Reference data cannot found" << '\n';
                break;
            default:
                std::cout << "0x6a * Undefined `0x6a` error" << '\n';
                break;
        };
        flag = true;
    };

    if (!flag)
        std::cout << "-- Undefined Case in " << std::hex << aSide << ", " << bSide << std::dec << '\n';

};