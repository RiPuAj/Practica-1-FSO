// Test para sala_reto.c

#include <assert.h>
#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

#include <stdio.h>
#include "../cabeceras/sala_reto.h"

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
 	// fflush fuerza que se imprima el mensaje anterior
	// sin necesidad de utilizar un salto de línea
	fflush(stdout);
	printf("\n");
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n\n");
}

void estado_sala(int nsala){

	printf("\x1b[32mRESULTADO:\x1b[0m SALA GRÁFICA\n");
	printf("\nNº -> Número de asiento\n");
	printf("ES -> Estado del asiento:\n");
	printf("\t0 -> libre\n");
	printf("\tID > 0 -> Asiento ocupado por ese ID\n");
	printf("Nº");

	int iter=0;
	for(int i = 0; i < capacidad(nsala); i++){
		printf("|%5.1d", i);
		if ((i+1) % 10 == 0){
			printf("\nID");
		
			for(int j = i-10+1; j<i+1; j++){
				printf("|%5.1d", estado_asiento(j, nsala));
			}
			
			if(i+1 < capacidad(nsala)){
				printf("\nNº");
				iter = i+1;
			}else{
				printf("\n");
				continue;
			}
			
		}
		
		if(i == capacidad(nsala)-1){
			printf("\nID");
			int n = capacidad(nsala);
			for(int j = iter; j<n; j++){
				printf("|%5.1d", estado_asiento(j,nsala));
			}
			printf("\n");
		}
	}
}

void sentarse(int id, int sala){
	
	if(id < 1){
		
		printf("\x1b[31mERROR:\x1b[0m Identificador no válido.\n\n");
		return;
	}
	
	if(sala < 0 || sala > total_salas()-1){
		
		printf("\x1b[31mERROR:\x1b[0m Número de sala no válido.\n\n");	
		return;
		
	} else {	
		int final = reserva_asiento(id, sala);
		
		if (final == -1){
		
			printf("\x1b[31mERROR:\x1b[0m Aforo está completo\n\n");
	
		}else if(final == -2){
			
			printf("\x1b[31mERROR:\x1b[0m Ese ID ya ha reservado\n\n");
			
		} else {
		
			printf("\x1b[32mRESULTADO:\x1b[0m El asiento reservado es el nº %d\n\n", final);
		}
	}

}

void liberarse(int asiento, int sala){

	if(asiento > capacidad(sala)-1 || asiento < 0){
		
		printf("\x1b[31mERROR:\x1b[0m Asiento no válido.\n\n");
		return;
	
	}

	if(sala < 0 || sala > total_salas()-1){
	
		printf("\x1b[31mERROR:\x1b[0m Sala no válido.\n\n");
		return;
	
	} else {
		int resultado = libera_asiento(asiento, sala);
		
		if(resultado == -1){
			
			printf("\x1b[31mERROR:\x1b[0m El asiento ya está libre.\n");
		
		} else {
		
			printf("\x1b[32mRESULTADO:\x1b[0m Asiento liberado correctamente.\n");
		
		}
	}
}

void estado(int asiento, int sala){

	if(asiento > capacidad(sala)-1 || asiento < 0){
		
		printf("\x1b[31mERROR:\x1b[0m Asiento no válido.\n\n");
		return;
	
	}else if(sala < 0 || sala > total_salas()-1){
	
		printf("\x1b[31mERROR:\x1b[0m Sala no válido.\n\n");
		return;
		
	} else {
	
		int estado = estado_asiento(asiento, sala);
	
		if (estado == 0){
		
			printf("\x1b[32mRESULTADO:\x1b[0m El asiento está libre");
			
		} else {
		
			printf("\x1b[32mRESULTADO:\x1b[0m El asiento está ocupado por el id %d", estado);
		
		}
	}
}

void menu(){
	int nsalas;
	int salaActual = -1;
	int opcion = 0;
	int opcionSala;
	
	printf("Teclee el número de salas -> ");
	scanf("%d", &nsalas);
	int capacidadSalas[nsalas];
	for(int i = 0; i < nsalas; i++){
		printf("Capacidad de la sala %d -> ", i);
		scanf("%d", &capacidadSalas[i]);
	} 
	crea_sala(nsalas, capacidadSalas);
	
	while(opcion != -1){
		printf("Salas disponibles :\n");
		for(int i = 0; i < nsalas; i++){			
			printf("\t%d.Sala nº %d\n", i, i);
		}
		
		printf("\t%d.Salir\n", nsalas);
		printf("\tTeclee el nº de sala a operar -> ");
		scanf("%d", &salaActual);
		printf("\n");		
		
		if(salaActual < 0 || salaActual > nsalas){	// Si la sala no es válida
			salaActual = -1;			// pregunta otra vez
		}
		
		if(salaActual == nsalas){			// Si la opción es salir
			opcion = -1;
			break;
		}
		
		while(salaActual != -1){
			printf("\n\x1b[32mSALA ACTUAL %d\x1B[0m\n", salaActual);
			printf("\nSelecciona una de las siguiente opciones:\n");
			printf("\t1.Reservar asiento\n");
			printf("\t2.Liberar asiento\n");
			printf("\t3.Estado asiento\n");
			printf("\t4.Asientos libres\n");
			printf("\t5.Asientos ocupados\n");
			printf("\t6.Capacidad\n");
			printf("\t7.Estado sala\n");
			printf("\t8.Nº Salas totales\n");
			printf("\t9.Atrás\n");
			printf("\tOpcion elegida -> ");
			scanf("%d", &opcionSala);
			printf("\n");
			
			switch(opcionSala){
				case 1:
					int id;
					printf("Teclee el id -> ");
					scanf("%d", &id);
					sentarse(id, salaActual);
					opcionSala = 0;
					break;
					
				case 2:
					int asiento;
					printf("Teclee el asiento -> ");
					scanf("%d", &asiento);
					liberarse(asiento, salaActual);
					opcionSala = 0;
					break;
					
				case 3:
					printf("Teclee el asiento -> ");
					scanf("%d", &asiento);
					estado(asiento, salaActual);
					opcionSala = 0;
					break;
				case 4:
					printf("\x1b[32mRESULTADO:\x1b[0m Asientos libres = %d", asientos_libres(salaActual));
					opcionSala = 0;
					break;
					
				case 5:
					printf("\x1b[32mRESULTADO:\x1b[0m Asientos ocupados = %d", asientos_ocupados(salaActual));
					opcionSala = 0;
					break;
				
				case 6:
					printf("\x1b[32mRESULTADO:\x1b[0m Capacidad de la sala es = %d", capacidad(salaActual));
					opcionSala = 0;
					break;
					
				case 7:
					estado_sala(salaActual);
					opcionSala = 0;
					break;
				
				case 8:
					printf("\x1b[32mRESULTADO:\x1b[0m Nº Salas Totales %d\n", total_salas());
					opcionSala = 0;
					break;
				
				case 9:
					salaActual = -1;
					opcionSala = 0;
					break;
					
			}
			
			
		}
	}
	
	elimina_salas();	
}

