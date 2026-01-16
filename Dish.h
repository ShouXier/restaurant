#ifndef DISH_H
#define DISH_H

#include <stdbool.h>

// 菜品类别枚举
typedef enum {
    HOT_DISH = 1,      // 热菜
    COLD_DISH,         // 凉菜
    SPECIAL_DISH,      // 特色菜
    STAPLE_FOOD,       // 主食
    BEVERAGE           // 饮品
} Category;

// 口味枚举
typedef enum {
    SPICY = 1,         // 辣
    SALTY,             // 咸
    SWEET,             // 甜
    COMMON             // 不限口味
} Flavor;

typedef struct {
    int id;                    // 编号
    char name[50];             // 名称
    Category category;         // 类别
    Flavor flavor;             // 口味
    double price;              // 价格
} Dish;

// 函数声明
void Dish_Init(Dish* dish);
void Dish_Create(Dish* dish, int id, const char* name, Category cat, Flavor flv, double price);
void Dish_SetId(Dish* dish, int id);
void Dish_SetName(Dish* dish, const char* name);
void Dish_SetCategory(Dish* dish, Category cat);
void Dish_SetFlavor(Dish* dish, Flavor flv);
void Dish_SetPrice(Dish* dish, double price);

int Dish_GetId(const Dish* dish);
const char* Dish_GetName(const Dish* dish);
Category Dish_GetCategory(const Dish* dish);
Flavor Dish_GetFlavor(const Dish* dish);
double Dish_GetPrice(const Dish* dish);

const char* Dish_GetCategoryString(const Dish* dish);
const char* Dish_GetFlavorString(const Dish* dish);
void Dish_Display(const Dish* dish);
void Dish_Input(Dish* dish);

#endif