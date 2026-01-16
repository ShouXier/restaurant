#include "Bill.h"
#include <stdio.h>
#include <string.h>

void Bill_Init(Bill* bill) {
    bill->itemCount = 0;
    bill->deliveryFee = 0.0;
}

void BillItem_Init(BillItem* item) {
    Dish_Init(&item->dish);
    item->quantity = 0;
}

void BillItem_Create(BillItem* item, const Dish* dish, int quantity) {
    item->dish = *dish;
    item->quantity = quantity;
}

double BillItem_GetSubtotal(const BillItem* item) {
    return Dish_GetPrice(&item->dish) * item->quantity;
}

bool Bill_AddItem(Bill* bill, const Dish* dish, int quantity) {
    if (quantity <= 0) {
        printf("数量必须大于0！\n");
        return false;
    }
    
    // 检查是否已存在该菜品
    for (int i = 0; i < bill->itemCount; i++) {
        if (bill->items[i].dish.id == dish->id) {
            bill->items[i].quantity += quantity;
            printf("已将 %s 的数量增加 %d\n", dish->name, quantity);
            return true;
        }
    }
    
    // 添加新菜品
    if (bill->itemCount >= MAX_BILL_ITEMS) {
        printf("账单已满，无法添加更多菜品！\n");
        return false;
    }
    
    BillItem_Create(&bill->items[bill->itemCount++], dish, quantity);
    printf("已添加 %s × %d\n", dish->name, quantity);
    return true;
}

bool Bill_RemoveItem(Bill* bill, int dishId) {
    for (int i = 0; i < bill->itemCount; i++) {
        if (bill->items[i].dish. id == dishId) {
            for (int j = i; j < bill->itemCount - 1; j++) {
                bill->items[j] = bill->items[j + 1];
            }
            bill->itemCount--;
            printf("已删除该菜品！\n");
            return true;
        }
    }
    printf("未找到该菜品！\n");
    return false;
}

bool Bill_ModifyQuantity(Bill* bill, int dishId, int newQuantity) {
    if (newQuantity <= 0) {
        printf("数量必须大于0！\n");
        return false;
    }
    
    for (int i = 0; i < bill->itemCount; i++) {
        if (bill->items[i].dish.id == dishId) {
            bill->items[i].quantity = newQuantity;
            printf("数量已修改为 %d\n", newQuantity);
            return true;
        }
    }
    printf("未找到该菜品！\n");
    return false;
}

void Bill_Clear(Bill* bill) {
    bill->itemCount = 0;
    bill->deliveryFee = 0.0;
}

double Bill_CalculateSubtotal(const Bill* bill) {
    double subtotal = 0.0;
    for (int i = 0; i < bill->itemCount; i++) {
        subtotal += BillItem_GetSubtotal(&bill->items[i]);
    }
    return subtotal;
}

double Bill_CalculateDeliveryFee(const Bill* bill) {
    return Bill_CalculateSubtotal(bill) * 0.1;
}

double Bill_CalculateTotal(const Bill* bill) {
    return Bill_CalculateSubtotal(bill) + bill->deliveryFee;
}

void Bill_Display(const Bill* bill) {
    if (bill->itemCount == 0) {
        printf("账单为空！\n");
        return;
    }
    
    printf("\n========== 账单详情 ==========\n");
    printf("%-8s%-20s%-8s%-8s%s\n", "编号", "名称", "单价", "数量", "小计");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < bill->itemCount; i++) {
        printf("%-8d%-20s?%-7.2f%-8d?%. 2f\n",
               bill->items[i]. dish.id,
               bill->items[i].dish.name,
               bill->items[i].dish.price,
               bill->items[i].quantity,
               BillItem_GetSubtotal(&bill->items[i]));
    }
    
    printf("------------------------------------------------------------\n");
    printf("%45s?%.2f\n", "菜品总计:  ", Bill_CalculateSubtotal(bill));
    printf("%45s?%.2f\n", "配送费: ", bill->deliveryFee);
    printf("%45s?%.2f\n", "总计:  ", Bill_CalculateTotal(bill));
    printf("==============================\n");
}

int Bill_GetItemCount(const Bill* bill) {
    return bill->itemCount;
}

const BillItem* Bill_GetItem(const Bill* bill, int index) {
    if (index >= 0 && index < bill->itemCount) {
        return &bill->items[index];
    }
    return NULL;
}

void Bill_SetDeliveryFee(Bill* bill, double fee) {
    bill->deliveryFee = fee;
}