#ifndef TEJECUTOR_T_F_H_
#define TEJECUTOR_T_F_H_

#include "Filtros.h"
#include <stdio.h>
#include <string.h>
#include "Cola.h"
#include "ListaSimple.h"




typedef struct{
                TListaSimple filtro;
                FILE *fentrada;
                FILE *fsalida;
               
               }Elemento;
         
typedef Elemento TEjecutor_T_F;

void PR_Crear(TEjecutor_T_F *ejecutor, FILE *archivo_entrada, TListaSimple filtros,
              FILE *archivo_salida);    
              
void PR_Ejecutar(TEjecutor_T_F * ejecutor);    

void PR_Destruir(TEjecutor_T_F * ejecutor);           


#endif /*TEJECUTOR_T_F_H_*/
