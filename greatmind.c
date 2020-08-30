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
    xCopy = lastX, yCopy = lastY;
    while(figure == getValueByCords(field, xCopy, yCopy)) {
        ++score; xCopy -= dX; yCopy -= dY;
    }

    return score;
}

Attack* newAttack() {
    Attack* new = (Attack*)malloc(sizeof(Attack));
    new->divider = 1;
    new->power = 1;
    new->potential = 0;
    return new;
}
int countAttackWeight(Attack* attack, int winLineLength) {
    if(attack->power == winLineLength) return (attack->power * 40) / attack->divider;
    if(attack->power  == winLineLength - 1 && attack->potential == 2) return (attack->power  * 25) / attack->divider;
    return (attack->power  + attack->potential * 2) / attack->divider;
}
AttackCollector* newAttackCollector() {
    AttackCollector* new = (AttackCollector*)malloc(sizeof(AttackCollector));
    new->figure = CROSS;
    new->attackCount = 0;
    new->attacks = (Attack**)malloc(sizeof(Attack*));
    new->distance = 1;
    new->curAttack = newAttack();
    new->checkBorder = 0;
    new->attackPlace = 1;
    return new;
}

Attack** getAttacks(AttackCollector* collector, gameField* field,
                    int cellX, int cellY, int figure, int dX, int dY) {
    collector->figure = figure;

    for(int curX = cellX - dX, curY = cellY - dY;
        (curX - cellX < 0)?cellX - curX:curX - cellX <= 5 &&
                                                (curY - cellY < 0)?cellY - curY:curY - cellY <= 5;
        curX -= dX, curY -= dY) if(checkCell(collector, field, curX, curY)) break;

    turnAround(collector);

    for(int curX = cellX + dX, curY = cellY + dY;
        (curX - cellX < 0)?cellX - curX:curX - cellX <= 5 &&
                                        (curY - cellY < 0)?cellY - curY:curY - cellY <= 5;
        curX += dX, curY += dY) if(checkCell(collector, field, curX, curY)) break;

    return collector->attacks;
}
int checkCell(AttackCollector* collector, gameField* field, int x, int y) {
    int figure = getValueByCords(field, x, y);

    if(figure == CROSS || figure == ZERO) {
        if(collector->figure != figure) {
            addAttack(collector);
            return figure;
        }else {
            collector->curAttack->power++;
            collector->attackPlace++;
        }
    }else if(figure == BORDER) {
        addAttack(collector);
        return figure;
    }else {
        if(collector->curAttack->power) {
            collector->curAttack->potential++;
            addAttack(collector);
            collector->curAttack = newAttack();
            collector->curAttack->potential++;
        }
        collector->curAttack->divider++;
        collector->attackPlace++;
    }
    if(collector->distance == 4 && figure == collector->figure) {
        collector->checkBorder = 1;
    }else if(collector->distance == 5) {
        if(collector->checkBorder) {
            if(figure == collector->figure || figure == 0)
                collector->curAttack->potential++;
            addAttack(collector);
        }
        return figure;
    }
    collector->distance++;
    return 0;
}
void addAttack(AttackCollector* collector) {
    ++collector->attackCount;
    collector->attacks = (Attack**)realloc(collector->attacks, collector->attackCount*sizeof(Attack*));
    collector->attacks[collector->attackCount - 1] = collector->curAttack;
}
void turnAround(AttackCollector* collector) {
    --collector->attackCount;
    collector->distance = 1;
    collector->checkBorder = 0;
    collector->curAttack = collector->attacks[0];
    collector->attacks = (Attack**)realloc(collector->attacks + 1, collector->attackCount*sizeof(Attack*));
}

Attack** collectAttacksOnLine(gameField* field,
                          int curX, int curY, int figure, int dX, int dY) {
    AttackCollector* collector = newAttackCollector();
    getAttacks(collector, field, curX, curY, figure, dX, dY);
    return filteredAttacks(collector);
}
Attack** filteredAttacks(AttackCollector* collector) {
    AttackCollector* costyl = newAttackCollector();
    if(collector->attackPlace >= 5) {
        for(int i = 0; i < collector->attackCount; i++) {
            if(collector->attacks[i]->power && collector->attacks[i]->potential ||
                    collector->attacks[i]->power >= 5) {
                collector->curAttack = collector->attacks[i];
                addAttack(costyl);
            }
        }
    }
    free(collector);

    return costyl->attacks;
}
AttackCollection* getAllAttacks(gameField* field, int xCord, int yCord) {
    if(getValueByCords(field, xCord, yCord)) return NULL;
    AttackCollection* result = newCollection();

    result->attacksX[0] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, 0);
    result->attacksX[1] = collectAttacksOnLine(field, xCord, yCord, CROSS, 0, 1);
    result->attacksX[2] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, -1);
    result->attacksX[3] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, 1);

    result->attacksY[0] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, 0);
    result->attacksY[1] = collectAttacksOnLine(field, xCord, yCord, ZERO, 0, 1);
    result->attacksY[2] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, -1);
    result->attacksY[3] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, 1);

    return result;
}
AttackCollection* newCollection() {
    return (AttackCollection*)malloc(sizeof(AttackCollection));
}

int isBreakPoint(AttackCollector* collector) {
    if(!collector || !collector->attackCount) return 0;
    Attack* centAttack;

    for(int i = 0; i < collector->attackCount; i++) {
        if(collector->attacks[i]->divider == 1) centAttack = collector->attacks[i];
    }

    if(centAttack->power >=4) return 1;
    if(centAttack->power >= 3 && centAttack->potential ==  2) return 1;

    for(int i = 0; i < collector->attackCount; i++) {
        int score = centAttack->power;
        if(collector->attacks[i]->divider == 2) {
            if(centAttack->potential == 2 && collector->attacks[i]->potential == 2) ++score;
            if(score + collector->attacks[i]->power >= 4) return 1;
        }
    }
    return 0;
}
int countWeight(gameField* field, int xCord, int yCord) {
    AttackCollection* attackCollection = getAllAttacks(field, xCord, yCord);
    if(!attackCollection) return 0;
    int weight = 0;
    //TODO
    return 1;
}