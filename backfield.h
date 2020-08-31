//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_BACKFIELD_H
#define CROSSZERO_BACKFIELD_H

#include "mainheader.h"

enum value {VOID, CROSS, ZERO, BORDER};

typedef struct {
    int count;  // размеры массивов
    int *xCord; // массив с координатами крестиков
    int *yCord; // массив с координатами нулей
    int *value; // значение клетки
}fieldMap;

typedef struct{
    int size; // длина поля
    fieldMap *gameMap; // указатель на структуру с картой поля
}gameField;

gameField* newGameField(); //выделяет память под новое поле

void setNewMap(gameField* field, int sizeOfMap);

void writeValue(gameField* field, int xCord, int yCord, int value); // записывает новое значение в карту

void addValue(gameField* field, int value, int index);
void addXCord(gameField* field, int xCord, int index);
void addYCord(gameField* field, int yCord, int index);

int getValueByCords(gameField* field, int xCord, int yCord); // получаем значение по координатам
int getSize(gameField* field);
int getCountOfNonVoidCells(gameField* field);
int* getValues(gameField* field);
int* getXCords(gameField* field);
int* getYCords(gameField* field);

#endif //CROSSZERO_BACKFIELD_H
