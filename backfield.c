//
// Created by hubbyk on 26.04.2020.
//

#include "backfield.h"

gameField* newGameField() {
    return (gameField*)malloc(sizeof(gameField));
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

int getValueByCords(gameField* field, int xCord, int yCord) {
    for(int i = 0; i < field->gameMap->count; i++) {
        if(field->gameMap->xCord[i] == xCord &&
           field->gameMap->yCord[i] == yCord) return field->gameMap->value[i];
    }

    return VOID;
}