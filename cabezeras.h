//Diego Andrey Lopez Camal - 1298580
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 9
#define CLEAR "clear"

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[42m\x1b[30m"  
#define BLUE    "\x1b[44m\x1b[37m" 
#define RED     "\x1b[41m\x1b[37m"  
#define YELLOW  "\x1b[43m\x1b[30m"  

typedef struct nodo{
    int val;
    int pos[2];
    int dir[4];
}Nodo;

int** cargarLaberinto();
void imprimirLaberinto(int**, int, Nodo*, int, int**, int, int, int);
Nodo crearNodo(int,int,int**,int);
int existeMovimiento(Nodo*);
void resolverLaberinto(int**, int, Nodo**, int, int, int, int);
void imprimirSolucion(int**,int, Nodo*, int,int);

