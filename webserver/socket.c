#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

/* Fonction pour créer le serveur */
int creer_serveur(int port)
{
   int                socket_serveur;
   struct sockaddr_in addr;

/* descripteur socket du côté serveur */
   socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
   /* Domaine :   AF_INET  = IPv4 */
   /* Type :   SOCK_STREAM    = TCP */
   /* Protocol :  0     = TCP est le seul protocole, donc 0 */

/* Test erreur */
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

/* On demande à notre socket d'écouter continuellement et d'accepter 10 connexions dans la file d'attente de co */
   if (listen(socket_serveur, 10) == -1)
   {
      perror("listen socket_serveur");
      return -1;
   }
   return socket_serveur;
}

void traitement_signal(int sig)
{
   printf("Signal %d reçu\n", sig);
   int status;
   waitpid(-1, &status, WUNTRACED);
}

void initialiser_signaux(void)
{
   struct sigaction sa;

   sa.sa_handler = traitement_signal;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;
   if (sigaction(SIGCHLD, &sa, NULL) == -1)
   {
      perror("sigaction(SIGCHLD)");
   }
   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
   {
      perror("siignal");
   }
}