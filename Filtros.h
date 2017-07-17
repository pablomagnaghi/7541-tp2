#ifndef FILTROS_H_
#define FILTROS_H_

#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "Cola.h"
#include "ListaSimple.h"
#include "Pila.h"
#include "ListaOrdenada.h"

typedef char TPalabra [64];
typedef TCola TTubo;

typedef int TProcesarFn(void *datos_filtro,TTubo *entrada,TTubo *salida,int eof);

typedef struct 
	{
    	TProcesarFn * fnProceso;
    	void *datos_filtro;
	}TFilter;

/*Pre:Lista de filtros no creada y archivo de filtros no vacio
 *Post:Lista de filtros creada*/
void Crear_Lista_Filtros(TListaSimple *Lista_Filtros, FILE *parchivofiltros);

/*Pre:Lista de filtros  creada y no vacia
 *Post:Lista de filtros destruida*/
void Destruir_Lista_Filtros(TListaSimple * Lista_Filtros);

/*Primitivas filtros*/   

/*Mayusculas*/

int Pasar_a_mayuscula_Procesar(void * datos_filtro, TTubo *entrada, 
TTubo *salida, int eof);


/*Minusculas*/

int Pasar_a_minuscula_Procesar(void * datos_filtro, TTubo *entrada, 
TTubo *salida, int eof);


/*Pasar primeros N*/

typedef struct {
               	 int numero;
               } Primeros_Dato;


void PrimerosN_Crear(void *filtro,int n);

int PrimerosN_procesar(void * datos_filtro, TTubo *entrada, 
					   TTubo *salida, int eof);

void PrimerosN_destruir(Primeros_Dato *filtro);



typedef struct {
                int numero;
                } Ultimos_Dato;
                
void UltimosN_Crear(void *filtro,int n);

int UltimosN_procesar(void * datos_filtro, TTubo *entrada, 
					  TTubo *salida, int eof);


void UltimosN_destruir(void *filtro);

/* Filtro Extraer Enesimo Campo */
typedef struct {
                int numero;
                } Extraer_Dato;
                
void ExtraerN_Crear(void *filtro,int n);

int ExtraerN_procesar(void * datos_filtro, TTubo *entrada, 
					  TTubo *salida, int eof);


void ExtraerN_destruir(void *filtro); 




/*Filtrar Palabra*/

typedef struct{
	TPalabra palabra;
}FiltrarPalabra_Dato;

void FiltrarPalabra_Crear(void *filtro, TPalabra palabra);
	
int FiltrarPalabra_procesar(void *datos_filtro, TTubo *entrada, TTubo *salida, int eof);

void separarPalabras(char cadena[], char palabrasSeparadas[][], int* cantPalabras);

void FiltrarPalabra_destruir(FiltrarPalabra_Dato *filtro);

/*Ordenar*/

typedef struct{
	TPalabra orden;
}Ordenar_Dato;

void Ordenar_Crear(void *filtro, TPalabra orden);
	
int Ordenar_procesar(void *datos_filtro, TTubo *entrada, TTubo *salida, int eof);

void Ordenar_destruir(Ordenar_Dato *filtro);

void invertirOrden(char* stringsArray[], int longitud);

void ordenarArray(char* stringsArray[], int longitud);

int compararStrings1(void *a, void *b);

int compararStrings2(void *a, void *b);

void imprimirString(void* dato);

/*Eliminar Repetidas*/

void EliminarRepetidas_Crear(void *filtro);
	
int EliminarRepetidas_procesar(void *datos_filtro, TTubo *entrada, TTubo *salida, int eof);

void EliminarRepetidas_destruir(Ordenar_Dato *filtro);

void ContarRepetidasConsecutivas_Crear(void *filtro);

int ContarRepetidasConsecutivas_procesar(void *datos_filtro, TTubo *entrada, TTubo *salida, int eof);

void ContarRepetidasConsecutivas_destruir(void *filtro);

#endif /*FILTROS_H_*/
