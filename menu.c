//
// Created by hubbyk on 30.04.2020.
//

#include "menu.h"
#include <stdio.h>
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>    /*Для Linux и Windows*/
#else
#include <GLUT/GLUT.h>  /*Для Mac OS*/
#endif

void outGlobalMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(250, 450);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(250, 150);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(550, 150);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(550, 450);
    glEnd();

    glutSwapBuffers();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(250, 450);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(250, 150);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(550, 150);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(550, 450);
    glEnd();

    glutSwapBuffers();
}
