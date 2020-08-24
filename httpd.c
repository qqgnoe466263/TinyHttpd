#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

#define ISspace(x) isspace((int)x)
int get_line(int sock, char *buf, int size);


void execute_cgi(client, path, method, query_string)
{
    return;
}


void cat(int client, FILE *resource)
{
	char buf[1024];
    fgets(buf, sizeof(buf), resource);
    while (!feof(resource)) {
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}

/*
 * Send a regular file to the client. Use headers, and report
 * errors to client if they occur.
 * */
void serve_file(int client, const char *filename)
{
    FILE *resource = NULL;
    int numchars = 1;
    char buf[1024];
    
    /* make sure buf has something to into loop */
    buf[0] = 'A';
    buf[1] = '\x00';

    while ((numchars > 0) && strcmp("\n", buf))
        numchars = get_line(client, buf, sizeof(buf));

    resource = fopen(filename, "r");
    if (resource == NULL)
        not_found(client);
    else {
        headers(client, filename);
        cat(client, resource);
    }
    fclose(resource);
}


int get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\x00';
    int n = 0;
    
    while ((i < size - 1) && (c != '\n')) {
        n = recv(sock, &c, 1, 0); 
        if (n > 0) {
            if (c == '\r') {
                n = recv(sock, &c, 1, MSG_PEEK);
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
        }
        buf[i] = c;
        i++;
    }
    buf[i] = '\x00';

    return i;
}

   
/* A request has caused a call to accept() on the server port to 
 * return. Process the request qppropriately.
 * */
void accept_request(const int client)
{
    char buf[1024];
    char method[255];
    char url[255];
    char path[512];
    size_t i = 0, j = 0;
    /* becomes true if server decides the is
     * a cgi program
     * */
    int cgi = 0;
    struct stat st;
    char *query_string = NULL;


    int numchars = get_line(client, buf, sizeof(buf));

    /* First line is request line like POST GET .... methods */
    while (!ISspace(buf[j]) && (i < sizeof(method) - 1)) {
        method[i] = buf[j];
        i++; j++;
    }
    method[i] = '\x00';

    if (strcasecmp(method, "GET") && strcasecmp(method, "POST")) {
        unimplemented(client); 
        return;
    }

    if (strcasecmp(method, "POST") == 0)
        cgi = 1;

    i = 0;
    /* bypass all blank-space */
    while (ISspace(buf[j]) && (j < sizeof(buf)))
        j++;

    /* parse URL */
    while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf))) {
        url[i] = buf[j];
        i++; j++;
    }
    url[i] = '\x00';

    if (strcasecmp(method, "GET") == 0) {
        query_string = url;

        /*
         * travesing the URL to find the ? it is 
         * indicated that we need cgi to handle the
         * paramters.
         * */
        while ((*query_string != '?') && (*query_string != '\x00'))
            query_string++;
        
        if (*query_string == '?') {
            cgi = 1;
            *query_string = '\x00';
            query_string++;
        }
    }

    printf("[D] %s \n", path);
    if (path[strlen(path) - 1] == '/')
        strcat(path, "index.html");

    /* printf("[D] %s \n", path);
     * -> htdocs/index.html
     * */
    
    if (stat(path, &st) == -1) {
        while ((numchars > 0) && strcmp("\n", buf))
            numchars = get_line(client, buf, sizeof(buf));
        not_found(client);
    } else {
        /* if this file is a dir */
	    if ((st.st_mode & S_IFMT) == S_IFDIR)	
            strcat(path, "/index.hmtl");

        /* if this file is an executable file */
        if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)) {
            cgi = 1; 
        }

        if (!cgi)
            serve_file(client, path);
        else
            execute_cgi(client, path, method, query_string);
	}
    close(client);
}

int startup(u_short *port)
{
    struct sockaddr_in name;

    int httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        die("socket");

    if (*port == 0)
        *port = 8080;

    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        die("bind");

    if (listen(httpd, 5) < 0)
        die("listen");

    return httpd;
}

int main()
{
	int server_sock = -1;
    int client_sock = -1;
	struct sockaddr_in client_name;
    int client_name_len = sizeof(client_name);
    u_short port = 0;
	


    server_sock = startup(&port);
    printf("[+] httpd running on port %d\n", port);
	
    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_name, &client_name_len);
        if (client_sock == -1) {
            die("accept");
        }
        accept_request(client_sock) ;   
    }

    close(server_sock);
    return 0;
	
}
