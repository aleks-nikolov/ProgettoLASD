#include "gstcliente.h"

void stampaMenuCliente(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Effettua prenotazione\n"
		   "2)Stampa prenotazioni attive\n"
		   "3)Gestisci punti e tickets\n"
		   "4)Logout\n\n"
	       "Inserire numero: ");
}

//funzioni per la gestione del primo case della gestisciCLiente

void stampaMenuPrenotazione(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Effettua prenotazione inserendo partenza e destinazione\n"
		   "2)Effettua prenotazione inserendo sola partenza\n"
		   "3)Mostra voli\n"
		   "4)Torna indietro\n\n"
	       "Inserire numero: ");
}

void stampaMenuSelezioneTratta(){
	printf("\nQuale tratta si desidera scegliere?\n"
		   "1)Tratta piu' economica\n"
		   "2)Tratta piu' breve\n\n"
		   "Inserire numero: ");
}

void stampaMenuSelezioneDestinazione(int * selettoreTratta, char *partenza){
    printf("\nQuale destinazione si desidera scegliere?\n"
           "1)Destinazione piu' economica\n"
           "2)Destinazione piu' gettonata\n"
           "3)Mostra tutte le destinazioni raggiungibili da %s\n\n"
           "Inserire numero: ", partenza);

    fflush(stdin);
    scanf("%d", selettoreTratta);
}

void costruisciCampiPrenotazione(t_grf * voli, t_grf * percorso, t_lista_S ** scali, float * prezzo, int * tempo){
	
	if(!grafoVuoto(percorso) && !grafoVuoto(percorso->next)){
		*prezzo += getPesoArco(getVertice(voli, percorso->nome), getVertice(voli, percorso->next->nome), 1);
		
		*tempo += getPesoArco(getVertice(voli, percorso->nome), getVertice(voli, percorso->next->nome), 2);
		
		if(!grafoVuoto(percorso->next->next)){
			*scali = inserisciInCoda_S(*scali, percorso->next->nome);
			
			costruisciCampiPrenotazione(voli, percorso->next, scali, prezzo, tempo);
		}
	}	
}

float utilizzaTickets(t_abr * utenteCorrente, int * ticketsUtilizzati){
	float sconto = 0.0;
	int selettoreAzione = 0;
	
	printf("\nSi desidera utilizzare tickets di sconto?(1 per si, altro per no): ");
	
	fflush(stdin);
	scanf("%d", &selettoreAzione);
	
	if(selettoreAzione == 1){
		int selettoreTicket = 0;
		int altroTentativoTicket = 0;
		int ticketRimanenti = MAX_TICKETS_UTILIZZABILI;
		
		do{
			mostraTickets(utenteCorrente);
		
			stampaMenuSelezioneTicket();
		
			fflush(stdin);
			scanf("%d", &selettoreTicket);
		
			if(1 <= selettoreTicket && selettoreTicket <= 5 && utenteCorrente->utente.tickets[selettoreTicket - 1] > 0){
				sconto += 5.0 * selettoreTicket;
				utenteCorrente->utente.tickets[selettoreTicket -1]--;
				ticketsUtilizzati[ticketRimanenti - 1] = selettoreTicket - 1;
				ticketRimanenti--;
					
				if(ticketRimanenti == 1)
					printf("\nSi desidera utilizzare un secondo ticket di sconto?(1 per si, altro per no): ");
						
			}else if(selettoreTicket < 1 || selettoreTicket > 5)
					printf("\nDato inserito non valido, riprovare?(1 per si, altro per no): ");
			 else if(utenteCorrente->utente.tickets[selettoreTicket - 1] == 0)
					printf("\nNon si hanno tickets di questo sconto rimanenti, riprovare?(1 per si, altro per no): ");		
				
				if(ticketRimanenti > 0){
					fflush(stdin);
					scanf("%d", &altroTentativoTicket);
				
				if(altroTentativoTicket != 1)
					ticketRimanenti = 0;
				}	
		}while(ticketRimanenti > 0);
	}
	return sconto;
}

