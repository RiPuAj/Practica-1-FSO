// Prueba de la librería sala

#include "../cabeceras/sala.h"
#include <stdio.h> 

void main(){
	crear_sala(capacidad());
	printf("La capacidad es: %d\n", capacidad());
	printf("Asientos ocupados = %d\n",asientos_ocupados());
	printf("Asientos libres = %d\n", asientos_libres());
	printf("El estado del asiento es = %d\n", estado_asiento(101));
	printf("El estado del asiento es = %d\n", estado_asiento(-23));
	printf("El estado del asiento es = %d\n", estado_asiento(27));
	printf("Asiento reservado = %d\n", reserva_asiento(3));
	printf("El estado del asiento es = %d\n", estado_asiento(0));
	printf("Id del asiento = %d\n", libera_asiento(0));
	printf("El estado del asiento es = %d\n", estado_asiento(0));	
	elimina_sala();
}
