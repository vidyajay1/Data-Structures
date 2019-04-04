#------------------------------------------------------------------------------
# Vidya Jayaraman
# vijayara
# PA2
# Makefile for CMPS 101-01 Programming Assignment 2
#
#       make                   makes InsertSortLinked
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

DigraphProperties : DigraphProperties.o List.o Digraph.o
	gcc -o DigraphProperties DigraphProperties.o List.o Digraph.o

DigraphProperties.o : DigraphProperties.c List.h Digraph.h
	gcc -c -std=c99 -Wall DigraphProperties.c

DigraphClient: DigraphClient.o List.o Digraph.o
	gcc -o DigraphClient DigraphClient.o List.o Digraph.o

DigraphClient.o : DigraphClient.c List.h Digraph.h
	gcc -c -std=c99 -Wall DigraphClient.c

List.o : List.c List.h 
	gcc -c -std=c99 -Wall List.c 

Digraph.o : Digraph.c Digraph.h List.h 
	gcc -c -std=c99 -Wall Digraph.c 

clean :
	rm -f DigraphProperties DigraphClient DigraphProperties.o DigraphClient.o List.o Digraph.o
 
