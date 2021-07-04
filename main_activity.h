//
// Created by my_fl on 2021-06-25.
//

#ifndef MAIN_CPP_MAIN_ACTIVITY_H
#define MAIN_CPP_MAIN_ACTIVITY_H

#include "main_include.h"
#include "main_activity_type.h"

class main_activity {

    //for static
public:
    static main_activity* getInstance();
    static void resetPrimary();
public:
    static main_activity* primaryAddress;


    //for nonstatic
private:
    void init();
    bool checkSynced() const;

private:
    unsigned int stageCount;
    unsigned int stageIndex;
    mainActivityStageItem** stageList;

public:
    void sync();
    void reset();
    const mainActivityStatusCode addStage(unsigned char* name, unsigned int nameSize, CALLBACK_FUNC_HDC callback, RECT rect, int number = 0);
    const mainActivityStatusCode selectStage(unsigned char* name);

    const mainActivityStatusCode currentStage(mainActivityStageData* ref);
    const mainActivityStatusCode currentStageCallback(CALLBACK_FUNC_HDC* callback_ref);\

    const mainActivityStatusCode currentStageSetArea(int x, int y, int cx, int cy);
public:
    main_activity();
    ~main_activity() = default;
    main_activity* body;
    bool isSynced;
};



#endif //MAIN_CPP_MAIN_ACTIVITY_H
