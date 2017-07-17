#include "TEjecutor_T_F.h"

int GuardarPalabras(FILE *archivo_salida,TCola *ColaSalida ,int eof);
int BuscarPalabras (FILE *archivo_entrada,TCola *ColaEntrada); 

void PR_Crear(TEjecutor_T_F *ejecutor ,FILE *archivo_entrada,TListaSimple filtros,
			  FILE *archivo_salida){
    
    TFilter aux;
    
    ls_MoverCorriente(&filtros,LS_PRIMERO);
    
    ls_Crear(&(ejecutor->filtro),sizeof(TFilter));
    ls_ElemCorriente(filtros,&aux);
    ls_Insertar(&(ejecutor->filtro),LS_PRIMERO,&aux);
    
    while(ls_MoverCorriente(&filtros,LS_SIGUIENTE))
        {
          ls_ElemCorriente(filtros,&aux);
          ls_Insertar(&(ejecutor->filtro),LS_SIGUIENTE,&aux);    
        }
    ejecutor->fentrada= archivo_entrada;
    ejecutor->fsalida= archivo_salida;
}  



void PR_Ejecutar(TEjecutor_T_F * ejecutor)
{
  TListaSimple ListaColas;
  TCola AuxCola; 
  TCola ColaFuente;
  TCola ColaEntrada;
  TCola ColaSalida;
  TFilter aux;
  int eof=0,auxeof=0;   
         
/*Si se recuperaron palabras se ejecutan los filtros*/
    C_Crear(&ColaFuente,sizeof(TPalabra));
    eof = BuscarPalabras (ejecutor->fentrada,&ColaFuente);
    if(! eof)
    {
    	  ls_MoverCorriente(&(ejecutor->filtro),LS_PRIMERO);
    	        
    	/*CREO LA LISTA DE TUBOS*/
    	        
    	  ls_Crear(&ListaColas,sizeof(TCola));
    	        
    	/*LOS PRIMEROS 2 ELEMENTOS LOS CREO POR QUE 
    	  A LO SUMO HAY UN FILTRO*/ 
    	              
    	/*CREO EL PRIMER ELEMENTO DE LA LISTA*/
    	  
    	  ls_Insertar(&ListaColas,LS_PRIMERO,&ColaFuente);
    	          
    	/*CREO EL SEGUNDO ELEMENTO DE LA LISTA Y LA SALIDA EN POTENCIA*/  
    	  C_Crear(&AuxCola,sizeof(TPalabra));
    	  ls_Insertar(&ListaColas,LS_SIGUIENTE,&AuxCola);
    	        
    	/*CREO EL RESTO DE LOS ELEMENTOS*/       
    	  while(ls_MoverCorriente(&(ejecutor->filtro),LS_SIGUIENTE))
    	  {
    		C_Crear(&AuxCola,sizeof(TPalabra));  
    	    ls_Insertar(&ListaColas,LS_SIGUIENTE,&AuxCola);
    	  }    	
/* Mientras el ultimo filtro no de EOF se repite el circuito de filtros
 * y tubos*/    
    while (!eof)
    {
/*MUEVO AL PRIMER NODO A LAS DOS LISTAS*/  
      ls_MoverCorriente(&(ejecutor->filtro),LS_PRIMERO);
      ls_MoverCorriente(&ListaColas,LS_PRIMERO);
            
/*OBTENGO LOS DOS PRIMEROS TUBOS : ENTRADA Y SALIDA*/
      ls_ElemCorriente(ListaColas,&ColaEntrada);
      ls_MoverCorriente(&ListaColas,LS_SIGUIENTE);
      ls_ElemCorriente(ListaColas,&ColaSalida);
            
    
/*OBTENGO EL PRIMER FILTRO*/
           
            ls_ElemCorriente(ejecutor->filtro,&aux);
            
            /* EJECUTO EL PRIMER FILTRO*/
            auxeof = TRUE;
            eof=aux.fnProceso(aux.datos_filtro,&ColaEntrada,&ColaSalida,auxeof);
            /*EJECUTO LOS FILTROS RESTANTES , SI LOS HAY*/
            
            while(ls_MoverCorriente(&(ejecutor->filtro),LS_SIGUIENTE))
            {
                ColaEntrada=ColaSalida;
                ls_MoverCorriente(&ListaColas,LS_SIGUIENTE);
                ls_ElemCorriente(ListaColas,&ColaSalida);
                
                ls_ElemCorriente(ejecutor->filtro,&aux);
                auxeof = eof;
                eof=aux.fnProceso(aux.datos_filtro,&ColaEntrada,&ColaSalida,auxeof);
            }
            
            /*Guarda las Palabras en el archivo de salida*/
                eof=GuardarPalabras(ejecutor->fsalida,&ColaSalida,eof);
            
    	} // Fin de recorrido de filtros
        fclose(ejecutor->fsalida);    
    }  


/*SE EJECUTARON TODOS LOS FILTROS Y SE GENERO LA SALIDA*/       
 
 
 }/*FIN DE FUNCION EJECUTAR*/    

 
 
int GuardarPalabras(FILE *archivo_salida,TCola *ColaSalida ,int eof) 
{   
     TPalabra nueva;
     
    while  (!C_Vacia(*(ColaSalida)))
     {      
         C_Sacar(ColaSalida,&nueva);
         fprintf(archivo_salida,"%s\n",nueva);
     }    
      if (eof)
    	  return TRUE;
      else
    	  return FALSE;
           
}  
     
          
/* Devuelve True si el caracter pasado por parametro es espacio o alfanumerico.*/
int esSeparador(char caracter)
{
  int retorno = 1;
  char* caracteresValidos = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  if (strchr(caracteresValidos,caracter))
	{
	  retorno = 0;
	}
	 return retorno;
}

/* Llena la cola de entrada con las palabras dentro del archivo*/
int BuscarPalabras (FILE *archivo_entrada,TCola *ColaEntrada)
{   
      char nueva[255],palabra[64];
      int i,j;
      
      if(feof(archivo_entrada))
    	  return 1;
      else
      {
      while(!feof(archivo_entrada))
      {
        fscanf(archivo_entrada,"%s",nueva);/*lee una linea completa*/
        strcat(nueva,"\0");
        i=j=0;
        while (nueva[i] != '\0')
        {
        while ( (!esSeparador(nueva[i])) && (nueva[i] != '\0') && j<64)
        {	
          palabra[j] = nueva[i];
          i++;
          j++;
        }
        
        palabra[j]= '\0';
/* Si se recupero una palabra se la guarda en la cola de entrada*/        
        if(strlen(palabra)>0)
        {
        	C_Agregar(ColaEntrada,&palabra);
        }
/* Si aun quedan caracteres por procesar reinicio el campo destino
 * palabra y me muevo al siguiente caracter de nueva.*/
        if(nueva[i]!= '\0')
        {
        	i++;
        	j=0;   	
        	palabra[j]= '\0';
        }
		
        }    
      }
      return 0;
      }                                                          
}    




void PR_Destruir(TEjecutor_T_F * ejecutor)
{
   ls_Vaciar( &(ejecutor->filtro));  
}    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
