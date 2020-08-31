//
// Created by hubbyk on 28.04.2020.
//

#ifndef CROSSZERO_PLAYER_H
#define CROSSZERO_PLAYER_H

typedef struct  {
    int rating;    //рейтинг игрока
    char name[15]; // имя игрока
    int complexity;
}player;

void setName(player*, char*); //устанавливает имя для игрока

void setRating(player*, int); //устанавливает рейтинг игрока

char* getName(player*); // получаем имя игрока

void setComplexityToPlayer(player* anyPlayer, int value);

int getRating(player*);

void makeMove(int X, int Y); //делает ход

player* newPlayer(char*, int, int); //создает нового игрока


#endif //CROSSZERO_PLAYER_H
