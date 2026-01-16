#include "Takeout_System.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void TakeoutSystem_Init(TakeoutSystem* sys, Takeout** p, int n, Menu* m) {
    sys->totalNumber = n;
    sys->menu = m;
    sys->list = (Takeout*)malloc(sizeof(Takeout) * MAX_TAKEOUT_ORDERS);
    if (sys->list == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    *p = sys->list;
}

void TakeoutSystem_Destroy(TakeoutSystem* sys) {
    if (sys->list != NULL) {
        free(sys->list);
        sys->list = NULL;
    }
}

int TakeoutSystem_GenerateOrderNumber(void) {
    static int orderCounter = 10000;
    return ++orderCounter;
}

void TakeoutSystem_InsertTakeout(TakeoutSystem* sys, Takeout* p, int* n) {
    if (*n >= MAX_TAKEOUT_ORDERS) {
        printf("订单系统已满！\n");
        return;
    }
    
    printf("\n========== 新建外卖订单 ==========\n");
    
    Takeout newOrder;
    Takeout_Init(&newOrder);
    Order_SetNumber(&newOrder. base, TakeoutSystem_GenerateOrderNumber());
    
    char name[20], phone[12], address[100], ps[200];
    
    while(getchar() != '\n');
    printf("请输入顾客姓名: ");
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = '\0';
    Order_SetName(&newOrder.base, name);
    
    printf("请输入联系电话: ");
    fgets(phone, 12, stdin);
    phone[strcspn(phone, "\n")] = '\0';
    Order_SetPhoneNumber(&newOrder.base, phone);
    
    printf("请输入配送地址: ");
    fgets(address, 100, stdin);
    address[strcspn(address, "\n")] = '\0';
    Takeout_SetAddress(&newOrder, address);
    
    printf("请输入备注（可选，直接回车跳过）: ");
    fgets(ps, 200, stdin);
    ps[strcspn(ps, "\n")] = '\0';
    Takeout_SetPostscript(&newOrder, ps);
    
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
        
        Bill_AddItem(Takeout_GetBill(&newOrder), dish, quantity);
        
        while(getchar() != '\n');
        printf("是否继续添加菜品？(y/n): ");
        scanf("%c", &continueAdd);
    }
    
    // 计算配送费
    Bill_SetDeliveryFee(Takeout_GetBill(&newOrder), 
                        Bill_CalculateDeliveryFee(Takeout_GetBill(&newOrder)));
    
    p[*n] = newOrder;
    (*n)++;
    
    printf("\n外卖订单创建成功！订单编号: %d\n", Order_GetNumber(&newOrder.base));
    Takeout_Display(&newOrder);
}

void TakeoutSystem_DeleteTakeout(TakeoutSystem* sys, Takeout* p, int* n) {
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

void TakeoutSystem_ModifyTakeout(TakeoutSystem* sys, Takeout* p, int n) {
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
            Takeout_Display(&p[i]);
            
            printf("\n请选择要修改的内容：\n");
            printf("1. 顾客信息\n");
            printf("2. 配送地址\n");
            printf("3. 备注\n");
            printf("4. 账单\n");
            printf("请选择: ");
            
            int choice;
            scanf("%d", &choice);
            while(getchar() != '\n');
            
            switch (choice) {
                case 1:  {
                    char name[20], phone[12];
                    printf("请输入新的顾客姓名:  ");
                    fgets(name, 20, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    Order_SetName(&p[i].base, name);
                    printf("请输入新的联系电话: ");
                    fgets(phone, 12, stdin);
                    phone[strcspn(phone, "\n")] = '\0';
                    Order_SetPhoneNumber(&p[i]. base, phone);
                    break;
                }
                case 2: {
                    char address[100];
                    printf("请输入新的配送地址: ");
                    fgets(address, 100, stdin);
                    address[strcspn(address, "\n")] = '\0';
                    Takeout_SetAddress(&p[i], address);
                    break;
                }
                case 3: {
                    char ps[200];
                    printf("请输入新的备注: ");
                    fgets(ps, 200, stdin);
                    ps[strcspn(ps, "\n")] = '\0';
                    Takeout_SetPostscript(&p[i], ps);
                    break;
                }
                case 4: {
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
                        printf("请输入菜品编号: ");
                        scanf("%d", &dishId);
                        Dish* dish = Menu_SearchDish(sys->menu, dishId);
                        if (dish != NULL) {
                            printf("请输入数量: ");
                            scanf("%d", &quantity);
                            Bill_AddItem(Takeout_GetBill(&p[i]), dish, quantity);
                            Bill_SetDeliveryFee(Takeout_GetBill(&p[i]), 
                                              Bill_CalculateDeliveryFee(Takeout_GetBill(&p[i])));
                        }
                    } else if (billChoice == 2) {
                        int dishId;
                        printf("请输入要???除的菜品编号: ");
                        scanf("%d", &dishId);
                        Bill_RemoveItem(Takeout_GetBill(&p[i]), dishId);
                        Bill_SetDeliveryFee(Takeout_GetBill(&p[i]), 
                                          Bill_CalculateDeliveryFee(Takeout_GetBill(&p[i])));
                    } else if (billChoice == 3) {
                        int dishId, quantity;
                        printf("请输入菜品编号: ");
                        scanf("%d", &dishId);
                        printf("请输入新的份数: ");
                        scanf("%d", &quantity);
                        Bill_ModifyQuantity(Takeout_GetBill(&p[i]), dishId, quantity);
                        Bill_SetDeliveryFee(Takeout_GetBill(&p[i]), 
                                          Bill_CalculateDeliveryFee(Takeout_GetBill(&p[i])));
                    }
                    break;
                }
                default:
                    printf("无效选项！\n");
                    return;
            }
            
            printf("订单修改成功！\n");
            Takeout_Display(&p[i]);
            return;
        }
    }
    printf("未找到该订单！\n");
}

void TakeoutSystem_SearchTakeout(TakeoutSystem* sys, Takeout* p, int n) {
    if (n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    printf("\n查询方式：\n");
    printf("1. 按订单编号查询\n");
    printf("2. 按顾客姓名查询\n");
    printf("3. 按电话号码查询\n");
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
                    Takeout_Display(&p[i]);
                    found = true;
                    break;
                }
            }
            break;
        }
        case 2: {
            char name[20];
            printf("请输入顾客姓名: ");
            fgets(name, 20, stdin);
            name[strcspn(name, "\n")] = '\0';
            for (int i = 0; i < n; i++) {
                if (strstr(Order_GetName(&p[i]. base), name) != NULL) {
                    Takeout_Display(&p[i]);
                    found = true;
                }
            }
            break;
        }
        case 3: {
            char phone[12];
            printf("请输入电话号码: ");
            fgets(phone, 12, stdin);
            phone[strcspn(phone, "\n")] = '\0';
            for (int i = 0; i < n; i++) {
                if (strcmp(Order_GetPhoneNumber(&p[i].base), phone) == 0) {
                    Takeout_Display(&p[i]);
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

void TakeoutSystem_DisplayAll(TakeoutSystem* sys, Takeout* p, int n) {
    if (n == 0) {
        printf("没有任何订单！\n");
        return;
    }
    
    printf("\n========== 共有外卖订单 %d 个 ==========\n", n);
    for (int i = 0; i < n; i++) {
        Takeout_Display(&p[i]);
        printf("\n");
    }
}

void TakeoutSystem_Set(TakeoutSystem* sys, int n) {
    sys->totalNumber = n;
}

void TakeoutSystem_Get(TakeoutSystem* sys, Takeout** p, int* n) {
    *p = sys->list;
    *n = sys->totalNumber;
}