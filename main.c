#include <stdio.h>
#include "game.h"
#include "menu.h"
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>    /*Для Linux и Windows*/
#else
#include <GLUT/GLUT.h>  /*Для Mac OS*/
#endif

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char * argv[]) {
    int userChoice = 1; //выбор пользователя - закон...
    gameSettings *settings = load(argc, argv);


    glutReshapeFunc(reshape);
    glutDisplayFunc(outGlobalMenu);

    glutMainLoop();

//    while(userChoice) {
//        userChoice = outGlobalMenu();
//
//        switch (userChoice) {
//            case startNewGame:
//                startGame(settings);
//                break;
//            case changeSettings:
//                changeCurrentGlobalSettings(settings);
//                break;
//            case outAuthors:
//                printf("Roma and Vasya\n");
//                break;
//            case exitG:
//                break;
//            default:
//                printf("blablabla");
//                break;
//        }
//    }


    return 0;
}
