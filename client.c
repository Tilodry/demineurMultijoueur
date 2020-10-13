#include "client.h"
int main(int argc,char **argv, char **env)
{
    SocketTCP s;
    int waiwiw[7] = {0,0,0,0,0};
    char reception[1000];
    char where[3] = {'0', 'R', '0'};

    if (argc < 3)
    {
   	  	fprintf(stderr,"Essayez plûtot comme ça : %s \"server\" \"port\"\n",argv[0]);
    	return(1);
    }

    while(1)
    {
        s = TCP_Ouvrir(1) ;
        printf("Appuyez sur une touche");
        where[1] = pression();
        if (!TCP_Connecter( s,argv[1], atoi(argv[2]) ))
		{
			printf("La connexion avec le serveur à échouée, vérifiez son état\n\n");
		}
        TCP_Envoyer(s, &waiwiw, sizeof(waiwiw));
        TCP_Recevoir(s, &waiwiw, sizeof(waiwiw));
        if(!waiwiw[1])
        {
            printf("Ca alors, vous êtes le premier utilisateur, vous définissez la taille du terrain !\n");
			waiwiw[1] = 1;
			waiwiw[2] = tailleX();
			waiwiw[3] = tailleY();
			waiwiw[4] = nbBombe(waiwiw[2], waiwiw[3]);
			TCP_Envoyer(s, &waiwiw, sizeof(waiwiw)); printf("Envoie de waiwiw en dehors de la boucle\n");
   			TCP_Recevoir(s, &reception, sizeof(reception)); printf("Reception de waiwiw en dehors de la boucle\n");
        }
        else
        {
			TCP_Envoyer(s, &waiwiw, sizeof(waiwiw)); printf("Envoie de waiwiw dans la boucle\n");
            TCP_Recevoir(s, &waiwiw, sizeof(waiwiw));
            TCP_Envoyer(s, &where, sizeof(where));
			TCP_Recevoir(s, &reception, sizeof(reception)); printf("Reception de waiwiw dans la boucle\n");
            system("clear");
            printf("Score du joueur A : %d ; Score du joueur B : %d", waiwiw[5], waiwiw[6]);		
			showTerrain(reception, waiwiw[2], waiwiw[3]);
        }
        TCP_Fermer(s);


    }
}