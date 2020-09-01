#include "game.h"
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>    /*Для Linux и Windows*/
#else
#include <GLUT/GLUT.h>  /*Для Mac OS*/
#endif

GAME *thisGame = NULL;
int delta=0;

char win[10]="Win! \0";
char lose[10]="Lose :( \0";
char raw[10]="Raw! \0";


float coord = 435, edge=327, Sedge=327;
char Line_Length[100]={'\0'};
char Side_Length[100]={'\0'};
char gamer_name[100]="Enter your name: \0";
int znak=0;
int isRaw = 0;
int gameResult = 0;

int global_x=0, global_y=0, temp_global_x=0, temp_global_y=0;

int local_x=0, local_y=0, temp_local_x=0, temp_local_y=0;


float r0=0.6f,g0=0.6f,b0=0.6f,
        r=1,g=0,b=0,
        r1=0,g1=1,b1=1,
        r2=0,g2=1,b2=1,
        r3=0,g3=1,b3=1,
        r4=0,g4=1,b4=1,
        rs1=1,gs1=0,bs1=0,
        rs2=1,gs2=1,bs2=1,
        rs3=1,gs3=1,bs3=1,
        rs4=1,gs4=1,bs4=1;

float field_y=800,field_x=0;
float cur_x=0, cur_y=800;

enum {GAMER, BOT};

struct {
    int inside_set;
    int number_string;
    int game_on;
    int enter_name;
    int start_game;
}global_menu;

struct {
    int first_move;
    int difficulty;
    int line_length;
    int side_length;
}flag_settings;

gameSettings* settings = NULL;
tableLine* ratingTable = NULL;

void reshape (int w, int h)
{

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void enter_your_name (float x, float y)
{
    int j = strlen(gamer_name);
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; i < j; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gamer_name[i]);
    }
}

void print_enter_your_name() {
    glClearColor(0.1,0.1,0.1,0.0f);
    glLineWidth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    enter_your_name(200,400);
    glLineWidth(40);
    glutSwapBuffers ();
};

