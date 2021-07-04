//
// Created by my_fl on 2021-06-08.
//

#include "main_draws.h"



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

};

void draw_check_failed_tryout(HDC hDC, RECT size){

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
    return RegisterClassA(&strcut);
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
            scene.addStage((unsigned char*)"alert", 6, draw_alert, virtualDrawArea);

            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            SetTimer(hWnd, main_draws_timeRefreshEvent, 1000, nullptr);
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            SetTimer(hWnd, main_draws_cardCheckRepeater, 20000, nullptr);
            main_scard_fn::cardReaderFn();
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            break;

        case WM_KEYDOWN:
            std::cout << "test key down!" << '\n';
        break;

        case WM_TIMER:
            switch (wParam) {
                case main_draws_timeRefreshEvent:
                    std::cout << "past a sec..." << '\n';
                    break;
                case main_draws_cardCheckRepeater:
                {
                    std::cout << "Run loop of card checking" << '\n';
                    main_scard_fn::cardReaderFn();
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
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_QUIT:
            MessageBox(NULL,(LPCSTR)L"quited",(LPCSTR)L"Debug alert",MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
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



    hMemDC = CreateCompatibleDC(hDC);
    bitmap = CreateCompatibleBitmap(hDC, data.rect.top, data.rect.bottom);

    old_hMemDC = (HDC)SelectObject(hMemDC, bitmap);

    main_draws::onDrawAtDesktop(hWnd, hMemDC, size);

    TransparentBlt(hDC, data.rect.left,data.rect.top,data.rect.right,data.rect.bottom,
                   hMemDC, 0, 0,  data.rect.top, data.rect.bottom,
                   RGB(255,0,255));

    ValidateRect(hWnd, &data.rect);

    SelectObject(hMemDC, old_hMemDC);
    DeleteObject(bitmap);
    DeleteDC(hMemDC);

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
};






