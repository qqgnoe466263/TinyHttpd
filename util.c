#include "util.h"


/* Return the informational HTTP headers about a file. */
void headers(int client, const char *filename)
{
    char buf[1024];
	/* could use filename to determine file type */
    (void)filename;

	strcpy(buf, "HTTP/1.0 200 OK\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
}


/* Print out an error message with perror() (for system errors; based
 * on value of errno, which indicates system call errors) and exit the
 * program indicating an error. 
 * */
void die(const char *s)
{
    char prefix[] = "[!] ";
    strcat(prefix, s);
    perror(s);
    exit(1);
}
/* Inform the client that the requested web method has not
 * been implemented.
 * */
void unimplemented(const int client)
{
    char buf[1024];
    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<html><head><title>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</title></head>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<body><p>http request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</body></html>\r\n");
    send(client, buf, strlen(buf), 0);
}
   

/* Give a client a 404 not found status message. */
void not_found(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 404 Not Found\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<html><title>Not Found</title>\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<body><p>The server could not fulfill\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "your request because the resource specified\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "is unavailable or nonexistent.\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "</body></html>\r\n");
	send(client, buf, strlen(buf), 0);
}

