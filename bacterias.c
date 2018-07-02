#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

char* leerArchivo(FILE* archivo)
{
    int size = sizeCadena(archivo);
    char* distribucion = (char*)malloc(sizeof(char)*size);

    fscanf(archivo,"%s",distribucion);
    return distribucion;
}

void unir(char* distribucion, int* min, char valor, char* auxDist, int auxSize, int i)
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
    int aux = strtol(auxDist,&end,10);
    int test = *min;
    if(test>aux)
    {
        *min=aux;
    }
}

void unirse(FILE* salida, char* distribucion)
{
    fprintf(salida,"%s\n",distribucion);
    int i;
    int auxSize = strlen(distribucion)+1;
    char* end;
    int min = strtol(distribucion,&end,10);
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
            fprintf(salida,"%d\n",min);
        }
        else
        {
            flag = 0;
        }
        

        auxSize--;
        free(distribucion);
        distribucion=(char*)malloc(sizeof(char)*auxSize);
        sprintf(distribucion,"%d",min);
    }
}

int main(){
    FILE* entrada = fopen("Entrada.in","r");
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
    
    return 0;
}