//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_BACKFIELD_H
#define CROSSZERO_BACKFIELD_H

#include "mainheader.h"

enum value {VOID, CROSS, ZERO};

typedef struct {
    int count;  // размеры массивов
    int *xCord; // массив с координатами крестиков
    int *yCord; // массив с координатами нулей
    int *value; // значение клетки
}fieldMap;

typedef struct{
    int length; // длина поля
    int height; // высота поля
    fieldMap *gameMap; // указатель на структуру с картой поля
}gameField;

gameField* newGameField(); //выделяет память под новое поле

void writeValue(gameField* field, int xCord, int yCord, int value); // записывает новое значение в карту

int getValueByCords(gameField* field, int xCord, int yCord); // получаем значение по координатам

#endif //CROSSZERO_BACKFIELD_H
