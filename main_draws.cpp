//
// Created by my_fl on 2021-06-08.
//

#include "main_draws.h"

HINSTANCE* main_draws::hInstance = nullptr;
HHOOK main_draws::keyboardHooked = nullptr;

void draw_default(HDC hDC, RECT size){
    //카드를 읽는 중에는 아무것도 그리지 않음
    HBRUSH brh;
    RECT rect{0,0, size.top, size.bottom};
    Rectangle(hDC, 0,0, size.top, size.bottom);
    brh = CreateSolidBrush(RGB(255, 0, 255));
    FillRect(hDC, &rect, brh);
};

void draw_alert(HDC hDC, RECT size){
    //카드가 없음
    //일정 시간뒤에 종료됨
    Rectangle(hDC, 0,0, size.top, size.bottom);

    RECT tDraw_test{0,0,size.top, size.bottom};
    DrawTextA(hDC, "test string1123", -1, &tDraw_test, DT_TOP|DT_LEFT|DT_NOCLIP);
    DrawTextA(hDC, "test string2456", -1, &tDraw_test, DT_BOTTOM|DT_RIGHT|DT_NOCLIP);
};

void draw_check_scard(HDC hDC, RECT size){

};

void draw_check_success(HDC hDC, RECT size){
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,300, 150};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\ncheck_\nsuccess\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_check_failed_tryout(HDC hDC, RECT size){
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,300, 150};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\ncheck_\nfailed_tryout\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_check_failed_scan(HDC hDC, RECT size) {
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,290, 140};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\ncheck_\nfailed_scan\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_wait_for_card_scan(HDC hDC, RECT size) {
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,290, 140};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\nwait_\nfor_card_scan\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_reset_serial(HDC hDC, RECT size) {
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,290, 140};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\nreset_\nserial\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_check_register_miss_check(HDC hDC, RECT size) {
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,290, 140};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\ncheck_\nregister_miss_check\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};

void draw_check_register_clear_check(HDC hDC, RECT size) {
    HFONT c;
    c = CreateFont(26,4,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                   CLIP_DEFAULT_PRECIS,PROOF_QUALITY, CLEARTYPE_QUALITY,TEXT("Arial"));
    RECT tDraw_test{3, 10,290, 140};
    SelectObject(hDC, c);
    SetTextColor(hDC, RGB(255,255,255));
    SetBkMode(hDC, RGB(255,0,255));
    DrawTextA(hDC, "draw_\ncheck_\nregister_clear_check\0", -1, &tDraw_test, DT_LEFT|DT_TOP|DT_WORDBREAK);
};


void runScardReader(unsigned char* ref_serialByte){
    main_scard_fn::cardReaderFn(ref_serialByte);
    std::cout << "Card serial number : ";
    for(int idxz = 0; idxz < 8; ++idxz)
        std::cout << std::hex << (int)ref_serialByte[idxz] << std::dec;
    std::cout << std::endl;
}

bool checkResultOfScardReaderFn(unsigned char copied_serialByte[8]){
    unsigned int i(0), x(0);
    for ( i=0;i<8;++i )
        if (copied_serialByte[i] == 0)
            ++x;
    if (x == 8)
        return false;
    else return true;
};


void keyboardHookingRefresh(HINSTANCE hinstance, HHOOK* keyboardHook) {
    std::cout << "keyboard hook refreshing.." << '\n';
    if (*keyboardHook != nullptr)
        UnhookWindowsHookEx(*keyboardHook);
    *keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&main_draws::_keyboardProc, hinstance, 0);
    if (*keyboardHook == nullptr)
        std::cout << "Hooking Error" << std::endl;
};

bool registerSerialChecker(const char a[8], const char b[8]) {
    unsigned idx(0);
    for (idx=0;idx<8;++idx) {
        if (a[idx] != b[idx])
            return false;
    }
    return true;
}

