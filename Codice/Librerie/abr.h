#include "liste.h"
#define LUNGHEZZA_NOME_UTENTE 21
#define LUNGHEZZA_PASSWORD 21
#define LUNGHEZZA_TICKETS 5

typedef struct t_utente{
	char nomeUtente[LUNGHEZZA_NOME_UTENTE];
	char password[LUNGHEZZA_PASSWORD];
	t_lista prenotazioni;
	int punti;
	int tickets[LUNGHEZZA_TICKETS];
	int admin;
}t_utente;

typedef struct t_abr{//definizione della struttura che andrà a contenere i vari utenti, in questo caso, un albero binario di ricerca
	struct t_abr * sinistro ;
	t_utente utente ;
	struct t_abr * destro;
}t_abr;

//funzioni per la gestione della struttura t_abr

t_abr_U * creaNodo_U(char * nomeUtente, char * password);

t_abr_U * inserisciNodo_U(t_abr * radice, char * nomeUtente, char * password);

int contains_U(t_abr * radice, char * nomeUtente, t_abr ** contenitore);
	
void mostraUtenti(t_abr * radice);

t_abr * inizializzaUtenti(); //metodo lanciato a inizio programma per inizializzare 3 utenti admin
