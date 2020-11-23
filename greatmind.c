//
// Created by hubbyk on 29.08.2020.
//

#include "greatmind.h"

int checkWin(gameField* field, int lastX, int lastY, int winLineLength) {

    if(checkLine(field, lastX, lastY, 1, 0) >= winLineLength) return 1;
    if(checkLine(field, lastX, lastY, 0, 1) >= winLineLength) return 1;
    if(checkLine(field, lastX, lastY, 1, 1) >= winLineLength) return 1;
    if(checkLine(field, lastX, lastY, 1, -1) >= winLineLength) return 1;

    return 0;

}
int checkLine(gameField* field, int lastX, int lastY, int dX, int dY) {
    int score = 0, xCopy = lastX, yCopy = lastY,
        figure = getValueByCords(field, lastX, lastY);

    while(figure == getValueByCords(field, xCopy, yCopy)) {
        ++score; xCopy += dX; yCopy += dY;
    }
    xCopy = lastX - dX, yCopy = lastY -dY;
    while(figure == getValueByCords(field, xCopy, yCopy)) {
        ++score; xCopy -= dX; yCopy -= dY;
    }

    return score;
}

int countAttackWeight(AttackCollector* collector) {
    if(collector->curPower == collector->winLineLength) return (collector->curPower * 1000) / collector->curDivider;
    if(collector->curPower  == collector->winLineLength - 1 && collector->curPotential == 2) return (collector->curPower  * ((collector->complexity > MEDIUM)?200:10)) / collector->curDivider;
    return (collector->curPower  + collector->curPotential * 2) / collector->curDivider;
}
AttackCollector* newAttackCollector(int winLineLength, int complexity) {
    AttackCollector* new = (AttackCollector*)malloc(sizeof(AttackCollector));

    new->capacity = 0;

    new->figure = CROSS;
    new->winLineLength = winLineLength;
    new->complexity = complexity;

    new->curDivider = 1;
    new->curPower = 1;
    new->curPotential = 0;

    new->firstPotential = 0;
    new->firstDivider = 0;
    new->firstPower = 0;

    new->distance = 1;
    new->checkBorder = 0;
    new->attackPlace = 1;

    return new;
}

void getAttacks(AttackCollector* collector, gameField* field,
                    int cellX, int cellY, int figure, int dX, int dY) {
    collector->figure = figure;

    for(int curX = cellX - dX, curY = cellY - dY;
        (curX - cellX < 0)?cellX - curX:curX - cellX <= collector->winLineLength &&
                                                (curY - cellY < 0)?cellY - curY:curY - cellY <= collector->winLineLength;
        curX -= 2 * dX, curY -= 2 * dY) {
        if (checkCell(collector, field, curX + dX, curY + dY)) break;
        if((curX - cellX < 0)?cellX - curX:curX - cellX <= collector->winLineLength &&
                                           (curY - cellY < 0)?cellY - curY:curY - cellY <= collector->winLineLength) {
            if (checkCell(collector, field, curX, curY)) break;
        }
    }

    turnAround(collector);

    for(int curX = cellX + dX, curY = cellY + dY;
        (curX - cellX < 0)?cellX - curX:curX - cellX <= collector->winLineLength &&
                                        (curY - cellY < 0)?cellY - curY:curY - cellY <= collector->winLineLength;
        curX += 2 * dX, curY += 2 * dY) {
        if(checkCell(collector, field, curX - dX, curY - dY)) break;
        if((curX - cellX < 0)?cellX - curX:curX - cellX <= collector->winLineLength &&
                                           (curY - cellY < 0)?cellY - curY:curY - cellY <= collector->winLineLength) {
            if(checkCell(collector, field, curX, curY)) break;
        }
    }
}
int checkCell(AttackCollector* collector, gameField* field, int x, int y) {
    int figure = getValueByCords(field, x, y);


    if(collector->figure > VOID) {

        handleCollector(collector);

        if(figure) {
            return figure;
        }else {
            if(collector->curPower) {
                collector->curPotential++;

                collector->curPower = 1;
                collector->curDivider = 1;
                collector->curPotential = 2;
            }
            collector->curDivider++;
            collector->attackPlace++;
        }
    }else {
        collector->curPower++;
        collector->attackPlace++;
    }

    if(collector->distance == collector->winLineLength - 1 && figure == collector->figure) {
        collector->checkBorder = 1;
    }else if(collector->distance == collector->winLineLength) {
        if(collector->checkBorder) {
            if(figure == collector->figure || figure == VOID)
                collector->curPotential++;

            handleCollector(collector);
        }
        return 1;
    }
    collector->distance++;
    return 0;
}

