//
// Created by hubbyk on 14.05.2020.
//

#ifndef CROSSZERO_RATETABLE_H
#define CROSSZERO_RATETABLE_H

#include "mainheader.h"

/*
 * Таблица рейтингов
 *
 * Все логично - таблица состоит из линий вида "имя рейтинг", разделены одним пробелом
 *
 * Представление таблицы в памяти:
 * Таблица - структура, состоящая из двух полей: размер таблицы (т.е. количество линий) и указатель на массив линий таблицы
 *
 * Для получения имени из строки таблицы использовать функцию getNameFromLine(указатель на таблицу, номер линии)
 * Для получения рейтинга из строки таблицы использовать функцию getRatingFromLine(указатель на таблицу, номер линии)
 *
 * После окончания игры обновляется рейтинг у игрока (смотри player.h)
 * Далее необходимо вызвать функцию updateRateTable(таблица, игрок (если выиграл))
 * В ходе работы данной функции будет добавлена новая, или обновлена существующая с этим именем запись, после таблица сортируется
 *
 * другие функции из ratetable.h в рамках данного проекта использоваться за пределами ratetable.c не должны
 * если все же возникнет необходимость (а не должна) - сообщить habbyk
 */

enum changeRating {LOSE, DRAW, WIN}; //на сколько будет изменяться рейтинг в зависимости от результата игры
//P.S. рейтинг будет домножаться на сложность игры
typedef struct tableLine{
    int rate;  //рейтинг
    char name[15]; //имя
    int height;
    struct tableLine* left;
    struct tableLine* right;
    struct tableLine* next;
}tableLine;

tableLine* newTableLine(char *playerName, int playerRating); //создаем новую строку в таблице с именем и рейтингом
/*Описание loadRateTable
 * Функция запускается при старте программы, пытается прочитать файл таблицы
 * Если такого файла нет - создает новый файл и заполняет записями по умолчанию - именами и рейтингами ботов разного уровня сложности
 * Если все-таки файл нашелся - читает и выгружает в оперативную память
 * Хранения таблицы в памяти описано в ratetable.h
 */
tableLine* loadRateTable();

tableLine* updateRateTable(tableLine* line, player* anyPlayer, int delta);

int getHeight(tableLine* line);
int balanceFactor(tableLine* line);
void fixHeight(tableLine* line);
tableLine* rotateLeft(tableLine* line);
tableLine* rotateRight(tableLine* line);
tableLine* balance(tableLine* line);
tableLine* addLine(tableLine* line, player* newPlayer);
tableLine* addLineN(tableLine* line, player* newPlayer);
tableLine* findMin(tableLine* line);
tableLine* removeMin(tableLine* line);
tableLine* removeLine(tableLine* line, player* anyPlayer);

player* getPlayerByName(tableLine* line, char* playerName);
player* searchPlayerByName(tableLine* line, char* playerName);
tableLine* buildByName(tableLine* oldLine, tableLine* newLine);
int getRatingByName(tableLine*, char* name);

void safeTable(tableLine* line);
void writeTable(FILE* tableFile, tableLine* line);
void closeTable(tableLine* line);

#endif //CROSSZERO_RATETABLE_H
