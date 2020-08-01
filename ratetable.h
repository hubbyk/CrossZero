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
typedef struct  {
    int rate;  //рейтинг
    char name[15]; //имя
}tableLine;

typedef struct {
    int tableSize;
    tableLine **lines;
}rateTable;

char* getNameFromLine(rateTable*, int lineNumber); //получаем имя игрока из строки таблицы с таким номером

int getRatingFromLine(rateTable*, int lineNumber); //ан-но получаем рейтинг

tableLine* readTableLine(FILE *rateTableFile, rateTable *ratingTable);//читает строку таблицы из файла

tableLine* newTableLine(rateTable *table, char *playerName, int playerRating); //создаем новую строку в таблице с именем и рейтингом
/*Описание loadRateTable
 * Функция запускается при старте программы, пытается прочитать файл таблицы
 * Если такого файла нет - создает новый файл и заполняет записями по умолчанию - именами и рейтингами ботов разного уровня сложности
 * Если все-таки файл нашелся - читает и выгружает в оперативную память
 * Хранения таблицы в памяти описано в ratetable.h
 */
rateTable* loadRateTable();

/*Описание updateRateTable
 * Смотри описание выше
 */
void updateRateTable(rateTable *ratingTable, player *anyPlayer); //обновляет рейтинговую таблицу после окончания игры

void sortTable(rateTable *ratingTable); //сортирует таблицу по рейтингу

void insertRateTableLine(rateTable *ratingTable, player *anyPlayer); //добавляет новую запись в таблицу (обертка для newTableLine)

int searchInTable(rateTable *ratingTable, player *anyPlayer); //ищет игрока в таблице

#endif //CROSSZERO_RATETABLE_H
