//
// Created by hubbyk on 13.05.2020.
//

#include "settings.h"
#include "malloc.h"

gameSettings* loadDefaultSettings() {
    gameSettings *settings = newSettings(); //создаем новую структуру настроек

    //задаем настройки по умолчанию
    setComplexity(settings, MEDIUM);
    setWinLineLength(settings, 3);
    setFieldSize(settings, 3);

    return settings;
}

gameSettings* newSettings() {
    gameSettings *settings = (gameSettings*) malloc(sizeof(*settings));
    return settings;
}

void setComplexity(gameSettings* settings, int comp) {
    settings->complexity = comp;
}
void setFieldSize(gameSettings* settings, int fieldSize) {
    settings->fieldSize = fieldSize;
}

void setWinLineLength(gameSettings* settings, int winLineLength) {
    settings->winLineLength = winLineLength;
}

int getComplexity(gameSettings* settings) {
    return settings->complexity;
}
int getFieldSize(gameSettings* settings) {
    return settings->fieldSize;
}
int getWinLineLength(gameSettings* settings) {
    return settings->winLineLength;
}

void setFirstMove(gameSettings* settings, int choice) {
    settings->firstMove = choice;
}