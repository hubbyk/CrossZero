//
// Created by hubbyk on 29.08.2020.
//

#include "mainheader.h"
#include "gameheader.h"

#ifndef CROSSZERO_GREATMIND_H
#define CROSSZERO_GREATMIND_H

typedef struct {
    int capacity;

    int winLineLength;
    int complexity;
    int figure;

    int curPower;
    int curPotential;
    int curDivider;

    int firstPower;
    int firstPotential;
    int firstDivider;

    int checkBorder;
    int distance;
    int attackPlace;

}AttackCollector;

int checkWin(gameField* field, int lastX, int lastY, int winLineLength);
int checkLine(gameField* field, int lastX, int lastY, int dX, int dY);

int countAttackWeigth(AttackCollector* collector);

void storeAttack(AttackCollector* collector);

int isBreakPoint(AttackCollector* collector);

AttackCollector* newAttackCollector(int winLineLength, int complexity);

void getAttacks(AttackCollector* collector, gameField* field,
                    int curX, int curY, int figure, int dX, int dY);

int checkCell(AttackCollector* collector, gameField* field, int x, int y);

void turnAround(AttackCollector* collector);
int countAttacksWeightOnLine(gameField* field, int complexity,
                                 int curX, int curY, int figure, int dX, int dY, int winLineLength);

int getAllAttacksWeight(gameField* field, int complexity, int xCord, int yCord, int winLineLength);
void handleCollector(AttackCollector* collector);

void godCreation(gameField* field, int winLineLength, int complexity, int* resX, int* resY, int figure);
#endif //CROSSZERO_GREATMIND_H
