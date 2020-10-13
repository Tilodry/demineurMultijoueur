#include "serveur.h"
int main(int argc,char **argv, char **env)
{
    srand(time(NULL));
    char serveurDistant[5000] ;
    SocketTCP sServeur, sCliente ;
    int waiwiw[7];
    int setup = 0;
    CASE* jeu;
    //CASE jeu[5000];
    char buffer[10000];
    int y = 1;
    int sizeX = 0;
    int sizeY = 0;
    int bombe = 0;
    char where[3];
    int pos = 0;
    int pos1 = 0;
    int score = 0;
    int score1 = 0;
    if (argc < 2)
    {
   	    fprintf(stderr,"Essayez plûtot comme ça : %s \"port\"\n",argv[0]);
       	return(1);
 	}

    printf("Ouverture TCP...");
    sServeur = TCP_Ouvrir(1);
    if(sServeur < 0)
    {
        printf("    Nous n'avons pas réussi a ouvrir le serveur, contactez Yann\n");
        exit(-1) ;
    }
    else printf("    Réussite\n");


    printf("Attachement au serveur ...");
    if(TCP_Attacher( sServeur, atoi(argv[1]) )  == Faux )
    {
        printf("    Nous n'avons pas réussi a attacher le serveur, contactez Yann\n");
        exit(-2) ;
    } 
    else printf("    Réussite\n");
    printf("Attente du premier client...\n");
    while(1)
    {
        sCliente = TCP_Accepter( sServeur, serveurDistant, 5000 );
        printf("________________________________\n\nClient détécté\n");
        TCP_Recevoir( sCliente, &waiwiw, sizeof(waiwiw));
        waiwiw[1] = setup;
        if (waiwiw[0] == 0)
        {
            waiwiw[0] = y;
            y++;
        }

        waiwiw[5] = score;
        waiwiw[6] = score1;
        printf("%d\n",waiwiw[2] = sizeX);
        waiwiw[3] = sizeY;
        waiwiw[4] = bombe;
        TCP_Envoyer( sCliente, &waiwiw, sizeof(waiwiw));
        if(!setup)
        {
            printf("Dans la boucle %d", setup);
            TCP_Recevoir( sCliente, &waiwiw, sizeof(waiwiw));
            printf("Initialisation de taille à : \n\ntailleX = %d, \ntailleY = %d, \nbombe = %d\n\n", waiwiw[2], waiwiw[3], waiwiw[4]);
            jeu = (CASE*) malloc(sizeof(CASE)*(waiwiw[2]*waiwiw[3]+1));
            //CASE jeu[waiwiw[2]*waiwiw[3]];
            printf("%p", jeu);
            initTerrain(jeu, waiwiw[2], waiwiw[3], waiwiw[4]);
            TCP_Envoyer( sCliente, &waiwiw, sizeof(waiwiw));
            
            //jeu = (CASE*) malloc (sizeof(CASE*)*sizeX*sizeY);
            //CASE* jeu[5000];
            sizeX = waiwiw[2];
            sizeY = waiwiw[3];
            bombe = waiwiw[4];
            
            setup = 1;
        }
        else 
        {
            printf("waiwiw[0] = %d,waiwiw[1] = %d,waiwiw[2] = %d,waiwiw[3] = %d,waiwiw[4] = %d\n", waiwiw[0], waiwiw[1], waiwiw[2], waiwiw[3], waiwiw[4]);
            printf("Sortie de la boucle\n");
            TCP_Recevoir( sCliente, &waiwiw, sizeof(waiwiw));
            TCP_Envoyer( sCliente, &waiwiw, sizeof(waiwiw));
            TCP_Recevoir( sCliente, &where, sizeof(where));
            printf("%c", where[1]);
            if (waiwiw[0] == 1)
            {
            switch (where[1])
            {
                case 'H':
                    if(pos >= sizeX) pos -= sizeX;
                    break;
                case 'B':
                    if(pos < sizeX*sizeY-sizeX)
                    pos += sizeX;
                            break;
                        case 'D':
                            if(pos < sizeX*sizeY-1)
                            pos += 1;
                            break;
                        case 'G':
                            if(pos != 0)
                            pos -= 1;
                            break;
                        case 'S':
                            
                            score += caseSpace(jeu, pos, sizeX, sizeY);
                            if (winCondition(jeu, sizeX, sizeY, bombe))
                            {
                                waiwiw[0] = winCondition(jeu, sizeX, sizeY, bombe);
                            }
                            if (looseCondition(jeu, pos))
                            {
                                waiwiw[0] = looseCondition(jeu, pos);
                            }
                            break;
                        case 'm':
                            casem(jeu, pos);
                            break;
                        default: 
                            break;
                    }
            }
            if (waiwiw[0] == 2)
            {
                switch (where[1])
            {
                case 'H':
                    if(pos1 >= sizeX) pos1 -= sizeX;
                    break;
                case 'B':
                    if(pos1 < sizeX*sizeY-sizeX)
                    pos1 += sizeX;
                            break;
                        case 'D':
                            if(pos1 < sizeX*sizeY-1)
                            pos1 += 1;
                            break;
                        case 'G':
                            if(pos1 != 0)
                            pos1 -= 1;
                            break;
                        case 'S':
                            score1 += caseSpace(jeu, pos1, sizeX, sizeY);
                            if (winCondition(jeu, sizeX, sizeY, bombe))
                            {
                                waiwiw[0] = winCondition(jeu, sizeX, sizeY, bombe);
                            }
                            if (looseCondition(jeu, pos1))
                            {
                                waiwiw[0] = looseCondition(jeu, pos1);
                            }
                            break;
                        case 'm':
                            casem(jeu, pos1);
                            break;
                        default: 
                            break;
                    }
            }
            for (int i = 0 ; i < sizeX * sizeY ; i++)
                    {   
                        if (i == pos)
                        {
                            buffer[i] = 'A';
                        }
                        else if (i == pos1)
                        {
                            buffer[i] = 'B';
                        }
                        else if (jeu[i].visible == 1)
                        {
                            buffer[i]= jeu[i].val;
                        }
                        else if(jeu[i].visible == 2)
                        {
                            buffer[i] = 'F';
                        }
                        else
                        {
                            buffer[i] = '#';
                        }
                    }
    	    TCP_Envoyer(sCliente, buffer, sizeof(buffer) ) ;
        }
    }
}