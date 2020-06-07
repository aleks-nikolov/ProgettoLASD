#include "gstpunti.h"

//funzioni per la gestione dell'applicativo nel caso in cui l'accesso venga effettuato da un cliente

void stampaMenuCliente();

//funzioni per la gestione del primo case della gestisciCliente

void stampaMenuPrenotazione();

void stampaMenuSelezioneTratta();

void stampaMenuSelezioneDestinazione(int * selettoreTratta, char * partenza);

void costruisciCampiPrenotazione(t_grf * voli, t_grf * percorso, t_lista_S ** scali, float * prezzo);

float utilizzaTickets(t_abr * utenteCorrente, int * ticketsUtilizzati);

void gestisciPrenotazione(t_grf * voli, t_abr * utenteCorrente, char * partenza, char * destinazione);

void gestisciPagamentoPartenzaDestinazione(t_grf * voli, t_grf * percorso, t_abr * utenteCorrente, int selettoreTratta, char * partenza, char * destinazione);

void gestisciPartenzaEDestinazione(t_grf * voli, t_abr * utenteCorrente);

void gestisciSolaPartenza(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);

void effettuaPrenotazione(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);

//funzioni per la gestione del secondo case della gestisciCLiente

void visualizzaPrenotazioni(t_abr * utenteCorrente);

//funzione per la gestione del quarto case della gestisciCliente

void terminaGestioneCliente(int * selettoreAzione);

//gestisciCliente

void gestisciCliente(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente);
