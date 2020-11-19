//
// Created by hubbyk on 26.04.2020.
//

#include "backfield.h"

gameField* newGameField(int size) {
    gameField *newField = (gameField*)malloc(sizeof(gameField));

    newField->size = size;
    newField->lines = (fieldLine*)calloc(size, sizeof(fieldLine));

    return newField;
}

//void setNewMap(gameField* field, int sizeOfMap) {
//    fieldMap* newMap = (fieldMap*)malloc(sizeof(fieldMap));
//    newMap->count = sizeOfMap;
//    newMap->value = (int*)calloc(sizeOfMap, sizeof(int));
//    newMap->xCord = (int*)calloc(sizeOfMap, sizeof(int));
//    newMap->yCord = (int*)calloc(sizeOfMap, sizeof(int));
//    field->gameMap = newMap;
//}

void writeValue(gameField* field, int xCord, int yCord, int value) {
//    ++field->gameMap->count;
//    //count position to insert
//
//    int *newMass = (int*)malloc(field->gameMap->count * sizeof(int));
//
//    field->gameMap->xCord = (int*)realloc(field->gameMap->xCord, field->gameMap->count * sizeof(int));
//    field->gameMap->yCord = (int*)realloc(field->gameMap->yCord, field->gameMap->count * sizeof(int));
//    field->gameMap->value = (int*)realloc(field->gameMap->value, field->gameMap->count * sizeof(int));
//
//    field->gameMap->xCord[field->gameMap->count - 1] = xCord;
//    field->gameMap->yCord[field->gameMap->count - 1] = yCord;
//    field->gameMap->value[field->gameMap->count - 1] = value;
    field->lines[xCord].bitMapState = field->lines[xCord].bitMapState ^ (1 << yCord);
    field->lines[xCord].bitMapValue = field->lines[xCord].bitMapValue ^ ((value - 1) << yCord);
}

//void addValue(gameField* field, int value, int index) {
//    field->gameMap->value[index] = value;
//}
//void addXCord(gameField* field, int xCord, int index) {
//    field->gameMap->xCord[index] = xCord;
//}
//void addYCord(gameField* field, int yCord, int index) {
//    field->gameMap->yCord[index] = yCord;
//}

int getValueByCords(gameField* field, int xCord, int yCord) {
    int lineBitMapState, lineBitMapValue, state;
//    for(int i = 0; i < field->gameMap->count; i++) {
//        if(xCord >= getSize(field) || yCord >= getSize(field) ||
//        xCord < 0 || yCord < 0) return BORDER;
//        if(field->gameMap->xCord[i] == xCord &&
//           field->gameMap->yCord[i] == yCord) return field->gameMap->value[i];
//    }
    if(xCord >= getSize(field) || yCord >= getSize(field) ||
       xCord < 0 || yCord < 0) return BORDER;

    lineBitMapState = field->lines[xCord].bitMapState;
    lineBitMapValue = field->lines[xCord].bitMapValue;

    if(lineBitMapState & (1 << yCord)) {
        return (lineBitMapValue & (1 << yCord))?CROSS:ZERO;
    }else {
        return VOID;
    }
}
int getSize(gameField* field) {
    return field->size;
}
//int getCountOfNonVoidCells(gameField* field) {
//    return field->gameMap->count;
//}
//int* getValues(gameField* field) {
//    return field->gameMap->value;
//}
//int* getXCords(gameField* field) {
//    return field->gameMap->xCord;
//}
//int* getYCords(gameField* field) {
//    return field->gameMap->yCord;
//}