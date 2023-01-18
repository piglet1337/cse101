#------------------------------------------------------------------------------
# Ryan Miller, rnmiller
# 2023 Winter CSE101 PA1
# 
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

CC = gcc
CFLAGS = -std=c17 -Wall -g

Lex : Lex.o List.o
	$(CC) $(CFLAGS) -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	$(CC) $(CFLAGS) -c Lex.c

ListClient: ListClient.o List.o
	$(CC) $(CFLAGS) -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	$(CC) $(CFLAGS) -g -c ListClient.c

ListTest: ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	$(CC) $(CFLAGS) -c ListTest.c

List.o : List.c List.h
	$(CC) $(CFLAGS) -c List.c

clean :
	rm -f Lex ListClient ListTest Lex.o ListClient.o List.o ListTest.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex in3 blah3
