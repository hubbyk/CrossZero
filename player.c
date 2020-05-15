//
// Created by hubbyk on 28.04.2020.
//

#include "player.h"

#include <malloc.h>
#include <string.h>

player* newPlayer(char* playerName, int rating) {
    player *anyPlayer = (player*) malloc(sizeof(*anyPlayer));
    setName(anyPlayer, playerName);
    setRating(anyPlayer, rating);
    return anyPlayer;
}

void setName(player *anyPlayer, char* playerName) {
    strcpy(anyPlayer->name, playerName);
}

void setRating(player* anyPlayer, int rating) {
    anyPlayer->rating = rating;
}

char* getName(player* anyPlayer) {
    return anyPlayer->name;
}


