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

void writeValue(gameField* field, int xCord, int yCord, int value) {
    field->lines[xCord].bitMapState = field->lines[xCord].bitMapState ^ (1 << yCord);
    field->lines[xCord].bitMapValue = field->lines[xCord].bitMapValue ^ ((value - 1) << yCord);
}

int getValueByCords(gameField* field, int xCord, int yCord) {
    int lineBitMapState, lineBitMapValue, state;

    if(xCord >= getSize(field) || yCord >= getSize(field) ||
       xCord < 0 || yCord < 0) return BORDER;

    lineBitMapState = field->lines[xCord].bitMapState;
    lineBitMapValue = field->lines[xCord].bitMapValue;

    if(lineBitMapState & (1 << yCord)) {
        return (lineBitMapValue & (1 << yCord))?ZERO:CROSS;
    }else {
        return VOID;
    }
}
int getSize(gameField* field) {
    return field->size;
}