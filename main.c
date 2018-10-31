
#include "page_table.h"
#include "disk.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

const char *algor;
struct disk *disk;
int *marcos_t;
int cambio = 0;

//Para el resumen 
int escrituras;
int faltas;
int lecturas;

void page_fault_handler( struct page_table *pt, int page )
{
	faltas++;
	int n_marco = page_table_get_nframes(pt);
	char *physmem = page_table_get_physmem(pt);
	srand(time(NULL));

	//Se pone un marco inicial
	int marco = 0;

	//Se elige el algoritmo deseado, si esta mal escrito, se corta el programa
	//Elige marco de forma aleatoria
	if(!strcmp(algor,"rand")) {
		printf("%i\nmarco", n_marco);
		marco = rand()%n_marco;
		
		printf("%d\n",marco);

	//Se va eligiendo por orden de llenado, desde los primeros hasta los ultimos
	}else if (!strcmp(algor,"fifo")){
		marco = page%n_marco;
		

	}else if (!strcmp(algor,"custom")){
		if (cambio == 0){
			marco = 0;
			cambio = 1;
			
		}
		else{
			marco = page%n_marco;
			cambio = 0;
			
		}


	}else{
		fprintf(stderr,"Algoritmo incorrecto: %s, el programa se cerrara\n",algor);
		exit(1);
	}

	//Se escribe al disco si existe una pagina cargada al marco
	if (marcos_t[marco]!=-1){
		disk_write(disk, marcos_t[marco], &physmem[marco]);
		escrituras++;					
	}

	//Se lee la pagina del disco
	disk_read(disk, page, &physmem[marco]);

	//Se carga al marco
	marcos_t[marco]=page;
	lecturas++;
	page_table_set_entry(pt,page,marco,PROT_WRITE);
	
}

int main( int argc, char *argv[] )
{
	if(argc!=5) {
		/* Add 'random' replacement algorithm if the size of your group is 3 */
		printf("usa: ./virtmem <numero paginas> <numero marcos> <rand|fifo|custom> <sort|scan|focus>\n");
		return 1;
	}

	
	int n_pag = atoi(argv[1]);
	int n_marco = atoi(argv[2]);
	algor = argv[3];
	const char *program = argv[4];

	if((n_pag < 0)) {
		fprintf(stderr,"El numero de paginas debe ser positivo ó 0.\nEl programa se cerrara.\n");
		exit(1);
	}

	// Si el numero de marcos es igual a cero, 
	if((n_marco <= 0)) {
		fprintf(stderr,"Debe existir un minimo de 1 marco para llevar a cabo la paginación.\nEl programa se cerrara.\n");
		exit(1);
	}

	disk = disk_open("myvirtualdisk",n_pag);
	if(!disk) {
		fprintf(stderr,"No se pudo crear el disco virtual: %s\n",strerror(errno));
		return 1;
	}

	//Se crea una tabla que contiene la misma cantidad de numero de marcos
	//aca se guardaran las paginas, se pone -1 para indicar que esta vacia
	marcos_t = malloc(n_marco*sizeof(int)); 
	for (int i = 0; i<n_marco;i++){
		marcos_t[i]=-1;
	}

	struct page_table *pt = page_table_create( n_pag, n_marco, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"No se pudo crear la tabla de paginas: %s\n",strerror(errno));
		return 1;
	}
	

	char *virtmem = page_table_get_virtmem(pt);

	if(!strcmp(program,"sort")) {
		sort_program(virtmem,n_pag*PAGE_SIZE);
		
	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,n_pag*PAGE_SIZE);

	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,n_pag*PAGE_SIZE);

	} else {
		fprintf(stderr,"Programa desconocido: %s\nEl programa se cerrara\n",argv[4]);
		exit(1);

	}

	//Resumen
    printf("//////Resumen//////\n");
	printf("Faltas de pagina: %i\n",faltas);
	printf("Lecturas al disco: %i\n",lecturas);
	printf("Escrituras al disco: %i\n",escrituras);

	//Se limpia y se elimina
	free(marcos_t);
	page_table_delete(pt);
	disk_close(disk);

	return 0;
}
