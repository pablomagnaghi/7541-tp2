#include "TEjecutor_T_F.h"

int main(int argc, char *argv[]){   
  TEjecutor_T_F ejecutor;  
  FILE *entrada;
  FILE *salida;
  FILE *definiciones;
  TListaSimple ListaFiltros;
  char PathEntrada[100];
  char PathSalida[100];
  char PathDef[100];
  
/* Se recuperan los parametros de ejecucion.*/
/* Se inicializan los string que contienen los parametros.*/
  	strcpy(PathEntrada,"\0");
  	strcpy(PathSalida,"\0");
  	strcpy(PathDef,"\0");
  	
  	if (argc != 4)
  	{
  	  printf("\nError: Se debe ejecutar de la siguiente manera:\n");
  	  printf("         ejecutar <PathEntrada> <PathSalida> <PathDefiniciones>\n\n");
  	  return 0;
  	}
  	else
  	{
  		strcpy(PathEntrada,argv[1]);
  		strcpy(PathSalida,argv[2]);
  		strcpy(PathDef,argv[3]);

        if((entrada=fopen(PathEntrada,"r"))!=NULL)
         {
           if((definiciones=fopen(PathDef,"r"))!=NULL)
             {
              if((salida=fopen(PathSalida,"w"))!=NULL)
                {
                 Crear_Lista_Filtros(&ListaFiltros, definiciones);
                 if (! (ls_Vacia(ListaFiltros))) 
                 {
                 PR_Crear(&ejecutor, entrada,ListaFiltros,salida);     
                 PR_Ejecutar(&ejecutor);  
                 PR_Destruir(&ejecutor);
                 Destruir_Lista_Filtros(&ListaFiltros);
                 printf("La operacion se ha ejecutado correctamente");
                 }
                 else
                	 printf("No se recibieron filtros validos\n");
                 } 
              else printf("Nombre del Archivo de salida incorrecto\n");
             
          }
          else  printf("Nombre del Archivo de Definiciones incorrecto\n");   
 
        }
        else printf("Nombre del Archivo de entrada incorrecto\n");      
      
 
  return 0;
  }
}