void print_game_result(float x, float y, char *str){
    int j =strlen(str);
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    for (int i = 0; i < j; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

void game_result(){
    glClearColor(0.1,0.1,0.1,0.0f);
    glLineWidth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //print_text(100,700);
    glutSwapBuffers ();
}


void print_text (float x, float y)
{

    float temp_x=0, temp_y=0;
    FILE *file=fopen("ratings.txt", "rb");
    char str[10000]={'\0'};
    int c, i=0;
    str[i++]=' ';
    c=fgetc(file);
    str[i++]=c;

    while ((c = getc(file)) != EOF) {
        str[i++] = c;
    }
    str[i] = 0;

    int j = strlen(str);
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);

    for (int i = 0; i < j; i++)
    {
       if(str[i]=='\n'){
           y-=50;
           glRasterPos2f(x, y);
       }
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

void rate_table(){
    glClearColor(0.1,0.1,0.1,0.0f);
    glLineWidth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    print_text(100,700);
    glutSwapBuffers ();
}

void drawing_main_menu_one_dark()
{
    glClearColor(0.1,0.1,0.1,0.0f);
    glLineWidth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(r0,g0,b0);
    glBegin(GL_QUADS);///слово ПРОДОЛЖИТЬ///буква П
    glVertex2f(42,500);
    glVertex2f(45,500);
    glVertex2f(45,470);
    glVertex2f(42,470);
    glVertex2f(45,500);
    glVertex2f(55,500);
    glVertex2f(55,497);
    glVertex2f(45,497);
    glVertex2f(55,500);
    glVertex2f(58,500);
    glVertex2f(58,470);
    glVertex2f(55,470);
    glVertex2f(68,500);////буква Р
    glVertex2f(71,500);
    glVertex2f(71,470);
    glVertex2f(68,470);
    glVertex2f(69,500);
    glVertex2f(79,500);
    glVertex2f(79,497);
    glVertex2f(69,497);
    glVertex2f(79,499);
    glVertex2f(82,499);
    glVertex2f(82,484);
    glVertex2f(79,484);
    glVertex2f(79,483);
    glVertex2f(68,483);
    glVertex2f(68,486);
    glVertex2f(79,486);
    glVertex2f(94,500);///буква О
    glVertex2f(105,500);
    glVertex2f(105,497);
    glVertex2f(94,497);
    glVertex2f(94,470);
    glVertex2f(105,470);
    glVertex2f(105,473);
    glVertex2f(94,473);
    glVertex2f(92,496);
    glVertex2f(95,496);
    glVertex2f(95,474);
    glVertex2f(92,474);
    glVertex2f(93,498);
    glVertex2f(96,498);
    glVertex2f(96,495);
    glVertex2f(93,495);
    glVertex2f(93,472);
    glVertex2f(96,472);
    glVertex2f(96,475);
    glVertex2f(93,475);
    glVertex2f(107,496);
    glVertex2f(104,496);
    glVertex2f(104,474);
    glVertex2f(107,474);
    glVertex2f(106,498);
    glVertex2f(103,498);
    glVertex2f(103,495);
    glVertex2f(106,495);
    glVertex2f(106,472);
    glVertex2f(103,472);
    glVertex2f(103,475);
    glVertex2f(106,475);
    glVertex2f(117,470);///буква Д
    glVertex2f(120,470);
    glVertex2f(120,474);
    glVertex2f(117,474);
    glVertex2f(133,470);
    glVertex2f(136,470);
    glVertex2f(136,474);
    glVertex2f(133,474);
    glVertex2f(117,474);
    glVertex2f(136,474);
    glVertex2f(136,477);
    glVertex2f(117,477);
    glVertex2f(133,474);
    glVertex2f(130,474);
    glVertex2f(130,500);
    glVertex2f(133,500);
    glVertex2f(130,500);
    glVertex2f(125,500);
    glVertex2f(125,497);
    glVertex2f(130,497);
    glVertex2f(124,498);
    glVertex2f(127,498);
    glVertex2f(127,495);
    glVertex2f(124,495);
    glVertex2f(123,491);
    glVertex2f(126,491);
    glVertex2f(126,495);
    glVertex2f(123,495);
    glVertex2f(122,491);
    glVertex2f(125,491);
    glVertex2f(125,488);
    glVertex2f(122,488);
    glVertex2f(121,484);
    glVertex2f(124,484);
    glVertex2f(124,488);
    glVertex2f(121,488);
    glVertex2f(120,484);
    glVertex2f(123,484);
    glVertex2f(123,481);
    glVertex2f(120,481);
    glVertex2f(119,477);
    glVertex2f(122,477);
    glVertex2f(122,481);
    glVertex2f(119,481);
    glVertex2f(148,500);///буква О
    glVertex2f(159,500);
    glVertex2f(159,497);
    glVertex2f(148,497);
    glVertex2f(148,470);
    glVertex2f(159,470);
    glVertex2f(159,473);
    glVertex2f(148,473);
    glVertex2f(146,496);
    glVertex2f(149,496);
    glVertex2f(149,474);
    glVertex2f(146,474);
    glVertex2f(147,498);
    glVertex2f(150,498);
    glVertex2f(150,495);
    glVertex2f(147,495);
    glVertex2f(147,472);
    glVertex2f(150,472);
    glVertex2f(150,475);
    glVertex2f(147,475);
    glVertex2f(161,496);
    glVertex2f(158,496);
    glVertex2f(158,474);
    glVertex2f(161,474);
    glVertex2f(160,498);
    glVertex2f(157,498);
    glVertex2f(157,495);
    glVertex2f(160,495);
    glVertex2f(160,472);
    glVertex2f(157,472);
    glVertex2f(157,475);
    glVertex2f(160,475);
    glVertex2f(175,500);///буква Л
    glVertex2f(178,500);
    glVertex2f(178,476);
    glVertex2f(175,476);
    glVertex2f(177,473);
    glVertex2f(174,473);
    glVertex2f(174,476);
    glVertex2f(177,476);
    glVertex2f(175,471);
    glVertex2f(172,471);
    glVertex2f(172,474);
    glVertex2f(175,474);
    glVertex2f(173,470);
    glVertex2f(171,470);
    glVertex2f(171,473);
    glVertex2f(173,473);
    glVertex2f(178,500);
    glVertex2f(188,500);
    glVertex2f(188,497);
    glVertex2f(178,497);
    glVertex2f(188,500);
    glVertex2f(191,500);
    glVertex2f(191,470);
    glVertex2f(188,470);
    glVertex2f(201,470);///буква Ж
    glVertex2f(204,470);
    glVertex2f(204,500);
    glVertex2f(201,500);
    glVertex2f(211,470);
    glVertex2f(214,470);
    glVertex2f(214,500);
    glVertex2f(211,500);
    glVertex2f(221,470);
    glVertex2f(224,470);
    glVertex2f(224,500);
    glVertex2f(221,500);
    glVertex2f(204,484);
    glVertex2f(221,484);
    glVertex2f(221,487);
    glVertex2f(204,487);
    glVertex2f(234,500);///буква И
    glVertex2f(237,500);
    glVertex2f(237,470);
    glVertex2f(234,470);
    glVertex2f(248,500);
    glVertex2f(251,500);
    glVertex2f(251,470);
    glVertex2f(248,470);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(237,470);
    glVertex2f(248,490);
    glVertex2f(237,471);
    glVertex2f(248,491);
    glVertex2f(237,472);
    glVertex2f(248,492);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(264,470);///буква Т
    glVertex2f(267,470);
    glVertex2f(267,500);
    glVertex2f(264,500);
    glVertex2f(258,500);
    glVertex2f(273,500);
    glVertex2f(273,497);
    glVertex2f(258,497);
    glVertex2f(280,500);///буква Ь
    glVertex2f(283,500);
    glVertex2f(283,470);
    glVertex2f(280,470);
    glVertex2f(283,470);
    glVertex2f(293,470);
    glVertex2f(293,473);
    glVertex2f(283,473);
    glVertex2f(293,471);
    glVertex2f(296,471);
    glVertex2f(296,486);
    glVertex2f(293,486);
    glVertex2f(293,485);
    glVertex2f(283,485);
    glVertex2f(283,488);
    glVertex2f(293,488);





    glColor3f(r,g,b);
    glVertex2f(42,450);///фраза НОВАЯ ИГРА///буква Н
    glVertex2f(45,450);
    glVertex2f(45,420);
    glVertex2f(42,420);
    glVertex2f(56,450);
    glVertex2f(59,450);
    glVertex2f(59,420);
    glVertex2f(56,420);
    glVertex2f(45,434);
    glVertex2f(56,434);
    glVertex2f(56,437);
    glVertex2f(45,437);
    glVertex2f(71,450);///буква О
    glVertex2f(82,450);
    glVertex2f(82,447);
    glVertex2f(71,447);
    glVertex2f(71,420);
    glVertex2f(82,420);
    glVertex2f(82,423);
    glVertex2f(71,423);
    glVertex2f(69,446);
    glVertex2f(72,446);
    glVertex2f(72,424);
    glVertex2f(69,424);
    glVertex2f(70,448);
    glVertex2f(73,448);
    glVertex2f(73,445);
    glVertex2f(70,445);
    glVertex2f(70,422);
    glVertex2f(73,422);
    glVertex2f(73,425);
    glVertex2f(70,425);
    glVertex2f(84,446);
    glVertex2f(81,446);
    glVertex2f(81,424);
    glVertex2f(84,424);
    glVertex2f(83,448);
    glVertex2f(80,448);
    glVertex2f(80,445);
    glVertex2f(83,445);
    glVertex2f(83,422);
    glVertex2f(80,422);
    glVertex2f(80,425);
    glVertex2f(83,425);
    glVertex2f(94,450);///буква В
    glVertex2f(97,450);
    glVertex2f(97,420);
    glVertex2f(94,420);
    glVertex2f(97,420);
    glVertex2f(107,420);
    glVertex2f(107,423);
    glVertex2f(97,423);
    glVertex2f(107,421);
    glVertex2f(110,421);
    glVertex2f(110,436);
    glVertex2f(107,436);
    glVertex2f(107,435);
    glVertex2f(97,435);
    glVertex2f(97,438);
    glVertex2f(107,438);
    glVertex2f(94,450);
    glVertex2f(105,450);
    glVertex2f(105,447);
    glVertex2f(94,447);
    glVertex2f(104,447);
    glVertex2f(107,447);
    glVertex2f(107,436);
    glVertex2f(104,436);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(120,420);///буква А
    glVertex2f(130,450);
    glVertex2f(121,420);
    glVertex2f(130,449);
    glVertex2f(122,420);
    glVertex2f(130,448);
    glVertex2f(123,420);
    glVertex2f(130,447);
    glVertex2f(124,420);
    glVertex2f(130,446);
    glVertex2f(130,450);
    glVertex2f(140,420);
    glVertex2f(130,449);
    glVertex2f(139,420);
    glVertex2f(130,448);
    glVertex2f(138,420);
    glVertex2f(130,447);
    glVertex2f(137,420);
    glVertex2f(130,446);
    glVertex2f(136,420);
    glVertex2f(124,428);
    glVertex2f(136,428);
    glVertex2f(124,429);
    glVertex2f(136,429);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(164,420);///буква Я
    glVertex2f(167,420);
    glVertex2f(167,450);
    glVertex2f(164,450);
    glVertex2f(164,450);
    glVertex2f(155,450);
    glVertex2f(155,447);
    glVertex2f(164,447);
    glVertex2f(152,449);
    glVertex2f(155,449);
    glVertex2f(155,436);
    glVertex2f(152,436);
    glVertex2f(155,435);
    glVertex2f(164,435);
    glVertex2f(164,438);
    glVertex2f(155,438);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(150,420);
    glVertex2f(164,434);
    glVertex2f(151,420);
    glVertex2f(164,433);
    glVertex2f(152,420);
    glVertex2f(164,432);
    glVertex2f(153,420);
    glVertex2f(164,431);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(187,450);///буква И
    glVertex2f(190,450);
    glVertex2f(190,420);
    glVertex2f(187,420);
    glVertex2f(201,450);
    glVertex2f(204,450);
    glVertex2f(204,420);
    glVertex2f(201,420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(190,420);
    glVertex2f(201,440);
    glVertex2f(190,421);
    glVertex2f(201,441);
    glVertex2f(190,422);
    glVertex2f(201,442);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(214,450);////буква Г
    glVertex2f(217,450);
    glVertex2f(217,420);
    glVertex2f(214,420);
    glVertex2f(217,450);
    glVertex2f(228,450);
    glVertex2f(228,447);
    glVertex2f(217,447);
    glVertex2f(237,450);////буква Р
    glVertex2f(240,450);
    glVertex2f(240,420);
    glVertex2f(237,420);
    glVertex2f(238,450);
    glVertex2f(248,450);
    glVertex2f(248,447);
    glVertex2f(238,447);
    glVertex2f(248,449);
    glVertex2f(251,449);
    glVertex2f(251,434);
    glVertex2f(248,434);
    glVertex2f(248,433);
    glVertex2f(237,433);
    glVertex2f(237,436);
    glVertex2f(248,436);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(261,420);///буква А
    glVertex2f(271,450);
    glVertex2f(262,420);
    glVertex2f(271,449);
    glVertex2f(263,420);
    glVertex2f(271,448);
    glVertex2f(264,420);
    glVertex2f(271,447);
    glVertex2f(265,420);
    glVertex2f(271,446);
    glVertex2f(271,450);
    glVertex2f(281,420);
    glVertex2f(271,449);
    glVertex2f(280,420);
    glVertex2f(271,448);
    glVertex2f(279,420);
    glVertex2f(271,447);
    glVertex2f(278,420);
    glVertex2f(271,446);
    glVertex2f(277,420);
    glVertex2f(265,428);
    glVertex2f(277,428);
    glVertex2f(265,429);
    glVertex2f(277,429);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(r1,g1,b1);
    glVertex2f(42,400);///слово НАСТРОЙКИ///буква Н
    glVertex2f(45,400);
    glVertex2f(45,370);
    glVertex2f(42,370);
    glVertex2f(56,400);
    glVertex2f(59,400);
    glVertex2f(59,370);
    glVertex2f(56,370);
    glVertex2f(45,384);
    glVertex2f(56,384);
    glVertex2f(56,387);
    glVertex2f(45,387);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(69,370);///буква А
    glVertex2f(79,400);
    glVertex2f(70,370);
    glVertex2f(79,399);
    glVertex2f(71,370);
    glVertex2f(79,398);
    glVertex2f(72,370);
    glVertex2f(79,397);
    glVertex2f(73,370);
    glVertex2f(79,396);
    glVertex2f(79,400);
    glVertex2f(89,370);
    glVertex2f(79,399);
    glVertex2f(88,370);
    glVertex2f(79,398);
    glVertex2f(87,370);
    glVertex2f(79,397);
    glVertex2f(86,370);
    glVertex2f(79,396);
    glVertex2f(85,370);
    glVertex2f(73,378);
    glVertex2f(85,378);
    glVertex2f(73,379);
    glVertex2f(85,379);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(100,400);///буква С
    glVertex2f(112,400);
    glVertex2f(112,397);
    glVertex2f(100,397);
    glVertex2f(100,370);
    glVertex2f(112,370);
    glVertex2f(112,373);
    glVertex2f(100,373);
    glVertex2f(98,396);
    glVertex2f(101,396);
    glVertex2f(101,374);
    glVertex2f(98,374);
    glVertex2f(99,398);
    glVertex2f(102,398);
    glVertex2f(102,395);
    glVertex2f(99,395);
    glVertex2f(99,372);
    glVertex2f(102,372);
    glVertex2f(102,375);
    glVertex2f(99,375);
    glVertex2f(128,370);///буква Т
    glVertex2f(131,370);
    glVertex2f(131,400);
    glVertex2f(128,400);
    glVertex2f(122,400);
    glVertex2f(137,400);
    glVertex2f(137,397);
    glVertex2f(122,397);
    glVertex2f(147,400);////буква Р
    glVertex2f(150,400);
    glVertex2f(150,370);
    glVertex2f(147,370);
    glVertex2f(148,400);
    glVertex2f(158,400);
    glVertex2f(158,397);
    glVertex2f(148,397);
    glVertex2f(158,399);
    glVertex2f(161,399);
    glVertex2f(161,384);
    glVertex2f(158,384);
    glVertex2f(158,383);
    glVertex2f(147,383);
    glVertex2f(147,386);
    glVertex2f(158,386);
    glVertex2f(172,400);///буква О
    glVertex2f(183,400);
    glVertex2f(183,397);
    glVertex2f(172,397);
    glVertex2f(172,370);
    glVertex2f(183,370);
    glVertex2f(183,373);
    glVertex2f(172,373);
    glVertex2f(170,396);
    glVertex2f(173,396);
    glVertex2f(173,374);
    glVertex2f(170,374);
    glVertex2f(171,398);
    glVertex2f(174,398);
    glVertex2f(174,395);
    glVertex2f(171,395);
    glVertex2f(171,372);
    glVertex2f(174,372);
    glVertex2f(174,375);
    glVertex2f(171,375);
    glVertex2f(185,396);
    glVertex2f(182,396);
    glVertex2f(182,374);
    glVertex2f(185,374);
    glVertex2f(184,398);
    glVertex2f(181,398);
    glVertex2f(181,395);
    glVertex2f(184,395);
    glVertex2f(184,372);
    glVertex2f(181,372);
    glVertex2f(181,375);
    glVertex2f(184,375);
    glVertex2f(195,400);///буква Й
    glVertex2f(198,400);
    glVertex2f(198,370);
    glVertex2f(195,370);
    glVertex2f(209,400);
    glVertex2f(212,400);
    glVertex2f(212,370);
    glVertex2f(209,370);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(198,370);
    glVertex2f(209,390);
    glVertex2f(198,371);
    glVertex2f(209,391);
    glVertex2f(198,372);
    glVertex2f(209,392);
    glVertex2f(203,402);
    glVertex2f(204,402);
    glVertex2f(202,403);
    glVertex2f(205,403);
    glVertex2f(201,404);
    glVertex2f(206,404);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(222,400);///буква К
    glVertex2f(225,400);
    glVertex2f(225,370);
    glVertex2f(222,370);
    glVertex2f(225,387);
    glVertex2f(227,387);
    glVertex2f(227,384);
    glVertex2f(225,384);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(227,387);
    glVertex2f(234,400);
    glVertex2f(227,387);
    glVertex2f(235,400);
    glVertex2f(227,386);
    glVertex2f(236,400);
    glVertex2f(227,386);
    glVertex2f(237,400);
    glVertex2f(227,385);
    glVertex2f(234,370);
    glVertex2f(227,385);
    glVertex2f(235,370);
    glVertex2f(227,384);
    glVertex2f(236,370);
    glVertex2f(227,384);
    glVertex2f(237,370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(228,387);
    glVertex2f(228,387);
    glVertex2f(228,384);
    glVertex2f(228,384);
    glVertex2f(247,400);///буква И
    glVertex2f(250,400);
    glVertex2f(250,370);
    glVertex2f(247,370);
    glVertex2f(261,400);
    glVertex2f(264,400);
    glVertex2f(264,370);
    glVertex2f(261,370);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(250,370);
    glVertex2f(261,390);
    glVertex2f(250,371);
    glVertex2f(261,391);
    glVertex2f(250,372);
    glVertex2f(261,392);
    glEnd();
    glColor3f(r2,g2,b2);
    glBegin(GL_QUADS);
    glVertex2f(44,350);///фраза ОБ ИГРЕ///буква О
    glVertex2f(55,350);
    glVertex2f(55,347);
    glVertex2f(44,347);
    glVertex2f(44,320);
    glVertex2f(55,320);
    glVertex2f(55,323);
    glVertex2f(44,323);
    glVertex2f(42,346);
    glVertex2f(45,346);
    glVertex2f(45,324);
    glVertex2f(42,324);
    glVertex2f(43,348);
    glVertex2f(46,348);
    glVertex2f(46,345);
    glVertex2f(43,345);
    glVertex2f(43,322);
    glVertex2f(46,322);
    glVertex2f(46,325);
    glVertex2f(43,325);
    glVertex2f(57,346);
    glVertex2f(54,346);
    glVertex2f(54,324);
    glVertex2f(57,324);
    glVertex2f(56,348);
    glVertex2f(53,348);
    glVertex2f(53,345);
    glVertex2f(56,345);
    glVertex2f(56,322);
    glVertex2f(53,322);
    glVertex2f(53,325);
    glVertex2f(56,325);
    glVertex2f(67,350);///буква Б
    glVertex2f(70,350);
    glVertex2f(70,320);
    glVertex2f(67,320);
    glVertex2f(70,320);
    glVertex2f(80,320);
    glVertex2f(80,323);
    glVertex2f(70,323);
    glVertex2f(80,321);
    glVertex2f(83,321);
    glVertex2f(83,336);
    glVertex2f(80,336);
    glVertex2f(80,335);
    glVertex2f(70,335);
    glVertex2f(70,338);
    glVertex2f(80,338);
    glVertex2f(67,350);
    glVertex2f(81,350);
    glVertex2f(81,347);
    glVertex2f(67,347);
    glVertex2f(103,350);///буква И
    glVertex2f(106,350);
    glVertex2f(106,320);
    glVertex2f(103,320);
    glVertex2f(117,350);
    glVertex2f(120,350);
    glVertex2f(120,320);
    glVertex2f(117,320);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(106,320);
    glVertex2f(117,340);
    glVertex2f(106,321);
    glVertex2f(117,341);
    glVertex2f(106,322);
    glVertex2f(117,342);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(130,350);////буква Г
    glVertex2f(133,350);
    glVertex2f(133,320);
    glVertex2f(130,320);
    glVertex2f(133,350);
    glVertex2f(144,350);
    glVertex2f(144,347);
    glVertex2f(133,347);
    glVertex2f(153,350);////буква Р
    glVertex2f(156,350);
    glVertex2f(156,320);
    glVertex2f(153,320);
    glVertex2f(154,350);
    glVertex2f(164,350);
    glVertex2f(164,347);
    glVertex2f(154,347);
    glVertex2f(164,349);
    glVertex2f(167,349);
    glVertex2f(167,334);
    glVertex2f(164,334);
    glVertex2f(164,333);
    glVertex2f(153,333);
    glVertex2f(153,336);
    glVertex2f(164,336);
    glVertex2f(177,350);////буква Е
    glVertex2f(180,350);
    glVertex2f(180,320);
    glVertex2f(177,320);
    glVertex2f(180,337);
    glVertex2f(192,337);
    glVertex2f(192,334);
    glVertex2f(180,334);
    glVertex2f(180,350);
    glVertex2f(192,350);
    glVertex2f(192,347);
    glVertex2f(180,347);
    glVertex2f(180,323);
    glVertex2f(192,323);
    glVertex2f(192,320);
    glVertex2f(180,320);
    glEnd();
    glColor3f(r3,g3,b3);
    glBegin(GL_QUADS);
    glVertex2f(42,300);///слово РЕЙТИНГ////буква Р
    glVertex2f(45,300);
    glVertex2f(45,270);
    glVertex2f(42,270);
    glVertex2f(43,300);
    glVertex2f(53,300);
    glVertex2f(53,297);
    glVertex2f(43,297);
    glVertex2f(53,299);
    glVertex2f(56,299);
    glVertex2f(56,284);
    glVertex2f(53,284);
    glVertex2f(53,283);
    glVertex2f(42,283);
    glVertex2f(42,286);
    glVertex2f(53,286);
    glVertex2f(66,300);////буква Е
    glVertex2f(69,300);
    glVertex2f(69,270);
    glVertex2f(66,270);
    glVertex2f(69,287);
    glVertex2f(81,287);
    glVertex2f(81,284);
    glVertex2f(69,284);
    glVertex2f(69,300);
    glVertex2f(81,300);
    glVertex2f(81,297);
    glVertex2f(69,297);
    glVertex2f(69,273);
    glVertex2f(81,273);
    glVertex2f(81,270);
    glVertex2f(69,270);
    glVertex2f(91,300);///буква Й
    glVertex2f(94,300);
    glVertex2f(94,270);
    glVertex2f(91,270);
    glVertex2f(105,300);
    glVertex2f(108,300);
    glVertex2f(108,270);
    glVertex2f(105,270);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(94,270);
    glVertex2f(105,290);
    glVertex2f(94,271);
    glVertex2f(105,291);
    glVertex2f(94,272);
    glVertex2f(105,292);
    glVertex2f(99,302);
    glVertex2f(100,302);
    glVertex2f(98,303);
    glVertex2f(101,303);
    glVertex2f(97,304);
    glVertex2f(102,304);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(124,270);///буква Т
    glVertex2f(127,270);
    glVertex2f(127,300);
    glVertex2f(124,300);
    glVertex2f(118,300);
    glVertex2f(133,300);
    glVertex2f(133,297);
    glVertex2f(118,297);
    glVertex2f(143,300);///буква И
    glVertex2f(146,300);
    glVertex2f(146,270);
    glVertex2f(143,270);
    glVertex2f(157,300);
    glVertex2f(160,300);
    glVertex2f(160,270);
    glVertex2f(157,270);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(146,270);
    glVertex2f(157,290);
    glVertex2f(146,271);
    glVertex2f(157,291);
    glVertex2f(146,272);
    glVertex2f(157,292);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(170,300);///буква Н
    glVertex2f(173,300);
    glVertex2f(173,270);
    glVertex2f(170,270);
    glVertex2f(184,300);
    glVertex2f(187,300);
    glVertex2f(187,270);
    glVertex2f(184,270);
    glVertex2f(173,284);
    glVertex2f(184,284);
    glVertex2f(184,287);
    glVertex2f(173,287);
    glVertex2f(197,300);////буква Г
    glVertex2f(200,300);
    glVertex2f(200,270);
    glVertex2f(197,270);
    glVertex2f(200,300);
    glVertex2f(211,300);
    glVertex2f(211,297);
    glVertex2f(200,297);
    glEnd();

    glColor3f(r4,g4,b4);
    glBegin(GL_QUADS);
    glVertex2f(42,250);///слово ВЫХОД///буква В
    glVertex2f(45,250);
    glVertex2f(45,220);
    glVertex2f(42,220);
    glVertex2f(45,220);
    glVertex2f(55,220);
    glVertex2f(55,223);
    glVertex2f(45,223);
    glVertex2f(55,221);
    glVertex2f(58,221);
    glVertex2f(58,236);
    glVertex2f(55,236);
    glVertex2f(55,235);
    glVertex2f(45,235);
    glVertex2f(45,238);
    glVertex2f(55,238);
    glVertex2f(42,250);
    glVertex2f(53,250);
    glVertex2f(53,247);
    glVertex2f(42,247);
    glVertex2f(52,247);
    glVertex2f(55,247);
    glVertex2f(55,236);
    glVertex2f(52,236);
    glVertex2f(68,250);///буква Ы
    glVertex2f(71,250);
    glVertex2f(71,220);
    glVertex2f(68,220);
    glVertex2f(71,220);
    glVertex2f(81,220);
    glVertex2f(81,223);
    glVertex2f(71,223);
    glVertex2f(81,221);
    glVertex2f(84,221);
    glVertex2f(84,236);
    glVertex2f(81,236);
    glVertex2f(81,235);
    glVertex2f(71,235);
    glVertex2f(71,238);
    glVertex2f(81,238);
    glVertex2f(92,250);
    glVertex2f(95,250);
    glVertex2f(95,220);
    glVertex2f(92,220);
    glVertex2f(113,236);
    glVertex2f(116,236);
    glVertex2f(116,235);
    glVertex2f(113,235);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(105,220);///буква Х
    glVertex2f(113,235);
    glVertex2f(106,220);
    glVertex2f(114,235);
    glVertex2f(107,220);
    glVertex2f(115,235);
    glVertex2f(108,220);
    glVertex2f(116,235);
    glVertex2f(121,220);
    glVertex2f(113,235);
    glVertex2f(122,220);
    glVertex2f(114,235);
    glVertex2f(123,220);
    glVertex2f(115,235);
    glVertex2f(124,220);
    glVertex2f(116,235);
    glVertex2f(121,250);
    glVertex2f(113,236);
    glVertex2f(122,250);
    glVertex2f(114,236);
    glVertex2f(123,250);
    glVertex2f(115,236);
    glVertex2f(124,250);
    glVertex2f(116,236);
    glVertex2f(105,250);
    glVertex2f(113,236);
    glVertex2f(106,250);
    glVertex2f(114,236);
    glVertex2f(107,250);
    glVertex2f(115,236);
    glVertex2f(108,250);
    glVertex2f(116,236);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(136,250);///буква О
    glVertex2f(147,250);
    glVertex2f(147,247);
    glVertex2f(136,247);
    glVertex2f(136,220);
    glVertex2f(147,220);
    glVertex2f(147,223);
    glVertex2f(136,223);
    glVertex2f(134,246);
    glVertex2f(137,246);
    glVertex2f(137,224);
    glVertex2f(134,224);
    glVertex2f(135,248);
    glVertex2f(138,248);
    glVertex2f(138,245);
    glVertex2f(135,245);
    glVertex2f(135,222);
    glVertex2f(138,222);
    glVertex2f(138,225);
    glVertex2f(135,225);
    glVertex2f(149,246);
    glVertex2f(146,246);
    glVertex2f(146,224);
    glVertex2f(149,224);
    glVertex2f(148,248);
    glVertex2f(145,248);
    glVertex2f(145,245);
    glVertex2f(148,245);
    glVertex2f(148,222);
    glVertex2f(145,222);
    glVertex2f(145,225);
    glVertex2f(148,225);
    glVertex2f(159,220);///буква Д
    glVertex2f(162,220);
    glVertex2f(162,224);
    glVertex2f(159,224);
    glVertex2f(175,220);
    glVertex2f(178,220);
    glVertex2f(178,224);
    glVertex2f(175,224);
    glVertex2f(159,224);
    glVertex2f(178,224);
    glVertex2f(178,227);
    glVertex2f(159,227);
    glVertex2f(175,224);
    glVertex2f(172,224);
    glVertex2f(172,250);
    glVertex2f(175,250);
    glVertex2f(172,250);
    glVertex2f(167,250);
    glVertex2f(167,247);
    glVertex2f(172,247);
    glVertex2f(166,248);
    glVertex2f(169,248);
    glVertex2f(169,245);
    glVertex2f(166,245);
    glVertex2f(165,241);
    glVertex2f(168,241);
    glVertex2f(168,245);
    glVertex2f(165,245);
    glVertex2f(164,241);
    glVertex2f(167,241);
    glVertex2f(167,238);
    glVertex2f(164,238);
    glVertex2f(163,234);
    glVertex2f(166,234);
    glVertex2f(166,238);
    glVertex2f(163,238);
    glVertex2f(162,234);
    glVertex2f(165,234);
    glVertex2f(165,231);
    glVertex2f(162,231);
    glVertex2f(161,227);
    glVertex2f(164,227);
    glVertex2f(164,231);
    glVertex2f(161,231);


    glEnd();
    glutSwapBuffers ();
}

void draw_about_game () {
    glLineWidth(1);
    glClearColor(0.1,0.1,0.1,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex2f(42,470);///Устюжанинов Р.К.///буква У
    glVertex2f(52,470);
    glVertex2f(52,473);
    glVertex2f(42,473);
    glVertex2f(51,471);
    glVertex2f(55,471);
    glVertex2f(55,476);
    glVertex2f(51,476);
    glVertex2f(54,474);
    glVertex2f(58,474);
    glVertex2f(58,479);
    glVertex2f(54,479);
    glVertex2f(58,477);
    glVertex2f(61,477);
    glVertex2f(61,500);
    glVertex2f(58,500);
    glVertex2f(42,483);
    glVertex2f(45,483);
    glVertex2f(45,500);
    glVertex2f(42,500);
    glVertex2f(43,485);
    glVertex2f(48,485);
    glVertex2f(48,481);
    glVertex2f(43,481);
    glVertex2f(46,482);
    glVertex2f(51,482);
    glVertex2f(51,479);
    glVertex2f(46,479);
    glVertex2f(46,479);
    glVertex2f(58,479);
    glVertex2f(58,482);
    glVertex2f(46,482);
    glVertex2f(73,500);///буква С
    glVertex2f(85,500);
    glVertex2f(85,497);
    glVertex2f(73,497);
    glVertex2f(73,470);
    glVertex2f(85,470);
    glVertex2f(85,473);
    glVertex2f(73,473);
    glVertex2f(71,496);
    glVertex2f(74,496);
    glVertex2f(74,474);
    glVertex2f(71,474);
    glVertex2f(72,498);
    glVertex2f(75,498);
    glVertex2f(75,495);
    glVertex2f(72,495);
    glVertex2f(72,472);
    glVertex2f(75,472);
    glVertex2f(75,475);
    glVertex2f(72,475);
    glVertex2f(101,470);///буква Т
    glVertex2f(104,470);
    glVertex2f(104,500);
    glVertex2f(101,500);
    glVertex2f(95,500);
    glVertex2f(110,500);
    glVertex2f(110,497);
    glVertex2f(95,497);
    glVertex2f(120,470);///буква Ю ///палки
    glVertex2f(123,470);
    glVertex2f(123,500);
    glVertex2f(120,500);
    glVertex2f(123,487);
    glVertex2f(133,487);
    glVertex2f(133,484);
    glVertex2f(123,484);
    glVertex2f(135,500);///кружок
    glVertex2f(146,500);
    glVertex2f(146,497);
    glVertex2f(135,497);
    glVertex2f(135,470);
    glVertex2f(146,470);
    glVertex2f(146,473);
    glVertex2f(135,473);
    glVertex2f(133,496);
    glVertex2f(136,496);
    glVertex2f(136,474);
    glVertex2f(133,474);
    glVertex2f(134,498);
    glVertex2f(137,498);
    glVertex2f(137,495);
    glVertex2f(134,495);
    glVertex2f(134,472);
    glVertex2f(137,472);
    glVertex2f(137,475);
    glVertex2f(134,475);
    glVertex2f(148,496);
    glVertex2f(145,496);
    glVertex2f(145,474);
    glVertex2f(148,474);
    glVertex2f(147,498);
    glVertex2f(144,498);
    glVertex2f(144,495);
    glVertex2f(147,495);
    glVertex2f(147,472);
    glVertex2f(144,472);
    glVertex2f(144,475);
    glVertex2f(147,475);
    glVertex2f(158,470);///буква Ж
    glVertex2f(161,470);
    glVertex2f(161,500);
    glVertex2f(158,500);
    glVertex2f(168,470);
    glVertex2f(171,470);
    glVertex2f(171,500);
    glVertex2f(168,500);
    glVertex2f(178,470);
    glVertex2f(181,470);
    glVertex2f(181,500);
    glVertex2f(178,500);
    glVertex2f(161,484);
    glVertex2f(178,484);
    glVertex2f(178,487);
    glVertex2f(161,487);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(191,470);///буква А
    glVertex2f(201,500);
    glVertex2f(192,470);
    glVertex2f(201,499);
    glVertex2f(193,470);
    glVertex2f(201,498);
    glVertex2f(194,470);
    glVertex2f(201,497);
    glVertex2f(195,470);
    glVertex2f(201,496);
    glVertex2f(201,500);
    glVertex2f(211,470);
    glVertex2f(201,499);
    glVertex2f(210,470);
    glVertex2f(201,498);
    glVertex2f(209,470);
    glVertex2f(201,497);
    glVertex2f(208,470);
    glVertex2f(201,496);
    glVertex2f(207,470);
    glVertex2f(195,478);
    glVertex2f(207,478);
    glVertex2f(195,479);
    glVertex2f(207,479);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(221,500);///буква Н
    glVertex2f(224,500);
    glVertex2f(224,470);
    glVertex2f(221,470);
    glVertex2f(235,500);
    glVertex2f(238,500);
    glVertex2f(238,470);
    glVertex2f(235,470);
    glVertex2f(224,484);
    glVertex2f(235,484);
    glVertex2f(235,487);
    glVertex2f(224,487);
    glVertex2f(248,500);///буква И
    glVertex2f(251,500);
    glVertex2f(251,470);
    glVertex2f(248,470);
    glVertex2f(262,500);
    glVertex2f(265,500);
    glVertex2f(265,470);
    glVertex2f(262,470);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(251,470);
    glVertex2f(262,490);
    glVertex2f(251,471);
    glVertex2f(262,491);
    glVertex2f(251,472);
    glVertex2f(262,492);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(275,500);///буква Н
    glVertex2f(278,500);
    glVertex2f(278,470);
    glVertex2f(275,470);
    glVertex2f(289,500);
    glVertex2f(292,500);
    glVertex2f(292,470);
    glVertex2f(289,470);
    glVertex2f(278,484);
    glVertex2f(289,484);
    glVertex2f(289,487);
    glVertex2f(278,487);
    glVertex2f(304,500);///буква О
    glVertex2f(315,500);
    glVertex2f(315,497);
    glVertex2f(304,497);
    glVertex2f(304,470);
    glVertex2f(315,470);
    glVertex2f(315,473);
    glVertex2f(304,473);
    glVertex2f(302,496);
    glVertex2f(305,496);
    glVertex2f(305,474);
    glVertex2f(302,474);
    glVertex2f(303,498);
    glVertex2f(306,498);
    glVertex2f(306,495);
    glVertex2f(303,495);
    glVertex2f(303,472);
    glVertex2f(306,472);
    glVertex2f(306,475);
    glVertex2f(303,475);
    glVertex2f(317,496);
    glVertex2f(314,496);
    glVertex2f(314,474);
    glVertex2f(317,474);
    glVertex2f(316,498);
    glVertex2f(313,498);
    glVertex2f(313,495);
    glVertex2f(316,495);
    glVertex2f(316,472);
    glVertex2f(313,472);
    glVertex2f(313,475);
    glVertex2f(316,475);
    glVertex2f(327,500);///буква В
    glVertex2f(330,500);
    glVertex2f(330,470);
    glVertex2f(327,470);
    glVertex2f(330,470);
    glVertex2f(340,470);
    glVertex2f(340,473);
    glVertex2f(330,473);
    glVertex2f(340,471);
    glVertex2f(343,471);
    glVertex2f(343,486);
    glVertex2f(340,486);
    glVertex2f(340,485);
    glVertex2f(330,485);
    glVertex2f(330,488);
    glVertex2f(340,488);
    glVertex2f(327,500);
    glVertex2f(338,500);
    glVertex2f(338,497);
    glVertex2f(327,497);
    glVertex2f(337,497);
    glVertex2f(340,497);
    glVertex2f(340,486);
    glVertex2f(337,486);
    glVertex2f(363,500);////буква Р
    glVertex2f(366,500);
    glVertex2f(366,470);
    glVertex2f(363,470);
    glVertex2f(364,500);
    glVertex2f(374,500);
    glVertex2f(374,497);
    glVertex2f(364,497);
    glVertex2f(374,499);
    glVertex2f(377,499);
    glVertex2f(377,484);
    glVertex2f(374,484);
    glVertex2f(374,483);
    glVertex2f(363,483);
    glVertex2f(363,486);
    glVertex2f(374,486);
    glVertex2f(377,470);///ТОЧКА
    glVertex2f(380,470);
    glVertex2f(380,473);
    glVertex2f(377,473);
    glVertex2f(387,500);///буква К
    glVertex2f(390,500);
    glVertex2f(390,470);
    glVertex2f(387,470);
    glVertex2f(390,487);
    glVertex2f(392,487);
    glVertex2f(392,484);
    glVertex2f(390,484);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(392,487);
    glVertex2f(399,500);
    glVertex2f(392,487);
    glVertex2f(400,500);
    glVertex2f(392,486);
    glVertex2f(401,500);
    glVertex2f(392,486);
    glVertex2f(402,500);
    glVertex2f(392,485);
    glVertex2f(399,470);
    glVertex2f(392,485);
    glVertex2f(400,470);
    glVertex2f(392,484);
    glVertex2f(401,470);
    glVertex2f(392,484);
    glVertex2f(402,470);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(409,470);///ТОЧКА
    glVertex2f(412,470);
    glVertex2f(412,473);
    glVertex2f(409,473);
    glVertex2f(42,450);///ПЛОТНИКОВ В.М.///БУКВА П
    glVertex2f(45,450);
    glVertex2f(45,420);
    glVertex2f(42,420);
    glVertex2f(45,450);
    glVertex2f(55,450);
    glVertex2f(55,447);
    glVertex2f(45,447);
    glVertex2f(55,450);
    glVertex2f(58,450);
    glVertex2f(58,420);
    glVertex2f(55,420);
    glVertex2f(72,450);///буква Л
    glVertex2f(75,450);
    glVertex2f(75,426);
    glVertex2f(72,426);
    glVertex2f(74,423);
    glVertex2f(71,423);
    glVertex2f(71,426);
    glVertex2f(74,426);
    glVertex2f(72,421);
    glVertex2f(69,421);
    glVertex2f(69,424);
    glVertex2f(72,424);
    glVertex2f(70,420);
    glVertex2f(68,420);
    glVertex2f(68,423);
    glVertex2f(70,423);
    glVertex2f(75,450);
    glVertex2f(85,450);
    glVertex2f(85,447);
    glVertex2f(75,447);
    glVertex2f(85,450);
    glVertex2f(88,450);
    glVertex2f(88,420);
    glVertex2f(85,420);
    glVertex2f(100,450);///буква О
    glVertex2f(111,450);
    glVertex2f(111,447);
    glVertex2f(100,447);
    glVertex2f(100,420);
    glVertex2f(111,420);
    glVertex2f(111,423);
    glVertex2f(100,423);
    glVertex2f(98,446);
    glVertex2f(101,446);
    glVertex2f(101,424);
    glVertex2f(98,424);
    glVertex2f(99,448);
    glVertex2f(102,448);
    glVertex2f(102,445);
    glVertex2f(99,445);
    glVertex2f(99,422);
    glVertex2f(102,422);
    glVertex2f(102,425);
    glVertex2f(99,425);
    glVertex2f(113,446);
    glVertex2f(110,446);
    glVertex2f(110,424);
    glVertex2f(113,424);
    glVertex2f(112,448);
    glVertex2f(109,448);
    glVertex2f(109,445);
    glVertex2f(112,445);
    glVertex2f(112,422);
    glVertex2f(109,422);
    glVertex2f(109,425);
    glVertex2f(112,425);
    glVertex2f(129,420);///буква Т
    glVertex2f(132,420);
    glVertex2f(132,450);
    glVertex2f(129,450);
    glVertex2f(123,450);
    glVertex2f(138,450);
    glVertex2f(138,447);
    glVertex2f(123,447);
    glVertex2f(148,450);///буква Н
    glVertex2f(151,450);
    glVertex2f(151,420);
    glVertex2f(148,420);
    glVertex2f(162,450);
    glVertex2f(165,450);
    glVertex2f(165,420);
    glVertex2f(162,420);
    glVertex2f(151,434);
    glVertex2f(162,434);
    glVertex2f(162,437);
    glVertex2f(151,437);
    glVertex2f(175,450);///буква И
    glVertex2f(178,450);
    glVertex2f(178,420);
    glVertex2f(175,420);
    glVertex2f(189,450);
    glVertex2f(192,450);
    glVertex2f(192,420);
    glVertex2f(189,420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(178,420);
    glVertex2f(189,440);
    glVertex2f(178,421);
    glVertex2f(189,441);
    glVertex2f(178,422);
    glVertex2f(189,442);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(202,450);///буква К
    glVertex2f(205,450);
    glVertex2f(205,420);
    glVertex2f(202,420);
    glVertex2f(205,437);
    glVertex2f(207,437);
    glVertex2f(207,434);
    glVertex2f(205,434);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(207,437);
    glVertex2f(214,450);
    glVertex2f(207,437);
    glVertex2f(215,450);
    glVertex2f(207,436);
    glVertex2f(216,450);
    glVertex2f(207,436);
    glVertex2f(217,450);
    glVertex2f(207,435);
    glVertex2f(214,420);
    glVertex2f(207,435);
    glVertex2f(215,420);
    glVertex2f(207,434);
    glVertex2f(216,420);
    glVertex2f(207,434);
    glVertex2f(217,420);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(229,450);///буква О
    glVertex2f(240,450);
    glVertex2f(240,447);
    glVertex2f(229,447);
    glVertex2f(229,420);
    glVertex2f(240,420);
    glVertex2f(240,423);
    glVertex2f(229,423);
    glVertex2f(227,446);
    glVertex2f(230,446);
    glVertex2f(230,424);
    glVertex2f(227,424);
    glVertex2f(228,448);
    glVertex2f(231,448);
    glVertex2f(231,445);
    glVertex2f(228,445);
    glVertex2f(228,422);
    glVertex2f(231,422);
    glVertex2f(231,425);
    glVertex2f(228,425);
    glVertex2f(242,446);
    glVertex2f(239,446);
    glVertex2f(239,424);
    glVertex2f(242,424);
    glVertex2f(241,448);
    glVertex2f(238,448);
    glVertex2f(238,445);
    glVertex2f(241,445);
    glVertex2f(241,422);
    glVertex2f(238,422);
    glVertex2f(238,425);
    glVertex2f(241,425);
    glVertex2f(252,450);///буква В
    glVertex2f(255,450);
    glVertex2f(255,420);
    glVertex2f(252,420);
    glVertex2f(255,420);
    glVertex2f(265,420);
    glVertex2f(265,423);
    glVertex2f(255,423);
    glVertex2f(265,421);
    glVertex2f(268,421);
    glVertex2f(268,436);
    glVertex2f(265,436);
    glVertex2f(265,435);
    glVertex2f(255,435);
    glVertex2f(255,438);
    glVertex2f(265,438);
    glVertex2f(252,450);
    glVertex2f(263,450);
    glVertex2f(263,447);
    glVertex2f(252,447);
    glVertex2f(262,447);
    glVertex2f(265,447);
    glVertex2f(265,436);
    glVertex2f(262,436);
    glVertex2f(288,450);///буква В
    glVertex2f(291,450);
    glVertex2f(291,420);
    glVertex2f(288,420);
    glVertex2f(291,420);
    glVertex2f(301,420);
    glVertex2f(301,423);
    glVertex2f(291,423);
    glVertex2f(301,421);
    glVertex2f(304,421);
    glVertex2f(304,436);
    glVertex2f(301,436);
    glVertex2f(301,435);
    glVertex2f(291,435);
    glVertex2f(291,438);
    glVertex2f(301,438);
    glVertex2f(288,450);
    glVertex2f(299,450);
    glVertex2f(299,447);
    glVertex2f(288,447);
    glVertex2f(298,447);
    glVertex2f(301,447);
    glVertex2f(301,436);
    glVertex2f(298,436);
    glVertex2f(310,420);///ТОЧКА
    glVertex2f(313,420);
    glVertex2f(313,423);
    glVertex2f(310,423);
    glVertex2f(323,420);///БУКВА М
    glVertex2f(326,420);
    glVertex2f(326,450);
    glVertex2f(323,450);
    glVertex2f(340,420);
    glVertex2f(343,420);
    glVertex2f(343,450);
    glVertex2f(340,450);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(333,434);
    glVertex2f(333,437);
    glVertex2f(340,450);
    glVertex2f(333,437);
    glVertex2f(340,449);
    glVertex2f(333,436);
    glVertex2f(340,448);
    glVertex2f(333,435);
    glVertex2f(340,447);
    glVertex2f(333,434);
    glVertex2f(326,450);
    glVertex2f(333,437);
    glVertex2f(326,449);
    glVertex2f(333,436);
    glVertex2f(326,448);
    glVertex2f(333,435);
    glVertex2f(326,447);
    glVertex2f(333,434);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(352,420);///ТОЧКА
    glVertex2f(355,420);
    glVertex2f(355,423);
    glVertex2f(352,423);
    glVertex2f(42,400);///ГРУППА 3651001/90001////буква Г
    glVertex2f(45,400);
    glVertex2f(45,370);
    glVertex2f(42,370);
    glVertex2f(45,400);
    glVertex2f(56,400);
    glVertex2f(56,397);
    glVertex2f(45,397);
    glVertex2f(65,400);////буква Р
    glVertex2f(68,400);
    glVertex2f(68,370);
    glVertex2f(65,370);
    glVertex2f(66,400);
    glVertex2f(76,400);
    glVertex2f(76,397);
    glVertex2f(66,397);
    glVertex2f(76,399);
    glVertex2f(79,399);
    glVertex2f(79,384);
    glVertex2f(76,384);
    glVertex2f(76,383);
    glVertex2f(65,383);
    glVertex2f(65,386);
    glVertex2f(76,386);
    glVertex2f(89,370);///буква У
    glVertex2f(99,370);
    glVertex2f(99,373);
    glVertex2f(89,373);
    glVertex2f(98,371);
    glVertex2f(102,371);
    glVertex2f(102,376);
    glVertex2f(98,376);
    glVertex2f(101,374);
    glVertex2f(105,374);
    glVertex2f(105,379);
    glVertex2f(101,379);
    glVertex2f(105,377);
    glVertex2f(108,377);
    glVertex2f(108,400);
    glVertex2f(105,400);
    glVertex2f(89,383);
    glVertex2f(92,383);
    glVertex2f(92,400);
    glVertex2f(89,400);
    glVertex2f(90,385);
    glVertex2f(95,385);
    glVertex2f(95,381);
    glVertex2f(90,381);
    glVertex2f(93,382);
    glVertex2f(98,382);
    glVertex2f(98,379);
    glVertex2f(93,379);
    glVertex2f(93,379);
    glVertex2f(105,379);
    glVertex2f(105,382);
    glVertex2f(93,382);
    glVertex2f(118,400);///БУКВА П
    glVertex2f(121,400);
    glVertex2f(121,370);
    glVertex2f(118,370);
    glVertex2f(121,400);
    glVertex2f(131,400);
    glVertex2f(131,397);
    glVertex2f(121,397);
    glVertex2f(131,400);
    glVertex2f(134,400);
    glVertex2f(134,370);
    glVertex2f(131,370);
    glVertex2f(144,400);///БУКВА П
    glVertex2f(147,400);
    glVertex2f(147,370);
    glVertex2f(144,370);
    glVertex2f(147,400);
    glVertex2f(157,400);
    glVertex2f(157,397);
    glVertex2f(147,397);
    glVertex2f(157,400);
    glVertex2f(160,400);
    glVertex2f(160,370);
    glVertex2f(157,370);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(170,370);///буква А
    glVertex2f(180,400);
    glVertex2f(171,370);
    glVertex2f(180,399);
    glVertex2f(172,370);
    glVertex2f(180,398);
    glVertex2f(173,370);
    glVertex2f(180,397);
    glVertex2f(174,370);
    glVertex2f(180,396);
    glVertex2f(180,400);
    glVertex2f(190,370);
    glVertex2f(180,399);
    glVertex2f(189,370);
    glVertex2f(180,398);
    glVertex2f(188,370);
    glVertex2f(180,397);
    glVertex2f(187,370);
    glVertex2f(180,396);
    glVertex2f(186,370);
    glVertex2f(174,378);
    glVertex2f(186,378);
    glVertex2f(174,379);
    glVertex2f(186,379);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(209,370);///цифра 3
    glVertex2f(220,370);
    glVertex2f(220,373);
    glVertex2f(209,373);
    glVertex2f(220,370);
    glVertex2f(217,370);
    glVertex2f(217,400);
    glVertex2f(220,400);
    glVertex2f(209,400);
    glVertex2f(220,400);
    glVertex2f(220,397);
    glVertex2f(209,397);
    glVertex2f(217,384);
    glVertex2f(209,384);
    glVertex2f(209,387);
    glVertex2f(217,387);
    glVertex2f(230,370);///цифра 6
    glVertex2f(233,370);
    glVertex2f(233,400);
    glVertex2f(230,400);
    glVertex2f(230,370);
    glVertex2f(241,370);
    glVertex2f(241,373);
    glVertex2f(230,373);
    glVertex2f(230,400);
    glVertex2f(241,400);
    glVertex2f(241,397);
    glVertex2f(230,397);
    glVertex2f(230,390);
    glVertex2f(241,390);
    glVertex2f(241,387);
    glVertex2f(230,387);
    glVertex2f(241,370);
    glVertex2f(238,370);
    glVertex2f(238,387);
    glVertex2f(241,387);
    glVertex2f(251,370);///цифра 5
    glVertex2f(262,370);
    glVertex2f(262,373);
    glVertex2f(251,373);
    glVertex2f(262,370);
    glVertex2f(259,370);
    glVertex2f(259,387);
    glVertex2f(262,387);
    glVertex2f(262,387);
    glVertex2f(251,387);
    glVertex2f(251,384);
    glVertex2f(262,384);
    glVertex2f(251,384);
    glVertex2f(254,384);
    glVertex2f(254,400);
    glVertex2f(251,400);
    glVertex2f(251,400);
    glVertex2f(262,400);
    glVertex2f(262,397);
    glVertex2f(251,397);
    glVertex2f(272,370);///цифра 1
    glVertex2f(275,370);
    glVertex2f(275,400);
    glVertex2f(272,400);
    glVertex2f(285,370);///цифра 0
    glVertex2f(296,370);
    glVertex2f(296,373);
    glVertex2f(285,373);
    glVertex2f(285,370);
    glVertex2f(288,370);
    glVertex2f(288,400);
    glVertex2f(285,400);
    glVertex2f(296,370);
    glVertex2f(293,370);
    glVertex2f(293,400);
    glVertex2f(296,400);
    glVertex2f(285,400);
    glVertex2f(296,400);
    glVertex2f(296,397);
    glVertex2f(285,397);
    glVertex2f(306,370);///цифра 0
    glVertex2f(317,370);
    glVertex2f(317,373);
    glVertex2f(306,373);
    glVertex2f(306,370);
    glVertex2f(309,370);
    glVertex2f(309,400);
    glVertex2f(306,400);
    glVertex2f(317,370);
    glVertex2f(314,370);
    glVertex2f(314,400);
    glVertex2f(317,400);
    glVertex2f(306,400);
    glVertex2f(317,400);
    glVertex2f(317,397);
    glVertex2f(306,397);
    glVertex2f(327,370);///цифра 1
    glVertex2f(330,370);
    glVertex2f(330,400);
    glVertex2f(327,400);
    glVertex2f(340,370);/// СЛЕШ
    glVertex2f(343,370);
    glVertex2f(353,400);
    glVertex2f(350,400);
    glVertex2f(363,370);///цифра 9
    glVertex2f(374,370);
    glVertex2f(374,373);
    glVertex2f(363,373);
    glVertex2f(374,370);
    glVertex2f(371,370);
    glVertex2f(371,400);
    glVertex2f(374,400);
    glVertex2f(363,400);
    glVertex2f(374,400);
    glVertex2f(374,397);
    glVertex2f(363,397);
    glVertex2f(363,400);
    glVertex2f(366,400);
    glVertex2f(366,380);
    glVertex2f(363,380);
    glVertex2f(363,380);
    glVertex2f(374,380);
    glVertex2f(374,383);
    glVertex2f(363,383);
    glVertex2f(384,370);///цифра 0
    glVertex2f(395,370);
    glVertex2f(395,373);
    glVertex2f(384,373);
    glVertex2f(384,370);
    glVertex2f(387,370);
    glVertex2f(387,400);
    glVertex2f(384,400);
    glVertex2f(395,370);
    glVertex2f(392,370);
    glVertex2f(392,400);
    glVertex2f(395,400);
    glVertex2f(384,400);
    glVertex2f(395,400);
    glVertex2f(395,397);
    glVertex2f(384,397);
    glVertex2f(405,370);///цифра 0
    glVertex2f(416,370);
    glVertex2f(416,373);
    glVertex2f(405,373);
    glVertex2f(405,370);
    glVertex2f(408,370);
    glVertex2f(408,400);
    glVertex2f(405,400);
    glVertex2f(416,370);
    glVertex2f(413,370);
    glVertex2f(413,400);
    glVertex2f(416,400);
    glVertex2f(405,400);
    glVertex2f(416,400);
    glVertex2f(416,397);
    glVertex2f(405,397);
    glVertex2f(426,370);///цифра 0
    glVertex2f(437,370);
    glVertex2f(437,373);
    glVertex2f(426,373);
    glVertex2f(426,370);
    glVertex2f(429,370);
    glVertex2f(429,400);
    glVertex2f(426,400);
    glVertex2f(437,370);
    glVertex2f(434,370);
    glVertex2f(434,400);
    glVertex2f(437,400);
    glVertex2f(426,400);
    glVertex2f(437,400);
    glVertex2f(437,397);
    glVertex2f(426,397);
    glVertex2f(447,370);///цифра 1
    glVertex2f(450,370);
    glVertex2f(450,400);
    glVertex2f(447,400);
    glEnd();
    glutSwapBuffers();

}

void draw_settings() {
    glLineWidth(1);
    glClearColor(0.1, 0.1, 0.1, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(rs1, gs1, bs1);
    glBegin(GL_QUADS);
    glVertex2f(42, 420);///1-Й ХОД///ЦИФРА 1
    glVertex2f(45, 420);
    glVertex2f(45, 450);
    glVertex2f(42, 450);
    glVertex2f(50, 434);///ТИРЕ
    glVertex2f(58, 434);
    glVertex2f(58, 437);
    glVertex2f(50, 437);
    glVertex2f(63, 450);///буква Й
    glVertex2f(66, 450);
    glVertex2f(66, 420);
    glVertex2f(63, 420);
    glVertex2f(77, 450);
    glVertex2f(80, 450);
    glVertex2f(80, 420);
    glVertex2f(77, 420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(66, 420);
    glVertex2f(77, 440);
    glVertex2f(66, 421);
    glVertex2f(77, 441);
    glVertex2f(66, 422);
    glVertex2f(77, 442);
    glVertex2f(71, 452);
    glVertex2f(72, 452);
    glVertex2f(70, 453);
    glVertex2f(73, 453);
    glVertex2f(69, 454);
    glVertex2f(74, 454);
    glVertex2f(105, 420);///слово ХОД///буква Х
    glVertex2f(113, 435);
    glVertex2f(106, 420);
    glVertex2f(114, 435);
    glVertex2f(107, 420);
    glVertex2f(115, 435);
    glVertex2f(108, 420);
    glVertex2f(116, 435);
    glVertex2f(121, 420);
    glVertex2f(113, 435);
    glVertex2f(122, 420);
    glVertex2f(114, 435);
    glVertex2f(123, 420);
    glVertex2f(115, 435);
    glVertex2f(124, 420);
    glVertex2f(116, 435);
    glVertex2f(121, 450);
    glVertex2f(113, 436);
    glVertex2f(122, 450);
    glVertex2f(114, 436);
    glVertex2f(123, 450);
    glVertex2f(115, 436);
    glVertex2f(124, 450);
    glVertex2f(116, 436);
    glVertex2f(105, 450);
    glVertex2f(113, 436);
    glVertex2f(106, 450);
    glVertex2f(114, 436);
    glVertex2f(107, 450);
    glVertex2f(115, 436);
    glVertex2f(108, 450);
    glVertex2f(116, 436);

    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(136, 450);///буква О
    glVertex2f(147, 450);
    glVertex2f(147, 447);
    glVertex2f(136, 447);
    glVertex2f(136, 420);
    glVertex2f(147, 420);
    glVertex2f(147, 423);
    glVertex2f(136, 423);
    glVertex2f(134, 446);
    glVertex2f(137, 446);
    glVertex2f(137, 424);
    glVertex2f(134, 424);
    glVertex2f(135, 448);
    glVertex2f(138, 448);
    glVertex2f(138, 445);
    glVertex2f(135, 445);
    glVertex2f(135, 422);
    glVertex2f(138, 422);
    glVertex2f(138, 425);
    glVertex2f(135, 425);
    glVertex2f(149, 446);
    glVertex2f(146, 446);
    glVertex2f(146, 424);
    glVertex2f(149, 424);
    glVertex2f(148, 448);
    glVertex2f(145, 448);
    glVertex2f(145, 445);
    glVertex2f(148, 445);
    glVertex2f(148, 422);
    glVertex2f(145, 422);
    glVertex2f(145, 425);
    glVertex2f(148, 425);
    glVertex2f(159, 420);///буква Д
    glVertex2f(162, 420);
    glVertex2f(162, 424);
    glVertex2f(159, 424);
    glVertex2f(175, 420);
    glVertex2f(178, 420);
    glVertex2f(178, 424);
    glVertex2f(175, 424);
    glVertex2f(159, 424);
    glVertex2f(178, 424);
    glVertex2f(178, 427);
    glVertex2f(159, 427);
    glVertex2f(175, 424);
    glVertex2f(172, 424);
    glVertex2f(172, 450);
    glVertex2f(175, 450);
    glVertex2f(172, 450);
    glVertex2f(167, 450);
    glVertex2f(167, 447);
    glVertex2f(172, 447);
    glVertex2f(166, 448);
    glVertex2f(169, 448);
    glVertex2f(169, 445);
    glVertex2f(166, 445);
    glVertex2f(165, 441);
    glVertex2f(168, 441);
    glVertex2f(168, 445);
    glVertex2f(165, 445);
    glVertex2f(164, 441);
    glVertex2f(167, 441);
    glVertex2f(167, 438);
    glVertex2f(164, 438);
    glVertex2f(163, 434);
    glVertex2f(166, 434);
    glVertex2f(166, 438);
    glVertex2f(163, 438);
    glVertex2f(162, 434);
    glVertex2f(165, 434);
    glVertex2f(165, 431);
    glVertex2f(162, 431);
    glVertex2f(161, 427);
    glVertex2f(164, 427);
    glVertex2f(164, 431);
    glVertex2f(161, 431);
    glEnd();

    glColor3f(rs2,gs2,bs2);
    glBegin(GL_QUADS);
    glVertex2f(44,400);///слово СЛОЖНОСТЬ///буква С
    glVertex2f(56,400);
    glVertex2f(56,397);
    glVertex2f(44,397);
    glVertex2f(44,370);
    glVertex2f(56,370);
    glVertex2f(56,373);
    glVertex2f(44,373);
    glVertex2f(42,396);
    glVertex2f(45,396);
    glVertex2f(45,374);
    glVertex2f(42,374);
    glVertex2f(43,398);
    glVertex2f(46,398);
    glVertex2f(46,395);
    glVertex2f(43,395);
    glVertex2f(43,372);
    glVertex2f(46,372);
    glVertex2f(46,375);
    glVertex2f(43,375);
    glVertex2f(69,400);///буква Л
    glVertex2f(72,400);
    glVertex2f(72,376);
    glVertex2f(69,376);
    glVertex2f(71,373);
    glVertex2f(68,373);
    glVertex2f(68,376);
    glVertex2f(71,376);
    glVertex2f(69,371);
    glVertex2f(66,371);
    glVertex2f(66,374);
    glVertex2f(69,374);
    glVertex2f(67,370);
    glVertex2f(65,370);
    glVertex2f(65,373);
    glVertex2f(67,373);
    glVertex2f(72,400);
    glVertex2f(82,400);
    glVertex2f(82,397);
    glVertex2f(72,397);
    glVertex2f(82,400);
    glVertex2f(85,400);
    glVertex2f(85,370);
    glVertex2f(82,370);
    glVertex2f(97,400);///буква О
    glVertex2f(108,400);
    glVertex2f(108,397);
    glVertex2f(97,397);
    glVertex2f(97,370);
    glVertex2f(108,370);
    glVertex2f(108,373);
    glVertex2f(97,373);
    glVertex2f(95,396);
    glVertex2f(98,396);
    glVertex2f(98,374);
    glVertex2f(95,374);
    glVertex2f(96,398);
    glVertex2f(99,398);
    glVertex2f(99,395);
    glVertex2f(96,395);
    glVertex2f(96,372);
    glVertex2f(99,372);
    glVertex2f(99,375);
    glVertex2f(96,375);
    glVertex2f(110,396);
    glVertex2f(107,396);
    glVertex2f(107,374);
    glVertex2f(110,374);
    glVertex2f(109,398);
    glVertex2f(106,398);
    glVertex2f(106,395);
    glVertex2f(109,395);
    glVertex2f(109,372);
    glVertex2f(106,372);
    glVertex2f(106,375);
    glVertex2f(109,375);
    glVertex2f(120,370);///буква Ж
    glVertex2f(123,370);
    glVertex2f(123,400);
    glVertex2f(120,400);
    glVertex2f(130,370);
    glVertex2f(133,370);
    glVertex2f(133,400);
    glVertex2f(130,400);
    glVertex2f(140,370);
    glVertex2f(143,370);
    glVertex2f(143,400);
    glVertex2f(140,400);
    glVertex2f(123,384);
    glVertex2f(140,384);
    glVertex2f(140,387);
    glVertex2f(123,387);
    glVertex2f(153,400);///буква Н
    glVertex2f(156,400);
    glVertex2f(156,370);
    glVertex2f(153,370);
    glVertex2f(167,400);
    glVertex2f(170,400);
    glVertex2f(170,370);
    glVertex2f(167,370);
    glVertex2f(156,384);
    glVertex2f(167,384);
    glVertex2f(167,387);
    glVertex2f(156,387);
    glVertex2f(182,400);///буква О
    glVertex2f(193,400);
    glVertex2f(193,397);
    glVertex2f(182,397);
    glVertex2f(182,370);
    glVertex2f(193,370);
    glVertex2f(193,373);
    glVertex2f(182,373);
    glVertex2f(180,396);
    glVertex2f(183,396);
    glVertex2f(183,374);
    glVertex2f(180,374);
    glVertex2f(181,398);
    glVertex2f(184,398);
    glVertex2f(184,395);
    glVertex2f(181,395);
    glVertex2f(181,372);
    glVertex2f(184,372);
    glVertex2f(184,375);
    glVertex2f(181,375);
    glVertex2f(195,396);
    glVertex2f(192,396);
    glVertex2f(192,374);
    glVertex2f(195,374);
    glVertex2f(194,398);
    glVertex2f(191,398);
    glVertex2f(191,395);
    glVertex2f(194,395);
    glVertex2f(194,372);
    glVertex2f(191,372);
    glVertex2f(191,375);
    glVertex2f(194,375);
    glVertex2f(207,400);///буква С
    glVertex2f(219,400);
    glVertex2f(219,397);
    glVertex2f(207,397);
    glVertex2f(207,370);
    glVertex2f(219,370);
    glVertex2f(219,373);
    glVertex2f(207,373);
    glVertex2f(205,396);
    glVertex2f(208,396);
    glVertex2f(208,374);
    glVertex2f(205,374);
    glVertex2f(206,398);
    glVertex2f(209,398);
    glVertex2f(209,395);
    glVertex2f(206,395);
    glVertex2f(206,372);
    glVertex2f(209,372);
    glVertex2f(209,375);
    glVertex2f(206,375);
    glVertex2f(235,370);///буква Т
    glVertex2f(238,370);
    glVertex2f(238,400);
    glVertex2f(235,400);
    glVertex2f(229,400);
    glVertex2f(244,400);
    glVertex2f(244,397);
    glVertex2f(229,397);
    glVertex2f(251,400);///буква Ь
    glVertex2f(254,400);
    glVertex2f(254,370);
    glVertex2f(251,370);
    glVertex2f(254,370);
    glVertex2f(264,370);
    glVertex2f(264,373);
    glVertex2f(254,373);
    glVertex2f(264,371);
    glVertex2f(267,371);
    glVertex2f(267,386);
    glVertex2f(264,386);
    glVertex2f(264,385);
    glVertex2f(254,385);
    glVertex2f(254,388);
    glVertex2f(264,388);
    glEnd();


    glColor3f(rs3,gs3,bs3);
    glBegin(GL_QUADS);
    glVertex2f(46,350);///слово ЛИНИЯ///буква Л
    glVertex2f(49,350);
    glVertex2f(49,326);
    glVertex2f(46,326);
    glVertex2f(48,323);
    glVertex2f(45,323);
    glVertex2f(45,326);
    glVertex2f(48,326);
    glVertex2f(46,321);
    glVertex2f(43,321);
    glVertex2f(43,324);
    glVertex2f(46,324);
    glVertex2f(44,320);
    glVertex2f(42,320);
    glVertex2f(42,323);
    glVertex2f(44,323);
    glVertex2f(49,350);
    glVertex2f(59,350);
    glVertex2f(59,347);
    glVertex2f(49,347);
    glVertex2f(59,350);
    glVertex2f(62,350);
    glVertex2f(62,320);
    glVertex2f(59,320);
    glVertex2f(72,350);///буква И
    glVertex2f(75,350);
    glVertex2f(75,320);
    glVertex2f(72,320);
    glVertex2f(86,350);
    glVertex2f(89,350);
    glVertex2f(89,320);
    glVertex2f(86,320);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(75,320);
    glVertex2f(86,340);
    glVertex2f(75,321);
    glVertex2f(86,341);
    glVertex2f(75,322);
    glVertex2f(86,342);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(99,350);///буква Н
    glVertex2f(102,350);
    glVertex2f(102,320);
    glVertex2f(99,320);
    glVertex2f(113,350);
    glVertex2f(116,350);
    glVertex2f(116,320);
    glVertex2f(113,320);
    glVertex2f(102,334);
    glVertex2f(113,334);
    glVertex2f(113,337);
    glVertex2f(102,337);
    glVertex2f(126,350);///буква И
    glVertex2f(129,350);
    glVertex2f(129,320);
    glVertex2f(126,320);
    glVertex2f(140,350);
    glVertex2f(143,350);
    glVertex2f(143,320);
    glVertex2f(140,320);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(129,320);
    glVertex2f(140,340);
    glVertex2f(129,321);
    glVertex2f(140,341);
    glVertex2f(129,322);
    glVertex2f(140,342);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(167,320);///буква Я
    glVertex2f(170,320);
    glVertex2f(170,350);
    glVertex2f(167,350);
    glVertex2f(167,350);
    glVertex2f(158,350);
    glVertex2f(158,347);
    glVertex2f(167,347);
    glVertex2f(155,349);
    glVertex2f(158,349);
    glVertex2f(158,336);
    glVertex2f(155,336);
    glVertex2f(158,335);
    glVertex2f(167,335);
    glVertex2f(167,338);
    glVertex2f(158,338);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(153,320);
    glVertex2f(167,334);
    glVertex2f(154,320);
    glVertex2f(167,333);
    glVertex2f(155,320);
    glVertex2f(167,332);
    glVertex2f(156,320);
    glVertex2f(167,331);
    glEnd();
    glBegin(GL_LINES);///левая галочка <<
    glVertex2f(320,340);
    glVertex2f(313,335);
    glVertex2f(313,335);
    glVertex2f(320,330);
    glVertex2f(320,341);
    glVertex2f(312,335);
    glVertex2f(312,335);
    glVertex2f(320,329);
    glVertex2f(320,342);
    glVertex2f(311,335);
    glVertex2f(311,335);
    glVertex2f(320,328);
    glEnd();




    glColor3f(rs4,gs4,bs4);
    glBegin(GL_QUADS);
    glVertex2f(42,300);///слово ПОЛЕ///БУКВА П
    glVertex2f(45,300);
    glVertex2f(45,270);
    glVertex2f(42,270);
    glVertex2f(45,300);
    glVertex2f(55,300);
    glVertex2f(55,297);
    glVertex2f(45,297);
    glVertex2f(55,300);
    glVertex2f(58,300);
    glVertex2f(58,270);
    glVertex2f(55,270);
    glVertex2f(70,300);///буква О
    glVertex2f(81,300);
    glVertex2f(81,297);
    glVertex2f(70,297);
    glVertex2f(70,270);
    glVertex2f(81,270);
    glVertex2f(81,273);
    glVertex2f(70,273);
    glVertex2f(68,296);
    glVertex2f(71,296);
    glVertex2f(71,274);
    glVertex2f(68,274);
    glVertex2f(69,298);
    glVertex2f(72,298);
    glVertex2f(72,295);
    glVertex2f(69,295);
    glVertex2f(69,272);
    glVertex2f(72,272);
    glVertex2f(72,275);
    glVertex2f(69,275);
    glVertex2f(83,296);
    glVertex2f(80,296);
    glVertex2f(80,274);
    glVertex2f(83,274);
    glVertex2f(82,298);
    glVertex2f(79,298);
    glVertex2f(79,295);
    glVertex2f(82,295);
    glVertex2f(82,272);
    glVertex2f(79,272);
    glVertex2f(79,275);
    glVertex2f(82,275);
    glVertex2f(97,300);///буква Л
    glVertex2f(100,300);
    glVertex2f(100,276);
    glVertex2f(97,276);
    glVertex2f(99,273);
    glVertex2f(96,273);
    glVertex2f(96,276);
    glVertex2f(99,276);
    glVertex2f(97,271);
    glVertex2f(94,271);
    glVertex2f(94,274);
    glVertex2f(97,274);
    glVertex2f(95,270);
    glVertex2f(93,270);
    glVertex2f(93,273);
    glVertex2f(95,273);
    glVertex2f(100,300);
    glVertex2f(110,300);
    glVertex2f(110,297);
    glVertex2f(100,297);
    glVertex2f(110,300);
    glVertex2f(113,300);
    glVertex2f(113,270);
    glVertex2f(110,270);
    glVertex2f(123,300);////буква Е
    glVertex2f(126,300);
    glVertex2f(126,270);
    glVertex2f(123,270);
    glVertex2f(126,287);
    glVertex2f(138,287);
    glVertex2f(138,284);
    glVertex2f(126,284);
    glVertex2f(126,300);
    glVertex2f(138,300);
    glVertex2f(138,297);
    glVertex2f(126,297);
    glVertex2f(126,273);
    glVertex2f(138,273);
    glVertex2f(138,270);
    glVertex2f(126,270);
    glEnd();
    glBegin(GL_LINES);///левая галочка <<
    glVertex2f(320,290);
    glVertex2f(313,285);
    glVertex2f(313,285);
    glVertex2f(320,280);
    glVertex2f(320,291);
    glVertex2f(312,285);
    glVertex2f(312,285);
    glVertex2f(320,279);
    glVertex2f(320,292);
    glVertex2f(311,285);
    glVertex2f(311,285);
    glVertex2f(320,278);
    glEnd();
    ///////////////////////////////////////////////////////////////////////////////////////////////////



    if (flag_settings.first_move == GAMER){
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(327, 450);///слово ИГРОК///буква И
        glVertex2f(330, 450);
        glVertex2f(330, 420);
        glVertex2f(327, 420);
        glVertex2f(341, 450);
        glVertex2f(344, 450);
        glVertex2f(344, 420);
        glVertex2f(341, 420);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(330, 420);
        glVertex2f(341, 440);
        glVertex2f(330, 421);
        glVertex2f(341, 441);
        glVertex2f(330, 422);
        glVertex2f(341, 442);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(354, 450);////буква Г
        glVertex2f(357, 450);
        glVertex2f(357, 420);
        glVertex2f(354, 420);
        glVertex2f(357, 450);
        glVertex2f(368, 450);
        glVertex2f(368, 447);
        glVertex2f(357, 447);
        glVertex2f(377, 450);////буква Р
        glVertex2f(380, 450);
        glVertex2f(380, 420);
        glVertex2f(377, 420);
        glVertex2f(378, 450);
        glVertex2f(388, 450);
        glVertex2f(388, 447);
        glVertex2f(378, 447);
        glVertex2f(388, 449);
        glVertex2f(391, 449);
        glVertex2f(391, 434);
        glVertex2f(388, 434);
        glVertex2f(388, 433);
        glVertex2f(377, 433);
        glVertex2f(377, 436);
        glVertex2f(388, 436);
        glVertex2f(403, 450);///буква О
        glVertex2f(414, 450);
        glVertex2f(414, 447);
        glVertex2f(403, 447);
        glVertex2f(403, 420);
        glVertex2f(414, 420);
        glVertex2f(414, 423);
        glVertex2f(403, 423);
        glVertex2f(401, 446);
        glVertex2f(404, 446);
        glVertex2f(404, 424);
        glVertex2f(401, 424);
        glVertex2f(402, 448);
        glVertex2f(405, 448);
        glVertex2f(405, 445);
        glVertex2f(402, 445);
        glVertex2f(402, 422);
        glVertex2f(405, 422);
        glVertex2f(405, 425);
        glVertex2f(402, 425);
        glVertex2f(416, 446);
        glVertex2f(413, 446);
        glVertex2f(413, 424);
        glVertex2f(416, 424);
        glVertex2f(415, 448);
        glVertex2f(412, 448);
        glVertex2f(412, 445);
        glVertex2f(415, 445);
        glVertex2f(415, 422);
        glVertex2f(412, 422);
        glVertex2f(412, 425);
        glVertex2f(415, 425);
        glVertex2f(426, 450);///буква К
        glVertex2f(429, 450);
        glVertex2f(429, 420);
        glVertex2f(426, 420);
        glVertex2f(429, 437);
        glVertex2f(431, 437);
        glVertex2f(431, 434);
        glVertex2f(429, 434);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(431, 437);
        glVertex2f(438, 450);
        glVertex2f(431, 437);
        glVertex2f(439, 450);
        glVertex2f(431, 436);
        glVertex2f(440, 450);
        glVertex2f(431, 436);
        glVertex2f(441, 450);
        glVertex2f(431, 435);
        glVertex2f(438, 420);
        glVertex2f(431, 435);
        glVertex2f(439, 420);
        glVertex2f(431, 434);
        glVertex2f(440, 420);
        glVertex2f(431, 434);
        glVertex2f(441, 420);
        glEnd();
        glColor3f(rs1,gs1,bs1);
        glBegin(GL_LINES);///ГАЛОЧКИ <<>>
        glVertex2f(320,440);
        glVertex2f(313,435);
        glVertex2f(313,435);
        glVertex2f(320,430);
        glVertex2f(320,441);
        glVertex2f(312,435);
        glVertex2f(312,435);
        glVertex2f(320,429);
        glVertex2f(320,442);
        glVertex2f(311,435);
        glVertex2f(311,435);
        glVertex2f(320,428);
        glVertex2f(448,440);
        glVertex2f(455,435);
        glVertex2f(455,435);
        glVertex2f(448,430);
        glVertex2f(448,441);
        glVertex2f(456,435);
        glVertex2f(456,435);
        glVertex2f(448,429);
        glVertex2f(448,442);
        glVertex2f(457,435);
        glVertex2f(457,435);
        glVertex2f(448,428);
        glEnd();
        glColor3f(1,1,1);
        for(int i=0;i<strlen(Line_Length);i++) {
            if (Line_Length[i] == '0') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 0
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge, 320);
                glVertex2f(edge + 3, 320);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '1') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 1
                glVertex2f(edge + 3, 320);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge, 350);
                edge += 13;
                glEnd();
            } else if (Line_Length[i] == '2') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 2
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge, 320);
                glVertex2f(edge + 3, 320);
                glVertex2f(edge + 3, 337);
                glVertex2f(edge, 337);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge, 337);
                glVertex2f(edge, 334);
                glVertex2f(edge + 11, 334);
                glVertex2f(edge + 8, 334);
                glVertex2f(edge + 11, 334);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 8, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '3') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 3
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                glVertex2f(edge + 8, 334);
                glVertex2f(edge, 334);
                glVertex2f(edge, 337);
                glVertex2f(edge + 8, 337);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '4') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 350);///цифра 4
                glVertex2f(edge + 3, 350);
                glVertex2f(edge + 3, 334);
                glVertex2f(edge, 334);
                glVertex2f(edge, 334);
                glVertex2f(edge + 11, 334);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge, 337);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 8, 350);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '5') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 5
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 337);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge, 337);
                glVertex2f(edge, 334);
                glVertex2f(edge + 11, 334);
                glVertex2f(edge, 334);
                glVertex2f(edge + 3, 334);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '6') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 6
                glVertex2f(edge + 3, 320);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge, 320);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                glVertex2f(edge, 340);
                glVertex2f(edge + 11, 340);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge, 337);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 337);
                glVertex2f(edge + 11, 337);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '7') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 350);///цифра 7
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                glVertex2f(edge + 4, 320);
                glVertex2f(edge + 7, 320);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 8, 350);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '8') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 8
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge, 320);
                glVertex2f(edge + 3, 320);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                glVertex2f(edge, 334);
                glVertex2f(edge + 11, 334);
                glVertex2f(edge + 11, 337);
                glVertex2f(edge, 337);
                edge += 21;
                glEnd();
            } else if (Line_Length[i] == '9') {
                glBegin(GL_QUADS);
                glVertex2f(edge, 320);///цифра 9
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 11, 323);
                glVertex2f(edge, 323);
                glVertex2f(edge + 11, 320);
                glVertex2f(edge + 8, 320);
                glVertex2f(edge + 8, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge, 350);
                glVertex2f(edge + 11, 350);
                glVertex2f(edge + 11, 347);
                glVertex2f(edge, 347);
                glVertex2f(edge, 350);
                glVertex2f(edge + 3, 350);
                glVertex2f(edge + 3, 330);
                glVertex2f(edge, 330);
                glVertex2f(edge, 330);
                glVertex2f(edge + 11, 330);
                glVertex2f(edge + 11, 333);
                glVertex2f(edge, 333);
                edge += 21;
                glEnd();
            }
        }
        glBegin(GL_LINES);
        glColor3f(rs3,gs3,bs3);
        glVertex2f(edge-3,340);///правая галочка >>
        glVertex2f(edge+4,335);
        glVertex2f(edge+4,335);
        glVertex2f(edge-3,330);
        glVertex2f(edge-3,341);
        glVertex2f(edge+5,335);
        glVertex2f(edge+5,335);
        glVertex2f(edge-3,329);
        glVertex2f(edge-3,342);
        glVertex2f(edge+6,335);
        glVertex2f(edge+6,335);
        glVertex2f(edge-3,328);
        glEnd();

        glColor3f(1,1,1);
        for(int i=0;i<strlen(Side_Length);i++) {
            if (Side_Length[i] == '0') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 0
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '1') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 1
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                Sedge += 13;
                glEnd();
            } else if (Side_Length[i] == '2') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 2
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '3') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 3
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '4') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 4
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '5') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 5
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '6') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 6
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 290);
                glVertex2f(Sedge + 11, 290);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '7') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 7
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 4, 270);
                glVertex2f(Sedge + 7, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '8') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 8
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '9') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 9
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge + 11, 280);
                glVertex2f(Sedge + 11, 283);
                glVertex2f(Sedge, 283);
                Sedge += 21;
                glEnd();
            }
        }

        glBegin(GL_LINES);///КРЕСТИК
        glVertex2f(Sedge,293);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge,292);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge,290);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge,278);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge,279);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge,280);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge,281);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge+10,293);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge+10,292);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge+10,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+10,290);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge+10,278);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge+10,279);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+10,280);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge+10,281);
        glVertex2f(Sedge+5,287);
        glEnd();
        Sedge+=20;
        for(int i=0;i<strlen(Side_Length);i++) {
            if (Side_Length[i] == '0') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 0
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '1') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 1
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                Sedge += 13;
                glEnd();
            } else if (Side_Length[i] == '2') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 2
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '3') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 3
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '4') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 4
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '5') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 5
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '6') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 6
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 290);
                glVertex2f(Sedge + 11, 290);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '7') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 7
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 4, 270);
                glVertex2f(Sedge + 7, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '8') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 8
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '9') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 9
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge + 11, 280);
                glVertex2f(Sedge + 11, 283);
                glVertex2f(Sedge, 283);
                Sedge += 21;
                glEnd();
            }
        }
        glBegin(GL_LINES);
        glColor3f(rs4,gs4,bs4);
        glVertex2f(Sedge-3,290);///правая галочка >>
        glVertex2f(Sedge+4,285);
        glVertex2f(Sedge+4,285);
        glVertex2f(Sedge-3,280);
        glVertex2f(Sedge-3,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge-3,279);
        glVertex2f(Sedge-3,292);
        glVertex2f(Sedge+6,285);
        glVertex2f(Sedge+6,285);
        glVertex2f(Sedge-3,278);
        glEnd();

        if(flag_settings.difficulty == EASY){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(331,400);///слово ЛЕГКО///буква Л
            glVertex2f(334,400);
            glVertex2f(334,376);
            glVertex2f(331,376);
            glVertex2f(333,373);
            glVertex2f(330,373);
            glVertex2f(330,376);
            glVertex2f(333,376);
            glVertex2f(331,371);
            glVertex2f(328,371);
            glVertex2f(328,374);
            glVertex2f(331,374);
            glVertex2f(329,370);
            glVertex2f(327,370);
            glVertex2f(327,373);
            glVertex2f(329,373);
            glVertex2f(334,400);
            glVertex2f(344,400);
            glVertex2f(344,397);
            glVertex2f(334,397);
            glVertex2f(344,400);
            glVertex2f(347,400);
            glVertex2f(347,370);
            glVertex2f(344,370);
            glVertex2f(357,400);////буква Е
            glVertex2f(360,400);
            glVertex2f(360,370);
            glVertex2f(357,370);
            glVertex2f(360,387);
            glVertex2f(372,387);
            glVertex2f(372,384);
            glVertex2f(360,384);
            glVertex2f(360,400);
            glVertex2f(372,400);
            glVertex2f(372,397);
            glVertex2f(360,397);
            glVertex2f(360,373);
            glVertex2f(372,373);
            glVertex2f(372,370);
            glVertex2f(360,370);
            glVertex2f(382, 400);////буква Г
            glVertex2f(385, 400);
            glVertex2f(385, 370);
            glVertex2f(382, 370);
            glVertex2f(385, 400);
            glVertex2f(396, 400);
            glVertex2f(396, 397);
            glVertex2f(385, 397);
            glVertex2f(406, 400);///буква К
            glVertex2f(409, 400);
            glVertex2f(409, 370);
            glVertex2f(406, 370);
            glVertex2f(409, 387);
            glVertex2f(411, 387);
            glVertex2f(411, 384);
            glVertex2f(409, 384);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(411, 387);
            glVertex2f(418, 400);
            glVertex2f(411, 387);
            glVertex2f(419, 400);
            glVertex2f(411, 386);
            glVertex2f(420, 400);
            glVertex2f(411, 386);
            glVertex2f(421, 400);
            glVertex2f(411, 385);
            glVertex2f(418, 370);
            glVertex2f(411, 385);
            glVertex2f(419, 370);
            glVertex2f(411, 384);
            glVertex2f(420, 370);
            glVertex2f(411, 384);
            glVertex2f(421, 370);
            glEnd();
            glBegin(GL_QUADS);
            glVertex2f(433, 400);///буква О
            glVertex2f(444, 400);
            glVertex2f(444, 397);
            glVertex2f(433, 397);
            glVertex2f(433, 370);
            glVertex2f(444, 370);
            glVertex2f(444, 373);
            glVertex2f(433, 373);
            glVertex2f(431, 396);
            glVertex2f(434, 396);
            glVertex2f(434, 374);
            glVertex2f(431, 374);
            glVertex2f(432, 398);
            glVertex2f(435, 398);
            glVertex2f(435, 395);
            glVertex2f(432, 395);
            glVertex2f(432, 372);
            glVertex2f(435, 372);
            glVertex2f(435, 375);
            glVertex2f(432, 375);
            glVertex2f(446, 396);
            glVertex2f(443, 396);
            glVertex2f(443, 374);
            glVertex2f(446, 374);
            glVertex2f(445, 398);
            glVertex2f(442, 398);
            glVertex2f(442, 395);
            glVertex2f(445, 395);
            glVertex2f(445, 372);
            glVertex2f(442, 372);
            glVertex2f(442, 375);
            glVertex2f(445, 375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(453,390);
            glVertex2f(460,385);
            glVertex2f(460,385);
            glVertex2f(453,380);
            glVertex2f(453,391);
            glVertex2f(461,385);
            glVertex2f(461,385);
            glVertex2f(453,379);
            glVertex2f(453,392);
            glVertex2f(462,385);
            glVertex2f(462,385);
            glVertex2f(453,378);




            glEnd();

        }
        else if(flag_settings.difficulty == MEDIUM){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329,400);///слово СРЕДНЕ///буква С
            glVertex2f(341,400);
            glVertex2f(341,397);
            glVertex2f(329,397);
            glVertex2f(329,370);
            glVertex2f(341,370);
            glVertex2f(341,373);
            glVertex2f(329,373);
            glVertex2f(327,396);
            glVertex2f(330,396);
            glVertex2f(330,374);
            glVertex2f(327,374);
            glVertex2f(328,398);
            glVertex2f(331,398);
            glVertex2f(331,395);
            glVertex2f(328,395);
            glVertex2f(328,372);
            glVertex2f(331,372);
            glVertex2f(331,375);
            glVertex2f(328,375);
            glVertex2f(351,400);////буква Р
            glVertex2f(354,400);
            glVertex2f(354,370);
            glVertex2f(351,370);
            glVertex2f(352,400);
            glVertex2f(362,400);
            glVertex2f(362,397);
            glVertex2f(352,397);
            glVertex2f(362,399);
            glVertex2f(365,399);
            glVertex2f(365,384);
            glVertex2f(362,384);
            glVertex2f(362,383);
            glVertex2f(351,383);
            glVertex2f(351,386);
            glVertex2f(362,386);
            glVertex2f(375,400);////буква Е
            glVertex2f(378,400);
            glVertex2f(378,370);
            glVertex2f(375,370);
            glVertex2f(378,387);
            glVertex2f(390,387);
            glVertex2f(390,384);
            glVertex2f(378,384);
            glVertex2f(378,400);
            glVertex2f(390,400);
            glVertex2f(390,397);
            glVertex2f(378,397);
            glVertex2f(378,373);
            glVertex2f(390,373);
            glVertex2f(390,370);
            glVertex2f(378,370);
            glVertex2f(400,370);///буква Д
            glVertex2f(403,370);
            glVertex2f(403,374);
            glVertex2f(400,374);
            glVertex2f(416,370);
            glVertex2f(419,370);
            glVertex2f(419,374);
            glVertex2f(416,374);
            glVertex2f(400,374);
            glVertex2f(419,374);
            glVertex2f(419,377);
            glVertex2f(400,377);
            glVertex2f(416,374);
            glVertex2f(413,374);
            glVertex2f(413,400);
            glVertex2f(416,400);
            glVertex2f(413,400);
            glVertex2f(408,400);
            glVertex2f(408,397);
            glVertex2f(413,397);
            glVertex2f(407,398);
            glVertex2f(410,398);
            glVertex2f(410,395);
            glVertex2f(407,395);
            glVertex2f(406,391);
            glVertex2f(409,391);
            glVertex2f(409,395);
            glVertex2f(406,395);
            glVertex2f(405,391);
            glVertex2f(408,391);
            glVertex2f(408,388);
            glVertex2f(405,388);
            glVertex2f(404,384);
            glVertex2f(407,384);
            glVertex2f(407,388);
            glVertex2f(404,388);
            glVertex2f(403,384);
            glVertex2f(406,384);
            glVertex2f(406,381);
            glVertex2f(403,381);
            glVertex2f(402,377);
            glVertex2f(405,377);
            glVertex2f(405,381);
            glVertex2f(402,381);
            glVertex2f(429,400);///буква Н
            glVertex2f(432,400);
            glVertex2f(432,370);
            glVertex2f(429,370);
            glVertex2f(443,400);
            glVertex2f(446,400);
            glVertex2f(446,370);
            glVertex2f(443,370);
            glVertex2f(432,384);
            glVertex2f(443,384);
            glVertex2f(443,387);
            glVertex2f(432,387);
            glVertex2f(456,400);////буква Е
            glVertex2f(459,400);
            glVertex2f(459,370);
            glVertex2f(456,370);
            glVertex2f(459,387);
            glVertex2f(471,387);
            glVertex2f(471,384);
            glVertex2f(459,384);
            glVertex2f(459,400);
            glVertex2f(471,400);
            glVertex2f(471,397);
            glVertex2f(459,397);
            glVertex2f(459,373);
            glVertex2f(471,373);
            glVertex2f(471,370);
            glVertex2f(459,370);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(478,390);
            glVertex2f(485,385);
            glVertex2f(485,385);
            glVertex2f(478,380);
            glVertex2f(478,391);
            glVertex2f(486,385);
            glVertex2f(486,385);
            glVertex2f(478,379);
            glVertex2f(478,392);
            glVertex2f(487,385);
            glVertex2f(487,385);
            glVertex2f(478,378);
            glEnd();
        }
        else if(flag_settings.difficulty == HARD){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329,400);///слово СЛОЖНО///буква С
            glVertex2f(341,400);
            glVertex2f(341,397);
            glVertex2f(329,397);
            glVertex2f(329,370);
            glVertex2f(341,370);
            glVertex2f(341,373);
            glVertex2f(329,373);
            glVertex2f(327,396);
            glVertex2f(330,396);
            glVertex2f(330,374);
            glVertex2f(327,374);
            glVertex2f(328,398);
            glVertex2f(331,398);
            glVertex2f(331,395);
            glVertex2f(328,395);
            glVertex2f(328,372);
            glVertex2f(331,372);
            glVertex2f(331,375);
            glVertex2f(328,375);
            glVertex2f(355,400);///буква Л
            glVertex2f(358,400);
            glVertex2f(358,376);
            glVertex2f(355,376);
            glVertex2f(357,373);
            glVertex2f(354,373);
            glVertex2f(354,376);
            glVertex2f(357,376);
            glVertex2f(355,371);
            glVertex2f(352,371);
            glVertex2f(352,374);
            glVertex2f(355,374);
            glVertex2f(353,370);
            glVertex2f(351,370);
            glVertex2f(351,373);
            glVertex2f(353,373);
            glVertex2f(358,400);
            glVertex2f(368,400);
            glVertex2f(368,397);
            glVertex2f(358,397);
            glVertex2f(368,400);
            glVertex2f(371,400);
            glVertex2f(371,370);
            glVertex2f(368,370);
            glVertex2f(383, 400);///буква О
            glVertex2f(394, 400);
            glVertex2f(394, 397);
            glVertex2f(383, 397);
            glVertex2f(383, 370);
            glVertex2f(394, 370);
            glVertex2f(394, 373);
            glVertex2f(383, 373);
            glVertex2f(381, 396);
            glVertex2f(384, 396);
            glVertex2f(384, 374);
            glVertex2f(381, 374);
            glVertex2f(382, 398);
            glVertex2f(385, 398);
            glVertex2f(385, 395);
            glVertex2f(382, 395);
            glVertex2f(382, 372);
            glVertex2f(385, 372);
            glVertex2f(385, 375);
            glVertex2f(382, 375);
            glVertex2f(396, 396);
            glVertex2f(393, 396);
            glVertex2f(393, 374);
            glVertex2f(396, 374);
            glVertex2f(395, 398);
            glVertex2f(392, 398);
            glVertex2f(392, 395);
            glVertex2f(395, 395);
            glVertex2f(395, 372);
            glVertex2f(392, 372);
            glVertex2f(392, 375);
            glVertex2f(395, 375);
            glVertex2f(406,370);///буква Ж
            glVertex2f(409,370);
            glVertex2f(409,400);
            glVertex2f(406,400);
            glVertex2f(416,370);
            glVertex2f(419,370);
            glVertex2f(419,400);
            glVertex2f(416,400);
            glVertex2f(426,370);
            glVertex2f(429,370);
            glVertex2f(429,400);
            glVertex2f(426,400);
            glVertex2f(409,384);
            glVertex2f(426,384);
            glVertex2f(426,387);
            glVertex2f(409,387);
            glVertex2f(439,400);///буква Н
            glVertex2f(442,400);
            glVertex2f(442,370);
            glVertex2f(439,370);
            glVertex2f(453,400);
            glVertex2f(456,400);
            glVertex2f(456,370);
            glVertex2f(453,370);
            glVertex2f(442,384);
            glVertex2f(453,384);
            glVertex2f(453,387);
            glVertex2f(442,387);
            glVertex2f(468,400);///буква О
            glVertex2f(479,400);
            glVertex2f(479,397);
            glVertex2f(468,397);
            glVertex2f(468,370);
            glVertex2f(479,370);
            glVertex2f(479,373);
            glVertex2f(468,373);
            glVertex2f(466,396);
            glVertex2f(469,396);
            glVertex2f(469,374);
            glVertex2f(466,374);
            glVertex2f(467,398);
            glVertex2f(470,398);
            glVertex2f(470,395);
            glVertex2f(467,395);
            glVertex2f(467,372);
            glVertex2f(470,372);
            glVertex2f(470,375);
            glVertex2f(467,375);
            glVertex2f(481,396);
            glVertex2f(478,396);
            glVertex2f(478,374);
            glVertex2f(481,374);
            glVertex2f(480,398);
            glVertex2f(477,398);
            glVertex2f(477,395);
            glVertex2f(480,395);
            glVertex2f(480,372);
            glVertex2f(477,372);
            glVertex2f(477,375);
            glVertex2f(480,375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(488,390);
            glVertex2f(495,385);
            glVertex2f(495,385);
            glVertex2f(488,380);
            glVertex2f(488,391);
            glVertex2f(496,385);
            glVertex2f(496,385);
            glVertex2f(488,379);
            glVertex2f(488,392);
            glVertex2f(497,385);
            glVertex2f(497,385);
            glVertex2f(488,378);
            glEnd();
        }
        else if(flag_settings.difficulty == DARK_SOULS){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329, 400);///фраза ОЧЕНЬ СЛОЖНО///буква О
            glVertex2f(340, 400);
            glVertex2f(340, 397);
            glVertex2f(329, 397);
            glVertex2f(329, 370);
            glVertex2f(340, 370);
            glVertex2f(340, 373);
            glVertex2f(329, 373);
            glVertex2f(327, 396);
            glVertex2f(330, 396);
            glVertex2f(330, 374);
            glVertex2f(327, 374);
            glVertex2f(328, 398);
            glVertex2f(331, 398);
            glVertex2f(331, 395);
            glVertex2f(328, 395);
            glVertex2f(328, 372);
            glVertex2f(331, 372);
            glVertex2f(331, 375);
            glVertex2f(328, 375);
            glVertex2f(342, 396);
            glVertex2f(339, 396);
            glVertex2f(339, 374);
            glVertex2f(342, 374);
            glVertex2f(341, 398);
            glVertex2f(338, 398);
            glVertex2f(338, 395);
            glVertex2f(341, 395);
            glVertex2f(341, 372);
            glVertex2f(338, 372);
            glVertex2f(338, 375);
            glVertex2f(341, 375);
            glVertex2f(367,370);///буква Ч
            glVertex2f(370,370);
            glVertex2f(370,400);
            glVertex2f(367,400);
            glVertex2f(351,383);
            glVertex2f(354,383);
            glVertex2f(354,400);
            glVertex2f(351,400);
            glVertex2f(352,383);
            glVertex2f(357,383);
            glVertex2f(357,381);
            glVertex2f(352,381);
            glVertex2f(355,382);
            glVertex2f(360,382);
            glVertex2f(360,379);
            glVertex2f(355,379);
            glVertex2f(355,379);
            glVertex2f(367,379);
            glVertex2f(367,382);
            glVertex2f(355,382);
            glVertex2f(380,400);////буква Е
            glVertex2f(383,400);
            glVertex2f(383,370);
            glVertex2f(380,370);
            glVertex2f(383,387);
            glVertex2f(395,387);
            glVertex2f(395,384);
            glVertex2f(383,384);
            glVertex2f(383,400);
            glVertex2f(395,400);
            glVertex2f(395,397);
            glVertex2f(383,397);
            glVertex2f(383,373);
            glVertex2f(395,373);
            glVertex2f(395,370);
            glVertex2f(383,370);
            glVertex2f(405,400);///буква Н
            glVertex2f(408,400);
            glVertex2f(408,370);
            glVertex2f(405,370);
            glVertex2f(419,400);
            glVertex2f(422,400);
            glVertex2f(422,370);
            glVertex2f(419,370);
            glVertex2f(408,384);
            glVertex2f(419,384);
            glVertex2f(419,387);
            glVertex2f(408,387);
            glVertex2f(432,400);///буква Ь
            glVertex2f(435,400);
            glVertex2f(435,370);
            glVertex2f(432,370);
            glVertex2f(435,370);
            glVertex2f(445,370);
            glVertex2f(445,373);
            glVertex2f(435,373);
            glVertex2f(445,371);
            glVertex2f(448,371);
            glVertex2f(448,386);
            glVertex2f(445,386);
            glVertex2f(445,385);
            glVertex2f(435,385);
            glVertex2f(435,388);
            glVertex2f(445,388);
            glVertex2f(469,400);///слово СЛОЖНО///буква С
            glVertex2f(481,400);
            glVertex2f(481,397);
            glVertex2f(469,397);
            glVertex2f(469,370);
            glVertex2f(481,370);
            glVertex2f(481,373);
            glVertex2f(469,373);
            glVertex2f(467,396);
            glVertex2f(470,396);
            glVertex2f(470,374);
            glVertex2f(467,374);
            glVertex2f(468,398);
            glVertex2f(471,398);
            glVertex2f(471,395);
            glVertex2f(468,395);
            glVertex2f(468,372);
            glVertex2f(471,372);
            glVertex2f(471,375);
            glVertex2f(468,375);
            glVertex2f(495,400);///буква Л
            glVertex2f(498,400);
            glVertex2f(498,376);
            glVertex2f(495,376);
            glVertex2f(497,373);
            glVertex2f(494,373);
            glVertex2f(494,376);
            glVertex2f(497,376);
            glVertex2f(495,371);
            glVertex2f(492,371);
            glVertex2f(492,374);
            glVertex2f(495,374);
            glVertex2f(493,370);
            glVertex2f(491,370);
            glVertex2f(491,373);
            glVertex2f(493,373);
            glVertex2f(498,400);
            glVertex2f(508,400);
            glVertex2f(508,397);
            glVertex2f(498,397);
            glVertex2f(508,400);
            glVertex2f(511,400);
            glVertex2f(511,370);
            glVertex2f(508,370);
            glVertex2f(523, 400);///буква О
            glVertex2f(534, 400);
            glVertex2f(534, 397);
            glVertex2f(523, 397);
            glVertex2f(523, 370);
            glVertex2f(534, 370);
            glVertex2f(534, 373);
            glVertex2f(523, 373);
            glVertex2f(521, 396);
            glVertex2f(524, 396);
            glVertex2f(524, 374);
            glVertex2f(521, 374);
            glVertex2f(522, 398);
            glVertex2f(525, 398);
            glVertex2f(525, 395);
            glVertex2f(522, 395);
            glVertex2f(522, 372);
            glVertex2f(525, 372);
            glVertex2f(525, 375);
            glVertex2f(522, 375);
            glVertex2f(536, 396);
            glVertex2f(533, 396);
            glVertex2f(533, 374);
            glVertex2f(536, 374);
            glVertex2f(535, 398);
            glVertex2f(532, 398);
            glVertex2f(532, 395);
            glVertex2f(535, 395);
            glVertex2f(535, 372);
            glVertex2f(532, 372);
            glVertex2f(532, 375);
            glVertex2f(535, 375);
            glVertex2f(546,370);///буква Ж
            glVertex2f(549,370);
            glVertex2f(549,400);
            glVertex2f(546,400);
            glVertex2f(556,370);
            glVertex2f(559,370);
            glVertex2f(559,400);
            glVertex2f(556,400);
            glVertex2f(566,370);
            glVertex2f(569,370);
            glVertex2f(569,400);
            glVertex2f(566,400);
            glVertex2f(549,384);
            glVertex2f(566,384);
            glVertex2f(566,387);
            glVertex2f(549,387);
            glVertex2f(579,400);///буква Н
            glVertex2f(582,400);
            glVertex2f(582,370);
            glVertex2f(579,370);
            glVertex2f(593,400);
            glVertex2f(596,400);
            glVertex2f(596,370);
            glVertex2f(593,370);
            glVertex2f(582,384);
            glVertex2f(593,384);
            glVertex2f(593,387);
            glVertex2f(582,387);
            glVertex2f(608,400);///буква О
            glVertex2f(619,400);
            glVertex2f(619,397);
            glVertex2f(608,397);
            glVertex2f(608,370);
            glVertex2f(619,370);
            glVertex2f(619,373);
            glVertex2f(608,373);
            glVertex2f(606,396);
            glVertex2f(609,396);
            glVertex2f(609,374);
            glVertex2f(606,374);
            glVertex2f(607,398);
            glVertex2f(610,398);
            glVertex2f(610,395);
            glVertex2f(607,395);
            glVertex2f(607,372);
            glVertex2f(610,372);
            glVertex2f(610,375);
            glVertex2f(607,375);
            glVertex2f(621,396);
            glVertex2f(618,396);
            glVertex2f(618,374);
            glVertex2f(621,374);
            glVertex2f(620,398);
            glVertex2f(617,398);
            glVertex2f(617,395);
            glVertex2f(620,395);
            glVertex2f(620,372);
            glVertex2f(617,372);
            glVertex2f(617,375);
            glVertex2f(620,375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(628,390);
            glVertex2f(635,385);
            glVertex2f(635,385);
            glVertex2f(628,380);
            glVertex2f(628,391);
            glVertex2f(636,385);
            glVertex2f(636,385);
            glVertex2f(628,379);
            glVertex2f(628,392);
            glVertex2f(637,385);
            glVertex2f(637,385);
            glVertex2f(628,378);
            glEnd();
        }
    }

    else if(flag_settings.first_move == BOT){
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(327, 450);///слово КОМПЬЮТЕР///буква К
        glVertex2f(330, 450);
        glVertex2f(330, 420);
        glVertex2f(327, 420);
        glVertex2f(330, 437);
        glVertex2f(332, 437);
        glVertex2f(332, 434);
        glVertex2f(330, 434);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(332, 437);
        glVertex2f(339, 450);
        glVertex2f(332, 437);
        glVertex2f(340, 450);
        glVertex2f(332, 436);
        glVertex2f(341, 450);
        glVertex2f(332, 436);
        glVertex2f(342, 450);
        glVertex2f(332, 435);
        glVertex2f(339, 420);
        glVertex2f(332, 435);
        glVertex2f(340, 420);
        glVertex2f(332, 434);
        glVertex2f(341, 420);
        glVertex2f(332, 434);
        glVertex2f(342, 420);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(354, 450);///буква О
        glVertex2f(365, 450);
        glVertex2f(365, 447);
        glVertex2f(354, 447);
        glVertex2f(354, 420);
        glVertex2f(365, 420);
        glVertex2f(365, 423);
        glVertex2f(354, 423);
        glVertex2f(352, 446);
        glVertex2f(355, 446);
        glVertex2f(355, 424);
        glVertex2f(352, 424);
        glVertex2f(353, 448);
        glVertex2f(356, 448);
        glVertex2f(356, 445);
        glVertex2f(353, 445);
        glVertex2f(353, 422);
        glVertex2f(356, 422);
        glVertex2f(356, 425);
        glVertex2f(353, 425);
        glVertex2f(367, 446);
        glVertex2f(364, 446);
        glVertex2f(364, 424);
        glVertex2f(367, 424);
        glVertex2f(366, 448);
        glVertex2f(363, 448);
        glVertex2f(363, 445);
        glVertex2f(366, 445);
        glVertex2f(366, 422);
        glVertex2f(363, 422);
        glVertex2f(363, 425);
        glVertex2f(366, 425);
        glVertex2f(377,420);///БУКВА М
        glVertex2f(380,420);
        glVertex2f(380,450);
        glVertex2f(377,450);
        glVertex2f(394,420);
        glVertex2f(397,420);
        glVertex2f(397,450);
        glVertex2f(394,450);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(387,434);
        glVertex2f(387,437);
        glVertex2f(394,450);
        glVertex2f(387,437);
        glVertex2f(394,449);
        glVertex2f(387,436);
        glVertex2f(394,448);
        glVertex2f(387,435);
        glVertex2f(394,447);
        glVertex2f(387,434);
        glVertex2f(380,450);
        glVertex2f(387,437);
        glVertex2f(380,449);
        glVertex2f(387,436);
        glVertex2f(380,448);
        glVertex2f(387,435);
        glVertex2f(380,447);
        glVertex2f(387,434);
        glEnd();
        glBegin(GL_QUADS);
        glVertex2f(404,420);///буква П
        glVertex2f(407,420);
        glVertex2f(407,450);
        glVertex2f(404,450);
        glVertex2f(407,450);
        glVertex2f(417,450);
        glVertex2f(417,447);
        glVertex2f(407,447);
        glVertex2f(417,450);
        glVertex2f(420,450);
        glVertex2f(420,420);
        glVertex2f(417,420);
        glVertex2f(430,450);///буква Ь
        glVertex2f(433,450);
        glVertex2f(433,420);
        glVertex2f(430,420);
        glVertex2f(433,420);
        glVertex2f(443,420);
        glVertex2f(443,423);
        glVertex2f(433,423);
        glVertex2f(443,421);
        glVertex2f(446,421);
        glVertex2f(446,436);
        glVertex2f(443,436);
        glVertex2f(443,435);
        glVertex2f(433,435);
        glVertex2f(433,438);
        glVertex2f(443,438);
        glVertex2f(456,420);///буква Ю ///палки
        glVertex2f(459,420);
        glVertex2f(459,450);
        glVertex2f(456,450);
        glVertex2f(459,437);
        glVertex2f(469,437);
        glVertex2f(469,434);
        glVertex2f(459,434);
        glVertex2f(471,450);///кружок
        glVertex2f(482,450);
        glVertex2f(482,447);
        glVertex2f(471,447);
        glVertex2f(471,420);
        glVertex2f(482,420);
        glVertex2f(482,423);
        glVertex2f(471,423);
        glVertex2f(469,446);
        glVertex2f(472,446);
        glVertex2f(472,424);
        glVertex2f(469,424);
        glVertex2f(470,448);
        glVertex2f(473,448);
        glVertex2f(473,445);
        glVertex2f(470,445);
        glVertex2f(470,422);
        glVertex2f(473,422);
        glVertex2f(473,425);
        glVertex2f(470,425);
        glVertex2f(484,446);
        glVertex2f(481,446);
        glVertex2f(481,424);
        glVertex2f(484,424);
        glVertex2f(483,448);
        glVertex2f(480,448);
        glVertex2f(480,445);
        glVertex2f(483,445);
        glVertex2f(483,422);
        glVertex2f(480,422);
        glVertex2f(480,425);
        glVertex2f(483,425);
        glVertex2f(499,420);///буква Т
        glVertex2f(502,420);
        glVertex2f(502,450);
        glVertex2f(499,450);
        glVertex2f(493,450);
        glVertex2f(508,450);
        glVertex2f(508,447);
        glVertex2f(493,447);
        glVertex2f(518,450);////буква Е
        glVertex2f(521,450);
        glVertex2f(521,420);
        glVertex2f(518,420);
        glVertex2f(521,437);
        glVertex2f(533,437);
        glVertex2f(533,434);
        glVertex2f(521,434);
        glVertex2f(521,450);
        glVertex2f(533,450);
        glVertex2f(533,447);
        glVertex2f(521,447);
        glVertex2f(521,423);
        glVertex2f(533,423);
        glVertex2f(533,420);
        glVertex2f(521,420);
        glVertex2f(543,450);////буква Р
        glVertex2f(546,450);
        glVertex2f(546,420);
        glVertex2f(543,420);
        glVertex2f(544,450);
        glVertex2f(554,450);
        glVertex2f(554,447);
        glVertex2f(544,447);
        glVertex2f(554,449);
        glVertex2f(557,449);
        glVertex2f(557,434);
        glVertex2f(554,434);
        glVertex2f(554,433);
        glVertex2f(543,433);
        glVertex2f(543,436);
        glVertex2f(554,436);
        glEnd();

        glColor3f(rs1,gs1,bs1);
        glBegin(GL_LINES);
        glVertex2f(320,440);
        glVertex2f(313,435);
        glVertex2f(313,435);
        glVertex2f(320,430);
        glVertex2f(320,441);
        glVertex2f(312,435);
        glVertex2f(312,435);
        glVertex2f(320,429);
        glVertex2f(320,442);
        glVertex2f(311,435);
        glVertex2f(311,435);
        glVertex2f(320,428);
        glVertex2f(564,440);
        glVertex2f(571,435);
        glVertex2f(571,435);
        glVertex2f(564,430);
        glVertex2f(564,441);
        glVertex2f(572,435);
        glVertex2f(572,435);
        glVertex2f(564,429);
        glVertex2f(564,442);
        glVertex2f(573,435);
        glVertex2f(573,435);
        glVertex2f(564,428);
        glEnd();
        glColor3f(1,1,1);
        for(int i=0;i<strlen(Line_Length);i++){
            if(Line_Length[i]=='0'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 0
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge,320);
                glVertex2f(edge+3,320);
                glVertex2f(edge+3,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='1'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 1
                glVertex2f(edge+3,320);
                glVertex2f(edge+3,350);
                glVertex2f(edge,350);
                edge+=13;
                glEnd();
            }
            else if(Line_Length[i]=='2'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 2
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge,320);
                glVertex2f(edge+3,320);
                glVertex2f(edge+3,337);
                glVertex2f(edge,337);
                glVertex2f(edge+11,337);
                glVertex2f(edge,337);
                glVertex2f(edge,334);
                glVertex2f(edge+11,334);
                glVertex2f(edge+8,334);
                glVertex2f(edge+11,334);
                glVertex2f(edge+11,350);
                glVertex2f(edge+8,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='3'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 3
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                glVertex2f(edge+8,334);
                glVertex2f(edge,334);
                glVertex2f(edge,337);
                glVertex2f(edge+8,337);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='4'){
                glBegin(GL_QUADS);
                glVertex2f(edge,350);///цифра 4
                glVertex2f(edge+3,350);
                glVertex2f(edge+3,334);
                glVertex2f(edge,334);
                glVertex2f(edge,334);
                glVertex2f(edge+11,334);
                glVertex2f(edge+11,337);
                glVertex2f(edge,337);
                glVertex2f(edge+8,320);
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,350);
                glVertex2f(edge+8,350);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='5'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 5
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,337);
                glVertex2f(edge+11,337);
                glVertex2f(edge+11,337);
                glVertex2f(edge,337);
                glVertex2f(edge,334);
                glVertex2f(edge+11,334);
                glVertex2f(edge,334);
                glVertex2f(edge+3,334);
                glVertex2f(edge+3,350);
                glVertex2f(edge,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='6'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 6
                glVertex2f(edge+3,320);
                glVertex2f(edge+3,350);
                glVertex2f(edge,350);
                glVertex2f(edge,320);
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                glVertex2f(edge,340);
                glVertex2f(edge+11,340);
                glVertex2f(edge+11,337);
                glVertex2f(edge,337);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,337);
                glVertex2f(edge+11,337);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='7'){
                glBegin(GL_QUADS);
                glVertex2f(edge,350);///цифра 7
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                glVertex2f(edge+4,320);
                glVertex2f(edge+7,320);
                glVertex2f(edge+11,350);
                glVertex2f(edge+8,350);
                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='8'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 8
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge,320);
                glVertex2f(edge+3,320);
                glVertex2f(edge+3,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                glVertex2f(edge,334);
                glVertex2f(edge+11,334);
                glVertex2f(edge+11,337);
                glVertex2f(edge,337);

                edge+=21;
                glEnd();
            }
            else if(Line_Length[i]=='9'){
                glBegin(GL_QUADS);
                glVertex2f(edge,320);///цифра 9
                glVertex2f(edge+11,320);
                glVertex2f(edge+11,323);
                glVertex2f(edge,323);
                glVertex2f(edge+11,320);
                glVertex2f(edge+8,320);
                glVertex2f(edge+8,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge,350);
                glVertex2f(edge+11,350);
                glVertex2f(edge+11,347);
                glVertex2f(edge,347);
                glVertex2f(edge,350);
                glVertex2f(edge+3,350);
                glVertex2f(edge+3,330);
                glVertex2f(edge,330);
                glVertex2f(edge,330);
                glVertex2f(edge+11,330);
                glVertex2f(edge+11,333);
                glVertex2f(edge,333);
                edge+=21;
                glEnd();
            }
        }
        glBegin(GL_LINES);
        glColor3f(rs3,gs3,bs3);
        glVertex2f(edge-3,340);///правая галочка >>
        glVertex2f(edge+4,335);
        glVertex2f(edge+4,335);
        glVertex2f(edge-3,330);
        glVertex2f(edge-3,341);
        glVertex2f(edge+5,335);
        glVertex2f(edge+5,335);
        glVertex2f(edge-3,329);
        glVertex2f(edge-3,342);
        glVertex2f(edge+6,335);
        glVertex2f(edge+6,335);
        glVertex2f(edge-3,328);
        glEnd();

        glColor3f(1,1,1);
        for(int i=0;i<strlen(Side_Length);i++) {
            if (Side_Length[i] == '0') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 0
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '1') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 1
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                Sedge += 13;
                glEnd();
            } else if (Side_Length[i] == '2') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 2
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '3') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 3
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '4') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 4
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '5') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 5
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '6') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 6
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 290);
                glVertex2f(Sedge + 11, 290);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '7') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 7
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 4, 270);
                glVertex2f(Sedge + 7, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '8') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 8
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '9') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 9
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge + 11, 280);
                glVertex2f(Sedge + 11, 283);
                glVertex2f(Sedge, 283);
                Sedge += 21;
                glEnd();
            }



        }


        glBegin(GL_LINES);///КРЕСТИК
        glVertex2f(Sedge,293);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge,292);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge,290);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge,278);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge,279);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge,280);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge,281);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge+10,293);
        glVertex2f(Sedge+5,287);
        glVertex2f(Sedge+10,292);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge+10,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+10,290);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge+10,278);
        glVertex2f(Sedge+5,284);
        glVertex2f(Sedge+10,279);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+10,280);
        glVertex2f(Sedge+5,286);
        glVertex2f(Sedge+10,281);
        glVertex2f(Sedge+5,287);
        glEnd();
        Sedge+=20;
        for(int i=0;i<strlen(Side_Length);i++) {
            if (Side_Length[i] == '0') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 0
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '1') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 1
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                Sedge += 13;
                glEnd();
            } else if (Side_Length[i] == '2') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 2
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '3') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 3
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 8, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '4') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 4
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '5') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 5
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 3, 284);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '6') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 6
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 290);
                glVertex2f(Sedge + 11, 290);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 287);
                glVertex2f(Sedge + 11, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '7') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 300);///цифра 7
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge + 4, 270);
                glVertex2f(Sedge + 7, 270);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 8, 300);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '8') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 8
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge, 270);
                glVertex2f(Sedge + 3, 270);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 284);
                glVertex2f(Sedge + 11, 284);
                glVertex2f(Sedge + 11, 287);
                glVertex2f(Sedge, 287);
                Sedge += 21;
                glEnd();
            } else if (Side_Length[i] == '9') {
                glBegin(GL_QUADS);
                glVertex2f(Sedge, 270);///цифра 9
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 11, 273);
                glVertex2f(Sedge, 273);
                glVertex2f(Sedge + 11, 270);
                glVertex2f(Sedge + 8, 270);
                glVertex2f(Sedge + 8, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 11, 300);
                glVertex2f(Sedge + 11, 297);
                glVertex2f(Sedge, 297);
                glVertex2f(Sedge, 300);
                glVertex2f(Sedge + 3, 300);
                glVertex2f(Sedge + 3, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge, 280);
                glVertex2f(Sedge + 11, 280);
                glVertex2f(Sedge + 11, 283);
                glVertex2f(Sedge, 283);
                Sedge += 21;
                glEnd();
            }
        }
        glBegin(GL_LINES);
        glColor3f(rs4,gs4,bs4);
        glVertex2f(Sedge-3,290);///правая галочка >>
        glVertex2f(Sedge+4,285);
        glVertex2f(Sedge+4,285);
        glVertex2f(Sedge-3,280);
        glVertex2f(Sedge-3,291);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge+5,285);
        glVertex2f(Sedge-3,279);
        glVertex2f(Sedge-3,292);
        glVertex2f(Sedge+6,285);
        glVertex2f(Sedge+6,285);
        glVertex2f(Sedge-3,278);
        glEnd();


        if(flag_settings.difficulty == EASY){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(331,400);///слово ЛЕГКО///буква Л
            glVertex2f(334,400);
            glVertex2f(334,376);
            glVertex2f(331,376);
            glVertex2f(333,373);
            glVertex2f(330,373);
            glVertex2f(330,376);
            glVertex2f(333,376);
            glVertex2f(331,371);
            glVertex2f(328,371);
            glVertex2f(328,374);
            glVertex2f(331,374);
            glVertex2f(329,370);
            glVertex2f(327,370);
            glVertex2f(327,373);
            glVertex2f(329,373);
            glVertex2f(334,400);
            glVertex2f(344,400);
            glVertex2f(344,397);
            glVertex2f(334,397);
            glVertex2f(344,400);
            glVertex2f(347,400);
            glVertex2f(347,370);
            glVertex2f(344,370);
            glVertex2f(357,400);////буква Е
            glVertex2f(360,400);
            glVertex2f(360,370);
            glVertex2f(357,370);
            glVertex2f(360,387);
            glVertex2f(372,387);
            glVertex2f(372,384);
            glVertex2f(360,384);
            glVertex2f(360,400);
            glVertex2f(372,400);
            glVertex2f(372,397);
            glVertex2f(360,397);
            glVertex2f(360,373);
            glVertex2f(372,373);
            glVertex2f(372,370);
            glVertex2f(360,370);
            glVertex2f(382, 400);////буква Г
            glVertex2f(385, 400);
            glVertex2f(385, 370);
            glVertex2f(382, 370);
            glVertex2f(385, 400);
            glVertex2f(396, 400);
            glVertex2f(396, 397);
            glVertex2f(385, 397);
            glVertex2f(406, 400);///буква К
            glVertex2f(409, 400);
            glVertex2f(409, 370);
            glVertex2f(406, 370);
            glVertex2f(409, 387);
            glVertex2f(411, 387);
            glVertex2f(411, 384);
            glVertex2f(409, 384);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(411, 387);
            glVertex2f(418, 400);
            glVertex2f(411, 387);
            glVertex2f(419, 400);
            glVertex2f(411, 386);
            glVertex2f(420, 400);
            glVertex2f(411, 386);
            glVertex2f(421, 400);
            glVertex2f(411, 385);
            glVertex2f(418, 370);
            glVertex2f(411, 385);
            glVertex2f(419, 370);
            glVertex2f(411, 384);
            glVertex2f(420, 370);
            glVertex2f(411, 384);
            glVertex2f(421, 370);
            glEnd();
            glBegin(GL_QUADS);
            glVertex2f(433, 400);///буква О
            glVertex2f(444, 400);
            glVertex2f(444, 397);
            glVertex2f(433, 397);
            glVertex2f(433, 370);
            glVertex2f(444, 370);
            glVertex2f(444, 373);
            glVertex2f(433, 373);
            glVertex2f(431, 396);
            glVertex2f(434, 396);
            glVertex2f(434, 374);
            glVertex2f(431, 374);
            glVertex2f(432, 398);
            glVertex2f(435, 398);
            glVertex2f(435, 395);
            glVertex2f(432, 395);
            glVertex2f(432, 372);
            glVertex2f(435, 372);
            glVertex2f(435, 375);
            glVertex2f(432, 375);
            glVertex2f(446, 396);
            glVertex2f(443, 396);
            glVertex2f(443, 374);
            glVertex2f(446, 374);
            glVertex2f(445, 398);
            glVertex2f(442, 398);
            glVertex2f(442, 395);
            glVertex2f(445, 395);
            glVertex2f(445, 372);
            glVertex2f(442, 372);
            glVertex2f(442, 375);
            glVertex2f(445, 375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(453,390);
            glVertex2f(460,385);
            glVertex2f(460,385);
            glVertex2f(453,380);
            glVertex2f(453,391);
            glVertex2f(461,385);
            glVertex2f(461,385);
            glVertex2f(453,379);
            glVertex2f(453,392);
            glVertex2f(462,385);
            glVertex2f(462,385);
            glVertex2f(453,378);




            glEnd();

        }
        else if(flag_settings.difficulty == MEDIUM){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329,400);///слово СРЕДНЕ///буква С
            glVertex2f(341,400);
            glVertex2f(341,397);
            glVertex2f(329,397);
            glVertex2f(329,370);
            glVertex2f(341,370);
            glVertex2f(341,373);
            glVertex2f(329,373);
            glVertex2f(327,396);
            glVertex2f(330,396);
            glVertex2f(330,374);
            glVertex2f(327,374);
            glVertex2f(328,398);
            glVertex2f(331,398);
            glVertex2f(331,395);
            glVertex2f(328,395);
            glVertex2f(328,372);
            glVertex2f(331,372);
            glVertex2f(331,375);
            glVertex2f(328,375);
            glVertex2f(351,400);////буква Р
            glVertex2f(354,400);
            glVertex2f(354,370);
            glVertex2f(351,370);
            glVertex2f(352,400);
            glVertex2f(362,400);
            glVertex2f(362,397);
            glVertex2f(352,397);
            glVertex2f(362,399);
            glVertex2f(365,399);
            glVertex2f(365,384);
            glVertex2f(362,384);
            glVertex2f(362,383);
            glVertex2f(351,383);
            glVertex2f(351,386);
            glVertex2f(362,386);
            glVertex2f(375,400);////буква Е
            glVertex2f(378,400);
            glVertex2f(378,370);
            glVertex2f(375,370);
            glVertex2f(378,387);
            glVertex2f(390,387);
            glVertex2f(390,384);
            glVertex2f(378,384);
            glVertex2f(378,400);
            glVertex2f(390,400);
            glVertex2f(390,397);
            glVertex2f(378,397);
            glVertex2f(378,373);
            glVertex2f(390,373);
            glVertex2f(390,370);
            glVertex2f(378,370);
            glVertex2f(400,370);///буква Д
            glVertex2f(403,370);
            glVertex2f(403,374);
            glVertex2f(400,374);
            glVertex2f(416,370);
            glVertex2f(419,370);
            glVertex2f(419,374);
            glVertex2f(416,374);
            glVertex2f(400,374);
            glVertex2f(419,374);
            glVertex2f(419,377);
            glVertex2f(400,377);
            glVertex2f(416,374);
            glVertex2f(413,374);
            glVertex2f(413,400);
            glVertex2f(416,400);
            glVertex2f(413,400);
            glVertex2f(408,400);
            glVertex2f(408,397);
            glVertex2f(413,397);
            glVertex2f(407,398);
            glVertex2f(410,398);
            glVertex2f(410,395);
            glVertex2f(407,395);
            glVertex2f(406,391);
            glVertex2f(409,391);
            glVertex2f(409,395);
            glVertex2f(406,395);
            glVertex2f(405,391);
            glVertex2f(408,391);
            glVertex2f(408,388);
            glVertex2f(405,388);
            glVertex2f(404,384);
            glVertex2f(407,384);
            glVertex2f(407,388);
            glVertex2f(404,388);
            glVertex2f(403,384);
            glVertex2f(406,384);
            glVertex2f(406,381);
            glVertex2f(403,381);
            glVertex2f(402,377);
            glVertex2f(405,377);
            glVertex2f(405,381);
            glVertex2f(402,381);
            glVertex2f(429,400);///буква Н
            glVertex2f(432,400);
            glVertex2f(432,370);
            glVertex2f(429,370);
            glVertex2f(443,400);
            glVertex2f(446,400);
            glVertex2f(446,370);
            glVertex2f(443,370);
            glVertex2f(432,384);
            glVertex2f(443,384);
            glVertex2f(443,387);
            glVertex2f(432,387);
            glVertex2f(456,400);////буква Е
            glVertex2f(459,400);
            glVertex2f(459,370);
            glVertex2f(456,370);
            glVertex2f(459,387);
            glVertex2f(471,387);
            glVertex2f(471,384);
            glVertex2f(459,384);
            glVertex2f(459,400);
            glVertex2f(471,400);
            glVertex2f(471,397);
            glVertex2f(459,397);
            glVertex2f(459,373);
            glVertex2f(471,373);
            glVertex2f(471,370);
            glVertex2f(459,370);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(478,390);
            glVertex2f(485,385);
            glVertex2f(485,385);
            glVertex2f(478,380);
            glVertex2f(478,391);
            glVertex2f(486,385);
            glVertex2f(486,385);
            glVertex2f(478,379);
            glVertex2f(478,392);
            glVertex2f(487,385);
            glVertex2f(487,385);
            glVertex2f(478,378);
            glEnd();
        }
        else if(flag_settings.difficulty == HARD){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329,400);///слово СЛОЖНО///буква С
            glVertex2f(341,400);
            glVertex2f(341,397);
            glVertex2f(329,397);
            glVertex2f(329,370);
            glVertex2f(341,370);
            glVertex2f(341,373);
            glVertex2f(329,373);
            glVertex2f(327,396);
            glVertex2f(330,396);
            glVertex2f(330,374);
            glVertex2f(327,374);
            glVertex2f(328,398);
            glVertex2f(331,398);
            glVertex2f(331,395);
            glVertex2f(328,395);
            glVertex2f(328,372);
            glVertex2f(331,372);
            glVertex2f(331,375);
            glVertex2f(328,375);
            glVertex2f(355,400);///буква Л
            glVertex2f(358,400);
            glVertex2f(358,376);
            glVertex2f(355,376);
            glVertex2f(357,373);
            glVertex2f(354,373);
            glVertex2f(354,376);
            glVertex2f(357,376);
            glVertex2f(355,371);
            glVertex2f(352,371);
            glVertex2f(352,374);
            glVertex2f(355,374);
            glVertex2f(353,370);
            glVertex2f(351,370);
            glVertex2f(351,373);
            glVertex2f(353,373);
            glVertex2f(358,400);
            glVertex2f(368,400);
            glVertex2f(368,397);
            glVertex2f(358,397);
            glVertex2f(368,400);
            glVertex2f(371,400);
            glVertex2f(371,370);
            glVertex2f(368,370);
            glVertex2f(383, 400);///буква О
            glVertex2f(394, 400);
            glVertex2f(394, 397);
            glVertex2f(383, 397);
            glVertex2f(383, 370);
            glVertex2f(394, 370);
            glVertex2f(394, 373);
            glVertex2f(383, 373);
            glVertex2f(381, 396);
            glVertex2f(384, 396);
            glVertex2f(384, 374);
            glVertex2f(381, 374);
            glVertex2f(382, 398);
            glVertex2f(385, 398);
            glVertex2f(385, 395);
            glVertex2f(382, 395);
            glVertex2f(382, 372);
            glVertex2f(385, 372);
            glVertex2f(385, 375);
            glVertex2f(382, 375);
            glVertex2f(396, 396);
            glVertex2f(393, 396);
            glVertex2f(393, 374);
            glVertex2f(396, 374);
            glVertex2f(395, 398);
            glVertex2f(392, 398);
            glVertex2f(392, 395);
            glVertex2f(395, 395);
            glVertex2f(395, 372);
            glVertex2f(392, 372);
            glVertex2f(392, 375);
            glVertex2f(395, 375);
            glVertex2f(406,370);///буква Ж
            glVertex2f(409,370);
            glVertex2f(409,400);
            glVertex2f(406,400);
            glVertex2f(416,370);
            glVertex2f(419,370);
            glVertex2f(419,400);
            glVertex2f(416,400);
            glVertex2f(426,370);
            glVertex2f(429,370);
            glVertex2f(429,400);
            glVertex2f(426,400);
            glVertex2f(409,384);
            glVertex2f(426,384);
            glVertex2f(426,387);
            glVertex2f(409,387);
            glVertex2f(439,400);///буква Н
            glVertex2f(442,400);
            glVertex2f(442,370);
            glVertex2f(439,370);
            glVertex2f(453,400);
            glVertex2f(456,400);
            glVertex2f(456,370);
            glVertex2f(453,370);
            glVertex2f(442,384);
            glVertex2f(453,384);
            glVertex2f(453,387);
            glVertex2f(442,387);
            glVertex2f(468,400);///буква О
            glVertex2f(479,400);
            glVertex2f(479,397);
            glVertex2f(468,397);
            glVertex2f(468,370);
            glVertex2f(479,370);
            glVertex2f(479,373);
            glVertex2f(468,373);
            glVertex2f(466,396);
            glVertex2f(469,396);
            glVertex2f(469,374);
            glVertex2f(466,374);
            glVertex2f(467,398);
            glVertex2f(470,398);
            glVertex2f(470,395);
            glVertex2f(467,395);
            glVertex2f(467,372);
            glVertex2f(470,372);
            glVertex2f(470,375);
            glVertex2f(467,375);
            glVertex2f(481,396);
            glVertex2f(478,396);
            glVertex2f(478,374);
            glVertex2f(481,374);
            glVertex2f(480,398);
            glVertex2f(477,398);
            glVertex2f(477,395);
            glVertex2f(480,395);
            glVertex2f(480,372);
            glVertex2f(477,372);
            glVertex2f(477,375);
            glVertex2f(480,375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(488,390);
            glVertex2f(495,385);
            glVertex2f(495,385);
            glVertex2f(488,380);
            glVertex2f(488,391);
            glVertex2f(496,385);
            glVertex2f(496,385);
            glVertex2f(488,379);
            glVertex2f(488,392);
            glVertex2f(497,385);
            glVertex2f(497,385);
            glVertex2f(488,378);
            glEnd();
        }
        else if(flag_settings.difficulty == DARK_SOULS){
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glVertex2f(329, 400);///фраза ОЧЕНЬ СЛОЖНО///буква О
            glVertex2f(340, 400);
            glVertex2f(340, 397);
            glVertex2f(329, 397);
            glVertex2f(329, 370);
            glVertex2f(340, 370);
            glVertex2f(340, 373);
            glVertex2f(329, 373);
            glVertex2f(327, 396);
            glVertex2f(330, 396);
            glVertex2f(330, 374);
            glVertex2f(327, 374);
            glVertex2f(328, 398);
            glVertex2f(331, 398);
            glVertex2f(331, 395);
            glVertex2f(328, 395);
            glVertex2f(328, 372);
            glVertex2f(331, 372);
            glVertex2f(331, 375);
            glVertex2f(328, 375);
            glVertex2f(342, 396);
            glVertex2f(339, 396);
            glVertex2f(339, 374);
            glVertex2f(342, 374);
            glVertex2f(341, 398);
            glVertex2f(338, 398);
            glVertex2f(338, 395);
            glVertex2f(341, 395);
            glVertex2f(341, 372);
            glVertex2f(338, 372);
            glVertex2f(338, 375);
            glVertex2f(341, 375);
            glVertex2f(367,370);///буква Ч
            glVertex2f(370,370);
            glVertex2f(370,400);
            glVertex2f(367,400);
            glVertex2f(351,383);
            glVertex2f(354,383);
            glVertex2f(354,400);
            glVertex2f(351,400);
            glVertex2f(352,383);
            glVertex2f(357,383);
            glVertex2f(357,381);
            glVertex2f(352,381);
            glVertex2f(355,382);
            glVertex2f(360,382);
            glVertex2f(360,379);
            glVertex2f(355,379);
            glVertex2f(355,379);
            glVertex2f(367,379);
            glVertex2f(367,382);
            glVertex2f(355,382);
            glVertex2f(380,400);////буква Е
            glVertex2f(383,400);
            glVertex2f(383,370);
            glVertex2f(380,370);
            glVertex2f(383,387);
            glVertex2f(395,387);
            glVertex2f(395,384);
            glVertex2f(383,384);
            glVertex2f(383,400);
            glVertex2f(395,400);
            glVertex2f(395,397);
            glVertex2f(383,397);
            glVertex2f(383,373);
            glVertex2f(395,373);
            glVertex2f(395,370);
            glVertex2f(383,370);
            glVertex2f(405,400);///буква Н
            glVertex2f(408,400);
            glVertex2f(408,370);
            glVertex2f(405,370);
            glVertex2f(419,400);
            glVertex2f(422,400);
            glVertex2f(422,370);
            glVertex2f(419,370);
            glVertex2f(408,384);
            glVertex2f(419,384);
            glVertex2f(419,387);
            glVertex2f(408,387);
            glVertex2f(432,400);///буква Ь
            glVertex2f(435,400);
            glVertex2f(435,370);
            glVertex2f(432,370);
            glVertex2f(435,370);
            glVertex2f(445,370);
            glVertex2f(445,373);
            glVertex2f(435,373);
            glVertex2f(445,371);
            glVertex2f(448,371);
            glVertex2f(448,386);
            glVertex2f(445,386);
            glVertex2f(445,385);
            glVertex2f(435,385);
            glVertex2f(435,388);
            glVertex2f(445,388);
            glVertex2f(469,400);///слово СЛОЖНО///буква С
            glVertex2f(481,400);
            glVertex2f(481,397);
            glVertex2f(469,397);
            glVertex2f(469,370);
            glVertex2f(481,370);
            glVertex2f(481,373);
            glVertex2f(469,373);
            glVertex2f(467,396);
            glVertex2f(470,396);
            glVertex2f(470,374);
            glVertex2f(467,374);
            glVertex2f(468,398);
            glVertex2f(471,398);
            glVertex2f(471,395);
            glVertex2f(468,395);
            glVertex2f(468,372);
            glVertex2f(471,372);
            glVertex2f(471,375);
            glVertex2f(468,375);
            glVertex2f(495,400);///буква Л
            glVertex2f(498,400);
            glVertex2f(498,376);
            glVertex2f(495,376);
            glVertex2f(497,373);
            glVertex2f(494,373);
            glVertex2f(494,376);
            glVertex2f(497,376);
            glVertex2f(495,371);
            glVertex2f(492,371);
            glVertex2f(492,374);
            glVertex2f(495,374);
            glVertex2f(493,370);
            glVertex2f(491,370);
            glVertex2f(491,373);
            glVertex2f(493,373);
            glVertex2f(498,400);
            glVertex2f(508,400);
            glVertex2f(508,397);
            glVertex2f(498,397);
            glVertex2f(508,400);
            glVertex2f(511,400);
            glVertex2f(511,370);
            glVertex2f(508,370);
            glVertex2f(523, 400);///буква О
            glVertex2f(534, 400);
            glVertex2f(534, 397);
            glVertex2f(523, 397);
            glVertex2f(523, 370);
            glVertex2f(534, 370);
            glVertex2f(534, 373);
            glVertex2f(523, 373);
            glVertex2f(521, 396);
            glVertex2f(524, 396);
            glVertex2f(524, 374);
            glVertex2f(521, 374);
            glVertex2f(522, 398);
            glVertex2f(525, 398);
            glVertex2f(525, 395);
            glVertex2f(522, 395);
            glVertex2f(522, 372);
            glVertex2f(525, 372);
            glVertex2f(525, 375);
            glVertex2f(522, 375);
            glVertex2f(536, 396);
            glVertex2f(533, 396);
            glVertex2f(533, 374);
            glVertex2f(536, 374);
            glVertex2f(535, 398);
            glVertex2f(532, 398);
            glVertex2f(532, 395);
            glVertex2f(535, 395);
            glVertex2f(535, 372);
            glVertex2f(532, 372);
            glVertex2f(532, 375);
            glVertex2f(535, 375);
            glVertex2f(546,370);///буква Ж
            glVertex2f(549,370);
            glVertex2f(549,400);
            glVertex2f(546,400);
            glVertex2f(556,370);
            glVertex2f(559,370);
            glVertex2f(559,400);
            glVertex2f(556,400);
            glVertex2f(566,370);
            glVertex2f(569,370);
            glVertex2f(569,400);
            glVertex2f(566,400);
            glVertex2f(549,384);
            glVertex2f(566,384);
            glVertex2f(566,387);
            glVertex2f(549,387);
            glVertex2f(579,400);///буква Н
            glVertex2f(582,400);
            glVertex2f(582,370);
            glVertex2f(579,370);
            glVertex2f(593,400);
            glVertex2f(596,400);
            glVertex2f(596,370);
            glVertex2f(593,370);
            glVertex2f(582,384);
            glVertex2f(593,384);
            glVertex2f(593,387);
            glVertex2f(582,387);
            glVertex2f(608,400);///буква О
            glVertex2f(619,400);
            glVertex2f(619,397);
            glVertex2f(608,397);
            glVertex2f(608,370);
            glVertex2f(619,370);
            glVertex2f(619,373);
            glVertex2f(608,373);
            glVertex2f(606,396);
            glVertex2f(609,396);
            glVertex2f(609,374);
            glVertex2f(606,374);
            glVertex2f(607,398);
            glVertex2f(610,398);
            glVertex2f(610,395);
            glVertex2f(607,395);
            glVertex2f(607,372);
            glVertex2f(610,372);
            glVertex2f(610,375);
            glVertex2f(607,375);
            glVertex2f(621,396);
            glVertex2f(618,396);
            glVertex2f(618,374);
            glVertex2f(621,374);
            glVertex2f(620,398);
            glVertex2f(617,398);
            glVertex2f(617,395);
            glVertex2f(620,395);
            glVertex2f(620,372);
            glVertex2f(617,372);
            glVertex2f(617,375);
            glVertex2f(620,375);
            glEnd();
            glColor3f(rs2,gs2,bs2);
            glBegin(GL_LINES);///ГАЛОЧКИ <<>>
            glVertex2f(320,390);
            glVertex2f(313,385);
            glVertex2f(313,385);
            glVertex2f(320,380);
            glVertex2f(320,391);
            glVertex2f(312,385);
            glVertex2f(312,385);
            glVertex2f(320,379);
            glVertex2f(320,392);
            glVertex2f(311,385);
            glVertex2f(311,385);
            glVertex2f(320,378);
            glVertex2f(628,390);
            glVertex2f(635,385);
            glVertex2f(635,385);
            glVertex2f(628,380);
            glVertex2f(628,391);
            glVertex2f(636,385);
            glVertex2f(636,385);
            glVertex2f(628,379);
            glVertex2f(628,392);
            glVertex2f(637,385);
            glVertex2f(637,385);
            glVertex2f(628,378);
            glEnd();
        }

    }


    glutSwapBuffers();

}

