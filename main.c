#include <stdio.h>
#include "game.h"
#include "menu.h"
#include "ratetable.h"


int main(int argc, char * argv[]) {
    rateTable* RATING_TABLE = loadRateTable();
    player* Dory = newPlayer("Dory", 50);
    updateRateTable(RATING_TABLE, Dory);
    for(int i = 0; i < RATING_TABLE->tableSize; i++) {
        printf("%s %d\n", getNameFromLine(RATING_TABLE, i + 1), getRatingFromLine(RATING_TABLE, i + 1));
    }
    return 0;
}
