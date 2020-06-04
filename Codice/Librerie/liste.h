#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gstadmin.h"

typedef struct t_lista_S{//definizione della struttura che andrà a contenere i vari scali, in questo caso, una lista singolarmente linkata
	char scalo[LUNGHEZZA_NOME_AEROPORTO];
	struct t_lista_S * next;
}t_lista_S;

typedef struct t_prenotazione{//definizione del tipo t_prenotazione
	char partenza[LUNGHEZZA_NOME_AEROPORTO];
	char destinazione[LUNGHEZZA_NOME_AEROPORTO];
	t_lista_S * scali;
	float prezzo;
	//va aggiunta lista di stringhe per gli scali
}t_prenotazione;

typedef struct t_lista_P{//definizione della struttura che andrà a contenere le prenotazioni di ogni utente, in questo caso, una lista singolarmente linkata
	t_prenotazione prenotazioni;
	struct t_lista_P * next;
}t_lista_P;

//funzioni per la gestione della struttura t_lista_S

t_lista_S * creaNodo_S (char * nomeAeroporto);

t_lista_S * inserisciInTesta_S (t_lista_S * top, char * nomeAeroporto);

t_lista_S * rimuoviElemento_S(t_lista_S * top, char * nomeAeroporto);

int contains_S (t_lista_S * top, char * nomeAeroporto);

void mostraScali(t_lista_S * top);

//funzioni per la gestione della struttura t_lista_P

t_lista_P * creaNodo_P (char * partenza, char * destinazione, t_lista_S * scali, float prezzo);

t_lista_P * inserisciInTesta_P (t_lista_P * top, char * partenza, char * destinazione, t_lista_S * scali, float prezzo);

t_lista_P * rimuoviElemento_P(t_lista_P * top, char * partenza, char * destinazione);

int contains_P (t_lista_P * top, char * partenza, char * destinazione);

void mostraPrenotazioni(t_lista_P * top);



