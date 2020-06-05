#include "gstcliente.h"

void stampaMenuCliente(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Effettua prenotazione\n"
		   "2)Stampa prenotazioni attive\n"
		   "3)Gestisci punti e tickets\n"
		   "4)Logout\n\n"
	       "Inserire numero: ");
}

void stampaMenuPrenotazione(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Effettua prenotazione inserendo sola partenza\n"
		   "2)Effettua prenotazione inserendo partenza e destinazione\n"
		   "3)Mostra voli\n"
		   "4)Torna indietro\n\n"
	       "Inserire numero: ");
}

void gestisciPartenzaEDestinazione(t_grf * voli, t_abr * utenteCorrente){
	
}
void gestisciSolaPartenza(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente){
	
}

void effettuaPrenotazione(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente){
	int selettoreAzione;
	
	do{
		selettoreAzione = 0;
		
	   	stampaMenuPrenotazione();
		
		fflush(stdin);
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
                gestisciPartenzaEDestinazione(voli, utenteCorrente);
                break;
                
            case 2:
                gestisciSolaPartenza(utenti, voli, utenteCorrente);
                break;

            case 3:
                stampaGrafo(voli);
                break;

            case 4:
            	puts("");
                break;
				
            default:
                printf("\nDato inserito non rientra nelle opzioni, riprovare;\n");    
		}
        fflush(stdin);
        
	}while(selettoreAzione != 4);
}

void gestisciTickets(t_abr * utenteCorrente){
	
}

void terminaGestioneCliente(int * selettoreAzione){
		*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di logout, si reinserisca 4 per confermare: ");
		fflush(stdin);	
		scanf("%d" , selettoreAzione);
		if(*selettoreAzione == 4)
			printf("\nLogout avvenuto con successo");
}

void gestisciCliente(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente){
	int selettoreAzione;
	
	do{
		selettoreAzione = 0;
		
		stampaMenuCliente();
		
		fflush(stdin);
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
                effettuaPrenotazione(utenti, voli, utenteCorrente);
                break;
                
            case 2:
            	if(utenteCorrente->utente.prenotazioni)
                	mostraPrenotazioni(utenteCorrente->utente.prenotazioni);
                else
                	printf("Oh! Non hai nessuna prenotazione you cheap fucker!\n");
                break;

            case 3:
                gestisciTickets(utenteCorrente);
                break;

            case 4:
                terminaGestioneCliente(&selettoreAzione);
                break;

            default:
                printf("\nDato inserito non rientra nelle opzioni, riprovare;\n");    
		}
        fflush(stdin);
		
	}while(selettoreAzione != 4);
}
