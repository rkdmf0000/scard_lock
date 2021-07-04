//
// Created by my_fl on 2021-06-26.
//

#ifndef MAIN_CPP_MAIN_ACTIVITY_TYPE_H
#define MAIN_CPP_MAIN_ACTIVITY_TYPE_H

#include "main_include.h"

typedef void(*CALLBACK_FUNC)(void);
typedef void(*CALLBACK_FUNC_HDC)(HDC, RECT);

enum class mainActivityStatusCode {
    SUCCESS,
    INTERNAL_ERROR,
    NOT_SYNCED,
    NOT_FOUND,
    NULL_ACCESS
};

struct mainActivityStageData {
    RECT rect{};
    int number;
    unsigned int nameSize;
    unsigned char* name;
};

struct mainActivityStageItem {
    mainActivityStageItem(void) {
        std::cout << "constructor0" << '\n';
    };
    mainActivityStageItem(const mainActivityStageItem* ref) {
        std::cout << "constructor1" << '\n';
    };
    mainActivityStageItem(const mainActivityStageItem& ref) {
        std::cout << "constructor2" << '\n';
    };
    mainActivityStageItem(const mainActivityStageItem&& ref) {
        std::cout << "constructor3" << '\n';
    };

    mainActivityStageData pack;
    CALLBACK_FUNC_HDC callback;
};

#endif //MAIN_CPP_MAIN_ACTIVITY_TYPE_H
