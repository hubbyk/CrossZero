//
// Created by hubbyk on 26.04.2020.
//

#ifndef CROSSZERO_GAME_H
#define CROSSZERO_GAME_H

#include "backfield.h"
#include "player.h"

typedef struct { //TODO необходимо добавить уровень сложности
    int fieldHeight; //параметры поля
    int fieldLength;
    int countToWin; //сколько нужно для выигрыша
    player *human; //игроки
    player *bot;
}gameSettings;

gameSettings* load(int argc, char * argv[]); //TODO ищет сохраненные игры, задает настройки по умолчанию

int startGame(gameSettings*); /*
 * загружает игру, загружает поле
 * создает игроков
 * загружает интерфейс игры
 */

void safeGame(); //TODO сохраняет игру

gameSettings* newSettings(); //создает новую структуру настроек

void printSettings(gameSettings*); //выводят настройки, в консоль

void changeCurrentGlobalSettings(gameSettings*); //редактирование глобальных настроек

//сетеры для полей структуры gameField, скучаю по Java(((
void setFieldHeight(gameSettings*, int);

void setFieldLength(gameSettings*, int);

void setCountToWin(gameSettings*, int);

void setPlayers(gameSettings*, player *human, player *bot);//TODO освобождает память из-под старых
//сетеры для полей структуры gameField, скучаю по Java(((
int getFieldHeight(gameSettings*);

int getFieldLength(gameSettings*);

int getCountToWin(gameSettings*);

player* getPlayerHuman(gameSettings*);

player* getPlayerBot(gameSettings*);
#endif //CROSSZERO_GAME_H
