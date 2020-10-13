#include "argv.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdio.h>
#include "monconio.h"
#include "ansi.h"
#include <time.h>
#include "TCP_Plugin.h"

#define HAUT 65
#define BAS 66
#define DROITE 67
#define GAUCHE 68
#define m 109
#define SPACE 32
#define ECHAP 27
#define MODEFLECHE '['

typedef struct
    {
        char visible;
        char val;
    } CASE ;

int initTerrain(CASE*, int, int, int);
int winCondition(CASE* jeu, int sizeX, int sizeY, int bombe);
int caseSpace(CASE* jeu, int absPos, int sizeX,int sizeY);
int casem(CASE* jeu, int absPos);
int looseCondition(CASE* jeu, int absPos);
int showAround(CASE* jeu, int sizeX, int absPos);
