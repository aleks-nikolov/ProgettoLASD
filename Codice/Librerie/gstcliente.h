#include "abr.h"

//funzioni per la gestione dell'applicativo nel caso in cui l'accesso venga effettuato da un cliente

void stampaMenuCliente();

void stampaMenuPrenotazione();

void stampaMenuSelezioneTratta(int * selettoreTratta);

void calcolaPuntiOttenuti(float prezzo);

void gestisciPartenzaEDestinazione(t_grf * voli, t_abr * utenteCorrente);

void gestisciSolaPartenza(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);

void effettuaPrenotazione(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);

void stampaMenuTickets();

void mostraPunti(t_abr * utenteCorrente);

void mostraTickets(t_abr * utenteCorrente);

void stampaRegoleConversione();

void convertiPunti(t_abr * utenteCorrente);

void gestisciTickets(t_abr * utenteCorrente);

void terminaGestioneCliente(int * selettoreAzione);

void gestisciCliente(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);
