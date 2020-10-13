#include "client.h"

int tailleX()
{
    int X;
    printf("\n\rDéfinissez la taille du terrain\n\r");
    printf("Inserez la largeur désirée :\n\r");
    scanf("%d", &X);
    while (X > 100 || X < 5)
    {
        printf("\n\rLargeur désirée non valable, veuillez insérer une largeur comprise entre 5 et 100\n\r");
        scanf("%d", &X);
    }
    return (X);
}

int tailleY()
{
    int Y;
    printf("\n\rInserez la hauteur désirée :\n\r");
    scanf("%d", &Y);
    while (Y > 100 || Y < 5)
    {
        printf("\n\rHauteur désirée non valable, veuillez insérer une hauteur comprise entre 5 et 100\n\r");
        scanf("%d", &Y);
    }
    return (Y);
}

int nbBombe(int X,int Y)
{
    int b;
    printf("\n\rInserez un nombre de bombe\n\r");
    scanf("%d", &b);
    /*while(b > X*Y || b < 1)
    {
        printf("\n\rNombre de bombe désirée non valable, veuillez insérer un nombre de bombe compris entre 1 et %d\n\r",X*Y);
        scanf("%d", &b);
    }*/
    return (b);
}

void showTerrain(char* jeu, int sizeX, int sizeY)
{
    printf("\r\n\n\n");
    int ind = 0;
    for(int i = 0; i<sizeY ; i++)
    {
        for(int j = 0; j<sizeX ; j++)
        {
            printf("    ");
            
                if(jeu[ind] != '.' && jeu[ind] != '*' && jeu[ind] != '#')
                {
                    if (jeu[ind] <= '2')
                    {
                        FGCOLOR(GREEN);
                        printf("%c",jeu[ind]);
                    }
                    else if (jeu[ind] <='4')
                    {
                        FGCOLOR(CYAN);
                        printf("%c",jeu[ind]);

                    }
                    else if (jeu[ind] <='6')
                    {
                        FGCOLOR(YELLOW);
                        printf("%c",jeu[ind]);

                    }
                    else
                    {
                        FGCOLOR(RED);
                        printf("%c",jeu[ind]);
                    } 
                }
                else if (jeu[ind] == '*')
                {
                    FGCOLOR(RED);
                    printf("%c",jeu[ind]);
                }
                else if (jeu[ind]==2)
                {
                    printf("F");
                }
                else if(jeu[ind] == '.')
                {
                    FGCOLOR(WHITE);
                    printf("%c", jeu[ind]);
                }
                else
                {
                    FGCOLOR(WHITE);
                    printf("#");
                } 
            RESET;
            ind ++;
        }
        printf("           ");
        UNDERLINE;
        printf("|%d|\n\r\n\n",i+1);
        RESET;
    }
}

char pression(void)
{
    ttyraw(0);
    unsigned char ch[4] = {0,0,0,0};
    int nblu = 0;
    int i = 0;
    while (nblu == 0 && i != 200)
    {
        i++;
        if (inputAvailable()) nblu = read(STDIN_FILENO,ch,sizeof(ch));
        usleep(1000);
    }
    ttyreset(0);
    if (ch[0] == SPACE)
	{
		return('S');
	}
    if(ch[0] == m)
    {
        return('m');   
    }        
    if(nblu >= 3)
    { // si plus d'un caratère mode echaptement détecté
        switch (ch[2]) 
        {
            case HAUT:
                return ('H');
                break;
            case BAS:
                return ('B');
                break;
            case DROITE:
                return ('D');
                break;
            case GAUCHE:
                return ('G');
                break;
            default:
                break;
        }
    }
    return ('R');   
}