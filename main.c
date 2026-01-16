#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Takeout_System.h"
#include "Dinein_System.h"
#include "Utils.h"

// 全局菜单对象
Menu globalMenu;

// 菜单管理系统函数
void menuManagement(void) {
    while (1) {
        clearScreen();
        printHeader("菜单管理系统");
        
        printf("\n1. 添加菜品\n");
        printf("2. 删除菜品\n");
        printf("3. 修改菜品\n");
        printf("4. 查询菜品\n");
        printf("5. 显示所有菜品\n");
        printf("0. 返回上级菜单\n");
        printf("\n请选择功能: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                Dish newDish;
                Dish_Init(&newDish);
                Dish_Input(&newDish);
                Menu_InsertDish(&globalMenu, &newDish);
                pauseScreen();
                break;
            }
            case 2: {
                int id;
                printf("请输入要删除的菜品编号: ");
                scanf("%d", &id);
                Menu_DeleteDish(&globalMenu, id);
                pauseScreen();
                break;
            }
            case 3: {
                int id;
                printf("请输入要修改的菜品编号: ");
                scanf("%d", &id);
                Dish* dish = Menu_SearchDish(&globalMenu, id);
                if (dish != NULL) {
                    printf("\n当前菜品信息：\n");
                    Dish_Display(dish);
                    printf("\n请输入新的菜品信息：\n");
                    Dish newDish;
                    Dish_Init(&newDish);
                    Dish_Input(&newDish);
                    Menu_ModifyDish(&globalMenu, id, &newDish);
                } else {
                    printf("未找到该菜品！\n");
                }
                pauseScreen();
                break;
            }
            case 4: {
                printf("\n查询方式：\n");
                printf("1. 按编号查询\n");
                printf("2. 按名称查询\n");
                printf("请选择: ");
                int searchChoice;
                scanf("%d", &searchChoice);
                
                if (searchChoice == 1) {
                    int id;
                    printf("请输入菜品编号: ");
                    scanf("%d", &id);
                    Dish* dish = Menu_SearchDish(&globalMenu, id);
                    if (dish != NULL) {
                        printf("\n查询结果：\n");
                        Dish_Display(dish);
                    } else {
                        printf("未找到该菜品！\n");
                    }
                } else if (searchChoice == 2) {
                    char name[50];
                    while(getchar() != '\n');
                    printf("请输入菜品名称: ");
                    fgets(name, 50, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    Menu_SearchDishByName(&globalMenu, name);
                }
                pauseScreen();
                break;
            }
            case 5:
                Menu_DisplayAll(&globalMenu);
                pauseScreen();
                break;
            case 0:
                return;
            default:
                printf("无效选项！\n");
                pauseScreen();
        }
    }
}

// 外卖订单管理系统函数
void takeoutManagement(void) {
    Takeout* p = NULL;
    TakeoutSystem mysys;
    TakeoutSystem_Init(&mysys, &p, 0, &globalMenu);
    int number = 0;
    
    while (1) {
        clearScreen();
        printHeader("外卖订单管理系统");
        
        printf("\n1. 新建外卖订单\n");
        printf("2. 删除外卖订单\n");
        printf("3. 修改外卖订单\n");
        printf("4. 查询外卖订单\n");
        printf("5. 显示所有外卖订单\n");
        printf("0. 返回上级菜单\n");
        printf("\n请选择功能: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                TakeoutSystem_InsertTakeout(&mysys, p, &number);
                pauseScreen();
                break;
            case 2:
                TakeoutSystem_DeleteTakeout(&mysys, p, &number);
                pauseScreen();
                break;
            case 3:
                TakeoutSystem_ModifyTakeout(&mysys, p, number);
                pauseScreen();
                break;
            case 4:
                TakeoutSystem_SearchTakeout(&mysys, p, number);
                pauseScreen();
                break;
            case 5:
                TakeoutSystem_DisplayAll(&mysys, p, number);
                pauseScreen();
                break;
            case 0:
                TakeoutSystem_Destroy(&mysys);
                return;
            default: 
                printf("无效选项！\n");
                pauseScreen();
        }
    }
}

// 堂食订单管理系统函数
void dineinManagement(void) {
    Dinein* p = NULL;
    DineinSystem mysys;
    DineinSystem_Init(&mysys, &p, 0, &globalMenu);
    int number = 0;
    
    while (1) {
        clearScreen();
        printHeader("堂食订单管理系统");
        
        printf("\n1. 新建堂食订单\n");
        printf("2. 删除堂食订单\n");
        printf("3. 修改堂食订单\n");
        printf("4. 查询堂食订单\n");
        printf("5. 显示所有堂食订单\n");
        printf("0. 返回上级菜单\n");
        printf("\n请选择功能: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                DineinSystem_InsertDinein(&mysys, p, &number);
                pauseScreen();
                break;
            case 2:
                DineinSystem_DeleteDinein(&mysys, p, &number);
                pauseScreen();
                break;
            case 3:
                DineinSystem_ModifyDinein(&mysys, p, number);
                pauseScreen();
                break;
            case 4:
                DineinSystem_SearchDinein(&mysys, p, number);
                pauseScreen();
                break;
            case 5:
                DineinSystem_DisplayAll(&mysys, p, number);
                pauseScreen();
                break;
            case 0:
                DineinSystem_Destroy(&mysys);
                return;
            default:
                printf("无效选项！\n");
                pauseScreen();
        }
    }
}

// 主菜单函数
void mainMenu(void) {
    while (1) {
        clearScreen();
        
        printf("\n");
        printf("============================================================\n");
        printf("                                                            \n");
        printf("                  餐馆订餐管理系统                          \n");
        printf("                                                            \n");
        printf("                Restaurant Management System               \n");
        printf("                                                            \n");
        printf("============================================================\n");
        
        printf("\n============================================================\n");
        printf("  1. 菜单管理系统 (Menu Management)                        \n");
        printf("  2. 外卖订单管理系统 (Takeout Order Management)           \n");
        printf("  3. 堂食订单管理系统 (Dine-in Order Management)           \n");
        printf("  0. 退出系统 (Exit)                                        \n");
        printf("============================================================\n");
        
        printf("\n请选择模块 (Please select): ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                menuManagement();
                break;
            case 2:
                takeoutManagement();
                break;
            case 3:
                dineinManagement();
                break;
            case 0:
                printf("\n谢谢使用餐馆订餐管理系统，再见！\n");
                return;
            default:
                printf("\n无效选项，请重新输入。\n");
                pauseScreen();
        }
    }
}

int main(void) {
    // 初始化示例菜单数据
    printf("正在初始化系统...\n");
    Menu_Init(&globalMenu);
    Menu_InitSampleData(&globalMenu);
    printf("系统初始化完成！\n");
    
    // 进入主菜单
    mainMenu();
    
    return 0;
}