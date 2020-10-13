#include "serveur.h"

int initTerrain(CASE* jeu, int sizeX, int sizeY, int bombe)
{
    int at;
    for(int i = 0; i<sizeX*sizeY; i++)
        {
            jeu[i].visible=0;
            jeu[i].val='0';
        }    
    for(int i = 0 ; i<bombe ; i++)
    {
        at = rand() % (sizeX*sizeY);
        if(jeu[at].val!='*')
            {
               jeu[at].val='*';
            }
            else i--;
        }
    int id = 0;
    for (int i = 0 ; i < sizeX*sizeY ; i++)
    {
        if (jeu[id].val == '0')
        {                    
            if ((id) % sizeX != sizeX-1)
            {
                if (jeu[id+1].val=='*') jeu[id].val += 1;
                if (jeu[id-sizeX+1].val=='*') jeu[id].val += 1;
                if (jeu[id+sizeX+1].val=='*') jeu[id].val += 1;
            }
            if (id % sizeX != 0)
            {
                if (jeu[id-sizeX-1].val=='*') jeu[id].val += 1;
                if (jeu[id-1].val=='*') jeu[id].val += 1;
                if (jeu[id+sizeX-1].val=='*') jeu[id].val += 1;                    
            }
            if (jeu[id-sizeX].val=='*') jeu[id].val += 1;
            if (jeu[id+sizeX].val=='*') jeu[id].val += 1;    
        }
        if (jeu[id].val == '0')
        {
            jeu[id].val = '.';
        }
        id++;
    }
    return 1;
}

int looseCondition(CASE* jeu, int absPos)
{
    if(jeu[absPos].val == '*')
    {
        return 2;         
    }
    return 0;
}

int winCondition(CASE* jeu, int sizeX, int sizeY, int bombe)
{
    int check = 0;
    int i;
    for (i = 0 ; i <= sizeX*sizeY ; i++)
    {
        if (jeu[i].visible == 1)
        {
            check += 1;
        }
    }
    if (check >= sizeX*sizeY-bombe)
    {
        return 3;
    }
    else return 0;
}

int caseSpace(CASE* jeu, int absPos, int sizeX,int sizeY)
{
    if (jeu[absPos].visible == 1) return 0;
 	jeu[absPos].visible=1;
    showAround(jeu, sizeX, absPos);
    return 1;
}

int casem(CASE* jeu, int absPos)
{
    if (jeu[absPos].visible == 2)
    {
        jeu[absPos].visible=0;
    }
    else if (jeu[absPos].visible==0)jeu[absPos].visible=2;
    else;

    return 1;
}

int showAround(CASE* jeu, int sizeX, int absPos)
{
    if (jeu[absPos].val=='.')
            {
                if ((absPos) % sizeX != sizeX-1)
                {
                    if (jeu[absPos+1].val != '*' && jeu[absPos+1].visible != 1)
                    {
                        jeu[absPos+1].visible = 1;
                        if (jeu[absPos+1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos+1);
                        }
                    }
                    if (jeu[absPos-sizeX+1].val != '*' && jeu[absPos-sizeX+1].visible != 1)
                    {
                        jeu[absPos-sizeX+1].visible = 1;
                        if (jeu[absPos-sizeX+1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos-sizeX+1);
                        }
                    }
                    if (jeu[absPos+sizeX+1].val != '*' && jeu[absPos+sizeX+1].visible != 1)
                    {
                        jeu[absPos+sizeX+1].visible = 1;
                        if (jeu[absPos+sizeX+1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos+sizeX+1);
                        }
                    }
                }
                if (absPos % sizeX != 0)
                {
                    if (jeu[absPos-1].val != '*' && jeu[absPos-1].visible != 1)
                    {
                        jeu[absPos-1].visible = 1;
                        if (jeu[absPos-1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos-1);
                        }
                    }
                    if (jeu[absPos-sizeX-1].val != '*' && jeu[absPos-sizeX-1].visible != 1)
                    {
                        jeu[absPos-sizeX-1].visible = 1;
                        if (jeu[absPos-sizeX-1].val == '.')
                        {  
                            showAround(jeu, sizeX, absPos-sizeX-1);
                        }
                    }
                    if (jeu[absPos+sizeX-1].val != '*' && jeu[absPos+sizeX-1].visible != 1)
                    {
                        jeu[absPos+sizeX-1].visible = 1;
                        if (jeu[absPos+sizeX-1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos+sizeX-1);
                        }
                    }
                }
                 
                if (jeu[absPos+sizeX].val != '*' && jeu[absPos+sizeX].visible != 1)
                {
                    jeu[absPos+sizeX].visible = 1;
                    if (jeu[absPos+sizeX].val == '.')
                    {
                    showAround(jeu, sizeX, absPos+sizeX);
                    }
                }
                if (jeu[absPos-sizeX].val != '*' && jeu[absPos-sizeX].visible != 1)
                {
                    jeu[absPos-sizeX].visible = 1;
                    if (jeu[absPos-sizeX].val == '.')
                    {
                    showAround(jeu, sizeX, absPos-sizeX);
                    }
                }
            }
    return 1;
}