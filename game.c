//
// Created by hubbyk on 26.04.2020.
//

#include "game.h"
#include "backfield.h"
#include "frontfield.h"
#include "player.h"

#include <malloc.h>
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>    /*Для Linux и Windows*/
#else
#include <GLUT/GLUT.h>  /*Для Mac OS*/
#endif

gameSettings* load(int argc, char * argv[]) {
    gameSettings *settings = newSettings(); //создаем новую структуру настроек
    //задаем настройки по умолчанию
    setCountToWin(settings, 3);
    setFieldHeight(settings, 3);
    setFieldLength(settings, 3);
    setPlayers(settings, newPlayer("Player1"), newPlayer("Bot"));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); /*Включаем двойную буферизацию и четырехкомпонентный цвет*/

    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL lesson 1");

    return settings;
}

int startGame(gameSettings *settings) {
    printf("Game Started\n");
    //TODO
    return 1;
}

gameSettings* newSettings() {
    gameSettings *settings = (gameSettings*) malloc(sizeof(*settings));
    return settings;
}

void printSettings(gameSettings* settings) {
    printf("Field size: %dx%d\nCount to win: %d\n", getFieldHeight(settings), getFieldLength(settings), getCountToWin(settings));
    printf("Players: %s vs %s\n", getName(getPlayerHuman(settings)), getName(getPlayerBot(settings)));
}

void changeCurrentGlobalSettings(gameSettings* settings) {
    int fieldHeight, fieldLength, countToWin;
    char human[30] = {'\0'};
    printSettings(settings);

    printf("Enter field size: ");
    scanf("%d %d", &fieldLength, &fieldHeight);
    printf("Enter count to win: ");
    scanf("%d", &countToWin);
    printf("Enter player Name: ");
    scanf("%s", human);

    setFieldLength(settings, fieldLength);
    setFieldHeight(settings, fieldHeight);
    setCountToWin(settings, countToWin);
    setPlayers(settings, newPlayer(human), newPlayer("Bot"));
}

void setFieldHeight(gameSettings* settings, int fieldHeight) {
    settings->fieldHeight = fieldHeight;
}
void setFieldLength(gameSettings* settings, int fieldLength) {
    settings->fieldLength = fieldLength;
}
void setCountToWin(gameSettings* settings, int countToWin) {
    settings->countToWin = countToWin;
}
void setPlayers(gameSettings* settings, player *human, player *bot) {
    settings->human = human;
    settings->bot = bot;
}

int getFieldHeight(gameSettings* settings) {
    return settings->fieldHeight;
}
int getFieldLength(gameSettings* settings) {
    return settings->fieldLength;
}
int getCountToWin(gameSettings* settings) {
    return settings->countToWin;
}
player* getPlayerHuman(gameSettings* settings) {
    return settings->human;
}
player* getPlayerBot(gameSettings* settings) {
    return settings->bot;
}