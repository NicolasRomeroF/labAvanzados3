#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <funciones.h>

/*Funcion que recibe un archivo con la cadena que representa la distribucion
  inicial de las colonias y devuelve el tamanio de esta.
  Entrada: archivo
  Salida: Tamanio de la colonia*/
int sizeCadena(FILE* archivo)
{
    int i = 0;
    int flag = 1;
    while (flag==1)
    {
        if(fgetc(archivo)=='\n' || feof(archivo))
        {
            flag=0;
        }
        
        else
        {
            i++;
        }
    }
    rewind(archivo);
    return i+1;
}

/*Obtiene la distribucion inicial de las bacterias desde un archivo de texto plano
  Entrada: archivo
  Salida: distribucion inicial de la colonia*/
char* leerArchivo(FILE* archivo)
{
    int size = sizeCadena(archivo);
    char* distribucion = (char*)malloc(sizeof(char)*size);

    fscanf(archivo,"%s",distribucion);
    return distribucion;
}

/*Funcion que reduce en 1 el tamanio de una distribucion fucionando dos colonias
  Entrada: distribucion, minimo actual, valor de la fusion, distribucion auxiliar, tamanio auxiliar, posicion a reemplazar
  Salida: minimo nuevo*/
void unir(char* distribucion, long* min, char valor, char* auxDist, int auxSize, int i)
{
    char* end;
    auxDist=(char*)malloc(sizeof(char)*(auxSize)-1);
    int contU = 0;
    
    while(contU<i)
    {
        auxDist[contU]=distribucion[contU];
        contU++;
    }
    auxDist[i]=valor;
    contU=i+2;
    while(contU<auxSize)
    {
        auxDist[contU-1]=distribucion[contU];
        contU++;
    }
    long aux = strtol(auxDist,&end,10);
    long test = *min;
    if(test>aux)
    {
        *min=aux;
    }
}

/*Funcion que reduce una distribucion de colonias fusionandalos mediante el metodo goloso.
  Entrada: archivo, distribucion inicial
  Salida: Traza de la reduccion*/
void unirse(FILE* salida, char* distribucion)
{
    fprintf(salida,"%s\n",distribucion);
    int i;
    int auxSize = strlen(distribucion)+1;
    char* end;
    long min = strtol(distribucion,&end,10);
    char* auxDist=NULL;
    int flag = 1;
    int cambio = 0;
    while(flag == 1 )
    {
        i = 0;
        while(i+1<auxSize)
        {
            if(distribucion[i] == '1')
            {
                if(distribucion[i+1] == '2')
                { 
                    unir(distribucion, &min, '3', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
                if(distribucion[i+1] == '3')
                {
                    unir(distribucion, &min, '2', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
            }
            if(distribucion[i] == '2')
            {
                if(distribucion[i+1] == '1')
                {
                    unir(distribucion, &min, '3', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
                if(distribucion[i+1] == '3')
                {
                    unir(distribucion, &min, '1', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
            }
            if(distribucion[i] == '3')
            {
                if(distribucion[i+1] == '1')
                {
                    unir(distribucion, &min, '2', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
                if(distribucion[i+1] == '2')
                {
                    unir(distribucion, &min, '1', auxDist, auxSize, i);
                    free(auxDist);
                    cambio = 1;
                }
            }          
            i++;
        }
        if(cambio==1)
        {        
            if(auxSize>0)
            {
                cambio = 0;
            }
            else
            {
                flag = 0;
            }
            fprintf(salida,"%ld\n",min);
        }
        else
        {
            flag = 0;
        }
        

        auxSize--;
        free(distribucion);
        distribucion=(char*)malloc(sizeof(char)*auxSize);
        sprintf(distribucion,"%ld",min);
    }
}

int inicio()
{
    FILE* entrada = fopen("entrada.in","r");
    if(entrada==NULL)
    {
        printf("Error al abrir el archivo de entrada \n");
        return 1;
    }
    char* distribucion = leerArchivo(entrada);
    fclose(entrada);

    FILE* salida = fopen("Salida.out","w");
    if(salida==NULL)
    {
        printf("Error al crear archivo de salida\n");
        return 1;
    }
    unirse(salida,distribucion);
    fclose(salida);
    printf("Archivo de salida creado! \n");
    return 0;
    
}

