#ifndef TAKEOUT_SYSTEM_H
#define TAKEOUT_SYSTEM_H

#include "Takeout.h"
#include "Menu.h"

#define MAX_TAKEOUT_ORDERS 100

typedef struct {
    Takeout* list;
    int totalNumber;
    Menu* menu;
} TakeoutSystem;

void TakeoutSystem_Init(TakeoutSystem* sys, Takeout** p, int n, Menu* m);
void TakeoutSystem_Destroy(TakeoutSystem* sys);
void TakeoutSystem_InsertTakeout(TakeoutSystem* sys, Takeout* p, int* n);
void TakeoutSystem_DeleteTakeout(TakeoutSystem* sys, Takeout* p, int* n);
void TakeoutSystem_ModifyTakeout(TakeoutSystem* sys, Takeout* p, int n);
void TakeoutSystem_SearchTakeout(TakeoutSystem* sys, Takeout* p, int n);
void TakeoutSystem_DisplayAll(TakeoutSystem* sys, Takeout* p, int n);
void TakeoutSystem_Set(TakeoutSystem* sys, int n);
void TakeoutSystem_Get(TakeoutSystem* sys, Takeout** p, int* n);
int TakeoutSystem_GenerateOrderNumber(void);

#endif