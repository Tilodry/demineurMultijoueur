
/*
	donnee : array [O,,255] of Byte ;
Ouvrir() : SocketTCP ;

TCP_Fermer( 		s 		: SocketTCP ) 	;

TCP_Attacher(		s 		: SocketTCP	;
			port 		: entier	) booléen ;

TCP_Envoyer( 		s 		: SocketTCP 	;
			données 	: Tampon 	;
			adresse 	: chaine 	;
			port 		: entier 	) entier ;

TCP_Recevoir(		s 		: SocketTCP 	;
			données 	: pointeur de Tampon 	;
			adresseSource 	: pointeur de Tampon 	) entier ;
*/

//#ifdef MONIAPLUGIN_LINUX
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//#endif

#ifdef MONIAPLUGIN_WIN32

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ws2tcpip.h>
#include <unistd.h>
#define MINGW32
int WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD,
		       char*,DWORD,int);
void bzero(void* a, int l){ //TODO mieux
	int i ;
	for( i = 0; i< l; i++)
		((char*)a)[i] = 0 ;
}

#endif

#define HAUT 65
#define BAS 66
#define DROITE 67
#define GAUCHE 68
#define m 109
#define SPACE 32
#define ECHAP 27
#define MODEFLECHE '['

typedef short 	SocketTCP ;
typedef enum 	_booleen{ Faux , Vrai } booleen;
typedef short 	entier ;
typedef char * 	chaine ;


SocketTCP TCP_Ouvrir(	entier debug);

void TCP_Fermer(	SocketTCP s);

booleen TCP_Attacher( 	SocketTCP sServeur, 
			entier port );

entier TCP_Envoyer( 	SocketTCP sCliente, 
			void * donneesAEcrire,
			entier tailleDonneeAEcrire );

entier TCP_Recevoir( 	SocketTCP sCliente, 
			void * donnees,
			entier tailleDonneeMax  );

SocketTCP TCP_Accepter(	SocketTCP sServeur, 
			chaine adresse,
			entier tailleAdresseMax );

booleen TCP_Connecter( 	SocketTCP s, 
			chaine adresse, 
			entier port );


