#ifndef __SOCKET_H__
#define __SOCKET_H__


enum http_method
{
   HTTP_GET,
   HTTP_UNSUPPORTED,
};

typedef struct
{
   enum http_method method;
   int              major_version;
   int              minor_version;
   char             *url;
} http_request;

int creer_serveur(int port);
void initialiser_signaux(void);
void traitement_signal(int sig);
char* fgets_or_exit(char *buffer, int size, FILE *stream);
int parse_http_request(const char *request_line, http_request *request);
void skip_headers(FILE *client);
void send_status(FILE *client, int code, const char *reason_phrase);
void send_response(FILE *client, int code, const char *reason_phrase, const char *message_body);
char *rewrite_url(char *url);

#endif