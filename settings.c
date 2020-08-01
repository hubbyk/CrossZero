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
void setFieldSize(gameSettings* settings, int fieldSize) {
    settings->fieldSize = fieldSize;
}

void setWinLineLength(gameSettings* settings, int winLineLength) {
    settings->winLineLength = winLineLength;
}
void setPlayers(gameSettings* settings, player *player1, player *player2) {
    player* oldPlayerH = settings->player1;
    settings->player1 = player1;
    free(oldPlayerH);

    player* oldPlayerB = settings->player2;
    settings->player2 = player2;
    free(oldPlayerB);
}

int getComplexity(gameSettings* settings) {
    return settings->complexity;
}
int getFieldHeight(gameSettings* settings) {
    return settings->fieldSize;
}
int getWinLineLength(gameSettings* settings) {
    return settings->winLineLength;
}
player* getPlayerHuman(gameSettings* settings) {
    return settings->player1;
}
player* getPlayerBot(gameSettings* settings) {
    return settings->player2;
}