void draw_game_field(){
    glClearColor(0.1,0.1,0.1,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.9,0.5,0);
    glLineWidth(10);
    glBegin(GL_LINES);
    for (int i=0;i<(flag_settings.side_length+1);i++){
        glVertex2f(0,field_y);///горизонтальные линии
        glVertex2f(100*flag_settings.side_length,field_y);
        glVertex2f(field_x,800);///вертикальные линии
        glVertex2f(field_x,800-flag_settings.side_length*100);

        field_x+=100;
        field_y-=100;
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0,1,0);///КУРСОР
    glVertex2f(cur_x,cur_y);
    glVertex2f(cur_x+100,cur_y);
    glVertex2f(cur_x+100,cur_y-100);
    glVertex2f(cur_x,cur_y-100);
    glVertex2f(cur_x+100,cur_y-103);
    glVertex2f(cur_x+100,cur_y);
    glVertex2f(cur_x,cur_y-103);
    glVertex2f(cur_x,cur_y);
    glEnd();

    local_x=cur_x/100;
    local_y=7-(cur_y/100-1);

    temp_local_x=local_x;
    temp_local_y=local_y;
    temp_global_x=global_x;
    temp_global_y=global_y;

    global_y-=local_y;
    global_x-=local_x;

    for (local_x=0;local_x<flag_settings.side_length;local_x++){
        for(local_y=0;local_y<flag_settings.side_length;local_y++){
            znak=getValueByCords(getBattlefield(thisGame), global_x, global_y);
            if(znak==CROSS){
                glBegin(GL_LINES);
                glColor3f(1, 0, 1);
                glVertex2f(local_x*100+50+30, 800-100*local_y-50+30);
                glVertex2f(local_x*100+50-30, 800-100*local_y-50-30);
                glVertex2f(local_x*100+50+30, 800-100*local_y-50-30);
                glVertex2f(local_x*100+50-30, 800-100*local_y-50+30);
                glEnd();
            }
            else if(znak==ZERO){
                glColor3f(0.2,1,1);
                glBegin(GL_QUADS);
                glLineWidth(40);
                glVertex2f(local_x*100+50-30,800-100*local_y-50);
                glVertex2f(local_x*100+50, 800-100*local_y-50+30);
                glVertex2f(local_x*100+50+30, 800-100*local_y-50);
                glVertex2f(local_x*100+50, 800-100*local_y-50-30);
                glColor3f(0,0,0);
                glVertex2f(local_x*100+50-23,800-100*local_y-50);
                glVertex2f(local_x*100+50, 800-100*local_y-50+23);
                glVertex2f(local_x*100+50+23, 800-100*local_y-50);
                glVertex2f(local_x*100+50, 800-100*local_y-50-23);
                glEnd();
            }
            global_y++;
        }
        global_x++;
        global_y=temp_global_y-temp_local_y;
    }
    global_x=temp_global_x-temp_local_x;


    local_x=cur_x/100;
    local_y=7-(cur_y/100-1);

    if(flag_settings.side_length<8){
        global_x += local_x;
        global_y += local_y;
    }
    else {
        global_x += local_x;
        global_y += local_y;
    }


    glutSwapBuffers();
    field_y=800;
    field_x=0;
}

