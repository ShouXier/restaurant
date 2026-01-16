#include "Dinein.h"
#include <stdio.h>
#include <string.h>

void Dinein_Init(Dinein* dinein) {
    Order_Init(&dinein->base);
    dinein->tableNumber = 0;
    dinein->peopleCount = 0;
    strcpy(dinein->reserveTime, "");
    Bill_Init(&dinein->cost);
}

void Dinein_Create(Dinein* dinein, int num, const char* name, const char* phone, 
                   int table, int people, const char* time) {
    Order_Create(&dinein->base, num, name, phone);
    dinein->tableNumber = table;
    dinein->peopleCount = people;
    strncpy(dinein->reserveTime, time, 19);
    dinein->reserveTime[19] = '\0';
    Bill_Init(&dinein->cost);
}

void Dinein_SetTableNumber(Dinein* dinein, int table) {
    dinein->tableNumber = table;
}

void Dinein_SetPeopleCount(Dinein* dinein, int people) {
    dinein->peopleCount = people;
}

void Dinein_SetReserveTime(Dinein* dinein, const char* time) {
    strncpy(dinein->reserveTime, time, 19);
    dinein->reserveTime[19] = '\0';
}

int Dinein_GetTableNumber(const Dinein* dinein) {
    return dinein->tableNumber;
}

int Dinein_GetPeopleCount(const Dinein* dinein) {
    return dinein->peopleCount;
}

const char* Dinein_GetReserveTime(const Dinein* dinein) {
    return dinein->reserveTime;
}

Bill* Dinein_GetBill(Dinein* dinein) {
    return &dinein->cost;
}

const Bill* Dinein_GetBillConst(const Dinein* dinein) {
    return &dinein->cost;
}

void Dinein_Set(Dinein* dinein) {
    Order_Set(&dinein->base);
    
    printf("请输入桌号: ");
    scanf("%d", &dinein->tableNumber);
    
    printf("请输入用餐人数: ");
    scanf("%d", &dinein->peopleCount);
    
    while(getchar() != '\n');
    printf("请输入预约时间（可选）: ");
    fgets(dinein->reserveTime, 20, stdin);
    dinein->reserveTime[strcspn(dinein->reserveTime, "\n")] = '\0';
}

void Dinein_Get(const Dinein* dinein) {
    Order_Get(&dinein->base);
    printf("桌号: %d\n", dinein->tableNumber);
    printf("用餐人数: %d\n", dinein->peopleCount);
    if (strlen(dinein->reserveTime) > 0) {
        printf("预约时间:  %s\n", dinein->reserveTime);
    }
}

void Dinein_Display(const Dinein* dinein) {
    printf("\n========== 堂食订单 ==========\n");
    Dinein_Get(dinein);
    Bill_Display(&dinein->cost);
}