void gestisciPagamentoPartenzaDestinazione(t_grf * voli, t_grf * percorso, t_abr * utenteCorrente, int selettoreTratta, char * partenza, char * destinazione){
	float sconto;
	int confermaPrenotazione = 0;
	float prezzo = 0;
	int tempo = 0;
	t_lista_S * scali = NULL;
	int ticketsUtilizzati[MAX_TICKETS_UTILIZZABILI];
	
	inizializzaTicketsUtilizzati(ticketsUtilizzati);
	
	puts("");
	
	stampaPercorso(voli, percorso, selettoreTratta);
	
	costruisciCampiPrenotazione(voli, percorso, &scali, &prezzo, &tempo);
	
	printf(" per un prezzo totale di %.2f euro e tempo totale di %d minuti\n", prezzo, tempo);
	
	sconto = utilizzaTickets(utenteCorrente, ticketsUtilizzati);
	
	prezzo = prezzo * (1 - (sconto/100));

	printf("\n%s, conferma la prenotazione di costo %.2f euro?(1 per si, altro per no): ", utenteCorrente->utente.nomeUtente, prezzo);
	
	fflush(stdin);
	scanf("%d", &confermaPrenotazione);
    
	if(confermaPrenotazione == 1){
		utenteCorrente->utente.prenotazioni = inserisciInCoda_P(utenteCorrente->utente.prenotazioni, partenza, destinazione, scali, prezzo, tempo);
	                				
		utenteCorrente->utente.punti += calcolaPuntiOttenuti(prezzo);
	                				
	    printf("\nPrenotazione avvenuta con successo!\n");  
	}else{
		if(sconto)
			restituisciTickets(utenteCorrente, ticketsUtilizzati);
		printf("\nPrenotazione annullata;\n");
	}		           				            			
}

void gestisciPrenotazione(t_grf * voli, t_abr * utenteCorrente, char * partenza, char * destinazione) {
    int selettoreTratta, altroTentativoTratta;

    do{
        selettoreTratta = altroTentativoTratta = 0;

        stampaMenuSelezioneTratta();
        
        fflush(stdin);		
		scanf("%d", &selettoreTratta);

        if(selettoreTratta == 1 || selettoreTratta == 2){
            dijkstra(&voli, partenza, destinazione, selettoreTratta);

            t_grf * percorso = costruisciPercorso(&voli, destinazione);

            gestisciPagamentoPartenzaDestinazione(voli, percorso, utenteCorrente, selettoreTratta, partenza, destinazione);
        }else{
            printf("\nDato inserito non rientra nelle opzioni, riprovare;\n");
            altroTentativoTratta = 1;
        }
    }while(altroTentativoTratta == 1);
}

void gestisciPartenzaEDestinazione(t_grf * voli, t_abr * utenteCorrente){
	int altroTentativoPartenza;
	int altroTentativoDestinazione;
	
	char partenza[LUNGHEZZA_NOME_AEROPORTO];
	char destinazione[LUNGHEZZA_NOME_AEROPORTO];
	
	do{
		altroTentativoPartenza = 0;
		
		printf("\nInserire aeroporto di partenza: ");
	
		fflush(stdin);
		gets(partenza);
	
		if(strlen(partenza) <= 100 && aeroportoEsistente(voli, partenza)){
			
			do{
				altroTentativoDestinazione = 0;
				
				printf("\nInserire aeroporto di destinazione: ");
			
				fflush(stdin);
				gets(destinazione);
				
                if (strcmp(strupr(partenza),strupr(destinazione))!= 0 && strlen(destinazione) <= 100 && aeroportoEsistente(voli, destinazione)) {
                    t_grf *raggiungibili = bfs(voli, partenza);
                    //bfs effettua una breadth first search e controlla che l'aeroporto di destinazione sia raggiungibile da quello di partenza
                    if (aeroportoEsistente(raggiungibili, destinazione))
						gestisciPrenotazione(voli, utenteCorrente, partenza, destinazione);
                    else
                        printf("\n%s non e' raggiungibile da %s\n\n", destinazione, partenza);

                }else {
                	if(!aeroportoEsistente(voli, destinazione))
                        printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 per si, altro per no): ");
                 	else if(strcmp(strupr(partenza),strupr(destinazione))== 0) 
                    	printf("\nPer favore inserire aeroporti di partenza e destinazine diversi, riprovare?(1 per si, altro per no): ");

                    	fflush(stdin);
                    	scanf("%d", &altroTentativoDestinazione);
				}
			}while(altroTentativoDestinazione == 1);
			
		}else{
			printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 per si, altro per no): ");
			
			fflush(stdin);
			scanf("%d", &altroTentativoPartenza);
		}
	}while(altroTentativoPartenza == 1);
}

