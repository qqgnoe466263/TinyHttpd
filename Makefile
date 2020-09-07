#!Makefile
CC = gcc
CFLAGS = -g -W -Wall -lpthread
DEBUG = -D DEBUG
SRC =  $(wildcard *.c)

all: httpd vul-cgi
httpd:
	$(CC) $(CFLAGS) $(SRC) -o httpd

vul-cgi:
	gcc ./htdocs/vul-cgi.c -o ./htdocs/vul-cgi -no-pie

debug: 
	$(CC) $(CFLAGS) $(SRC) $(DEBUG) -o httpd

run:
	./httpd

clean:
	rm httpd ./htdocs/vul-cgi
