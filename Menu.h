#ifndef MENU_H
#define MENU_H

#include "Dish.h"
#include <stdbool.h>

#define MAX_DISHES 100

typedef struct {
    Dish dishes[MAX_DISHES];
    int count;
} Menu;

void Menu_Init(Menu* menu);
bool Menu_InsertDish(Menu* menu, const Dish* dish);
bool Menu_DeleteDish(Menu* menu, int id);
bool Menu_ModifyDish(Menu* menu, int id, const Dish* dish);
Dish* Menu_SearchDish(Menu* menu, int id);
void Menu_SearchDishByName(Menu* menu, const char* name);
void Menu_DisplayAll(const Menu* menu);
int Menu_GetCount(const Menu* menu);
const Dish* Menu_GetDish(const Menu* menu, int index);
void Menu_InitSampleData(Menu* menu);

#endif