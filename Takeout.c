#include "Takeout.h"
#include <stdio.h>
#include <string.h>

void Takeout_Init(Takeout* takeout) {
    Order_Init(&takeout->base);
    strcpy(takeout->address, "");
    strcpy(takeout->postscript, "");
    Bill_Init(&takeout->cost);
}

void Takeout_Create(Takeout* takeout, int num, const char* name, const char* phone, 
                    const char* addr, const char* ps) {
    Order_Create(&takeout->base, num, name, phone);
    strncpy(takeout->address, addr, 99);
    takeout->address[99] = '\0';
    strncpy(takeout->postscript, ps, 199);
    takeout->postscript[199] = '\0';
    Bill_Init(&takeout->cost);
}

void Takeout_SetAddress(Takeout* takeout, const char* addr) {
    strncpy(takeout->address, addr, 99);
    takeout->address[99] = '\0';
}

void Takeout_SetPostscript(Takeout* takeout, const char* ps) {
    strncpy(takeout->postscript, ps, 199);
    takeout->postscript[199] = '\0';
}

const char* Takeout_GetAddress(const Takeout* takeout) {
    return takeout->address;
}

const char* Takeout_GetPostscript(const Takeout* takeout) {
    return takeout->postscript;
}

Bill* Takeout_GetBill(Takeout* takeout) {
    return &takeout->cost;
}

const Bill* Takeout_GetBillConst(const Takeout* takeout) {
    return &takeout->cost;
}

void Takeout_Set(Takeout* takeout) {
    Order_Set(&takeout->base);
    
    printf("请输入配送地址: ");
    fgets(takeout->address, 100, stdin);
    takeout->address[strcspn(takeout->address, "\n")] = '\0';
    
    printf("请输入备注（可选）: ");
    fgets(takeout->postscript, 200, stdin);
    takeout->postscript[strcspn(takeout->postscript, "\n")] = '\0';
}

void Takeout_Get(const Takeout* takeout) {
    Order_Get(&takeout->base);
    printf("配送地址: %s\n", takeout->address);
    if (strlen(takeout->postscript) > 0) {
        printf("备注: %s\n", takeout->postscript);
    }
}

void Takeout_Display(const Takeout* takeout) {
    printf("\n========== 外卖订单 ==========\n");
    Takeout_Get(takeout);
    Bill_Display(&takeout->cost);
}