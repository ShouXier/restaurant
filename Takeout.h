#ifndef TAKEOUT_H
#define TAKEOUT_H

#include "Order.h"
#include "Bill.h"

typedef struct {
    Order base;              // 基类
    char address[100];       // 配送地址
    char postscript[200];    // 备注
    Bill cost;               // 账单
} Takeout;

void Takeout_Init(Takeout* takeout);
void Takeout_Create(Takeout* takeout, int num, const char* name, const char* phone, 
                    const char* addr, const char* ps);
void Takeout_SetAddress(Takeout* takeout, const char* addr);
void Takeout_SetPostscript(Takeout* takeout, const char* ps);
const char* Takeout_GetAddress(const Takeout* takeout);
const char* Takeout_GetPostscript(const Takeout* takeout);
Bill* Takeout_GetBill(Takeout* takeout);
const Bill* Takeout_GetBillConst(const Takeout* takeout);
void Takeout_Set(Takeout* takeout);
void Takeout_Get(const Takeout* takeout);
void Takeout_Display(const Takeout* takeout);

#endif