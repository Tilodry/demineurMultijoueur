# demineurMultijoueur
Demineur en version jouable a plusieurs en LAN.
Compilation client : "gcc -Wall -o client client.c fdemineur.c TCP_Plugin.c monconio.c"
Compilation serveur : "gcc -Wall -o serveurdemineur serveurdemineur.c TCP_Plugin.c fdemineur.c monconio.c"
