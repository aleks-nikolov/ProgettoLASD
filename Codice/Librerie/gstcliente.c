#include "gstcliente.h"

void stampaMenuCliente(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Effettua prenotazione\n"
		   "2)Stampa prenotazioni attive\n"
		   "3)Gestisci punti e tickets\n"
		   "4)Logout\n\n"
	       "Inserire numero: ");
}

/*

gestisciTickets(utenteCorrente){
}

mostraPrenotazioni((*utenteCorrente)->utente.prenotazioni){
}

effettuaPrenotazione(utenti, voli, utenteCorrente){
}

*/

void terminaGestioneCliente(int * selettoreAzione){
		*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di logout, si reinserisca 4 per confermare: ");
		fflush(stdin);	
		scanf("%d" , selettoreAzione);
		if(*selettoreAzione == 4)
			printf("\nLogout avvenuto con successo");
}

void gestisciCliente(t_abr * utenti, t_grf * voli, t_abr ** utenteCorrente){
	int selettoreAzione;
	
	do{
		
		stampaMenuCliente();
		
		fflush(stdin);
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
                //effettuaPrenotazione(utenti, voli, utenteCorrente);
                break;
                
            case 2:
            	puts("");
                //mostraPrenotazioni((*utenteCorrente)->utente.prenotazioni);
                break;

            case 3:
                //gestisciTickets(utenteCorrente);
                break;

            case 4:
                terminaGestioneCliente(&selettoreAzione);
                break;

            default:
                printf("\nDato inserito non rientra nelle opzioni, riprovare;");    
		}
        fflush(stdin);
		
	}while(selettoreAzione != 4);
}
