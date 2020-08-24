#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>

#define SERVER_STRING "Server: TinyHttpd/0.0.1\r\n"

void unimplemented(const int client);
void bad_request(int client);
void not_found(int client);
void die(const char *s);
void headers(int client, const char *filename);

#endif
