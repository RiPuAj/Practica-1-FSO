#include <stdlib.h>
#include <stdio.h>

int** salas;
int* capacidadMax;
int* libres;
int salasTotales;



int reserva_asiento (int id, int sala){

	int asientoLibre = -1;
	
	if(id < 1){			// Revisamos que el asiento sea válido
		return -1;
	}
	
	if(*(libres+sala) == 0){	// Revisamos que el aforo no esté completo
		return -1;
	}

	if (sala < 0 || sala > salasTotales-1){		// Revisamos que el nº de sala esté correcto
		return -1;
	}
	
	for(int i = 0; i < *(capacidadMax+sala); i++){
		
		if(asientoLibre < 0){			// Buscamos un asiento libre solo 1 vez
			if(*(*(salas+sala)+i) == -1){
				asientoLibre = i;
			}	
		}
		
		if(*(*(salas+sala)+i) == id){		// Miramos si la persona ya tiene un
			return -2;			// asiento asignado
		}
	}
	
	*(*(salas+sala)+asientoLibre) = id;		// Si no tiene asiento asignado se lo 
	*(libres+sala)= *(libres+sala)-1;		// asignamos con el guardado antes
	
	return asientoLibre;
	
}

int libera_asiento (int asiento, int sala){
	
	if(asiento < 0 || asiento > *(capacidadMax+sala)-1){		// Revisamos que el asiento es válido
		return -1;	
	}
	
	if (sala < 0 || sala > salasTotales-1){		// Revisamos que la sala sea válida
		return -1;
	}
	
	if(*(*(salas+sala)+asiento) == -1){		// Revisamos que el asiento no esté libre
		return -1;
	}
	
	int idSentado = *(*(salas+sala)+asiento);	// Liberamos el asiento
	*(*(salas+sala)) = -1;
	*(libres+sala) = *(libres+sala)+1;
	return idSentado;	
}

int estado_asiento(int asiento, int sala){

	if(asiento < 0 || asiento > *(capacidadMax+sala)-1){		// Revisamos que el asiento es válido
		return -1;
	}
	
	if (sala < 0 || sala > salasTotales-1){		// Revisamos que la sala sea válida
		return -1;
	}
	
	if(*(*(salas+sala)+asiento) == -1){		// Revisamos que el asiento esté libre
		return 0;
	} 
	
	return *(*(salas+sala)+asiento);		// Devolvemos id de la persona sentada
	
}

int asientos_libres (int sala){		// Devolvemos los asientos libres
	return *(libres+sala);
}

int asientos_ocupados (int sala){	// Devolvemos los asientos ocupados
	return (*(capacidadMax+sala)-*(libres+sala));
}

int capacidad (int sala){

	if(sala < 0 || sala > salasTotales-1){		// Revisamos que la sala sea válida
		
		return -1;
	
	} else {
	
		return *(capacidadMax+sala);		// Devolvemos la capacidad
	
	}
}

int total_salas(){
	return salasTotales;				// Devolvemos el número de salas
}

void crea_sala (int nsalas, int* capacidadSalas){
	
	salasTotales = nsalas;				// Nº de salas totales
	salas = malloc(nsalas*sizeof(long*));		// Reservamos espacios para los punteros
	capacidadMax = malloc(nsalas*sizeof(int));	// Reservamos espacio para las capacidades
	libres = malloc(nsalas*sizeof(int));		// Reservamos espacio para el nº de asientos libres
	
	for(int i = 0; i<nsalas; i++){
		*(capacidadMax+i) = *(capacidadSalas+i);	// Inicializamos las capacidades
		*(salas+i) = malloc(*(capacidadMax+i)*sizeof(int));	// Creamos las salas
		*(libres+i) = *(capacidadMax+i);		// Inicializamos los asientos libres
		
		for (int j = 0; j < *(capacidadMax+i); j++){
			*(*(salas+i)+j) = -1;		// Inicializamos los asientos a -1
		}
		
		printf("\x1b[34mSISTEMA\x1b[0m: Sala con capacidad %d creada correctamente\n", *(capacidadMax+i));
	
	}
}
	
void elimina_salas(){
	
	for(int i = 0; i < salasTotales; i++){	// Eliminamos el contenido de cada sala
		free(*(salas+i));
		printf("\x1b[34mSISTEMA\x1b[0m: Sala %d eliminada correctamente\n", i);
	}
	
	// Eliminamos la lista de punteros, la de las capacidades y la de los asientos libres
	
	free(salas);
	free(capacidadMax);
	free(libres);
}


