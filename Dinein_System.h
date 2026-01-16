#ifndef DINEIN_SYSTEM_H
#define DINEIN_SYSTEM_H

#include "Dinein.h"
#include "Menu.h"

#define MAX_DINEIN_ORDERS 100

typedef struct {
    Dinein* list;
    int totalNumber;
    Menu* menu;
} DineinSystem;

void DineinSystem_Init(DineinSystem* sys, Dinein** p, int n, Menu* m);
void DineinSystem_Destroy(DineinSystem* sys);
void DineinSystem_InsertDinein(DineinSystem* sys, Dinein* p, int* n);
void DineinSystem_DeleteDinein(DineinSystem* sys, Dinein* p, int* n);
void DineinSystem_ModifyDinein(DineinSystem* sys, Dinein* p, int n);
void DineinSystem_SearchDinein(DineinSystem* sys, Dinein* p, int n);
void DineinSystem_DisplayAll(DineinSystem* sys, Dinein* p, int n);
void DineinSystem_Set(DineinSystem* sys, int n);
void DineinSystem_Get(DineinSystem* sys, Dinein** p, int* n);
int DineinSystem_GenerateOrderNumber(void);

#endif