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

Attack* newAttack() {
    Attack* new = (Attack*)malloc(sizeof(Attack));
    new->divider = 1;
    new->power = 1;
    new->potential = 0;
    new->next = NULL;
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
    new->attacks = NULL;
    new->distance = 1;
    new->curAttack = newAttack();
    new->checkBorder = 0;
    new->attackPlace = 1;
    return new;
}

Attack* getAttacks(AttackCollector* collector, gameField* field,
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
        return 1;
    }
    collector->distance++;
    return 0;
}
void addAttack(AttackCollector* collector) {
    Attack* cur = collector->attacks;
    Attack* prevAttack;
    if(!cur) {
        collector->attacks = collector->curAttack;
    } else {
        while (cur) {
            prevAttack = cur;
            cur = cur->next;
        }
        prevAttack->next = collector->curAttack;
    }
}
void turnAround(AttackCollector* collector) {
    collector->distance = 1;
    collector->checkBorder = 0;
    collector->curAttack = collector->attacks;
    collector->attacks = collector->attacks->next;
    collector->curAttack->next = NULL;
}

Attack* collectAttacksOnLine(gameField* field,
                          int curX, int curY, int figure, int dX, int dY) {
    AttackCollector* collector = newAttackCollector();
    getAttacks(collector, field, curX, curY, figure, dX, dY);
    return filteredAttacks(collector);
}
Attack* filteredAttacks(AttackCollector* collector) {
    AttackCollector* costyl = newAttackCollector();
    if(collector->attackPlace >= 5) {
        for(Attack* attack = collector->attacks; attack;) {
            if(attack->power && attack->potential ||
                    attack->power >= 5) {
                Attack* atkCopy = newAttack();
                memcpy(atkCopy, attack, sizeof(Attack));
                atkCopy->next = NULL;
                costyl->curAttack = atkCopy;
                addAttack(costyl);
            }
            attack = attack->next;
        }
    }
    free(collector);

    return costyl->attacks;
}
AttackCollection* getAllAttacks(gameField* field, int xCord, int yCord) {
    if(getValueByCords(field, xCord, yCord)) return NULL;
    AttackCollection* result = newCollection();

    result->attacksCross[0] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, 0);
    result->attacksCross[1] = collectAttacksOnLine(field, xCord, yCord, CROSS, 0, 1);
    result->attacksCross[2] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, -1);
    result->attacksCross[3] = collectAttacksOnLine(field, xCord, yCord, CROSS, 1, 1);

    result->attacksZero[0] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, 0);
    result->attacksZero[1] = collectAttacksOnLine(field, xCord, yCord, ZERO, 0, 1);
    result->attacksZero[2] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, -1);
    result->attacksZero[3] = collectAttacksOnLine(field, xCord, yCord, ZERO, 1, 1);

    return result;
}
AttackCollection* newCollection() {
    return (AttackCollection*)malloc(sizeof(AttackCollection));
}

int isBreakPoint(Attack* attacks) {
    if(!attacks) return 0;
    Attack* centAttack;

    for(Attack* attack = attacks; attack;) {
        if(attack->divider == 1) centAttack = attack;
        attack = attack->next;
    }

    if(centAttack->power >=4) return 1;
    if(centAttack->power >= 3 && centAttack->potential ==  2) return 1;

    for(Attack* attack = attacks; attack;) {
        int score = centAttack->power;
        if(attack->divider == 2) {
            if(centAttack->potential == 2 && attack->potential == 2) ++score;
            if(score + attack->power >= 4) return 1;
        }
        attack = attack->next;
    }
    return 0;
}
int countWeight(gameField* field, int xCord, int yCord) {
    AttackCollection* attackCollection = getAllAttacks(field, xCord, yCord);
    if(!attackCollection) return 0;
    int weight = 0;

    weight += count(attackCollection->attacksZero, ZERO);
    weight += count(attackCollection->attacksCross, CROSS);

    return weight;
}

int count(Attack** attacks, int figure) {
    int weight = 0, breakPoints = 0;

    for(int i = 0; i < 4; i++) {
        if(isBreakPoint(attacks[i])) {
            if(++breakPoints == 2) {
                weight += 100;
                return weight;
            }
        }
        for(Attack* attack= attacks[i]; attack;) {
            if(attack->power > 5) attack->power = 5;
            if(attack->power == 5 && figure == ZERO) weight += 100;
            weight += countAttackWeight(attack, 5);
            attack = attack->next;
        }
    }

    return weight;
}

Attack* getAttack(Attack* start, int index) {
    for(int i = 0; i < index && start; i++, start = start->next) {
        if(i == index) return start;
    }
    return NULL;
}

void godCreation(gameField* field, int lastX, int lastY, int* resX, int* resY) {
    int maxWeight = 0, curWeight, resultX, resultY;

    for(int i = 0; i < field->size; i++) {
        for (int j = 0; j < field->size; j++) {
            curWeight = countWeight(field, j, i);
            if(curWeight > maxWeight) {
                maxWeight = curWeight;
                resultX = j; resultY = i;
            }
        }
    }
    *resX = resultX; *resY = resultY;
    writeValue(field, resultX, resultY, ZERO);
}