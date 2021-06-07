#include "main.h"

#ifndef FN_SLEEP
#include <time.h>
void FN_SLEEP(unsigned int milli_sec) {
    clock_t start_clk = clock();
    milli_sec--;
    while(1) {
      if( (clock()- start_clk) > milli_sec )
          break;
    };
};
#endif


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
                std::cout << "*Undefined `0x6a` error" << '\n';
                break;
        };
        flag = true;
    };

    if (!flag)
        std::cout << "-- Undefined Case in " << aSide << ", " << bSide << '\n';

};






void FnT0Action(SCARDCONTEXT& hSC, SCARDHANDLE& hSCardConnect) {

    DWORD _res(0);
    LPBYTE _readerSystemName;
    DWORD _readerSystemNameSize;
    _res = getAttr(&_readerSystemName, &_readerSystemNameSize, &hSCardConnect, SCARD_ATTR_DEVICE_SYSTEM_NAME);
    std::cout << "Reader System Name : " << _readerSystemName << "("<< _readerSystemNameSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res <<  '\n' << '\n';

    LPBYTE _readerSerialNo;
    DWORD _readerSerialNoSize;
    _res = getAttr(&_readerSerialNo, &_readerSerialNoSize, &hSCardConnect, SCARD_ATTR_VENDOR_IFD_SERIAL_NO);
    std::cout << "Reader Serial Number : " << _readerSerialNo << "("<< _readerSerialNoSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res  << '\n' << '\n';

    LPBYTE _readerBWT;
    DWORD _readerBWTSize;
    _res = getAttr(&_readerBWT, &_readerBWTSize, &hSCardConnect, SCARD_ATTR_CURRENT_BWT);
    std::cout << "Reader BWT : " << _readerBWT << "("<< _readerBWTSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res << '\n' << '\n';

    LPBYTE _readerFriendlyName;
    DWORD _readerFriendlyNameSize;
    _res = getAttr(&_readerFriendlyName, &_readerFriendlyNameSize, &hSCardConnect, SCARD_ATTR_DEVICE_FRIENDLY_NAME);
    std::cout << "Reader Friendly Name : " << _readerFriendlyName << "("<< _readerFriendlyNameSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res << '\n' << '\n';

    LPBYTE _readerVendorIFDType;
    DWORD _readerVendorIFDTypeSize;
    _res = getAttr(&_readerVendorIFDType, &_readerVendorIFDTypeSize, &hSCardConnect, SCARD_ATTR_VENDOR_IFD_TYPE);
    std::cout << "Reader Vendor IFD Type : " << _readerVendorIFDType << "("<< _readerVendorIFDTypeSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res << '\n' << '\n';

    LPBYTE _readerChannelID;
    DWORD _readerChannelIDSize;
    _res = getAttr(&_readerChannelID, &_readerChannelIDSize, &hSCardConnect, SCARD_ATTR_CHANNEL_ID);
    std::cout << "Reader Channel ID : " << (int)_readerChannelID << "("<< _readerChannelIDSize << ")" << '\n';
    std::cout << (_res == SCARD_S_SUCCESS ? "[success]" : "[failed]") << " " << (_res == ERROR_NOT_SUPPORTED ? "[not support]" : "@") << _res << '\n' << '\n';

    //정리
    SCardFreeMemory(hSC, _readerSystemName);
    SCardFreeMemory(hSC, _readerSerialNo);
    SCardFreeMemory(hSC, _readerBWT);
    SCardFreeMemory(hSC, _readerFriendlyName);
    SCardFreeMemory(hSC, _readerVendorIFDType);
    SCardFreeMemory(hSC, _readerChannelID);



    //APDU PROTOCOL - START
    //##############################
    //##############################
    {
        std::cout << "##########################" << '\n';
        std::cout << "#FILE READ" << '\n';
        std::cout << "##########################" << '\n';
        INT idx(0);
        BYTE SendBuffer[] = {COMMAND_DO_SELECT_FILE, KO_FN_AID_RID, KO_FN_AID_PIX_DF_FN, 0xa2};
        BYTE ReceiveBuffer[44];
        LONG Res(0);
        DWORD SendSize = sizeof(SendBuffer), ReceiveSize = sizeof(ReceiveBuffer);
        SCARD_IO_REQUEST t;
        t.dwProtocol = SCARD_PROTOCOL_T0;
        t.cbPciLength = sizeof(t);
        Res = SCardTransmit(hSCardConnect, &t,SendBuffer, SendSize,nullptr,ReceiveBuffer, &ReceiveSize);
        std::cout << (int)Res << ", debug : ";
        for(idx=0; idx<ReceiveSize; ++idx)
            std::cout << std::hex <<  (int)(unsigned char)ReceiveBuffer[idx] << std::dec << " ";
        std::cout << "[SIZE:" << ReceiveSize << ']';
        std::cout << std::endl;
        if (ReceiveSize == 2)
            printSWForTransmitRequest(ReceiveBuffer[0], ReceiveBuffer[1]);
    };

    {
        std::cout << "##########################" << '\n';
        std::cout << "#GET CSN" << '\n';
        std::cout << "##########################" << '\n';
        INT idx(0);
        BYTE SendBuffer[] = {COMMAND_GET_CARD_SERIAL, 0x08};
        BYTE ReceiveBuffer[10];
        LONG Res(0);
        DWORD SendSize = sizeof(SendBuffer), ReceiveSize = sizeof(ReceiveBuffer);
        SCARD_IO_REQUEST t;
        t.dwProtocol = SCARD_PROTOCOL_T0;
        t.cbPciLength = sizeof(t);
        Res = SCardTransmit(hSCardConnect, &t,SendBuffer, SendSize,nullptr,ReceiveBuffer, &ReceiveSize);
        std::cout << (int)Res << ", debug : ";
        for(idx=0; idx<ReceiveSize; ++idx)
            std::cout << std::hex <<  (int)(unsigned char)ReceiveBuffer[idx] << std::dec << " ";
        std::cout << "[SIZE:" << ReceiveSize << ']';
        std::cout << std::endl;
        if (ReceiveSize == 2)
            printSWForTransmitRequest(ReceiveBuffer[0], ReceiveBuffer[1]);
    };

    //##############################
    //##############################
    //APDU PROTOCOL - END



    //종료
    std::cout << "- is over" << '\n';
    FN_SLEEP(3000);

    system("PAUSE");
    exit(0);
};