void registerPutValueReadyStat(const bool stat) {
    HKEY handle;
    LONG res;
    DWORD value = (DWORD)stat;

    res = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            nullptr,
            0, KEY_ALL_ACCESS,
            &handle);

    if (res != ERROR_SUCCESS) {
        std::cout << "register open3 failed" << '\n';
    }

    res = RegSetValueEx(handle, "ScardLock_ed", 0, REG_DWORD, (LPBYTE)&value, sizeof(value));
    std::cout << "stat saved" << '\n';

    if (res != ERROR_SUCCESS) {
        std::cout << "register set value3 failed" << '\n';
    }

    RegCloseKey(handle);
};

void registerPutValueSerial(const unsigned char serial[8]) {
    HKEY handle;
    LONG res;

    res = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            nullptr,
            0, KEY_ALL_ACCESS,
            &handle);

    if (res != ERROR_SUCCESS) {
        std::cout << "register open1 failed" << '\n';
    }

    res = RegSetValueEx(handle, "ScardLock_serial", 0, REG_SZ, (LPBYTE)serial, 8);
    std::cout << "serial saved" << '\n';

    if (res != ERROR_SUCCESS) {
        std::cout << "register set value1 failed" << '\n';
    }

    RegCloseKey(handle);
};

bool registerGetReadyStat() {
    HKEY handle;
    LONG res;
    DWORD buffer;
    res = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            nullptr,
            0, KEY_ALL_ACCESS,
            &handle);

    if (res != ERROR_SUCCESS)
        std::cout << "register open4 failed" << '\n';

    DWORD type;
    DWORD byte = sizeof(DWORD); //8바이트 넣었는데 레지스트리에서 읽어올때 \n 까지 붙여서 오기때문에 9로 쓴다 (추측)
    res = RegQueryValueExA(handle, "ScardLock_ed", nullptr, &type, (LPBYTE) &buffer, &byte);
    if (res != ERROR_SUCCESS)
        std::cout << "register query4 failed" << res << '\n';
    RegCloseKey(handle);


    return (buffer == 1 ? true : false);
}

void registerGetSerial(char* buffer) {
    HKEY handle;
    LONG res;

    res = RegOpenKeyEx(
            HKEY_CURRENT_USER,
            nullptr,
            0, KEY_ALL_ACCESS,
            &handle);

    if (res != ERROR_SUCCESS)
        std::cout << "register open2 failed" << '\n';

    DWORD type;
    DWORD byte = 9; //8바이트 넣었는데 레지스트리에서 읽어올때 \n 까지 붙여서 오기때문에 9로 쓴다 (추측)
    res = RegQueryValueExA(handle, "ScardLock_serial", nullptr, &type, (LPBYTE) buffer, &byte);
    if (res != ERROR_SUCCESS)
        std::cout << "register query2 failed" << res << '\n';

    RegCloseKey(handle);
}



void registerRenew(UCHAR* serial) {

    if (!registerGetReadyStat()) {
        std::cout << "it is now re-set the serial" << '\n';
        registerPutValueSerial(serial);
        registerPutValueReadyStat(true);
    } else {
        std::cout << "pass the re-set" << '\n';
    }
};

//main_scard_fn



ATOM main_draws::initRegister(HINSTANCE& handle, WNDCLASSA &strcut) {
    strcut                  = {};
    strcut.hInstance        = handle;
    strcut.lpfnWndProc      = (WNDPROC)main_draws::_wndProc;
    strcut.hIcon            = LoadIconA(handle, IDI_WINLOGO);
    strcut.hCursor          = LoadCursorA(handle, IDC_ARROW);
    strcut.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    strcut.cbClsExtra       = 0;
    strcut.cbWndExtra       = 0;
    strcut.style            = CS_GLOBALCLASS; //CS_VREDRAW | CS_DROPSHADOW | CS_NOCLOSE
    strcut.lpszClassName    = (LPCSTR)MAIN_CPP_MAIN_DRAWS_CLASSNAME; //23-byte
    strcut.lpszMenuName     = 0;

    main_draws::hInstance = &handle;

    return RegisterClassA(&strcut);
}


