//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_BACKFIELD_H
#define CROSSZERO_BACKFIELD_H

#include "mainheader.h"

enum value {VOID, CROSS, ZERO, BORDER};

typedef struct {
    int bitMapState;
    int bitMapValue;
}fieldLine;

typedef struct{
    int size; // длина поля
    fieldLine *lines;
}gameField;

gameField* newGameField(int size); //выделяет память под новое поле

void writeValue(gameField* field, int xCord, int yCord, int value); // записывает новое значение в карту

int getValueByCords(gameField* field, int xCord, int yCord); // получаем значение по координатам
int getSize(gameField* field);

#endif //CROSSZERO_BACKFIELD_H
