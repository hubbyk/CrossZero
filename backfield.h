//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_BACKFIELD_H
#define CROSSZERO_BACKFIELD_H

#include <bits/types/FILE.h>

typedef struct {
    int *xPos; //массив с координатами крестиков
    int *oPos; //массив с координатами нулей
}fieldMap;

typedef struct{
    FILE *fieldFile; // файл, в который будет сохраняться информация о поле (для сохранения игры)
    int length; // длина поля
    int height; // высота поля
    fieldMap *gameMap; // указатель на структуру с картой поля
}gameField;

void setFieldSize(int, int, gameField*); //задает параметры поля (высоту и ширину)

int getFieldLengthA(gameField*); //гетеры для полей gameField

int getFieldHeightA(gameField*);

int** getFieldMap(gameField*);

gameField* newGameField(); //выделяет память под новое поле

#endif //CROSSZERO_BACKFIELD_H
