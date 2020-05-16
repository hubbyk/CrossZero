//
// Created by hubbyk on 13.05.2020.
//

#ifndef CROSSZERO_SETTINGS_H
#define CROSSZERO_SETTINGS_H

#include "player.h"

/*
 * Настройки
 *
 * Настройки представляют собой структуру с настраиваемыми полями (их значение описано ниже)
 * При старте приложения загружаются настройки по умолчанию (описаны ниже)
 *
 * Для изменения значений полей структуры настроек использовать "сеттеры"
 * - функции вида setПолеСтруктуры(указатель на структуру, значение поля)
 * Посмотреть все эти функции можно ниже
 *
 * Для получения значений полей структуры настроек использовать "геттеры"
 * - функции вида getПолеСтруктуры(указатель на структуру)
 * Посмотреть все эти функции можно ниже
 */

enum complexity {HUMAN, EASY, MEDIUM, HARD, DARKSOULS};
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
    int winLineLength; //длина выигрышной цепочки
    player* player1;   //игроки
    player* player2;
}gameSettings;
/*
 * Получение структуры gameSettings
 */
gameSettings* loadDefaultSettings();
gameSettings* loadGameSettings(char* gameName);//загружает настройки сохраненной игры TODO
gameSettings* newSettings(); //создает новую структуру настроек, задает значения полей структуры по умолчанию
/*
 * Сеттеры для установления значений полей структуры gameSettings
 */
void setComplexity(gameSettings*, int);
void setFieldHeight(gameSettings*, int);
void setFieldLength(gameSettings*, int);
void setWinLineLength(gameSettings*, int);
void setPlayers(gameSettings*, player* player1, player* player2);
/*
 * Геттеры для получения значений полей структуры gameSettings
 */
int getComplexity(gameSettings*);
int getFieldHeight(gameSettings*);
int getFieldLength(gameSettings*);
int getWinLineLength(gameSettings*);
player* getPlayerHuman(gameSettings*);
player* getPlayerBot(gameSettings*);

#endif //CROSSZERO_SETTINGS_H
