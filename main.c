#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char marca[20];
    int tipo;
    float peso;

}eVehiculo;
eVehiculo* vehiculo_new();
eVehiculo* vehiculo_newParametros(char* idStr,char* marcaStr,char* tipoStr,char* pesoStr);
int vehiculo_setId(eVehiculo* this, int id);
int vehiculo_setMarca(eVehiculo* this, char marca[]);
int vehiculo_setTipo(eVehiculo* this, int tipo);
int vehiculo_setPeso(eVehiculo* this,float peso);

int vehiculo_getId(eVehiculo* this,int* id);
int vehiculo_getMarca(eVehiculo* this,char* marca);
int vehiculo_getTipo(eVehiculo* this,int* tipo);
int vehiculo_getPeso(eVehiculo* this,float* peso);

int parser_vehiculoToBin(FILE* pFile ,eVehiculo* pVehiculo);
int controller_saveAsBinary(char* path , eVehiculo* pVehiculo);
int controller_saveAsText(char* path ,eVehiculo* pVehiculo);



int main()
{
    eVehiculo* aux;
    int id;
    int tipo;
    char marca[20];
    float peso;

    aux =  vehiculo_newParametros("25","Volvo","1","20");

    vehiculo_getId(aux,&id);
    vehiculo_getTipo(aux,&tipo);
    vehiculo_getMarca(aux,marca);
    vehiculo_getPeso(aux,&peso);

    printf("%d %d %s %f",aux->id,aux->tipo,aux->marca,aux->peso);

    controller_saveAsBinary("vehiculo.bin" ,aux);
    controller_saveAsText("vehiculo.txt",aux);

    return 0;

}

eVehiculo* vehiculo_new()
{
    eVehiculo* newVehiculo = (eVehiculo*) malloc(sizeof(eVehiculo));

    if(newVehiculo != NULL)
    {
        newVehiculo->id = 0;
        strcpy(newVehiculo->marca, " ");
        newVehiculo->tipo = 0;
        newVehiculo->peso = 0;
    }

    return newVehiculo;
}

eVehiculo* vehiculo_newParametros(char* idStr,char* marcaStr,char* tipoStr,char* pesoStr)
{
    eVehiculo* nuevoVehiculo = vehiculo_new();

    if(nuevoVehiculo != NULL)
    {
        if(!(vehiculo_setId(nuevoVehiculo,atoi(idStr))&&
                vehiculo_setMarca(nuevoVehiculo,marcaStr)&&
                vehiculo_setTipo(nuevoVehiculo,atoi(tipoStr))&&
                vehiculo_setPeso(nuevoVehiculo,atof(pesoStr))))
        {
            free(nuevoVehiculo);
            nuevoVehiculo = NULL;
        }
    }

    return nuevoVehiculo;
}

int vehiculo_setId(eVehiculo* this, int id)
{
    int todoOk = 0;

    if(this != NULL && id >0)
    {
        this->id = id;
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_setMarca(eVehiculo* this, char marca[])
{
    int todoOk = 0;

    if(this != NULL && strlen(marca) >2  && strlen(marca) < 25)
    {
        strcpy(this->marca,marca);
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_setTipo(eVehiculo* this, int tipo)
{
    int todoOk = 0;

    if(this != NULL && tipo >0)
    {
        this->tipo = tipo;
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_setPeso(eVehiculo* this,float peso)
{
    int todoOk = 0;

    if (this != NULL && peso > 0)
    {
        this->peso = peso;
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_getId(eVehiculo* this,int* id)
{
    int todoOk = 0;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_getMarca(eVehiculo* this,char* marca)
{
    int todoOk = 0;

    if(this != NULL && marca != NULL)
    {
        strcpy(marca,this->marca);
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_getTipo(eVehiculo* this, int* tipo)
{
    int todoOk = 0;

    if(this != NULL && tipo > 0)
    {
        *tipo = this->tipo;
        todoOk = 1;
    }

    return todoOk;
}

int vehiculo_getPeso(eVehiculo* this,float* peso)
{
    int todoOk = 0;

    if(this != NULL && peso != NULL)
    {
        *peso = this->peso;
        todoOk = 1;
    }

    return todoOk;
}

int parser_vehiculoToBin(FILE* pFile , eVehiculo* pVehiculo)
{
	int todoOk = -1;

	if(pFile != NULL && pVehiculo != NULL)
	{
		fwrite(pVehiculo, sizeof(eVehiculo), 1, pFile);

		todoOk = 0;
	}

	return todoOk;
}

int controller_saveAsBinary(char* path , eVehiculo* pVehiculo)
{
	int todoOk = -1;
	FILE* pFile;

	pFile = fopen(path, "wb");

	if(pFile != NULL && pVehiculo != NULL)
	{
		parser_vehiculoToBin(pFile, pVehiculo);
		fclose(pFile);
		todoOk = 0;
		printf("Datos guardados con exito\n");
	}
	else
	{
		printf("Error al guardar el archivo txt\n");
	}

    return todoOk;
}

int controller_saveAsText(char* path ,eVehiculo* pVehiculo)
{
	int todoOk = 0;
	FILE* pFile;
	int id;
	char marca[20];
	int tipo;
	float peso;
	eVehiculo* auxVehiculo;

	if (path != NULL && pVehiculo != NULL )
	{
	    auxVehiculo = pVehiculo;
		pFile = fopen(path, "w");
		if (pFile == NULL)
		{
			printf("No se pudo abrir el archivo\n");
		}

		fprintf(pFile,"id,marca,tipo,peso\n");
			if (vehiculo_getId(auxVehiculo, &id) &&
					vehiculo_getMarca(auxVehiculo, marca) &&
					vehiculo_getTipo(auxVehiculo, &tipo) &&
					vehiculo_getPeso(auxVehiculo, &peso)
			)
			{
				fprintf(pFile, "%d,%s,%d,%.2f\n", id, marca, tipo, peso);
				todoOk = 1;
			}
    }

	fclose(pFile);

	return todoOk;
}










