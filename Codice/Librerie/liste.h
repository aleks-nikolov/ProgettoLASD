#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGHEZZA_PARTENZA 31
#define LUNGHEZZA_DESTINAZIONE 31

typedef struct t_prenotazione{//definizione del tipo t_prenotazione
	char partenza[LUNGHEZZA_PARTENZA];
	char destinazione[LUNGHEZZA_DESTINAZIONE];
	int numeroScali;
	float prezzo;
	//va aggiunta lista di stringhe per gli scali
}t_prenotazione;

typedef struct t_lista{//definizione della struttura che andrà a contenere le prenotazioni di ogni utente, in questo caso, una lista singolarmente linkata
	t_prenotazione prenotazioni;
	struct t_lista * next;
}t_lista;

//funzioni per la gestione della struttura t_lista

t_lista * creaNodo_P (char * partenza, char * destinazione, int numeroScali, float prezzo);

t_lista * inserisciInTesta_P (t_lista * top, char * partenza, char * destinazione, int numeroScali, float prezzo);

t_lista * rimuoviElemento_P(t_lista * top, char * partenza, char * destinazione);

int contains_P (t_lista * top, char * partenza, char * destinazione);

//void mostraPrenotazioni(t_lista * top);

