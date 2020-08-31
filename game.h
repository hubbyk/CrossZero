//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_GAME_H
#define CROSSZERO_GAME_H

#include "mainheader.h"
#include "gameheader.h"
#include "ratetable.h"
#include "greatmind.h"

typedef struct {
    player *player1;
    player *player2;
    gameSettings *settings;
    gameField *battlefield;
}GAME;

GAME* newGame();
GAME* createNewGame(gameSettings* settings, tableLine* line);
GAME* loadSavedGame(tableLine* table);

int startGame(GAME* thisGame, tableLine* table); // начинает игру
void end(GAME* game);

void setFirstPlayer(GAME* game, player* anyPlayer);
void setSecondPlayer(GAME* game, player* anyPlayer);
void setSettings(GAME* game, gameSettings* settings);
void setBattlefield(GAME* game, gameField* field);

player* getFirstPlayer(GAME* game);
player* getSecondPlayer(GAME* game);
player* getPlayerByComplexity(int complexity);
gameSettings* getSettings(GAME* game);
gameField* getBattlefield(GAME* game);

void safeGame(GAME* thisGame); // сохраняет текущую игру


#endif //CROSSZERO_GAME_H
