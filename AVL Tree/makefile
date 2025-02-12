all: myavl

myavl: main.o funcoes.o
	gcc -o myavl main.o funcoes.o
 
main.o: main.c header.h
	gcc -o main.o main.c -c -W -Wall -pedantic

funcoes.o: funcoes.c header.h
	gcc -o funcoes.o funcoes.c -c -W -Wall -pedantic
 