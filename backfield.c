//
// Created by hubbyk on 26.04.2020.
//

#include "backfield.h"

gameField* newGameField() {
    return (gameField*)malloc(sizeof(gameField));
}

void setNewMap(gameField* field, int sizeOfMap) {
    fieldMap* newMap = (fieldMap*)malloc(sizeof(fieldMap));
    newMap->count = sizeOfMap;
    newMap->value = (int*)calloc(sizeOfMap, sizeof(int));
    newMap->xCord = (int*)calloc(sizeOfMap, sizeof(int));
    newMap->yCord = (int*)calloc(sizeOfMap, sizeof(int));
    field->gameMap = newMap;
}

void writeValue(gameField* field, int xCord, int yCord, int value) {
    ++field->gameMap->count;

    field->gameMap->xCord = (int*)realloc(field->gameMap->xCord, field->gameMap->count * sizeof(int));
    field->gameMap->yCord = (int*)realloc(field->gameMap->yCord, field->gameMap->count * sizeof(int));
    field->gameMap->value = (int*)realloc(field->gameMap->value, field->gameMap->count * sizeof(int));

    field->gameMap->xCord[field->gameMap->count - 1] = xCord;
    field->gameMap->yCord[field->gameMap->count - 1] = yCord;
    field->gameMap->value[field->gameMap->count - 1] = value;
}

void addValue(gameField* field, int value, int index) {
    field->gameMap->value[index] = value;
}
void addXCord(gameField* field, int xCord, int index) {
    field->gameMap->xCord[index] = xCord;
}
void addYCord(gameField* field, int yCord, int index) {
    field->gameMap->yCord[index] = yCord;
}

int getValueByCords(gameField* field, int xCord, int yCord) {
    for(int i = 0; i < field->gameMap->count; i++) {
        if(xCord >= getSize(field) || yCord >= getSize(field) ||
        xCord < 0 || yCord < 0) return BORDER;
        if(field->gameMap->xCord[i] == xCord &&
           field->gameMap->yCord[i] == yCord) return field->gameMap->value[i];
    }

    return VOID;
}
int getSize(gameField* field) {
    return field->size;
}
int getCountOfNonVoidCells(gameField* field) {
    return field->gameMap->count;
}
int* getValues(gameField* field) {
    return field->gameMap->value;
}
int* getXCords(gameField* field) {
    return field->gameMap->xCord;
}
int* getYCords(gameField* field) {
    return field->gameMap->yCord;
}