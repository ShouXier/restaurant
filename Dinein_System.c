#include "Dinein_System.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void DineinSystem_Init(DineinSystem* sys, Dinein** p, int n, Menu* m) {
    sys->totalNumber = n;
    sys->menu = m;
    sys->list = (Dinein*)malloc(sizeof(Dinein) * MAX_DINEIN_ORDERS);
    if (sys->list == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    *p = sys->list;
}

void DineinSystem_Destroy(DineinSystem* sys) {
    if (sys->list != NULL) {
        free(sys->list);
        sys->list = NULL;
    }
}

int DineinSystem_GenerateOrderNumber(void) {
    static int orderCounter = 20000;
    return ++orderCounter;
}

void DineinSystem_InsertDinein(DineinSystem* sys, Dinein* p, int* n) {
    if (*n >= MAX_DINEIN_ORDERS) {
        printf("订单系统已满！\n");
        return;
    }
    
    printf("\n========== 新建堂食订单 ==========\n");
    
    Dinein newOrder;
    Dinein_Init(&newOrder);
    Order_SetNumber(&newOrder.base, DineinSystem_GenerateOrderNumber());
    
    char name[20], phone[12], time[20];
    int table, people;
    
    while(getchar() != '\n');
    printf("请输入顾客姓名: ");
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = '\0';
    Order_SetName(&newOrder.base, name);
    
    printf("请输入联系电话: ");
    fgets(phone, 12, stdin);
    phone[strcspn(phone, "\n")] = '\0';
    Order_SetPhoneNumber(&newOrder.base, phone);
    
    printf("请输入桌号: ");
    scanf("%d", &table);
    Dinein_SetTableNumber(&newOrder, table);
    
    printf("请输入用餐人数: ");
    scanf("%d", &people);
    Dinein_SetPeopleCount(&newOrder, people);
    
    while(getchar() != '\n');
    printf("请输入预约时间（可选，直接回车跳过）:  ");
    fgets(time, 20, stdin);
    time[strcspn(time, "\n")] = '\0';
    Dinein_SetReserveTime(&newOrder, time);
    
    // 添加菜品到账单
    printf("\n开始添加菜品...\n");
    Menu_DisplayAll(sys->menu);
    
    char continueAdd = 'y';
    while (continueAdd == 'y' || continueAdd == 'Y') {
        int dishId, quantity;
        printf("\n请输入菜品编号: ");
        scanf("%d", &dishId);
        
        Dish* dish = Menu_SearchDish(sys->menu, dishId);
        if (dish == NULL) {
            printf("未找到该菜品！\n");
            while(getchar() != '\n');
            printf("是否继续添加菜品？(y/n): ");
            scanf("%c", &continueAdd);
            continue;
        }
        
        printf("请输入数量: ");
        scanf("%d", &quantity);
        
        Bill_AddItem(Dinein_GetBill(&newOrder), dish, quantity);
        
        while(getchar() != '\n');
        printf("是??继续添加菜品？(y/n): ");
        scanf("%c", &continueAdd);
    }
    
    // 堂食不需要配送费
    Bill_SetDeliveryFee(Dinein_GetBill(&newOrder), 0.0);
    
    p[*n] = newOrder;
    (*n)++;
    
    printf("\n堂食订单创建成功！订单编号: %d\n", Order_GetNumber(&newOrder. base));
    Dinein_Display(&newOrder);
}