int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nShowCmd) {

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    //loop card discern
    long long runTimeCnt(0);

    //card reader system name list
    char _initReaderListFileName[] = "_reader_name.txt";


    //init reader list file
    std::ifstream readerList(_initReaderListFileName);
    if (!readerList.is_open()) {
        std::ofstream initWriter;
        initWriter.open(_initReaderListFileName);

        //default data
        char line1[29] = "HST USB Smart Card Reader 0\n";
        initWriter.write(line1, sizeof(line1) - 1);

        char line2[29] = "HST USB Smart Card Reader 1\n";
        initWriter.write(line2, sizeof(line2) - 1);

        char line3[30] = "HST USB Smart Card Reader 01\n";
        initWriter.write(line3, sizeof(line3) - 1);

        initWriter.close();
    }
    readerList.close();

    //prepare
    readerList.open(_initReaderListFileName);
    std::string readerItemLine;
    std::vector<std::string> vtReaderList;
    while (std::getline(readerList, readerItemLine)){
        std::cout << "reader item : " << readerItemLine.c_str() << '\n';
        vtReaderList.push_back(readerItemLine);
    };

    FN_SLEEP(1000);

    int readerSuccessIndex(-1);

    //설립
    SCARDCONTEXT    hSC;
    LONG            lSCardContextRes;

    lSCardContextRes = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hSC);

    //리더기 카드 연결
    SCARDHANDLE hSCardConnect;
    LONG lSCardConnectionRes;
    DWORD dlCardReaderProtocolRes;

    //run loop
    while(true) {

        //미관상 정리
        std::cout << std::endl << std::endl;

        ++runTimeCnt;

        //리더기 확인
        if (lSCardContextRes == SCARD_S_SUCCESS) {

            unsigned int listIdx(0);
            std::vector<std::string>::iterator listIter;
            for(listIter = vtReaderList.begin(); listIter!=vtReaderList.end(); ++listIter) {

                //정답 나왔으면, 아닌것들 스킵
                if (readerSuccessIndex != -1) {
                    if (listIdx != readerSuccessIndex) {
                        ++listIdx;
                        continue;;
                    }
                };

                //string casting
                std::string t = *listIter;



                lSCardConnectionRes = SCardConnectA(hSC, t.c_str(), SCARD_SHARE_SHARED,
                                                    SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hSCardConnect,
                                                    &dlCardReaderProtocolRes);

                switch(lSCardConnectionRes) {
                    case SCARD_S_SUCCESS:
                    case SCARD_W_REMOVED_CARD:
                        {
                            if (readerSuccessIndex == -1)
                                std::cout << "[ Spotted available reader and will be iteration pass by ]" << '\n';

                            readerSuccessIndex = listIdx;
                        }
                        break;
                    case SCARD_W_UNRESPONSIVE_CARD:
                        std::cout << "[ This smart card doesn't initialization proceed. Please make sure your card direction! ]" << '\n';
                        break;
                    case SCARD_E_READER_UNAVAILABLE:
                        std::cout << "[ Unavailable reader ]" << '\n';
                        break;
                    case SCARD_E_UNKNOWN_READER:
                        std::cout << "[ Unknown Reader Name ]" << '\n';
                        break;
                    default:
                        std::cout << "[ Undefined return value! ] : " << std::hex << (CONST DWORD)lSCardConnectionRes << std::dec << '\n';
                        break;
                };
                if (lSCardConnectionRes == SCARD_S_SUCCESS) {

                    switch (dlCardReaderProtocolRes) {
                        case SCARD_PROTOCOL_T0:
                            std::cout << "[protocol t0]" << '\n';
                            FnT0Action(hSC, hSCardConnect);
                            break;
                        case SCARD_PROTOCOL_T1:
                            std::cout << "[protocol t1]" << '\n';
                            break;
                        case SCARD_PROTOCOL_UNDEFINED:
                        default:
                            std::cout << "[undefined protocol]" << '\n';
                            break;
                    };
                } else {
                    std::cout << "failed [1]" << '\n';
                };


                ++listIdx;
            };

        } else {
            std::cout << "failed [0]" << '\n';
        };


        std::cout << "waiting.." << '\n';


        //FN_SLEEP(2000);
        Sleep(2525);

        //exit condition
        if (runTimeCnt == 100000000)
            break;
    };

    return 0;
};
