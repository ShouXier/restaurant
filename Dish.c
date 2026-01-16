#include "Dish.h"
#include <stdio.h>
#include <string.h>

void Dish_Init(Dish* dish) {
    dish->id = 0;
    strcpy(dish->name, "");
    dish->category = HOT_DISH;
    dish->flavor = COMMON;
    dish->price = 0.0;
}

void Dish_Create(Dish* dish, int id, const char* name, Category cat, Flavor flv, double price) {
    dish->id = id;
    strncpy(dish->name, name, 49);
    dish->name[49] = '\0';
    dish->category = cat;
    dish->flavor = flv;
    dish->price = price;
}

void Dish_SetId(Dish* dish, int id) {
    dish->id = id;
}

void Dish_SetName(Dish* dish, const char* name) {
    strncpy(dish->name, name, 49);
    dish->name[49] = '\0';
}

void Dish_SetCategory(Dish* dish, Category cat) {
    dish->category = cat;
}

void Dish_SetFlavor(Dish* dish, Flavor flv) {
    dish->flavor = flv;
}

void Dish_SetPrice(Dish* dish, double price) {
    dish->price = price;
}

int Dish_GetId(const Dish* dish) {
    return dish->id;
}

const char* Dish_GetName(const Dish* dish) {
    return dish->name;
}

Category Dish_GetCategory(const Dish* dish) {
    return dish->category;
}

Flavor Dish_GetFlavor(const Dish* dish) {
    return dish->flavor;
}

double Dish_GetPrice(const Dish* dish) {
    return dish->price;
}

const char* Dish_GetCategoryString(const Dish* dish) {
    switch (dish->category) {
        case HOT_DISH:  return "热菜";
        case COLD_DISH: return "凉菜";
        case SPECIAL_DISH: return "特色菜";
        case STAPLE_FOOD:  return "主食";
        case BEVERAGE: return "饮品";
        default: return "未知";
    }
}

const char* Dish_GetFlavorString(const Dish* dish) {
    switch (dish->flavor) {
        case SPICY:  return "辣";
        case SALTY: return "咸";
        case SWEET:   return "甜";
        case COMMON: return "不限口味";
        default: return "未知";
    }
}

void Dish_Display(const Dish* dish) {
    printf("%-8d%-20s%-12s%-12s?%. 2f\n", 
           dish->id, 
           dish->name, 
           Dish_GetCategoryString(dish), 
           Dish_GetFlavorString(dish), 
           dish->price);
}

void Dish_Input(Dish* dish) {
    printf("请输入菜品编号:  ");
    scanf("%d", &dish->id);
    
    while(getchar() != '\n');
    
    printf("请输入菜品名称: ");
    fgets(dish->name, 50, stdin);
    dish->name[strcspn(dish->name, "\n")] = '\0';
    
    printf("请选择类别 (1-热菜 2-凉菜 3-特色菜 4-主食 5-饮品): ");
    int cat;
    scanf("%d", &cat);
    dish->category = (Category)cat;
    
    printf("请选择口味 (1-辣 2-咸 3-甜 4-不限口味): ");
    int flv;
    scanf("%d", &flv);
    dish->flavor = (Flavor)flv;
    
    printf("请输入价格: ");
    scanf("%lf", &dish->price);
    while(getchar() != '\n');
}