void gestisciSolaPartenza(t_abr * utenti, t_grf * voli, t_abr * utenteCorrente){
    int altroTentativoPartenza;

    char partenza[LUNGHEZZA_NOME_AEROPORTO];

    do{
        altroTentativoPartenza = 0;

        printf("\nInserire aeroporto di partenza: ");
        fflush(stdin);
        gets(partenza);

        if (strlen(partenza) <= 100 && aeroportoEsistente(voli, partenza)) {

            if (haVoli(getVertice(voli, partenza))) {

                int selettoreDestinazione = 0;
                int altroTentativoTratta;

                do {
                    selettoreDestinazione = altroTentativoTratta = 0;

                    stampaMenuSelezioneDestinazione(&selettoreDestinazione, partenza);

                    if (selettoreDestinazione == 1) {  //caso destinazione più economica

                        t_grf *percorso = trovaPiuEconomico(voli, partenza);
                        t_grf *destinazione = percorso->next;

                        printf("\nLa meta piu' economica da %s e' l'aeroporto di %s\n", partenza, destinazione->nome);
                        gestisciPagamentoPartenzaDestinazione(voli, percorso, utenteCorrente, 1, partenza,
                                                              destinazione->nome);

                    } else if (selettoreDestinazione == 2) {   //caso destinazione più gettonata

                        //Resetta la popolarita dei voli ed imposta i valori di popolarita in base alle prenotazioni esistenti
                        voli = azzeraPopolarita(voli);
                        visita(utenti, voli, partenza);

                        //Restituisce l'aeroporto verso il quale ci sono più voli dalla partenza, oppure NULL se non è possibile stabilirlo
                        t_grf *destinazione = trovaPiuGettonato(voli, partenza);

                        //Se esiste una meta gettonata effettua una prenotazione per essa, altrimenti trova quella più economica
                        if (destinazione != NULL) {
                            printf("\nLa meta piu' gettonata da %s e' l'aeroporto di %s", partenza, destinazione->nome);
                            gestisciPrenotazione(voli, utenteCorrente, partenza, destinazione->nome);
                        } else {
                            t_grf *percorso = trovaPiuEconomico(voli, partenza);
                            destinazione = percorso->next;
                            printf("\nNon ci sono dati sufficienti per trovare la meta piu' gettonata da %s", partenza);
                            printf("\nEcco un'altra destinazione che le potrebbe interessare: %s", destinazione->nome);
                            gestisciPagamentoPartenzaDestinazione(voli, percorso, utenteCorrente, 1, partenza, destinazione->nome);
                        }

                    } else if (selettoreDestinazione == 3) {   //caso scelta destinazione tra quelle raggiungibili
                        int n, altroTentativo;

                        t_grf *raggiungibili = bfs(voli, partenza);
                        raggiungibili = eliminaAeroporto(raggiungibili, partenza);
                        t_grf *destinazione = NULL;
                        do {
                            altroTentativo = 0;

                            printf("\nDestinazioni raggiungibili da %s", partenza);
                            elencaGrafo(raggiungibili, 1);
                            printf("\nScegliere la destinazione desiderata, inserendo il numero a fianco all'aeroporto: ");
                            fflush(stdin);
                            scanf("%d", &n);
                            if (n < 1 || n > lunghezzaGrafo(raggiungibili)) {
                                altroTentativo = 1;
                                printf("\nInput invalido, riprovare? (1 per si, altro per no): ");
                                fflush(stdin);
                                scanf("%d", &altroTentativo);
                            } else
                                destinazione = getVerticeByPosizione(raggiungibili, n);
                        } while (altroTentativo == 1);

                        if (destinazione != NULL)
                            gestisciPrenotazione(voli, utenteCorrente, partenza, destinazione->nome);
                        else {
                            printf("\nImpossibile effettuare la prenotazione, torno al menu\n");
                            break;
                        }
                    } else {
                        printf("\nDato inserito non rientra nelle opzioni, riprovare;\n");
                        altroTentativoTratta = 1;
                    }
                } while (altroTentativoTratta == 1);
            } else {
                printf("\nAl momento non ci sono voli da %s, vuole inserire un'altra partenza? (1 per si, altro per no)", partenza);
                fflush(stdin);
                scanf("%d", &altroTentativoPartenza);
            }
        } else {
            printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 per si, altro per no): ");
            fflush(stdin);
            scanf("%d", &altroTentativoPartenza);
        }
    }while(altroTentativoPartenza == 1);
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
                selettoreAzione = 4;
                break;
                
            case 2:
                gestisciSolaPartenza(utenti, voli, utenteCorrente);
                selettoreAzione = 4;
                break;

            case 3:
                stampaGrafo(voli);
                puts("");
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

//funzione per la gestione del secondo case della gestisciCliente

void visualizzaPrenotazioni(t_abr * utenteCorrente){
	
    if(utenteCorrente->utente.prenotazioni){
    	puts("");
    	mostraPrenotazioni(utenteCorrente->utente.prenotazioni);
	}
    else
        printf("\nL'utente %s non ha effettuato alcuna prenotazione\n", utenteCorrente->utente.nomeUtente);
}

//funzione per la gestione del quarto case della gestisciCliente

void terminaGestioneCliente(int * selettoreAzione){
		*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di logout, si reinserisca 4 per confermare: ");
		fflush(stdin);	
		scanf("%d" , selettoreAzione);
		if(*selettoreAzione == 4)
			printf("\nLogout avvenuto con successo");
}

//gestisciCliente

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
            	visualizzaPrenotazioni(utenteCorrente);
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
