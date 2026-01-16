#ifndef BILL_H
#define BILL_H

#include "Dish.h"
#include <stdbool.h>

#define MAX_BILL_ITEMS 50

typedef struct {
    Dish dish;
    int quantity;
} BillItem;

typedef struct {
    BillItem items[MAX_BILL_ITEMS];
    int itemCount;
    double deliveryFee;
} Bill;

void Bill_Init(Bill* bill);
void BillItem_Init(BillItem* item);
void BillItem_Create(BillItem* item, const Dish* dish, int quantity);
double BillItem_GetSubtotal(const BillItem* item);

bool Bill_AddItem(Bill* bill, const Dish* dish, int quantity);
bool Bill_RemoveItem(Bill* bill, int dishId);
bool Bill_ModifyQuantity(Bill* bill, int dishId, int newQuantity);
void Bill_Clear(Bill* bill);
double Bill_CalculateSubtotal(const Bill* bill);
double Bill_CalculateDeliveryFee(const Bill* bill);
double Bill_CalculateTotal(const Bill* bill);
void Bill_Display(const Bill* bill);
int Bill_GetItemCount(const Bill* bill);
const BillItem* Bill_GetItem(const Bill* bill, int index);
void Bill_SetDeliveryFee(Bill* bill, double fee);

#endif