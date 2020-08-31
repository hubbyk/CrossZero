//
// Created by hubbyk on 13.05.2020.
//

#ifndef CROSSZERO_SETTINGS_H
#define CROSSZERO_SETTINGS_H

#include "mainheader.h"

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

/*
 * НАСТРОЙКИ ПО УМОЛЧАНИЮ
 * сложность: средняя
 * размеры поля: 3х3
 * игроки: player vs Pokug
 */
typedef struct {
    char playerName[15];
    int complexity;  //уровень сложности
    int fieldSize; //параметры поля
    int winLineLength; //длина выигрышной цепочки
    int firstMove; //кто ходит первым
}gameSettings;
/*
 * Получение структуры gameSettings
 */
gameSettings* loadDefaultSettings(); // задает значения полей структуры по умолчанию
gameSettings* newSettings(); //создает новую структуру настроек
/*
 * Сеттеры для установления значений полей структуры gameSettings
 */
void setComplexity(gameSettings*, int);
void setFieldSize(gameSettings*, int);
void setWinLineLength(gameSettings*, int);
void setFirstMove(gameSettings*, int);
void setPlayerName(gameSettings*, char* buf);
/*
 * Геттеры для получения значений полей структуры gameSettings
 */
int getComplexity(gameSettings*);
int getFieldSize(gameSettings*);
int getWinLineLength(gameSettings*);

#endif //CROSSZERO_SETTINGS_H
