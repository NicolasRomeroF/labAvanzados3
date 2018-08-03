#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int sizeCadena(FILE* archivo);

char* leerArchivo(FILE* archivo);

void unir(char* distribucion, long* min, char valor, char* auxDist, int auxSize, int i);

void unirse(FILE* salida, char* distribucion);

int inicio();

#endif
