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
void setFirstMove(gameSettings* settings, int choice) {
    settings->firstMove = choice;
}
void setWinLineLength(gameSettings* settings, int winLineLength) {
    settings->winLineLength = winLineLength;
}
void setPlayerName(gameSettings* settings, char* buf) {
    char* cursor = buf + 17;
    for(int i = 0; *cursor; i++, cursor++) {
        settings->playerName[i] = *cursor;
    }
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

