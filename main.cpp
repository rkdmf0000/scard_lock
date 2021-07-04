#include "main.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nShowCmd) {

    AllocConsole();
    freopen("CONOUT$", "w", stdout);


    WNDCLASS scardLockWNDClass;
    main_draws::errChkOfClassRegisterInit( main_draws::initRegister(hInstance, scardLockWNDClass) );


    HWND scardClockWindowHandle;
    scardClockWindowHandle = CreateWindowExA(0, MAIN_CPP_MAIN_DRAWS_CLASSNAME, "hello", 0, 0, 0, 250, 250, nullptr, nullptr, hInstance, 0);


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
