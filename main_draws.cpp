//
// Created by my_fl on 2021-06-08.
//

#include "main_draws.h"


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

    switch(uMsg) {
        case WM_CREATE:
            std::cout << "created!" << '\n';

            windowHWND = GetDesktopWindow();
            windowHDC = GetDC(0);

            virtualDrawArea.left = main_draws_positionLeft;
            virtualDrawArea.top = main_draws_positionTop;
            virtualDrawArea.right = main_draws_positionRight;
            virtualDrawArea.bottom = main_draws_positionBottom;

            (HANDLE)SetTimer(hWnd, main_draws_timeRefreshEvent, 1000, nullptr);
            break;

        case WM_KEYDOWN:
            std::cout << "test key down!" << '\n';
        break;

        case WM_TIMER:
            switch (wParam) {
                case main_draws_timeRefreshEvent:
                    std::cout << "test! a sec" << '\n';
                    break;
            };
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            //main_draws::eventOnPaint(hWnd);
            main_draws::eventOnPaintAtDesktop(windowHWND, windowHDC, &virtualDrawArea);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
    };
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

    hMemDC = CreateCompatibleDC(hDC);
    bitmap = CreateCompatibleBitmap(hDC, main_draws_memCX, main_draws_memCY);

    old_hMemDC = (HDC)SelectObject(hMemDC, bitmap);

    main_draws::onDrawAtDesktop(hWnd, hMemDC, size);

    TransparentBlt(hDC, size->left,size->top,size->right,size->bottom,
                   hMemDC, 0, 0,  main_draws_memCX, main_draws_memCY,
                   RGB(255,0,255));

    ValidateRect(hWnd, size);

    SelectObject(hMemDC, old_hMemDC);
    DeleteObject(bitmap);
    DeleteDC(hMemDC);

    Sleep(1000 / 36);
};

void main_draws::onDrawAtDesktop(HWND hWnd, HDC hDC, RECT* size) {
    //draw background
    Rectangle(hDC, 0,0, main_draws_memCX, main_draws_memCY);

    RECT tDraw_test{0,0,main_draws_memCX, main_draws_memCY};
    DrawTextA(hDC, "test string1", -1, &tDraw_test, DT_TOP|DT_LEFT|DT_NOCLIP);
    DrawTextA(hDC, "test string2", -1, &tDraw_test, DT_BOTTOM|DT_RIGHT|DT_NOCLIP);
};


