
#include "TCP_Plugin.h"

booleen TCP_debug = Vrai ;

SocketTCP TCP_Ouvrir(entier debug) {

	#ifdef MINGW32
	WSADATA wsadata;
		if (WSAStartup(MAKEWORD(1,1), &wsadata) == SOCKET_ERROR) {
			printf("Erreur initialisation Winsock");
			return -1;
		}
	#endif
	
	SocketTCP s ;
	if(debug)
		TCP_debug = Vrai ;
	else
		TCP_debug = Faux ;
	s = socket(AF_INET,SOCK_STREAM,0);
	if (s <= 0 )
		perror("TCP_Ouvrir()");
	return s ;
}

void TCP_Fermer(SocketTCP s){
	shutdown(s, 2);
	close(s);
}

booleen TCP_Attacher( 	SocketTCP sServeur, 
			entier port ){
	int on = 1;
	struct sockaddr_in localaddr ; 
	bzero(&localaddr,sizeof(localaddr));

	localaddr.sin_family = AF_INET; /* Protocole internet */
	/* Toutes les adresses IP de la station */
	localaddr.sin_addr.s_addr = INADDR_ANY ; 	

	/* port d'écoute par défaut au-dessus des ports réservés */
	localaddr.sin_port = htons(port);
      	
      	if (setsockopt(sServeur, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0){
          	if(TCP_debug) perror("TCP_Attacher => Problème dans la \
réutilisation d'un port fermé récemment erreur");
        }
	if (	bind(sServeur , (struct sockaddr*)&localaddr,
		   sizeof(localaddr) )  < 0 ) {
		if(TCP_debug) perror("TCP_Attacher => Erreur dans l'attachement \
de la socket, vérifiez si le port est libre");
		return Faux ;
	}

	if ( listen( sServeur ,10 ) < 0 ) { 
		if(TCP_debug) perror("TCP_Attacher => \
Erreur de mise en écoute de la socket");
		return Faux ;
	}

	return Vrai ;
}

entier TCP_Envoyer( 	SocketTCP sCliente, 
			void * donneesAEcrire,
			entier tailleDonneeAEcrire ){
	int retour = 0;
	retour = send( sCliente , donneesAEcrire, tailleDonneeAEcrire, 0 );
	if (retour < 0) { 
		if(TCP_debug) perror("TCP_Envoyer()=> erreur d'envoie des données");
		return -2 ;
	}else
		return retour ;
}

entier TCP_Recevoir( 	SocketTCP sCliente, 
			void * donnees,
			entier tailleDonneeMax  ){
	int retour ;
	retour = recv(sCliente, donnees, tailleDonneeMax, 0 ) ;
	if (retour == -1) { 
		if(TCP_debug) perror("TCP_Recevoir()=> Erreur de reception");
		return -2 ;
	}
	((char *)donnees)[retour] = '\0' ; // au cas ou...

	/*if(TCP_debug) fprintf(stderr, "TCP_Recevoir => reception de %d octects\n", 
			retour );*/
	return retour ;
}

SocketTCP TCP_Accepter(	SocketTCP sServeur, 
			chaine adresse,
			entier tailleAdresseMax ){
	struct sockaddr_in from ;
	unsigned int fromlen = sizeof(from) ;
	SocketTCP retour ;
	char hostBuffer[200] ;
	char serviceBuffer[200] ;
	int port ;

	bzero(&from,sizeof(from));
	
	retour = accept(sServeur, (struct sockaddr *) &from, &fromlen ) ;
	if (retour == -1) { 
		if(TCP_debug) perror("TCP_Accepter(...)");
		return -2 ;
	}

	if( getnameinfo( (struct sockaddr *) &from, fromlen, hostBuffer, 200, 
				serviceBuffer, 200, 0) <0 ){
		strncpy( hostBuffer, 
			"TCP_Accepter => Nom de machine non trouvée, \
pb de reverse DNS", 200 ) ;
	}

	port = ntohs(from.sin_port);
	/*if(TCP_debug) fprintf(stderr, "TCP_Accepter => Connexion en \
provenance de %s:%s(%d)\n", hostBuffer, serviceBuffer,port );*/

	if(tailleAdresseMax > 0 ) 
		adresse[0] = '\0' ;
	snprintf(adresse, tailleAdresseMax, "%s:%s(%d)", 
		hostBuffer,
		serviceBuffer,
		port ) ;

	return retour ;
}


booleen TCP_Connecter( 	SocketTCP s, 
			chaine adresse, 
			entier port ){

	struct sockaddr_in to ;
	struct hostent *toinfo ;
	unsigned int host = 0 ;
	//bzero2(&to, sizeof(to));
	toinfo = gethostbyname(adresse);// adresse est ici le serveur
	if(toinfo == NULL){
		if(TCP_debug) printf("TCP_Connecter => Erreur de recherche de nom\
(dns) de serveur");
	}
	memcpy(&host,toinfo->h_addr_list[0],toinfo->h_length);

	/*if(TCP_debug) printf("TCP_Connecter => connexion à %s:%d =>%d.%d.%d.%d\n", 
				adresse, port, 
				host&0x000000FF, 
				(host&0x0000FF00) >> 8, 
				(host&0x00FF0000) >> 16, 
				host >> 24);*/

	bzero(&to,sizeof(to));

	// Protocole internet 
	to.sin_family = AF_INET;

	// copie l'adresse dans la structure sockaddr_in. 
	memcpy(&to.sin_addr.s_addr,toinfo->h_addr_list[0],toinfo->h_length);

	// port d'écoute par défaut au-dessus des ports réservés
	to.sin_port = htons(port);
	// attention addr->sin_port = port n'est pas valide 
	// addr->sin_port est en ordre réseau 

	//Connect
	if (connect(s,(struct sockaddr*)&to,sizeof(to)) > 0) { 
		if(TCP_debug) printf("TCP_Connecter => Erreur de connexion");
		return Faux ;
	}
	return Vrai ;
}

////////////////////////////////////////////////////////////////////////////////

/*int mainClient(int argc,char **argv, char **env){
	SocketTCP s ;
	entier nbEnvoye = 0 ;
	entier nbRecu = 0 ;
	char reception[256] ;
	char * message = "Quelle heure est il ?" ;
	
	if (argc < 3){
   	  	fprintf(stderr,"usage : %s \"server\" \"port\"\n",argv[0]);
       		return(1);
     	}

	printf( "Connexion a : %s\n", argv[1] ) ;
	
	s = TCP_Ouvrir(1) ;
	if(s < 0){
		printf("Erreur de création de Socket >%d<\n", s );
		exit(-1);
	}
	TCP_Connecter( s,argv[1], atoi(argv[2]) ) ;

	nbEnvoye = TCP_Envoyer( s, message, strlen(message) ) ;
	printf( "%d octets envoyes =>%s<\n", nbEnvoye, message );

	nbRecu = TCP_Recevoir( s, reception, 255 ) ;
	printf( "%d octets recus =>%s<\n", nbRecu, reception ) ;

	TCP_Fermer(s);
	return (0);
}*/


////////////////////////////////////////////////////////////////////////////////

/*#include <time.h>

int main (int argc,char **argv, char **env){
	SocketTCP sServeur, sCliente ;

	entier nbEnvoye = 0 ;
	entier nbRecu = 0 ;

	char reception[256] ;
	char serveurDistant[256] ;

	entier i = 0 ;

	if (argc < 2){
   	  	fprintf(stderr,"usage : %s \"port\"\n",argv[0]);
       		return(1);
     	}

	sServeur = TCP_Ouvrir(1) ;
	if(sServeur < 0)
		exit(-1) ;

	if(TCP_Attacher( sServeur, atoi(argv[1]) )  == Faux )
		exit(-2) ;

	do{
		char * message = NULL ;
		time_t tod;

		sCliente = TCP_Accepter( sServeur, serveurDistant, 255 ) ;
		printf("Connexion entrante : %s\n", serveurDistant ) ;
		i ++ ;
		
		nbRecu = TCP_Recevoir( sCliente, reception, 255 ) ;
		printf( "%d octets recus =>%s<\n", nbRecu, reception ) ;
		
		tod = time(NULL) ;
       		message = ctime( &tod ) ;

		nbEnvoye = TCP_Envoyer( sCliente, message, strlen(message) ) ;
		printf( "%d octets envoyes =>%s<\n", nbEnvoye, message );

		TCP_Fermer( sCliente );

	}while( i < 10 ) ; // 10 conexions entrantes puis fermeture du serveur

	TCP_Fermer(sServeur);

	return (0);
}*/







