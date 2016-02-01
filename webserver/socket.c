#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


int creer_serveur(int port)
{
   int                socket_serveur;
   struct sockaddr_in addr;

   socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
   if (socket_serveur == -1)
   {
      perror("socket_serveur");
      return -1;
   }

   addr.sin_family      = AF_INET;
   addr.sin_port        = htons(port);
   addr.sin_addr.s_addr = INADDR_ANY;

   int optval = 1;
   if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
   {
      perror("Can not set SO_REUSEADDR option");
   }

   if (bind(socket_serveur, (struct sockaddr *)&addr, sizeof(addr)) == -1)
   {
      perror("bind socket_serveur");
      return -1;
   }

   if (listen(socket_serveur, 10) == -1)
   {
      perror("listen socket_serveur");
      return -1;
   }
   return socket_serveur;
}