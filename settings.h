//
// Created by hubbyk on 13.05.2020.
//

#ifndef CROSSZERO_SETTINGS_H
#define CROSSZERO_SETTINGS_H

#include "player.h"
enum complexity {EASY, MEDIUM, HARD, DARKSOULS};
/*
 * НАСТРОЙКИ ПО УМОЛЧАНИЮ
 * сложность: средняя
 * размеры поля: 3х3
 * игроки: player vs Pokug
 */
typedef struct {
    int complexity;  //уровень сложности
    int fieldHeight; //параметры поля
    int fieldLength;
    int countToWin;  //длина выигрышной цепочки
    player *human;   //игроки
    player *bot;
}gameSettings;
/*
 * Получение структуры gameSettings
 */
gameSettings* loadDefaultSettings();
gameSettings* loadGameSettings(char* gameName);//загружает настройки сохраненной игры TODO
gameSettings* newSettings(); //создает новую структуру настроек, задает значения полей структуры по умолчанию
/*
 * действия с настройками во время работы программы
 */
void changeCurrentGlobalSettings(gameSettings*); //редактирование глобальных настроек
/*
 * Сеттеры для установления значений полей структуры gameSettings
 */
void setComplexity(gameSettings*, int);
void setFieldHeight(gameSettings*, int);
void setFieldLength(gameSettings*, int);
void setCountToWin(gameSettings*, int);
void setPlayers(gameSettings*, player *human, player *bot);//TODO освобождает память из-под старых
/*
 * Геттеры для получения значений полей структуры gameSettings
 */
int getComplexity(gameSettings*);
int getFieldHeight(gameSettings*);
int getFieldLength(gameSettings*);
int getCountToWin(gameSettings*);
player* getPlayerHuman(gameSettings*);
player* getPlayerBot(gameSettings*);

#endif //CROSSZERO_SETTINGS_H