void push_special_keys (key,  x,  y){

    if(key == GLUT_KEY_DOWN ) {
        if (global_menu.inside_set){
            if(global_menu.number_string<4){
                global_menu.number_string++;
                if(global_menu.number_string==4){
                    rs1=1;
                    gs1=1;
                    bs1=1;
                    rs2=1;
                    gs2=1;
                    bs2=1;
                    rs3=1;
                    gs3=1;
                    bs3=1;
                    rs4=1;
                    gs4=0;
                    bs4=0;
                }
                else if(global_menu.number_string==3){
                    rs1=1;
                    gs1=1;
                    bs1=1;
                    rs2=1;
                    gs2=1;
                    bs2=1;
                    rs3=1;
                    gs3=0;
                    bs3=0;
                    rs4=1;
                    gs4=1;
                    bs4=1;
                }
                else if(global_menu.number_string==2){
                    rs1=1;
                    gs1=1;
                    bs1=1;
                    rs2=1;
                    gs2=0;
                    bs2=0;
                    rs3=1;
                    gs3=1;
                    bs3=1;
                    rs4=1;
                    gs4=1;
                    bs4=1;
                }



            }
            else{
                global_menu.number_string=1;
                rs1=1;
                gs1=0;
                bs1=0;
                rs2=1;
                gs2=1;
                bs2=1;
                rs3=1;
                gs3=1;
                bs3=1;
                rs4=1;
                gs4=1;
                bs4=1;
            }
        }

        else if(!global_menu.inside_set) {

            if (global_menu.game_on) {
                if(global_y<(flag_settings.side_length-1)) {
                    global_y++;
                    if (cur_y <= 800 && cur_y > (800 - (flag_settings.side_length - 1) * 100) && cur_y >= 200)
                        cur_y -= 100;
                }
                glutPostRedisplay();
            } else if (!global_menu.game_on) {
                if (coord > 235) {
                    coord -= 50;
                    if (coord == 385) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 1;
                        g1 = 0;
                        b1 = 0;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 335) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 1;
                        g2 = 0;
                        b2 = 0;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 285) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 1;
                        g3 = 0;
                        b3 = 0;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 235) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 1;
                        g4 = 0;
                        b4 = 0;
                    }
                } else {
                    coord += 200;
                    r = 1;
                    g = 0;
                    b = 0;
                    r1 = 0;
                    g1 = 1;
                    b1 = 1;
                    r2 = 0;
                    g2 = 1;
                    b2 = 1;
                    r3 = 0;
                    g3 = 1;
                    b3 = 1;
                    r4 = 0;
                    g4 = 1;
                    b4 = 1;
                }
            }
        }

        edge=327;
        Sedge=327;
        glutPostRedisplay();
    }
    else if (key == GLUT_KEY_UP){
        if(global_menu.inside_set){
            if(global_menu.number_string>1){
                global_menu.number_string--;
                if(global_menu.number_string==1){
                    rs1=1;
                    gs1=0;
                    bs1=0;
                    rs2=1;
                    gs2=1;
                    bs2=1;
                    rs3=1;
                    gs3=1;
                    bs3=1;
                    rs4=1;
                    gs4=1;
                    bs4=1;
                }
                else if(global_menu.number_string==2){
                    rs1=1;
                    gs1=1;
                    bs1=1;
                    rs2=1;
                    gs2=0;
                    bs2=0;
                    rs3=1;
                    gs3=1;
                    bs3=1;
                    rs4=1;
                    gs4=1;
                    bs4=1;
                }
                else if(global_menu.number_string==3){
                    rs1=1;
                    gs1=1;
                    bs1=1;
                    rs2=1;
                    gs2=1;
                    bs2=1;
                    rs3=1;
                    gs3=0;
                    bs3=0;
                    rs4=1;
                    gs4=1;
                    bs4=1;
                }
            }
            else{
                global_menu.number_string=4;
                rs1=1;
                gs1=1;
                bs1=1;
                rs2=1;
                gs2=1;
                bs2=1;
                rs3=1;
                gs3=1;
                bs3=1;
                rs4=1;
                gs4=0;
                bs4=0;
            }
        }
        else if(!global_menu.inside_set) {

            if (global_menu.game_on) {
                if(global_y>0){
                    global_y--;
                    if(cur_y<800 && cur_y>=(800-(flag_settings.side_length-1)*100)) cur_y+=100;
                }
                glutPostRedisplay();
            }
            else if (!global_menu.game_on) {

                if (coord < 435) {
                    coord += 50;
                    if (coord == 435) {
                        r = 1;
                        g = 0;
                        b = 0;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 385) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 1;
                        g1 = 0;
                        b1 = 0;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 335) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 1;
                        g2 = 0;
                        b2 = 0;
                        r3 = 0;
                        g3 = 1;
                        b3 = 1;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    } else if (coord == 285) {
                        r = 0;
                        g = 1;
                        b = 1;
                        r1 = 0;
                        g1 = 1;
                        b1 = 1;
                        r2 = 0;
                        g2 = 1;
                        b2 = 1;
                        r3 = 1;
                        g3 = 0;
                        b3 = 0;
                        r4 = 0;
                        g4 = 1;
                        b4 = 1;
                    }

                } else {
                    coord -= 200;
                    r = 0;
                    g = 1;
                    b = 1;
                    r1 = 0;
                    g1 = 1;
                    b1 = 1;
                    r2 = 0;
                    g2 = 1;
                    b2 = 1;
                    r3 = 0;
                    g3 = 1;
                    b3 = 1;
                    r4 = 1;
                    g4 = 0;
                    b4 = 0;
                }
            }

        }

        edge=327;
        Sedge=327;
        glutPostRedisplay();
    }

    else if(key==GLUT_KEY_RIGHT){
        if(global_menu.inside_set){
            if(global_menu.number_string==1){
                if(flag_settings.first_move == GAMER){
                    flag_settings.first_move=BOT;
                    setFirstMove(settings, BOT);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.first_move == BOT){
                    flag_settings.first_move=GAMER;
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
            }
            else if(global_menu.number_string==2){
                if(flag_settings.difficulty == EASY){
                    flag_settings.difficulty=MEDIUM;
                    setComplexity(settings, MEDIUM);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == MEDIUM){
                    flag_settings.difficulty=HARD;
                    setComplexity(settings, HARD);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == HARD){
                    flag_settings.difficulty=DARK_SOULS;
                    setComplexity(settings, DARK_SOULS );
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == DARK_SOULS){
                    flag_settings.difficulty=EASY;
                    setComplexity(settings, EASY);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }

            }
            else if(global_menu.number_string==3){
                if(flag_settings.line_length<flag_settings.side_length) {
                    flag_settings.line_length++;
                    setWinLineLength(settings, flag_settings.line_length);
                    memset(Line_Length, '\0', 100);
                    sprintf(Line_Length, "%d", flag_settings.line_length);
                    edge = 327;
                    Sedge = 327;
                    glutPostRedisplay();
                }
            }
            else if(global_menu.number_string==4){
                flag_settings.side_length++;
                setFieldSize(settings,flag_settings.side_length);
                memset(Side_Length,'\0',100);
                sprintf(Side_Length,"%d",flag_settings.side_length);
                Sedge=327;
                edge=327;
                glutPostRedisplay();
            }
        }

        else if (global_menu.game_on && !global_menu.inside_set){
            if(global_x<(flag_settings.side_length-1)) {
                global_x++;
                if (cur_x >= 0 && cur_x < (flag_settings.side_length - 1) * 100 && cur_x < 700) cur_x += 100;

            }
            glutPostRedisplay();
        }
    }
    else if(key==GLUT_KEY_LEFT){
        if(global_menu.inside_set){
            if(global_menu.number_string==1){
                if(flag_settings.first_move == GAMER){
                    flag_settings.first_move=BOT;
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.first_move == BOT){
                    flag_settings.first_move=GAMER;
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
            }
            else if(global_menu.number_string==2){
                if(flag_settings.difficulty == EASY){
                    flag_settings.difficulty=DARK_SOULS;
                    setComplexity(settings, DARK_SOULS);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == MEDIUM){
                    flag_settings.difficulty=EASY;
                    setComplexity(settings, EASY);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == HARD){
                    flag_settings.difficulty=MEDIUM;
                    setComplexity(settings, MEDIUM);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
                else if(flag_settings.difficulty == DARK_SOULS){
                    flag_settings.difficulty=HARD;
                    setComplexity(settings, HARD);
                    edge=327;
                    Sedge=327;
                    glutPostRedisplay();
                }
            }
            else if(global_menu.number_string==3){
                if(flag_settings.line_length>3 ) {
                    flag_settings.line_length--;
                    setWinLineLength(settings, flag_settings.line_length);
                }
                memset(Line_Length,'\0',100);
                sprintf(Line_Length,"%d",flag_settings.line_length);
                edge=327;
                Sedge=327;
                glutPostRedisplay();
            }
            else if(global_menu.number_string==4){
                if(flag_settings.side_length>3 && flag_settings.line_length<flag_settings.side_length) {
                    flag_settings.side_length--;
                    setFieldSize(settings,flag_settings.side_length);
                }
                memset(Side_Length,'\0',100);
                sprintf(Side_Length,"%d",flag_settings.side_length);
                Sedge=327;
                edge=327;
                glutPostRedisplay();
            }
        }

        else if (global_menu.game_on && !global_menu.inside_set){
            if(global_x>0) {
                global_x--;
                if (cur_x > 0 && cur_x <= (flag_settings.side_length - 1) * 100) cur_x -= 100;
            }
            glutPostRedisplay();
        }
    }
}

void push_keyboard(key,x,y){

    if (key == 13) {
        if (coord==435) {
            global_menu.enter_name=1;
            if(global_menu.enter_name) {
                if(!global_menu.start_game && !global_menu.game_on) {
                    glutDisplayFunc(print_enter_your_name);
                    glutPostRedisplay();
                }
                else {
                    if (strlen(gamer_name) > 17) {
                        global_menu.game_on = 1;
                        global_x = 0;
                        global_y = 0;
                        cur_y = 800;
                        cur_x = 0;
                        setPlayerName(settings, gamer_name);
                        if (global_menu.start_game){
                            thisGame = createNewGame(settings, ratingTable);
                            global_menu.start_game=0;
                        }


                        glutDisplayFunc(draw_game_field);

                        global_menu.enter_name=0;
                        glutPostRedisplay();
                    }
                }

            }
            else if(!global_menu.enter_name) {
                global_menu.game_on=1;
                global_x=0;
                global_y=0;
                cur_y=800;
                cur_x=0;
                thisGame=createNewGame(settings,ratingTable);
                glutDisplayFunc(draw_game_field);
                glutPostRedisplay();
            }
        }
        else if(coord==385){
            glutDisplayFunc(draw_settings);
            global_menu.inside_set=1;
            edge=327;
            Sedge=327;
            glutPostRedisplay();
        }
        else if(coord==335){
            glutDisplayFunc(draw_about_game);

            glutPostRedisplay();
        }

        else if(coord==285){
            glutDisplayFunc(rate_table);
            glutPostRedisplay();

        }
        else if(coord==235){
            ratingTable=updateRateTable(ratingTable, getFirstPlayer(thisGame), delta);
            safeTable(ratingTable);
            closeTable(ratingTable);
            end(thisGame);
            glutDestroyWindow(1);
        }
    }

    else if(key==27){
        glutDisplayFunc(drawing_main_menu_one_dark);
        memset(&gamer_name[17], '\0', 15);
        if(global_menu.game_on == 1) {
            ratingTable=updateRateTable(ratingTable, getFirstPlayer(thisGame), delta);
            safeTable(ratingTable);
            closeTable(ratingTable);
            end(thisGame);
        }
        global_menu.inside_set=0;
        global_menu.game_on=0;
        global_menu.start_game=0;
        glutPostRedisplay();
    }
    else if(key==32){
        if(global_menu.game_on){
            znak = getValueByCords(getBattlefield(thisGame), global_x, global_y);

            if(!znak) {
                int botX = 0, botY = 0;
                if(getFirstMove(getSettings(thisGame)) == GAMER) {
                    writeValue(getBattlefield(thisGame), global_x, global_y, CROSS);
                    ++isRaw;
                    if(isRaw == getFieldSize(getSettings(thisGame)) * getFieldSize(getSettings(thisGame))) {
                        gameResult = RAW;
                        //TODO надпись RAW
                    }
                    if(checkWin(getBattlefield(thisGame), global_x, global_y, getWinLineLength(getSettings(thisGame)))) {
                        delta = 10;
                        gameResult = PLAYER_1_WIN;
                        //TODO надпись WIN
                    }
                    setFirstMove(getSettings(thisGame), BOT);
                    godCreation(getBattlefield(thisGame), 0, 0, &botX, &botY);
                    ++isRaw;
                    if(isRaw == getFieldSize(getSettings(thisGame)) * getFieldSize(getSettings(thisGame))) {
                        gameResult = RAW;
                        //TODO надпись RAW
                    }
                    if(checkWin(getBattlefield(thisGame), botX, botY, getWinLineLength(getSettings(thisGame)))) {
                        delta = 0;
                        gameResult = PLAYER_2_WIN;
                        //TODO надпись LOSE
                    }
                    setFirstMove(getSettings(thisGame), GAMER);
                }else {
                    godCreation(getBattlefield(thisGame), 0, 0, &botX, &botY);
                    ++isRaw;
                    if(isRaw == getFieldSize(getSettings(thisGame)) * getFieldSize(getSettings(thisGame))) {
                        gameResult = RAW;
                        //TODO надпись RAW
                    }
                    if(checkWin(getBattlefield(thisGame), botX, botY, getWinLineLength(getSettings(thisGame)))) {
                        delta = 0;
                        gameResult = PLAYER_2_WIN;
                        //TODO надпись LOSE
                    }
                    ++isRaw;
                    if(isRaw == getFieldSize(getSettings(thisGame)) * getFieldSize(getSettings(thisGame))) {
                        gameResult = RAW;
                        //TODO надпись RAW
                    }
                    setFirstMove(getSettings(thisGame), GAMER);
                    writeValue(getBattlefield(thisGame), global_x, global_y, CROSS);
                    if(checkWin(getBattlefield(thisGame), global_x, global_y, getWinLineLength(getSettings(thisGame)))) {
                        delta = 10;
                        gameResult = PLAYER_1_WIN;
                        //TODO надпись WIN
                    }
                    ++isRaw;
                    setFirstMove(getSettings(thisGame), BOT);
                }
                glutDisplayFunc(draw_game_field);
                glutPostRedisplay();
            }

        }
    }
    else if(global_menu.enter_name){

        if(key==27){
            global_menu.enter_name=0;
            memset(&gamer_name[17], '\0', 15);
            glutDisplayFunc(drawing_main_menu_one_dark);
            global_menu.inside_set=0;
            global_menu.game_on=0;
            global_menu.start_game=0;
            glutPostRedisplay();
        }
        else if(key==8){
            if(strlen(gamer_name)>17){
                gamer_name[strlen(gamer_name)-1]='\0';
                glutDisplayFunc(print_enter_your_name);
                glutPostRedisplay();
                global_menu.start_game=1;
            }
        }
        else {
            if(key!=32 && key!=9 && strlen(gamer_name)<32) {
                gamer_name[strlen(gamer_name)] = key;
                glutDisplayFunc(print_enter_your_name);
                glutPostRedisplay();
                global_menu.start_game = 1;
            }
        }
    }
    else if (key=='q'){
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT ) {
            safeGame(thisGame);
            ratingTable=updateRateTable(ratingTable, getFirstPlayer(thisGame), delta);
            safeTable(ratingTable);
            closeTable(ratingTable);
            end(thisGame);
            glutDestroyWindow(1);
        }
    }
}

void default_gue_settings(){
    flag_settings.first_move = GAMER;
    flag_settings.difficulty=EASY;
    global_menu.number_string=1;
    global_menu.inside_set=0;
    flag_settings.line_length=3;
    flag_settings.side_length=3;
    global_menu.game_on=0;
    global_menu.start_game=0;
    Line_Length[0]='3';
    Side_Length[0]='3';
}

int main(int argc, char * argv[]) {
    settings = loadDefaultSettings();
    ratingTable = loadRateTable();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutCreateWindow("OpenGL lesson 1");
    default_gue_settings();
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawing_main_menu_one_dark);
    glutSpecialFunc(push_special_keys);
    glutKeyboardFunc(push_keyboard);
    glutMainLoop();
    //int znak = getValueByCords(getBattlefield(thisGame), 0, 0);
    //writeValue(getBattlefield(thisGame), 0, 0, CROSS);

    return 0;
}
