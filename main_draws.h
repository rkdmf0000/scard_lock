//
// Created by my_fl on 2021-06-08.
//

#ifndef MAIN_CPP_MAIN_DRAWS_H
#define MAIN_CPP_MAIN_DRAWS_H

#include "main_include.h"
#include "main_scard_fn.h"


#ifndef MAIN_CPP_MAIN_DRAWS_CLASSNAME
#define MAIN_CPP_MAIN_DRAWS_CLASSNAME "scard_lock_application"
#endif

#ifndef MAIN_CPP_MAIN_DRAWS_EVENT
#define MAIN_CPP_MAIN_DRAWS_EVENT
#define main_draws_timeRefreshEvent 1
#define main_draws_cardCheckRepeater 2
#endif

#ifndef MAIN_CPP_MAIN_DRAWS_SETS
#define MAIN_CPP_MAIN_DRAWS_SETS
#define main_draws_memCX 300
#define main_draws_memCY 150

#define main_draws_positionLeft 50
#define main_draws_positionTop 50
#define main_draws_positionRight 300
#define main_draws_positionBottom 150
#endif


class main_draws {


public:
    static LRESULT CALLBACK _wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


    static void eventOnPaint(HWND hWnd);
    static void onDraw(HWND hWnd, PAINTSTRUCT* ps);

    static void eventOnPaintAtDesktop(HWND hWnd, HDC hDC, RECT* size);
    static void onDrawAtDesktop(HWND hWnd, HDC hDC, RECT* size);

    static ATOM initRegister(HINSTANCE& handle, WNDCLASSA& strcut);
    static void errChkOfClassRegisterInit(const ATOM result);


};

#endif //MAIN_CPP_MAIN_DRAWS_H
