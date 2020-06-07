#include "abr.h"
#define MAX_TICKETS_UTILIZZABILI 2

//funzioni per la gestione del terzo case della gestisciCliente

int calcolaPuntiOttenuti(float prezzo);

void stampaMenuSelezioneTicket();

void stampaMenuTickets();

void mostraPunti(t_abr * utenteCorrente);

void mostraTickets(t_abr * utenteCorrente);

void stampaRegoleConversione();

void convertiPunti(t_abr * utenteCorrente);

void gestisciTickets(t_abr * utenteCorrente);

void restituisciTickets(t_abr * utenteCorrente, int * ticketsUtilizzati);

void inizializzaTicketsUtilizzati(int * ticketsUtilizzati);
