#include "gstcliente.h"

void stampaMenuIniziale();

void stampaMenuUtente();

void terminaProgramma(int * selettoreAzione);

void stampaRegoleCredenziali();

void effettuaRegistrazione(t_abr * utenti);

int eseguiAccesso(t_abr * utenti, t_abr ** contenitore);

void gestisciUtente(int esito, t_abr * utenti, t_grf ** voli, t_abr * utenteCorrente);



