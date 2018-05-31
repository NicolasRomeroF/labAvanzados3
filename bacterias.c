#include <stdio.h>
#include <stdlib.h>

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
    printf("size:%d %s",size,distribucion);
    return distribucion;
}

int main(){
    FILE* entrada = fopen("Entrada.in","r");
    if(entrada==NULL)
    {
        printf("Error al abrir el archivo de entrada \n");
        return 1;
    }
    leerArchivo(entrada);
    
    return 0;
}