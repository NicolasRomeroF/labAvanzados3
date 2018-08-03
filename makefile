CC = gcc

bacterias: funciones.c bacterias.c
		$(CC) -o bacterias funciones.c bacterias.c -I.