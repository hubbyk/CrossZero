//
// Created by hubbyk on 29.08.2020.
//

#include "mainheader.h"
#include "gameheader.h"

#ifndef CROSSZERO_GREATMIND_H
#define CROSSZERO_GREATMIND_H

typedef struct {
    int power;
    int potential;
    int divider;
}Attack;

typedef struct {
    int attackCount;
    int figure;
    int checkBorder;
    int distance;
    int attackPlace;
    Attack** attacks;
    Attack* curAttack;
}AttackCollector;

typedef struct {
    Attack** attacksX[4];
    Attack** attacksY[4];
}AttackCollection;

int checkWin(gameField* field, int lastX, int lastY, int winLineLength);
int checkLine(gameField* field, int lastX, int lastY, int dX, int dY);

Attack* newAttack();
int countAttackWeigth(int winLineLength, int power, int potential);

AttackCollector* newAttackCollector();

Attack** getAttacks(AttackCollector* collector, gameField* field,
                    int curX, int curY, int figure, int dX, int dY);
int checkCell(AttackCollector* collector, gameField* field, int x, int y);
void addAttack(AttackCollector* collector);
void turnAround(AttackCollector* collector);
Attack** collectAttacksOnLine(gameField* field,
                          int curX, int curY, int figure, int dX, int dY);
Attack** filteredAttacks(AttackCollector* collector);
AttackCollection* getAllAttacks(gameField* field, int xCord, int yCord);
AttackCollection* newCollection();

int isBreakPoint(AttackCollector* collector);

int getWeight(gameField* field, int xCord, int yCord);
int countWeight();
#endif //CROSSZERO_GREATMIND_H
