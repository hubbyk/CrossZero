//
// Created by hubbyk on 28.04.2020.
//

#ifndef CROSSZERO_PLAYER_H
#define CROSSZERO_PLAYER_H
typedef struct  {
    char *name; // имя игрока
}player;

void setName(player*, char*); //устанавливает имя для игрока

char* getName(player*); // получаем имя игрока

void makeMove(int X, int Y); //делает ход

player* newPlayer(char*); //создает нового игрока


#endif //CROSSZERO_PLAYER_H
