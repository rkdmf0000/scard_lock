#include "main.h"


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
        std::cout << Res << ", debug : ";
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
        std::cout << Res << ", debug : ";
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


    //순전히 디버그용
    //system("PAUSE");

    exit(0);
};





void cardReaderFn() {
    CONSOLE_SCREEN_BUFFER_INFO ww_csbi;
    int ww_columns, ww_rows;

    //loop card discern
    long long runTimeCnt(0);

    //dummy count
    unsigned int idx(0);

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
        //std::cout << std::endl << std::endl;

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


        std::cout << "waiting.. (" << (120-runTimeCnt) << "/120)" << '\n';

        //콘솔 크기 가져와!
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ww_csbi);
        ww_columns = ww_csbi.srWindow.Right - ww_csbi.srWindow.Left + 1;
        ww_rows = ww_csbi.srWindow.Bottom - ww_csbi.srWindow.Top + 1;

        //화면 정리
        //for(idx=0;idx<ww_rows-1;++idx)
        //    std::cout << '\n';


        Sleep(1000);

        //exit condition
        if (runTimeCnt == 120)
            break;
    };

};






int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nShowCmd) {

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    WNDCLASS scardLockWNDClass;
    main_draws::errChkOfClassRegisterInit( main_draws::initRegister(hInstance, scardLockWNDClass) );


    HWND scardClockWindowHandle;
    scardClockWindowHandle = CreateWindowExA(0, MAIN_CPP_MAIN_DRAWS_CLASSNAME, "hello", 0, 0, 0, 250, 250, nullptr, nullptr, hInstance, 0);

    if (!scardClockWindowHandle) {
        std::cout << "naga die" << '\n';
    } else {
        std::cout << "naga live" << '\n';
    };


    //ShowWindow(scardClockWindowHandle, SW_SHOW);
    ShowWindow(scardClockWindowHandle, SW_HIDE);
    UpdateWindow(scardClockWindowHandle);

    MSG msg = {};
    while (1)
    {
        if (PeekMessage(&msg, scardClockWindowHandle, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // 메세지가 없이 들어온다 쓸 생각하지 마라
            // 여긴 오로지 그리는데 사용될 예정.
            SendMessage(scardClockWindowHandle, WM_PAINT, 0, 0);
        };
    };

    system("PAUSE");
    return 0;
};
