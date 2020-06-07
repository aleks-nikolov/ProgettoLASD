#include "liste.h"
#define LUNGHEZZA_NOME_UTENTE 21
#define LUNGHEZZA_PASSWORD 21
#define LUNGHEZZA_TICKETS 5

//definizione del tipo t_utente

typedef struct t_utente{
	char nomeUtente[LUNGHEZZA_NOME_UTENTE];
	char password[LUNGHEZZA_PASSWORD];
	int admin;
	t_lista_P  * prenotazioni;
	int punti;
	int tickets[LUNGHEZZA_TICKETS];//ove tickets[0] è il numero di tickets di sconto da 5%, tickets[1] il numero di tickets di sconto da 10%...
}t_utente;

//definizione della struttura che andrà a contenere i vari utenti, in questo caso, un albero binario di ricerca

typedef struct t_abr{
	struct t_abr * sinistro ;
	t_utente utente ;
	struct t_abr * destro;
}t_abr;

//funzioni per la gestione della struttura t_abr

void inizializzaTickets(int * tickets);

t_abr * creaNodo_U(char * nomeUtente, char * password, int admin);

t_abr * inserisciNodo_U(t_abr * radice, char * nomeUtente, char * password, int admin);

int contains_U(t_abr * radice, char * nomeUtente, t_abr ** contenitore);
	
void mostraUtenti(t_abr * radice);

t_abr * inizializzaUtenti(); 

void visita(t_abr * radice, t_grf * voli, char * partenza);