void test_ReservaLlenadoSala(){
	INICIO_TEST("Reserva múltiple");
	
	int capSalas[3] = {10, 15, 20};
	crea_sala(3, capSalas);
	
	// Reservar sala 0
	for (int i = 1; i < capacidad(0)+51; i++){
		
		int asiento = reserva_asiento(i*10, 0);
				
		if(i-1 < capacidad(0)){
			
			DebeSerCierto(asiento == i-1);
			DebeSerCierto(estado_asiento(asiento, 0)==i*10);
			DebeSerCierto(asientos_libres(0)+asientos_ocupados(0)==capacidad(0));
		
		} else {

			DebeSerCierto(asiento == -1);
			DebeSerCierto(asientos_libres(0)+asientos_ocupados(0)==capacidad(0));
		}
	}
	
	// Reservar sala 1
	for (int i = 1; i < capacidad(1)+51; i++){
		
		int asiento = reserva_asiento(i*10, 1);
		
		if(i-1 < capacidad(1)){
		
			DebeSerCierto(asiento == i-1);
			DebeSerCierto(estado_asiento(asiento, 1)== i*10);
			DebeSerCierto(asientos_libres(1)+asientos_ocupados(1)==capacidad(1));
			
		} else {
		
			DebeSerCierto(asiento == -1);

		}
	}
	
	// Reservar sala 2
	for (int i = 1; i < capacidad(2)+51; i++){
		int asiento = reserva_asiento(i*10, 2);
		
		if(i-1 < capacidad(2)){		// Reserva normal
		
			DebeSerCierto(asiento == i-1);
			DebeSerCierto(estado_asiento(asiento, 2)==i*10);
			DebeSerCierto(asientos_libres(2)+asientos_ocupados(2)==capacidad(2));
		
		} else {	// Aforo completo, da error
		
			DebeSerCierto(asiento == -1);
			DebeSerCierto(asientos_libres(2)+asientos_ocupados(2)==capacidad(2));
		
		}
	}
	
	// Liberar Sala 0
	for(int i = 0; i < capacidad(0)+50; i++){
		int asientoLiberado = libera_asiento(i, 0);
		
		if(i < capacidad(0)){
		
			DebeSerCierto(asientoLiberado == (i+1)*10);
			DebeSerCierto(asientos_libres(0)+asientos_ocupados(0)==capacidad(0));
		
		} else {
		
			DebeSerCierto(asientoLiberado == -1);
			DebeSerCierto(asientos_libres(0)+asientos_ocupados(0)==capacidad(0));
		
		}
		
	}
	
	// Liberar Sala 1
	for(int i = 0; i < capacidad(1)+50; i++){
		
		int asientoLiberado = libera_asiento(i, 1);
		
		if(i < capacidad(1)){
		
			DebeSerCierto(asientoLiberado == (i+1)*10);
			DebeSerCierto(asientos_libres(1)+asientos_ocupados(1)==capacidad(1));
		
		} else {
			
			DebeSerCierto(asientoLiberado == -1);
			DebeSerCierto(asientos_libres(1)+asientos_ocupados(1)==capacidad(1));
		
		}
		
	}
	
	// Liberar Sala 2
	for(int i = 0; i < capacidad(2)+50; i++){
		
		int asientoLiberado = libera_asiento(i, 2);
		
		if(i < capacidad(2)){
		
			DebeSerCierto(asientoLiberado == (i+1)*10);
			DebeSerCierto(asientos_libres(2)+asientos_ocupados(2)==capacidad(2));
		
		} else {
		
			DebeSerCierto(asientoLiberado == -1);
			DebeSerCierto(asientos_libres(2)+asientos_ocupados(2)==capacidad(2));
		
		}
		
	}
	
	
	elimina_salas();
	FIN_TEST("Reserva múltiple");
}

void ejecuta_tests(){
	int x = 0;
	
	while (x != -1){
		printf("Elija una opción de test.\n");
		printf("\t1.Menu de opciones manuales\n");
		printf("\t2.Test de Reserva Llenado de la sala\n");
		printf("\t3.Salir\n");
		
		printf("Opción seleccionada -> ");
		scanf("%d", &x);
		
		switch(x){
			case 1:
				x = 0;
				menu();
				break;
			
			case 2:
				x = 0;
				test_ReservaLlenadoSala();
				break;
			
			case 3:
				x = -1;
				break;
		}
	}
}

void main(){
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
}
