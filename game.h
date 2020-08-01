//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_GAME_H
#define CROSSZERO_GAME_H

#include "mainheader.h"
#include "backfield.h"
#include "settings.h"

typedef struct {
    char gameName[15];
    gameSettings *settings;
}GAME;

int startGame(GAME thisGame); // начинает игру

void safeGame(GAME thisGame); // сохраняет текущую игру


#endif //CROSSZERO_GAME_H