LRESULT CALLBACK main_draws::_keyboardProc(INT nCode, WPARAM wParam, LPARAM lParam) {
    static bool activatedWave(false);
    static bool activatedLCtrl(false);
    static bool activatedLAlt(false);
    KBDLLHOOKSTRUCT* ABoutKeyboard = (KBDLLHOOKSTRUCT*)lParam;
    switch(wParam) {
        case WM_KEYUP:
            if (ABoutKeyboard->vkCode == 192)
                activatedWave = false;
            if (ABoutKeyboard->vkCode == 162)
                activatedLCtrl = false;
            if (ABoutKeyboard->vkCode == 164)
                activatedLAlt = false;
            break;
        case WM_KEYDOWN:
            if (ABoutKeyboard->vkCode == 192)
                activatedWave = true;
            if (ABoutKeyboard->vkCode == 162)
                activatedLCtrl = true;
            if (ABoutKeyboard->vkCode == 164)
                activatedLAlt = true;

            //키 조합
            if (activatedWave && activatedLCtrl && activatedLAlt) {
                std::cout << "- - - -CLEAR SERIAL REG" << '\n';
                main_activity scene;
                scene.sync();
                scene.selectStage((unsigned char*)"reset_serial");
                registerPutValueReadyStat(false);
            }

            break;
    }
    std::cout << "Recieved key : " << ABoutKeyboard->vkCode << std::endl;
    return CallNextHookEx ( main_draws::keyboardHooked, nCode , wParam, lParam );
}


