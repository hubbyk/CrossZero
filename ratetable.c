//
// Created by hubbyk on 14.05.2020.
//

#include "ratetable.h"
#include <string.h>
#include <malloc.h>

char* getNameFromLine(rateTable* table, int lineNumber) {
    char* result = (char *) calloc(15, sizeof(char));
    strncpy(result, (*table->lines + lineNumber - 1)->name, 15);
    return result;
}

int getRatingFromLine(rateTable* table, int lineNumber) {
    return (*table->lines + lineNumber - 1)->rate;
}

rateTable* loadRateTable() {
    char rateFileName[12] = {"ratings.txt"};
    FILE *rateFile;
    rateTable *ratingTable = (rateTable*) malloc(sizeof(rateTable));
    ratingTable->tableSize = 0;
    ratingTable->lines = (tableLine**) malloc(sizeof(tableLine));

    rateFile = fopen(rateFileName, "r+");
    if(rateFile == NULL) {
        /* Rating File ERROR
         * Creating new rate wile with default settings
         */
        rateFile = fopen("ratings.txt", "w+");
        if(rateFile == NULL) {
            /*FATAL ERROR
             * Can not load RATINGS_TABLE module
             */
            return NULL;
        }
        fprintf(rateFile, "Artorias 100\nEvdokim 80\nGarry 60\nBotty 40\n");

        newTableLine(ratingTable, "Artorias", 100);
        newTableLine(ratingTable, "Evdokim", 80);
        newTableLine(ratingTable, "Pokug", 60);
        newTableLine(ratingTable, "Botty", 40);
    }else {
        while(!feof(rateFile)) {
            readTableLine(rateFile, ratingTable);
        }
    }

    return ratingTable;
}

tableLine* readTableLine(FILE *rateTableFile, rateTable *table) {
    char playerName[15] = {'\0'}, inputString[100] = {'\0'};
    int playerRating = 0, index = 0;

    fgets(inputString, 100, rateTableFile);

    if(strlen(inputString) < 3) return NULL;

    for(; inputString[index] != ' ' && inputString[index]; index++) {
        playerName[index] = inputString[index];
    }
    ++index;
    for(;'0' <= inputString[index] && inputString[index] <= '9'; index++) {
        playerRating = playerRating * 10 + inputString[index] - 48;
    }

    return newTableLine(table, playerName, playerRating);
}

void updateRateTable(rateTable *ratingTable, player *anyPlayer) {
    int lineNumber = searchInTable(ratingTable, anyPlayer);
    if (lineNumber < 0) { //нет записи с этим игроком
        insertRateTableLine(ratingTable, anyPlayer);
    }else {
        (*ratingTable->lines + lineNumber)->rate = anyPlayer->rating;
    }
    sortTable(ratingTable);
}

void sortTable(rateTable *ratingTable) {
    for(int i = 0; i < ratingTable->tableSize - 2; i++) {
        for(int j = ratingTable->tableSize - 2; j; j--) {
            if((*ratingTable->lines + j)->rate < (*ratingTable->lines + j + 1)->rate) {
                tableLine temp = *(*ratingTable->lines + j);
                *(*ratingTable->lines + j) = *(*ratingTable->lines + j + 1);
                *(*ratingTable->lines + j + 1) = temp;
            }
        }
    }
}

tableLine* newTableLine(rateTable *table, char *playerName, int playerRating) {
    table->tableSize += 1;
    *table->lines = (tableLine*) realloc(*table->lines, table->tableSize * sizeof(**table->lines));
    (*table->lines + table->tableSize - 1)->rate = playerRating;
    strcpy((*table->lines + table->tableSize - 1)->name, playerName);
    return (*table->lines + table->tableSize);
}

void insertRateTableLine(rateTable *table, player *anyPlayer) {
    newTableLine(table, anyPlayer->name, anyPlayer->rating);
}

int searchInTable(rateTable *ratingTable, player *anyPlayer) {
    for(int index = 0; index < ratingTable->tableSize; index++) {
        if(!strcmp((*ratingTable->lines)->name, anyPlayer->name)) return index;
    }
    return -1;
}