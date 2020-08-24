#!Makefile
CC = gcc
CFLAGS = -g -W -Wall -lpthread

SRC =  $(wildcard *.c)

all: httpd
httpd: httpd.c util.c
	$(CC) $(CFLAGS) $(SRC) -o httpd
