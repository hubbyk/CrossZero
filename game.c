//
// Created by hubbyk on 26.04.2020.
//

#include "game.h"


GAME* loadSavedGame(tableLine* table) {
    FILE* gameFile = fopen("saved_game.txt", "r");
    GAME* loadedGame = newGame();
    //gameField* field = newGameField();
    gameField* field = NULL;
    gameSettings* settings = newSettings();
    int complexity, fieldSize, winLineLength, countOfNonVoidCell, firstMove;
    char playerName[15];

    fscanf(gameFile, "%d %d %d %d\n",
           &complexity, &fieldSize, &winLineLength, &firstMove);
    setComplexity(settings, complexity);
    setFieldSize(settings, fieldSize);
    setWinLineLength(settings, winLineLength);
    setFirstMove(settings, firstMove);

    fscanf(gameFile, "%s\n%d\n", playerName, &countOfNonVoidCell);
    setFirstPlayer(loadedGame, getPlayerByName(table, playerName));
    if(!getFirstPlayer(loadedGame)) setFirstPlayer(loadedGame, newPlayer(playerName, 0, HUMAN));
    setSecondPlayer(loadedGame, getPlayerByComplexity(getComplexity(settings)));
//
//    setNewMap(field, countOfNonVoidCell);
//
//    for(int i = 0; i < countOfNonVoidCell; i++) {
//        addValue(field, fgetc(gameFile) - 48, i);
//    }
//    fgetc(gameFile);
//    for(int i = 0; i < countOfNonVoidCell; i++) {
//        addXCord(field, fgetc(gameFile) - 48, i);
//    }
//    fgetc(gameFile);
//    for(int i = 0; i < countOfNonVoidCell; i++) {
//        addYCord(field, fgetc(gameFile) - 48, i);
//    }
//
    field = newGameField(getFieldSize(settings));

    for(int i = 0; i < fieldSize; i++) {
        fscanf(gameFile, "%d %d\n", &field->lines[i].bitMapState, &field->lines[i].bitMapValue);
    }

    fclose(gameFile);

    setBattlefield(loadedGame, field);
    setSettings(loadedGame, settings);

    return loadedGame;
}
GAME* createNewGame(gameSettings* settings, tableLine* line) {
    GAME* game = newGame();
    gameField* field = newGameField(settings->fieldSize);
    setSettings(game, settings);
    setFirstPlayer(game, newPlayer(settings->playerName, getRatingByName(line, settings->playerName), HUMAN));
    //setNewMap(field, 0);
    setBattlefield(game, field);
    setSecondPlayer(game, getPlayerByComplexity(getComplexity(settings)));

    return game;
}
GAME* newGame() {
    GAME* game = (GAME*)malloc(sizeof(GAME));
    setFirstPlayer(game, NULL);
    setSecondPlayer(game, NULL);
    setSettings(game, NULL);
    setBattlefield(game, NULL);
    return game;
}

void safeGame(GAME* thisGame) {
    FILE *gameFile = fopen("saved_game.txt", "w");
    gameField* field = getBattlefield(thisGame);

    // записываем настройки игры
    fprintf(gameFile, "%d %d %d %d\n",
            getComplexity(getSettings(thisGame)), getFieldSize(getSettings(thisGame)),
            getWinLineLength(getSettings(thisGame)), getFirstMove(getSettings(thisGame)));

    // записываем имена игроков
    fprintf(gameFile, "%s\n", getName(getFirstPlayer(thisGame))); //getCountOfNonVoidCells(getBattlefield(thisGame)));

    // записываем состояние поля, значения, коордната Х, координата У
    for(int i = 0; i < getFieldSize(getSettings(thisGame)); i++) {
        fprintf(gameFile, "%d %d\n", field->lines[i].bitMapState, field->lines[i].bitMapValue);
    }

    fclose(gameFile);
}

void end(GAME* game) {
    free(getFirstPlayer(game));
    free(getSecondPlayer(game));
    //free(getBattlefield(game)->gameMap);
    free(getBattlefield(game));
    free(getSettings(game));
    free(game);
}

void setFirstPlayer(GAME* game, player* anyPlayer) {
    game->player1 = anyPlayer;
}
void setSecondPlayer(GAME* game, player* anyPlayer) {
    game->player2 = anyPlayer;
}
void setSettings(GAME* game, gameSettings* settings) {
    game->settings = settings;
}
void setBattlefield(GAME* game, gameField* field) {
    game->battlefield = field;
}

player* getFirstPlayer(GAME* game) {
    return game->player1;
}
player* getSecondPlayer(GAME* game) {
    return game->player2;
}
player* getPlayerByComplexity(int complexity) {
    switch (complexity) {
        case EASY:
            return newPlayer("Botty", 40, EASY);
        case MEDIUM:
            return newPlayer("Pokug", 60, MEDIUM);
        case HARD:
            return newPlayer("Evdokim", 80, HARD);
        case DARK_SOULS:
            return newPlayer("Artorias", 100, DARK_SOULS);
        default:
            return NULL;
    }
}
gameSettings* getSettings(GAME* game) {
    return game->settings;
}
gameField* getBattlefield(GAME* game) {
    return game->battlefield;
}