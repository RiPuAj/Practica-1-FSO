// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//

#include <assert.h>
#include <stdio.h>
#include "../cabeceras/sala.h"

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
 	// fflush fuerza que se imprima el mensaje anterior
	// sin necesidad de utilizar un salto de línea
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n");
}

void estado_sala(){
	
	// Función para printear el estado de la sala (Nº Asientos e IDs)
	
	printf("\n\x1b[32mRESULTADO:\x1b[0m SALA GRÁFICA\n");
	printf("\nNº -> Número de asiento\n");
	printf("ES -> Estado del asiento:\n");
	printf("\t0 -> Asiento libre\n");
	printf("\tID > 0 -> Asiento ocupado por ese ID\n");
	printf("Nº");

	int iter ;//= 0;
	for(int i = 0; i < capacidad(); i++){
		printf("|%5.1d", i);
		if ((i+1) % 10 == 0){
			printf("\nID");
		
			for(int j = i-10+1; j<i+1; j++){
				printf("|%5.1d", estado_asiento(j));
			}
			
			if(i+1 < capacidad()){
				printf("\nNº");
				iter = i+1;
			}else{
				printf("\n");
				continue;
			}
			
		}
		
		if(i == capacidad()-1){
			printf("\nID");
			int n = capacidad();
			for(int j = iter; j<n; j++){
				printf("|%5.1d", estado_asiento(j));
			}
			printf("\n");
		}
	}
}

void sentarse(int id){
	
	if(id < 1){
		
		printf("\x1b[31mERROR:\x1b[0m Identificador no válido.\n\n");
		return;
	
	} else {	
	
		int final = reserva_asiento(id);
		
		if (final == -1){
		
			printf("\x1b[31mERROR:\x1b[0m No se pudo reservar el asiento ya que el aforo está completo\n\n");
	
		} else if(final == -2){
		
			printf("\x1b[31mERROR:\x1b[0m Este ID ya tiene un asiento asignado\n\n");
			
		} else {
		
			printf("\x1b[32mRESULTADO:\x1b[0m El asiento reservado es el nº %d\n\n", final);
		}
	}

}

void liberarse(int asiento){

	if(asiento > capacidad()-1 || asiento < 0){
		
		printf("\x1b[31mERROR:\x1b[0m Asiento no válido.\n\n");
		return;
		
	} else {
		int resultado = libera_asiento(asiento);
		
		if(resultado == -1){
			
			printf("\x1b[31mERROR:\x1b[0m El asiento ya está libre.\n");
		
		} else {
		
			printf("\x1b[32mRESULTADO:\x1b[0m Asiento liberado correctamente.\n");
		
		}
	}
}

void estado(int asiento){
	int estado = estado_asiento(asiento);
	
	if(estado == -1){
	
		printf("\x1b[31mERROR:\x1b[0m Asiento no válido.\n\n");
		return;
	}
	
	if(estado == 0){
	
		printf("\x1b[32mRESULTADO:\x1b[0m El asiento está libre\n\n");
		return;
	}
	
	if(estado > 0){
	
		printf("\x1b[32mRESULTADO:\x1b[0m Asiento ocupado por %d\n\n", estado);
		return;
	}
}