void DineinSystem_DeleteDinein(DineinSystem* sys, Dinein* p, int* n) {
    if (*n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    int orderNum;
    printf("请输入要删除的订单编号: ");
    scanf("%d", &orderNum);
    
    for (int i = 0; i < *n; i++) {
        if (Order_GetNumber(&p[i]. base) == orderNum) {
            for (int j = i; j < *n - 1; j++) {
                p[j] = p[j + 1];
            }
            (*n)--;
            printf("订单删除成功！\n");
            return;
        }
    }
    printf("未找到该订单！\n");
}

void DineinSystem_ModifyDinein(DineinSystem* sys, Dinein* p, int n) {
    if (n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    int orderNum;
    printf("请输入要修改的订单编号: ");
    scanf("%d", &orderNum);
    
    for (int i = 0; i < n; i++) {
        if (Order_GetNumber(&p[i].base) == orderNum) {
            printf("\n当前订单信息：\n");
            Dinein_Display(&p[i]);
            
            printf("\n请选择要??改的内容：\n");
            printf("1. 顾客信息\n");
            printf("2. 桌号\n");
            printf("3. 用餐人数\n");
            printf("4. 预约时间\n");
            printf("5. 账单\n");
            printf("请选择: ");
            
            int choice;
            scanf("%d", &choice);
            while(getchar() != '\n');
            
            switch (choice) {
                case 1: {
                    char name[20], phone[12];
                    printf("请输入新的顾客姓名: ");
                    fgets(name, 20, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    Order_SetName(&p[i].base, name);
                    printf("请输入新的联系电话: ");
                    fgets(phone, 12, stdin);
                    phone[strcspn(phone, "\n")] = '\0';
                    Order_SetPhoneNumber(&p[i].base, phone);
                    break;
                }
                case 2: {
                    int table;
                    printf("请输入新的桌号: ");
                    scanf("%d", &table);
                    Dinein_SetTableNumber(&p[i], table);
                    break;
                }
                case 3: {
                    int people;
                    printf("请输入新的用餐人数: ");
                    scanf("%d", &people);
                    Dinein_SetPeopleCount(&p[i], people);
                    break;
                }
                case 4: {
                    char time[20];
                    printf("请输入新的预约时间:  ");
                    fgets(time, 20, stdin);
                    time[strcspn(time, "\n")] = '\0';
                    Dinein_SetReserveTime(&p[i], time);
                    break;
                }
                case 5: {
                    printf("\n账单修改选项：\n");
                    printf("1. 添加菜品\n");
                    printf("2. 删除菜品\n");
                    printf("3. 修改数量\n");
                    printf("请选择: ");
                    int billChoice;
                    scanf("%d", &billChoice);
                    
                    if (billChoice == 1) {
                        Menu_DisplayAll(sys->menu);
                        int dishId, quantity;
                        printf("请输入菜品编号:  ");
                        scanf("%d", &dishId);
                        Dish* dish = Menu_SearchDish(sys->menu, dishId);
                        if (dish != NULL) {
                            printf("请输入数量: ");
                            scanf("%d", &quantity);
                            Bill_AddItem(Dinein_GetBill(&p[i]), dish, quantity);
                        }
                    } else if (billChoice == 2) {
                        int dishId;
                        printf("请输入要删除的菜品编号:  ");
                        scanf("%d", &dishId);
                        Bill_RemoveItem(Dinein_GetBill(&p[i]), dishId);
                    } else if (billChoice == 3) {
                        int dishId, quantity;
                        printf("请输入菜品编号: ");
                        scanf("%d", &dishId);
                        printf("请输入新的份数: ");
                        scanf("%d", &quantity);
                        Bill_ModifyQuantity(Dinein_GetBill(&p[i]), dishId, quantity);
                    }
                    break;
                }
                default: 
                    printf("无效选项！\n");
                    return;
            }
            
            printf("订单修改成功！\n");
            Dinein_Display(&p[i]);
            return;
        }
    }
    printf("未找到该订单！\n");
}

void DineinSystem_SearchDinein(DineinSystem* sys, Dinein* p, int n) {
    if (n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    printf("\n查询方式：\n");
    printf("1. 按订单编号查询\n");
    printf("2. 按桌号查询\n");
    printf("3. 按顾客姓名查询\n");
    printf("请选择: ");
    
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');
    
    bool found = false;
    
    switch (choice) {
        case 1: {
            int orderNum;
            printf("请输入订单编号: ");
            scanf("%d", &orderNum);
            for (int i = 0; i < n; i++) {
                if (Order_GetNumber(&p[i].base) == orderNum) {
                    Dinein_Display(&p[i]);
                    found = true;
                    break;
                }
            }
            break;
        }
        case 2: {
            int table;
            printf("请输入桌号: ");
            scanf("%d", &table);
            for (int i = 0; i < n; i++) {
                if (Dinein_GetTableNumber(&p[i]) == table) {
                    Dinein_Display(&p[i]);
                    found = true;
                }
            }
            break;
        }
        case 3: {
            char name[20];
            printf("请输入顾客姓名: ");
            fgets(name, 20, stdin);
            name[strcspn(name, "\n")] = '\0';
            for (int i = 0; i < n; i++) {
                if (strstr(Order_GetName(&p[i].base), name) != NULL) {
                    Dinein_Display(&p[i]);
                    found = true;
                }
            }
            break;
        }
        default:
            printf("无效选项！\n");
            return;
    }
    
    if (!found) {
        printf("未找到匹配的订单！\n");
    }
}

void DineinSystem_DisplayAll(DineinSystem* sys, Dinein* p, int n) {
    if (n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    printf("\n========== 共有堂食订单 %d 个 ==========\n", n);
    for (int i = 0; i < n; i++) {
        Dinein_Display(&p[i]);
        printf("\n");
    }
}

void DineinSystem_Set(DineinSystem* sys, int n) {
    sys->totalNumber = n;
}

void DineinSystem_Get(DineinSystem* sys, Dinein** p, int* n) {
    *p = sys->list;
    *n = sys->totalNumber;
}