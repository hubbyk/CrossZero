#include "game.h"



int main(int argc, char * argv[]) {
    gameSettings* settings = loadDefaultSettings();
    tableLine* ratingTable = loadRateTable();

    startGame(loadSavedGame(ratingTable), ratingTable);

    return 0;
}