int menu(){
	int aforo;
	int x = 0;
	
	printf("Capacidad de la sala -> ");
	scanf("%d", &aforo);
	
	crea_sala(aforo);
	
	printf("Menú para hacer pruebas manuales\n\n");
	while (x != -1){
		
		printf("\nSelecciona una de las siguiente opciones:\n");
		printf("\t1.Reservar asiento\n");
		printf("\t2.Liberar asiento\n");
		printf("\t3.Estado asiento\n");
		printf("\t4.Asientos libres\n");
		printf("\t5.Asientos ocupados\n");
		printf("\t6.Capacidad\n");
		printf("\t7.Estado sala\n");
		printf("\t8.Salir\n");
		printf("\tOpcion elegida -> ");
		scanf("%d", &x);
		
		
		switch(x){
			case 1:
				int id;
				printf("\tEscriba el id -> ");
				scanf("%d", &id);
				sentarse(id);
				x = 0;
				break;
			
			case 2:
				int asiento;
				printf("\tEscriba el nº de asiento -> ");
				scanf("%d", &asiento);
				liberarse(asiento);
				x = 0;
				break;
				
			case 3:
				printf("\tEscriba el nº de asiento -> ");
				scanf("%d", &asiento);
				estado(asiento);
				x = 0;
				break;
			
			case 4:
				printf("\n\x1b[32mRESULTADO:\x1b[0m Asientos libre = %d\n", asientos_libres());
				x = 0;
				break;
				
			case 5:
				printf("\n\x1b[32mRESULTADO:\x1b[0m Asientos ocupados = %d\n", asientos_ocupados());
				x = 0;
				break;
				
			case 6: 
				printf("\n\x1b[32mRESULTADO:\x1b[0m Capacidad = %d\n", capacidad());
				x = 0;
				break;
				
			case 7:
				estado_sala();
				x = 0;
				break;
				
			case 8:
				printf("Saliendo del menú.\n");
				x=-1;
				return -1;
				break;
		}
	}
	
	elimina_sala();
}

void test_ReservaBasica()
{
	int mi_asiento;
	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500

	INICIO_TEST("Reserva básica");
	crea_sala(CAPACIDAD_CUYAS);
	DebeSerCierto(capacidad()==CAPACIDAD_CUYAS);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	DebeSerCierto(estado_asiento(mi_asiento)>0);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	elimina_sala();
	FIN_TEST("Reserva básica");
}

void test_ReservaLlenadoSala(){
	
	#define CAPACIDAD_YELMOS 100
	
	INICIO_TEST("Reserva múltiple");
	crea_sala(CAPACIDAD_YELMOS);
	
	// Reservamos hasta llenar toda la sala
	for(int i = 1; i < 251; i++){
		if(i < 101){
		
			DebeSerCierto(reserva_asiento(i*10) == i-1);	// Comprobamos que nos devuelve el asiento correcto
			DebeSerCierto(asientos_libres() == capacidad()-i); // Comprobamos los asientos libres	
			DebeSerCierto(asientos_ocupados() == i); // Comprobamos asientos ocupados
			DebeSerCierto(asientos_libres()+asientos_ocupados()==CAPACIDAD_YELMOS); // Comprobamos que la suma de libres y ocupados es igual a la capacidad
			DebeSerCierto(estado_asiento(i-1) == i*10);	// Comprobamos que el estado del asiento nos devuelve el id correcto
	
		} else if (i < 151){
		
			DebeSerCierto(reserva_asiento(i*10) == -1);	// Comprobamos que no se haga la reserva ya que el aforo está lleno
		}
			
	}
	
	for(int i = 0; i < 150; i++){
		
		int asientoLiberado = libera_asiento(i);
		
		if(i < 100){	// Liberamos todo los asientos
		
			DebeSerCierto(asientoLiberado == (i+1)*10);	// Liberar asiento
			DebeSerCierto(estado_asiento(i) == 0);		// Verificar liberación
			
		} else {
			
			DebeSerCierto(libera_asiento(150-i) == -1);	// El asiento ya está
			DebeSerCierto(estado_asiento(150-i) == 0);	// liberado
		
		}
	}
	
	elimina_sala();
	FIN_TEST("Reserva múltiple");
}

void ejecuta_tests ()
{
	int eleccion = 0;
	while (eleccion != -1){
		printf("Elija que test quiere hacer:\n");
		printf("\t1.Menú de opciones manual.\n");
		printf("\t2.Test rápido de Reserva Simple.\n");
		printf("\t3.Test rápido de Reserva Llenado Sala.\n");
		printf("\t4.Salir\n");
		printf("Opción escogida -> ");
		scanf("%d", &eleccion);
		
		switch(eleccion){
			case 1:
				eleccion = menu();
				break;
				
			case 2:
				test_ReservaBasica();
				eleccion = 0;
				break;
				
			case 3:
				test_ReservaLlenadoSala();
				eleccion = 0;
				break;
				
			case 4:
				eleccion = -1;
				break;
		}
	} 
}

void main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
}
