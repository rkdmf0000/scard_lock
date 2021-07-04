//
// Created by my_fl on 2021-06-25.
//

#include "main_activity.h"

main_activity* main_activity::primaryAddress = nullptr;


main_activity* main_activity::getInstance() {
    if (main_activity::primaryAddress == nullptr) {
        main_activity::primaryAddress = (main_activity*) malloc( sizeof(main_activity) );
    }
    return main_activity::primaryAddress;
};

void main_activity::sync() {
    if (main_activity::primaryAddress == nullptr) {
        //std::cout << "new address allocated" << '\n';
        main_activity::primaryAddress = (main_activity*) malloc( sizeof(main_activity) );
        main_activity::primaryAddress->init();
    }
    //std::cout << "address copied!" << '\n';
    this->body = main_activity::primaryAddress;
    this->isSynced = true;
};

main_activity::main_activity() {
    this->init();
};


void main_activity::init() {
    this->isSynced      = false;
    this->body          = nullptr;

    this->stageList     = nullptr;
    this->stageCount    = 0;
    this->stageIndex    = 0;
};

void main_activity::resetPrimary() {
    if (main_activity::primaryAddress != nullptr) {
        free( main_activity::primaryAddress );
        main_activity::getInstance();
    }
};

void main_activity::reset() {
    if (!this->checkSynced()) {
        free( main_activity::primaryAddress );
        this->sync();
    }
};

const mainActivityStatusCode main_activity::addStage(unsigned char* name, unsigned int nameSize, CALLBACK_FUNC_HDC callback, RECT rect, int number) {

    if (!this->checkSynced())
        return mainActivityStatusCode::NOT_SYNCED;

    unsigned int idx(0);

    //############################
    // 값 추가 부위
    //############################
    mainActivityStageItem* va = (mainActivityStageItem*) malloc( sizeof(mainActivityStageItem) );
    va->pack.rect        = rect;
    va->pack.number      = number;
    va->pack.nameSize    = nameSize;
    va->pack.name        = name;

    std::cout << "--- NEW STAGE" << '\n';
    std::cout << "--- --- name : " << name << "(" << nameSize << ")" <<  '\n';
    std::cout << "--- --- area size : " << rect.top << "/" << rect.top << "/" << rect.bottom << "/" << rect.right << '\n';

    //############################
    //############################

    va->callback = callback;

    mainActivityStageItem** dump = (mainActivityStageItem**) malloc( sizeof(mainActivityStageItem) * this->body->stageCount + 1 );

    if (this->body->stageCount != 0) {
        for( idx=0;idx<this->body->stageCount;++idx ) {
            dump[idx] = this->body->stageList[idx];
        }
    }
    dump[this->body->stageCount] = va;

    delete[] this->body->stageList;

    this->body->stageList = dump;

    this->body->stageIndex = 0; //추가시 0으로 돌림
    ++this->body->stageCount;

    return mainActivityStatusCode::SUCCESS;
}

bool main_activity::checkSynced() const{
    if (this->isSynced || this->body != nullptr) return true;
    return false;
}


const mainActivityStatusCode main_activity::selectStage(unsigned char* name) {

    if (!this->checkSynced())
        return mainActivityStatusCode::NOT_SYNCED;

    unsigned int nameSearcherSize(0);
    while(name[nameSearcherSize])
        ++nameSearcherSize;

    ++nameSearcherSize; //null-byte

    bool isFound(false);
    unsigned int idx(0);
    for( idx=0;idx<this->body->stageCount;++idx ) {
        mainActivityStageItem* buffer = (mainActivityStageItem*)this->body->stageList[idx];
        if (buffer->pack.nameSize == nameSearcherSize) {
            bool isMatched(true);
            unsigned int iidx(0);
            for(iidx=0;iidx<buffer->pack.nameSize;++iidx) {
                if (name[iidx] != buffer->pack.name[iidx]) {
                    isMatched = false;
                    break;
                }
            }
            if (isMatched) {
                isFound = true;
                break;
            }
        }
    }

    if (isFound) {
        this->body->stageIndex = idx;
        return mainActivityStatusCode::SUCCESS;
    } else {
        return mainActivityStatusCode::NOT_FOUND;
    }

};


const mainActivityStatusCode main_activity::currentStage(mainActivityStageData* ref) {
    if (!this->checkSynced())
        return mainActivityStatusCode::NOT_SYNCED;

    ref->name = this->body->stageList[this->body->stageIndex]->pack.name;
    ref->nameSize = this->body->stageList[this->body->stageIndex]->pack.nameSize;
    ref->number = this->body->stageList[this->body->stageIndex]->pack.number;
    ref->rect = this->body->stageList[this->body->stageIndex]->pack.rect;

    return mainActivityStatusCode::SUCCESS;
}

const mainActivityStatusCode main_activity::currentStageCallback(CALLBACK_FUNC_HDC *callback_ref) {
    if (!this->checkSynced())
        return mainActivityStatusCode::NOT_SYNCED;

    *callback_ref = this->body->stageList[this->body->stageIndex]->callback;
    return mainActivityStatusCode::SUCCESS;
}

const mainActivityStatusCode main_activity::currentStageSetArea(const int x, const int y, const int cx, const int cy) {
    if (!this->checkSynced())
        return mainActivityStatusCode::NOT_SYNCED;

    this->body->stageList[this->body->stageIndex]->pack.rect.left = x;
    this->body->stageList[this->body->stageIndex]->pack.rect.right = y;
    this->body->stageList[this->body->stageIndex]->pack.rect.top = cx;
    this->body->stageList[this->body->stageIndex]->pack.rect.bottom = cy;

    return mainActivityStatusCode::SUCCESS;
};

