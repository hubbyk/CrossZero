//
// Created by hubbyk on 29.08.2020.
//

#include "mainheader.h"
#include "gameheader.h"

#ifndef CROSSZERO_GREATMIND_H
#define CROSSZERO_GREATMIND_H

typedef struct Attack{
    int power;
    int potential;
    int divider;
    struct Attack* next;
}Attack;

typedef struct {
    int winLineLength;
    int figure;
    int checkBorder;
    int distance;
    int attackPlace;
    Attack* attacks;
    Attack* curAttack;
}AttackCollector;

typedef struct {
    Attack* attacksCross[4];
    Attack* attacksZero[4];
}AttackCollection;

int checkWin(gameField* field, int lastX, int lastY, int winLineLength);
int checkLine(gameField* field, int lastX, int lastY, int dX, int dY);

Attack* newAttack();
int countAttackWeigth(Attack* attack, int winLineLength, int isYourFigure);

AttackCollector* newAttackCollector(int winLineLength);

Attack* getAttacks(AttackCollector* collector, gameField* field,
                    int curX, int curY, int figure, int dX, int dY);
Attack* getAttack(Attack* start, int index);
int checkCell(AttackCollector* collector, gameField* field, int x, int y);
void addAttack(AttackCollector* collector);
void turnAround(AttackCollector* collector);
Attack* collectAttacksOnLine(gameField* field,
                          int curX, int curY, int figure, int dX, int dY, int winLineLength);
Attack* filteredAttacks(AttackCollector* collector, int winLineLength);
AttackCollection* getAllAttacks(gameField* field, int xCord, int yCord, int winLineLength);
AttackCollection* newCollection();

int isBreakPoint(Attack* attack, int winLineLength);

//int getWeight(gameField* field, int xCord, int yCord);
int countWeight(gameField* field, int yourFigure, int xCord, int yCord, int winLineLength);
int count(Attack** attacks, int figure, int winLineLength, int isYourFigure);

void godCreation(gameField* field, int winLineLength, int yourFigure, int* resX, int* resY);
#endif //CROSSZERO_GREATMIND_H
