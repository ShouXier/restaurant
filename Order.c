#include "Order.h"
#include <stdio.h>
#include <string.h>

void Order_Init(Order* order) {
    order->number = 0;
    strcpy(order->name, "");
    strcpy(order->phoneNumber, "");
}

void Order_Create(Order* order, int num, const char* name, const char* phone) {
    order->number = num;
    strncpy(order->name, name, 19);
    order->name[19] = '\0';
    strncpy(order->phoneNumber, phone, 11);
    order->phoneNumber[11] = '\0';
}

void Order_SetNumber(Order* order, int num) {
    order->number = num;
}

void Order_SetName(Order* order, const char* name) {
    strncpy(order->name, name, 19);
    order->name[19] = '\0';
}

void Order_SetPhoneNumber(Order* order, const char* phone) {
    strncpy(order->phoneNumber, phone, 11);
    order->phoneNumber[11] = '\0';
}

int Order_GetNumber(const Order* order) {
    return order->number;
}

const char* Order_GetName(const Order* order) {
    return order->name;
}

const char* Order_GetPhoneNumber(const Order* order) {
    return order->phoneNumber;
}

void Order_Set(Order* order) {
    printf("请输入订单编号:  ");
    scanf("%d", &order->number);
    while(getchar() != '\n');
    
    printf("请输入顾客姓名: ");
    fgets(order->name, 20, stdin);
    order->name[strcspn(order->name, "\n")] = '\0';
    
    printf("请输入联系电话: ");
    fgets(order->phoneNumber, 12, stdin);
    order->phoneNumber[strcspn(order->phoneNumber, "\n")] = '\0';
}

void Order_Get(const Order* order) {
    printf("订单编号: %d\n", order->number);
    printf("顾客姓名:  %s\n", order->name);
    printf("联系电话: %s\n", order->phoneNumber);
}

void Order_Display(const Order* order) {
    Order_Get(order);
}