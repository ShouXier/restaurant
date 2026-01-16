#include "Menu.h" 
#include <stdio.h>
#include <string.h>

void Menu_Init(Menu* menu) {
    menu->count = 0;
}

bool Menu_InsertDish(Menu* menu, const Dish* dish) {
    if (menu->count >= MAX_DISHES) {
        printf("菜单已满，无法添加更多菜品！\n");
        return false;
    }
    
    // 检查是否已存在相同编号的菜品
    for (int i = 0; i < menu->count; i++) {
        if (menu->dishes[i].id == dish->id) {
            printf("编号为 %d 的菜品已存在！\n", dish->id);
            return false;
        }
    }
    
    menu->dishes[menu->count++] = *dish;
    printf("菜品添加成功！\n");
    return true;
}

bool Menu_DeleteDish(Menu* menu, int id) {
    for (int i = 0; i < menu->count; i++) {
        if (menu->dishes[i].id == id) {
            for (int j = i; j < menu->count - 1; j++) {
                menu->dishes[j] = menu->dishes[j + 1];
            }
            menu->count--;
            printf("菜品删除成功！\n");
            return true;
        }
    }
    printf("未找到编号为 %d 的菜品！\n", id);
    return false;
}

bool Menu_ModifyDish(Menu* menu, int id, const Dish* dish) {
    for (int i = 0; i < menu->count; i++) {
        if (menu->dishes[i].id == id) {
            menu->dishes[i] = *dish;
            printf("菜品修改成功！\n");
            return true;
        }
    }
    printf("未找到编号为 %d 的菜品！\n", id);
    return false;
}

Dish* Menu_SearchDish(Menu* menu, int id) {
    for (int i = 0; i < menu->count; i++) {
        if (menu->dishes[i].id == id) {
            return &menu->dishes[i];
        }
    }
    return NULL;
}

void Menu_SearchDishByName(Menu* menu, const char* name) {
    bool found = false;
    printf("\n查询结果：\n");
    printf("----------------------------------------------------------------------\n");
    printf("%-8s%-20s%-12s%-12s%s\n", "编号", "名称", "类别", "口味", "价格");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < menu->count; i++) {
        if (strstr(menu->dishes[i]. name, name) != NULL) {
            Dish_Display(&menu->dishes[i]);
            found = true;
        }
    }
    
    if (!found) {
        printf("未找到包含 \"%s\" 的菜品！\n", name);
    }
    printf("----------------------------------------------------------------------\n");
}

void Menu_DisplayAll(const Menu* menu) {
    if (menu->count == 0) {
        printf("菜单为空！\n");
        return;
    }
    
    printf("\n当前菜单共有 %d 道菜品：\n", menu->count);
    printf("----------------------------------------------------------------------\n");
    printf("%-8s%-20s%-12s%-12s%s\n", "编号", "名称", "类别", "口味", "价格");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < menu->count; i++) {
        Dish_Display(&menu->dishes[i]);
    }
    printf("----------------------------------------------------------------------\n");
}

int Menu_GetCount(const Menu* menu) {
    return menu->count;
}

const Dish* Menu_GetDish(const Menu* menu, int index) {
    if (index >= 0 && index < menu->count) {
        return &menu->dishes[index];
    }
    return NULL;
}

void Menu_InitSampleData(Menu* menu) {
    Dish dish;
    
    Dish_Create(&dish, 1001, "宫保鸡丁", HOT_DISH, SPICY, 38.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 1002, "糖醋里脊", HOT_DISH, SWEET, 48.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 1003, "麻婆豆腐", HOT_DISH, SPICY, 28.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 2001, "拍黄瓜", COLD_DISH, COMMON, 15.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 2002, "凉拌木耳", COLD_DISH, SALTY, 18.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 3001, "北京烤鸭", SPECIAL_DISH, COMMON, 128.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 4001, "白米饭", STAPLE_FOOD, COMMON, 3.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 4002, "炒饭", STAPLE_FOOD, COMMON, 18.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 5001, "可乐", BEVERAGE, SWEET, 8.0);
    Menu_InsertDish(menu, &dish);
    
    Dish_Create(&dish, 5002, "啤酒", BEVERAGE, COMMON, 10.0);
    Menu_InsertDish(menu, &dish);
}