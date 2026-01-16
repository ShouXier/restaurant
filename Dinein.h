#ifndef DINEIN_H
#define DINEIN_H

#include "Order.h"
#include "Bill.h"

typedef struct {
    Order base;              // 基类
    int tableNumber;         // 桌号
    int peopleCount;         // 用餐人数
    char reserveTime[20];    // 预约时间
    Bill cost;               // 账单
} Dinein;

void Dinein_Init(Dinein* dinein);
void Dinein_Create(Dinein* dinein, int num, const char* name, const char* phone, 
                   int table, int people, const char* time);
void Dinein_SetTableNumber(Dinein* dinein, int table);
void Dinein_SetPeopleCount(Dinein* dinein, int people);
void Dinein_SetReserveTime(Dinein* dinein, const char* time);
int Dinein_GetTableNumber(const Dinein* dinein);
int Dinein_GetPeopleCount(const Dinein* dinein);
const char* Dinein_GetReserveTime(const Dinein* dinein);
Bill* Dinein_GetBill(Dinein* dinein);
const Bill* Dinein_GetBillConst(const Dinein* dinein);
void Dinein_Set(Dinein* dinein);
void Dinein_Get(const Dinein* dinein);
void Dinein_Display(const Dinein* dinein);

#endif