//
// Created by hubbyk on 13.05.2020.
//

#include "settings.h"
#include <stdio.h>
#include "malloc.h"

gameSettings* loadDefaultSettings() {
    gameSettings *settings = newSettings(); //создаем новую структуру настроек

    //задаем настройки по умолчанию
    setComplexity(settings, MEDIUM);
    setCountToWin(settings, 3);
    setFieldHeight(settings, 3);
    setFieldLength(settings, 3);
    setPlayers(settings, newPlayer("Player1", 0), newPlayer("Pokug", 0));

    return settings;
}

gameSettings* newSettings() {
    gameSettings *settings = (gameSettings*) malloc(sizeof(*settings));
    return settings;
}


void setComplexity(gameSettings* settings, int comp) {
    settings->complexity = comp;
}
void setFieldHeight(gameSettings* settings, int fieldHeight) {
    settings->fieldHeight = fieldHeight;
}
void setFieldLength(gameSettings* settings, int fieldLength) {
    settings->fieldLength = fieldLength;
}
void setCountToWin(gameSettings* settings, int countToWin) {
    settings->countToWin = countToWin;
}
void setPlayers(gameSettings* settings, player *human, player *bot) {
    settings->human = human;
    settings->bot = bot;
}

int getComplexity(gameSettings* settings) {
    return settings->complexity;
}
int getFieldHeight(gameSettings* settings) {
    return settings->fieldHeight;
}
int getFieldLength(gameSettings* settings) {
    return settings->fieldLength;
}
int getCountToWin(gameSettings* settings) {
    return settings->countToWin;
}
player* getPlayerHuman(gameSettings* settings) {
    return settings->human;
}
player* getPlayerBot(gameSettings* settings) {
    return settings->bot;
}