//
// Created by hubbyk on 26.04.2020.
//

#include "game.h"


GAME* loadSavedGame(tableLine* table) {
    FILE* gameFile = fopen("saved_game.txt", "r");
    GAME* loadedGame = newGame();
    gameField* field = newGameField();
    gameSettings* settings = newSettings();
    int complexity, fieldSize, winLineLength, countOfNonVoidCell;
    char playerName[15];

    fscanf(gameFile, "%d %d %d\n",
           &complexity, &fieldSize, &winLineLength);
    setComplexity(settings, complexity);
    setFieldSize(settings, fieldSize);
    setWinLineLength(settings, winLineLength);

    fscanf(gameFile, "%s\n%d\n", playerName, &countOfNonVoidCell);
    setFirstPlayer(loadedGame, getPlayerByName(table, playerName));
    setSecondPlayer(loadedGame, getPlayerByComplexity(getComplexity(settings)));

    setNewMap(field, countOfNonVoidCell);

    for(int i = 0; i < countOfNonVoidCell; i++) {
        addValue(field, fgetc(gameFile) - 48, i);
    }
    fgetc(gameFile);
    for(int i = 0; i < countOfNonVoidCell; i++) {
        addXCord(field, fgetc(gameFile) - 48, i);
    }
    fgetc(gameFile);
    for(int i = 0; i < countOfNonVoidCell; i++) {
        addYCord(field, fgetc(gameFile) - 48, i);
    }

    fclose(gameFile);

    setBattlefield(loadedGame, field);
    setSettings(loadedGame, settings);

    return loadedGame;
}
GAME* createNewGame(gameSettings* settings) {
    GAME* game = newGame();
    gameField* field = newGameField();
    setSettings(game, settings);

    setNewMap(field, 0);
    setBattlefield(game, field);
    setSecondPlayer(game, getPlayerByComplexity(getComplexity(settings)));
    setFirstPlayer(game, newPlayer("Noob", 0));

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

int startGame(GAME* thisGame, tableLine* table) {

//    setGameName(thisGame, "TEST");

//    writeValue(getBattlefield(thisGame), 0, 0, CROSS);
//    writeValue(getBattlefield(thisGame), 1, 1, CROSS);
//    writeValue(getBattlefield(thisGame), 2, 2, CROSS);
//    writeValue(getBattlefield(thisGame), 2, 0, ZERO);
//    writeValue(getBattlefield(thisGame), 0, 2, ZERO);

    writeValue(getBattlefield(thisGame), 0, 1, CROSS);
    writeValue(getBattlefield(thisGame), 1, 0, CROSS);

    safeGame(thisGame);

    table = updateRateTable(table, getFirstPlayer(thisGame), 0);
    safeTable(table);
    closeTable(table);

    end(thisGame);
    return 1;
}
void safeGame(GAME* thisGame) {
    FILE *gameFile = fopen("saved_game.txt", "w");

    // записываем настройки игры
    fprintf(gameFile, "%d %d %d\n",
            getComplexity(getSettings(thisGame)), getFieldSize(getSettings(thisGame)),
            getWinLineLength(getSettings(thisGame)));

    // записываем имена игроков
    fprintf(gameFile, "%s\n%d\n", getName(getFirstPlayer(thisGame)), getCountOfNonVoidCells(getBattlefield(thisGame)));

    // записываем состояние поля, значения, коордната Х, координата У
    for(int i = 0; i < getCountOfNonVoidCells(getBattlefield(thisGame)); i++) {
        fprintf(gameFile, "%d",getValues(getBattlefield(thisGame))[i]);
    }
    fprintf(gameFile, "\n");
    for(int i = 0; i < getCountOfNonVoidCells(getBattlefield(thisGame)); i++) {
        fprintf(gameFile, "%d", getXCords(getBattlefield(thisGame))[i]);
    }
    fprintf(gameFile, "\n");
    for(int i = 0; i < getCountOfNonVoidCells(getBattlefield(thisGame)); i++) {
        fprintf(gameFile, "%d", getYCords(getBattlefield(thisGame))[i]);
    }
    fprintf(gameFile, "\n");

    fclose(gameFile);
}
void end(GAME* game) {
    free(getFirstPlayer(game));
    free(getSecondPlayer(game));
    free(getBattlefield(game)->gameMap);
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
            return newPlayer("Botty", 40);
        case MEDIUM:
            return newPlayer("Pokug", 60);
        case HARD:
            return newPlayer("Evdokim", 80);
        case DARK_SOULS:
            return newPlayer("Artorias", 100);
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