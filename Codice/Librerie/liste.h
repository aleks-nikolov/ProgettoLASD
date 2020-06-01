#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGHEZZA_PARTENZA 31
#define LUNGHEZZA_DESTINAZIONE 31

typedef struct t_prenotazione{
	char partenza[LUNGHEZZA_PARTENZA];
	char destinazione[LUNGHEZZA_DESTINAZIONE];
	int numeroScali;
	float prezzo;
}t_prenotazione;

typedef struct t_lista{
	t_prenotazione prenotazione;
	t_lista * next;
}t_lista;