void handleCollector(AttackCollector* collector) {
    if(!collector->firstPower) {
        storeAttack(collector);
    }
    if(collector->complexity > EASY) {
        if(isBreakPoint(collector))
            collector->capacity += collector->curPower * 100;
    }
    if(collector->complexity > HARD) {
        if(collector->curPower && collector->curPotential ||
           collector->curPower >= collector->winLineLength) {
            collector->capacity += countAttackWeight(collector);
        }
    }else {
        collector->capacity += countAttackWeight(collector);
    }
}

void turnAround(AttackCollector* collector) {
    collector->distance = 1;
    collector->checkBorder = 0;

    collector->curPower = collector->firstPower;
    collector->curPotential = collector->firstPotential;
    collector->curDivider = collector->firstDivider;
}

void storeAttack(AttackCollector* collector) {
    collector->firstPower = collector->curPower;
    collector->firstDivider = collector->curDivider;
    collector->firstPotential = collector->curPotential;
}

int countAttacksWeightOnLine(gameField* field, int complexity,
                                 int curX, int curY, int figure, int dX, int dY, int winLineLength) {
    int result;
    AttackCollector* collector = newAttackCollector(winLineLength, complexity);
    getAttacks(collector, field, curX, curY, figure, dX, dY);
    //result = (complexity > HARD)?filteredAttacks(collector, winLineLength):collector->attacks;
    result = collector->capacity;
    free(collector);
    return result;
}

int getAllAttacksWeight(gameField* field, int complexity, int xCord, int yCord, int winLineLength) {
    if(getValueByCords(field, xCord, yCord)) return 0;
    int result = 0;

    result += countAttacksWeightOnLine(field, complexity, xCord, yCord, CROSS, 1, 0, winLineLength);
    result += countAttacksWeightOnLine(field, complexity, xCord, yCord, CROSS, 0, 1, winLineLength);
    result += countAttacksWeightOnLine(field, complexity, xCord, yCord, CROSS, 1, -1, winLineLength);
    result += countAttacksWeightOnLine(field, complexity, xCord, yCord, CROSS, 1, 1, winLineLength);

    if(complexity > EASY) {
        result += countAttacksWeightOnLine(field, complexity, xCord, yCord, ZERO, 1, 0, winLineLength);
        result += countAttacksWeightOnLine(field, complexity, xCord, yCord, ZERO, 0, 1, winLineLength);
        result += countAttacksWeightOnLine(field, complexity, xCord, yCord, ZERO, 1, -1, winLineLength);
        result += countAttacksWeightOnLine(field, complexity, xCord, yCord, ZERO, 1, 1, winLineLength);
    }

    return result;
}

int isBreakPoint(AttackCollector* collector) {
    if(!collector) return 0;

    if(collector->curDivider == 1) {
        if (collector->curPower >= collector->winLineLength - 1) return 1;
        if (collector->curPower >= collector->winLineLength - 2 && collector->curPotential == 2) return 1;
    }

    if(collector->curDivider == 2) {
        if (collector->curPower >= collector->winLineLength - 2) return 1;
    }
    return 0;
}

void godCreation(gameField* field, int winLineLength, int complexity, int* resX, int* resY, int figure) {
    int maxWeight = 0, curWeight, resultX = 0, resultY = 0;

    for(int i = 0; i < field->size; i ++) {
        for (int j = 0; j < field->size; j += 2) {
            if(j + 1 < field->size) {
                curWeight = getAllAttacksWeight(field, complexity, j + 1, i, winLineLength);
                if(curWeight > maxWeight) {
                    maxWeight = curWeight;
                    resultX = j + 1; resultY = i;
                }
            }
            curWeight = getAllAttacksWeight(field, complexity, j, i, winLineLength);
            if(curWeight > maxWeight) {
                maxWeight = curWeight;
                resultX = j; resultY = i;
            }
        }
    }
    *resX = resultX; *resY = resultY;
    if(maxWeight == 0) {
        for(int i = 0; i < field->size; i++) {
            for (int j = 0; j < field->size; j += 2) {
                if(!getValueByCords(field, j, i)) {
                    resultX = j; resultY = i;
                }
                if(!getValueByCords(field, j + 1, i)) {
                    resultX = j; resultY = i;
                }
            }
        }
    }
    writeValue(field, resultX, resultY, figure);
}