LRESULT CALLBACK main_draws::_wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    static HWND windowHWND;
    static HDC windowHDC;
    static HANDLE hTimerPerASec;
    static RECT virtualDrawArea;

    main_activity scene;



    switch(uMsg) {
        case WM_CREATE:
            std::cout << "created!" << '\n';

            windowHWND = GetDesktopWindow();
            windowHDC = GetDC(0);

            virtualDrawArea.left = main_draws_positionLeft;
            virtualDrawArea.top = main_draws_positionTop;
            virtualDrawArea.right = main_draws_positionRight;
            virtualDrawArea.bottom = main_draws_positionBottom;

            scene.sync();
            scene.addStage((unsigned char*)"default", 8, draw_default, {0,0,0,0});
            scene.addStage((unsigned char*)"check_scard", 12, draw_check_scard, virtualDrawArea);
            scene.addStage((unsigned char*)"check_success", 14, draw_check_success, virtualDrawArea);
            scene.addStage((unsigned char*)"check_failed_tryout", 20, draw_check_failed_tryout, virtualDrawArea);
            scene.addStage((unsigned char*)"check_failed_scan", 18, draw_check_failed_scan, virtualDrawArea);
            scene.addStage((unsigned char*)"wait_for_card_scan", 19, draw_wait_for_card_scan, virtualDrawArea);
            scene.addStage((unsigned char*)"reset_serial", 13, draw_reset_serial, virtualDrawArea);
            scene.addStage((unsigned char*)"check_register_miss_check", 26, draw_check_register_miss_check, virtualDrawArea);
            scene.addStage((unsigned char*)"check_register_clear_check", 27, draw_check_register_clear_check, virtualDrawArea);
            scene.addStage((unsigned char*)"alert", 6, draw_alert, virtualDrawArea);

            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            SetTimer(hWnd, main_draws_timeRefreshEvent, 1000, nullptr);
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            SetTimer(hWnd, main_draws_cardCheckRepeater, 20000, nullptr);
            {
                unsigned char csn[8]{0};
                runScardReader(csn);
                main_activity scene;
                scene.sync();
                if (checkResultOfScardReaderFn(csn)) {
                    std::cout << "is completed with process" << '\n';
                    scene.selectStage((unsigned char*)"check_success");
                    registerRenew(csn);
                } else {
                    std::cout << "failed!" << '\n';
                    scene.selectStage((unsigned char*)"check_failed_scan");
                }
            }
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            keyboardHookingRefresh(*main_draws::hInstance, &main_draws::keyboardHooked);
            break;


        case WM_TIMER:
            switch (wParam) {
                case main_draws_timeRefreshEvent:
                    std::cout << "past a sec..." << '\n';
                    break;
                case main_draws_cardCheckRepeater:
                {
                    unsigned char csn[8]{0};
                    runScardReader(csn);
                    main_activity scene;
                    scene.sync();
                    if (checkResultOfScardReaderFn(csn)) {
                        std::cout << "is completed with process" << '\n';
                        registerRenew(csn);
                        scene.selectStage((unsigned char*)"check_success");
                    } else {
                        std::cout << "failed!" << '\n';
                        scene.selectStage((unsigned char*)"check_failed_scan");
                    }
                    keyboardHookingRefresh(*main_draws::hInstance, &main_draws::keyboardHooked);
                }
                break;
            }
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            //main_draws::eventOnPaint(hWnd);
            main_draws::eventOnPaintAtDesktop(windowHWND, windowHDC, &virtualDrawArea);
            break;

        case WM_APPCOMMAND:
            std::cout << "WM_APPCOMMAND" << '\n';
            break;

        case WM_ACTIVATE:
            std::cout << "WM_ACTIVATE" << '\n';
            break;

        case WM_HOTKEY:
            std::cout << "WM_HOTKEY" << '\n';
            break;

        case WM_DEADCHAR:
            std::cout << "WM_DEADCHAR" << '\n';
            break;

        case WM_SYSKEYDOWN:
        case WM_CHAR:
            std::cout << "char triggered" << '\n';
            break;

        case WM_KEYUP:
            std::cout << "test key up!" << wParam << " * " << lParam << '\n';
            break;

        case WM_KEYDOWN:
            std::cout << "test key down!" << wParam << " * " << lParam << '\n';
            break;

        case WM_NCDESTROY:
            MessageBox(NULL,(LPCSTR)L"WM_NCDESTROY",(LPCSTR)L"Debug alert",MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
            break;
        case WM_CLOSE:
            MessageBox(NULL,(LPCSTR)L"WM_CLOSE",(LPCSTR)L"Debug alert",MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
            break;
        case WM_DESTROY:
            MessageBox(NULL,(LPCSTR)L"WM_DESTROY",(LPCSTR)L"Debug alert",MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
            PostQuitMessage(0);
            break;
        case WM_QUIT:
            MessageBox(NULL,(LPCSTR)L"WM_QUIT",(LPCSTR)L"Debug alert",MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
            break;


    }
    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void main_draws::errChkOfClassRegisterInit(const ATOM result) {
    if (!result)
        std::cout << "Class register failed" << '\n';
}



void main_draws::eventOnPaint(HWND hWnd) {
//    PAINTSTRUCT ps;
//    BeginPaint(desktopHWND, &ps);
//    main_draws::onDraw(desktopHWND, &ps, desktopHDC);
//    EndPaint(desktopHWND, &ps);
//    Sleep(24);
};

void main_draws::onDraw(HWND hWnd, PAINTSTRUCT* ps) {
    //메인 프로세스 윈도우 그리기
};

void main_draws::eventOnPaintAtDesktop(HWND hWnd, HDC hDC, RECT* size) {
    HDC hMemDC, old_hMemDC;
    HBITMAP bitmap;

    main_activity scene;
    mainActivityStageData data;
    scene.sync();
    //scene.currentStageSetArea(size->left, size->right, size->top, size->bottom);
    scene.currentStage(&data);

    InvalidateRect(hWnd, &data.rect, false);

    hMemDC = CreateCompatibleDC(hDC);
    bitmap = CreateCompatibleBitmap(hDC, data.rect.top, data.rect.bottom);

    old_hMemDC = (HDC)SelectObject(hMemDC, bitmap);

    main_draws::onDrawAtDesktop(hWnd, hMemDC, size);

    TransparentBlt(hDC, data.rect.left,data.rect.top,data.rect.right,data.rect.bottom,
                   hMemDC, 0, 0,  data.rect.top, data.rect.bottom,
                   RGB(255,0,255));


    SelectObject(hMemDC, old_hMemDC);
    DeleteObject(bitmap);
    DeleteDC(hMemDC);

    ValidateRect(hWnd, &data.rect);

    //고정 딜레이
    Sleep(1000 / 36);
};

void main_draws::onDrawAtDesktop(HWND hWnd, HDC hDC, RECT* size) {
    //scene
    main_activity scene;
    CALLBACK_FUNC_HDC caller;
    scene.sync();
    scene.currentStageCallback(&caller);
    caller(hDC, *size);
}








