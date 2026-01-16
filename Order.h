#ifndef ORDER_H
#define ORDER_H

typedef struct {
    int number;
    char name[20];
    char phoneNumber[12];
} Order;

void Order_Init(Order* order);
void Order_Create(Order* order, int num, const char* name, const char* phone);
void Order_SetNumber(Order* order, int num);
void Order_SetName(Order* order, const char* name);
void Order_SetPhoneNumber(Order* order, const char* phone);
int Order_GetNumber(const Order* order);
const char* Order_GetName(const Order* order);
const char* Order_GetPhoneNumber(const Order* order);
void Order_Set(Order* order);
void Order_Get(const Order* order);
void Order_Display(const Order* order);

#endif