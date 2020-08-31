//
// Created by hubbyk on 14.05.2020.
//

#include "ratetable.h"
#include <string.h>
#include <malloc.h>

tableLine* loadRateTable() {
    char rateFileName[12] = {"ratings.txt"};
    FILE *rateFile;
    tableLine *ratingTable = NULL;
    char playerName[15] = {"\0"}, ch;
    int rating = 0;
    int complexity = HUMAN;

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

        ratingTable = addLine(ratingTable, newPlayer("Artorias", 100, DARK_SOULS));
        ratingTable = addLine(ratingTable, newPlayer("Evdokim", 80, HARD));
        ratingTable = addLine(ratingTable, newPlayer("Pokug", 60, MEDIUM));
        ratingTable = addLine(ratingTable, newPlayer("Botty", 40, EASY));
    }else {
        while(!feof(rateFile)) {
            for(int i = 0; (ch = (char)fgetc(rateFile)) != ' ' && !feof(rateFile); i++) {
                playerName[i] = ch;
            }
            for(int i = 0; (ch = (char)fgetc(rateFile)) != '\n' && !feof(rateFile); i++) {
                rating = rating * 10 + (ch) - 48;
            }
            if(!feof(rateFile)) {
                if(!strcmp(playerName, "Artorias")) complexity = DARK_SOULS;
                if(!strcmp(playerName, "Evdokim")) complexity = HARD;
                if(!strcmp(playerName, "Pokug")) complexity = MEDIUM;
                if(!strcmp(playerName, "Botty")) complexity = EASY;
                ratingTable = addLine(ratingTable, newPlayer(playerName, rating, complexity));

                memset(playerName, '\0', 15);
                rating = 0, complexity = HUMAN;
            }
        }
    }

    fclose(rateFile);

    return ratingTable;
}

tableLine* newTableLine(char *playerName, int playerRating) {
    tableLine* line = (tableLine*)malloc(sizeof(tableLine));
    strcpy(line->name, playerName);
    line->height = 1;
    line->rate = playerRating;
    line->right = NULL;
    line->left = NULL;
    return line;
}

tableLine* updateRateTable(tableLine* line, player* anyPlayer, int delta) {
    line = removeLine(line, anyPlayer);
    anyPlayer->rating += delta;
    addLine(line, anyPlayer);
    return line;
}

int getHeight(tableLine* line) {
    return (line)?line->height:0;
}
int balanceFactor(tableLine* line) {
    return getHeight(line->right) - getHeight(line->left);
}
void fixHeight(tableLine* line) {
    int hLeft = getHeight(line->left);
    int hRight = getHeight(line->right);
    line->height = (hLeft>hRight?hLeft:hRight)+1;
}
tableLine* rotateRight(tableLine* line) {
    tableLine* temp = line->left;
    line->left = temp->right;
    temp->right = line;
    fixHeight(line);
    fixHeight(temp);
    return temp;
}
tableLine* rotateLeft(tableLine* line) {
    tableLine* temp = line->right;
    line->right = line->left;
    temp->left = line;
    fixHeight(temp);
    fixHeight(line);
    return temp;
}
tableLine* balance(tableLine* line) {
    fixHeight(line);
    if(balanceFactor(line) == 2) {
        if(balanceFactor(line->right) < 0) {
            line->right = rotateRight(line->right);
        }
        return rotateLeft(line);
    }
    if(balanceFactor(line) == -2) {
        if(balanceFactor(line->left) > 0) {
            line->left = rotateLeft(line->left);
        }
        return rotateRight(line);
    }
    return line;
}
tableLine* addLine(tableLine* line, player* newPlayer) {
    if(!line) return newTableLine(getName(newPlayer), getRating(newPlayer));
    if(getRating(newPlayer) < line->rate) {
        line->left = addLine(line->left, newPlayer);
    }else {
        line->right = addLine(line->right, newPlayer);
    }
    return balance(line);
}
tableLine* addLineN(tableLine* line, player* newPlayer) {
    if(!line) return newTableLine(getName(newPlayer), getRating(newPlayer));
    if(strcmp(getName(newPlayer), line->name) < 0) {
        line->left = addLine(line->left, newPlayer);
    }else {
        line->right = addLine(line->right, newPlayer);
    }
    return balance(line);
}
tableLine* findMin(tableLine* line) {
    return (line->left)?findMin(line->left):line;
}
tableLine* removeMin(tableLine* line) {
    if(!line->left) return line->right;
    line->left = removeMin(line->left);
    return balance(line);
}
tableLine* removeLine(tableLine* line, player* anyPlayer) {
    if(!line) return NULL;
    if(getRating(anyPlayer) < line->rate) {
        line->left = removeLine(line->left, anyPlayer);
    }else if(getRating(anyPlayer) > line->rate) {
        line->right = removeLine(line->right, anyPlayer);
    }else {
        if(!strcmp(getName(anyPlayer), line->name)) {
            tableLine* l = line->left;
            tableLine* r = line->right;

            free(line);

            if(!r) return l;
            tableLine* min = findMin(r);
            min->right = removeMin(r);
            min->left = l;

            return balance(l);
        }else {
            line->right = removeLine(line->right, anyPlayer);
        }
    }

    return balance(line);
}

player* searchPlayerByName(tableLine* line, char* playerName) {
    if(!line)return NULL;
    if(!strcmp(playerName, line->name)) return newPlayer(playerName, line->rate, HUMAN);
    if(strcmp(playerName, line->name) < 0) {
        return getPlayerByName(line->left, playerName);
    }else {
        return getPlayerByName(line->right, playerName);
    }
}
player* getPlayerByName(tableLine* line, char* playerName) {
    tableLine* newTable = NULL;

    newTable = buildByName(line, newTable);
    return searchPlayerByName(newTable, playerName);
}

tableLine* buildByName(tableLine* line, tableLine* newLine) {
    if(line) {
        newLine = addLineN(newLine, newPlayer(line->name, line->rate, HUMAN));
        newLine = buildByName(line->right, newLine);
        //здесь все равно, верно выставлена сложность, или нет
        newLine = buildByName(line->left, newLine);
    }
    return newLine;
}

void safeTable(tableLine* line) {
    FILE* tableFile = fopen("ratings.txt", "w");
    writeTable(tableFile, line);
    fclose(tableFile);
}
void writeTable(FILE* tableFile, tableLine* line) {
    if(line->right) writeTable(tableFile, line->right);
    fprintf(tableFile, "%s %d\n", line->name, line->rate);
    if(line->left) writeTable(tableFile, line->left);
}
void closeTable(tableLine* line) {
    if(line->right) closeTable(line->right);
    if(line->left) closeTable(line->left);
    free(line);
}
int getRatingByName(tableLine* line, char* name) {
    player* anyPlayer = getPlayerByName(line, name);
    return (anyPlayer)?getRating(anyPlayer):0;
}