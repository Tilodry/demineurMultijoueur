#include "argv.h"
#include "stdio.h"
#include <stdlib.h>
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

int tailleX(void);
int tailleY(void);
int nbBombe(int,int);
void showTerrain(char* jeu, int sizeX, int sizeY);
char pression(void);



