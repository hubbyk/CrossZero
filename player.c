//
// Created by hubbyk on 28.04.2020.
//

#include "player.h"

#include <malloc.h>
#include <string.h>

player* newPlayer(char* playerName) {
    player *anyPlayer = (player*) malloc(sizeof(*anyPlayer));
    setName(anyPlayer, playerName);
    return anyPlayer;
}

void setName(player *anyPlayer, char* playerName) {
    anyPlayer->name = (char*) calloc(strlen(playerName), sizeof(char));
    strcpy(anyPlayer->name, playerName);
}

char* getName(player* anyPlayer) {
    return anyPlayer->name;
}


