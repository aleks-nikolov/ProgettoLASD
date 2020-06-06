#include "gstcliente.h"

void stampaMenuCliente(){
	printf("\nSeleziona azione da effettuare:\n\n"
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

void stampaMenuSelezioneTratta(int * selettoreTratta){
	printf("\nQuale tratta si desidera scegliere?\n"
		   "1)Tratta piu' economica\n"
		   "2)Tratta piu' breve\n\n"
		   "Inserire numero: ");
		   						
	fflush(stdin);		
	scanf("%d", selettoreTratta);
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

int utilizzaTickets(t_abr * utenteCorrente){
	int sconto = 5;

	
	return sconto;
}

void costruisciCampiPrenotazione(t_grf * voli, t_grf * percorso, t_lista_S ** scali, float * prezzo){
	t_grf * tmp = percorso;
	
	for(;!grafoVuoto(tmp) && !grafoVuoto(tmp->next);tmp = tmp->next){
		*prezzo += getPesoArco(getVertice(voli, tmp->nome), getVertice(voli, tmp->next->nome), 1);
		
		if(tmp->next->next)
			*scali = inserisciInCoda_S(*scali, tmp->next->nome);
	}	
	tmp = NULL;
	free(tmp);
}

int calcolaPuntiOttenuti(float prezzo){
	int puntiOttenuti = prezzo / 10;
	
	return puntiOttenuti;
}

void gestisciPagamentoPartenzaDestinazione(t_grf * voli, t_grf * percorso, t_abr * utenteCorrente, int selettoreTratta, char * partenza, char * destinazione){
	int sconto = 0;
	float prezzo = 0;
	t_lista_S * scali = NULL;
	
	stampaPercorso(voli, percorso, selettoreTratta);
	
	costruisciCampiPrenotazione(voli, percorso, &scali, &prezzo);
	
	printf(" per un prezzo totale di %.2f", prezzo);
	
	//va inserito l'utilizzo di tickets e applicazione sconti
                				
    utenteCorrente->utente.prenotazioni = inserisciInCoda_P(utenteCorrente->utente.prenotazioni, partenza, destinazione, scali, prezzo);
                				
	utenteCorrente->utente.punti += calcolaPuntiOttenuti(prezzo);
                				
    printf("\n\nPrenotazione avvenuta con successo!\n");            			
}

void gestisciPrenotazione(t_grf * voli, t_abr * utenteCorrente, char * partenza, char * destinazione) {
    int selettoreTratta, altroTentativoTratta;

    do{
        selettoreTratta = altroTentativoTratta = 0;

        stampaMenuSelezioneTratta(&selettoreTratta);

        if(selettoreTratta == 1 || selettoreTratta == 2){
            dijkstra(&voli, partenza, destinazione, selettoreTratta);

            t_grf * percorso = costruisciPercorso(&voli, destinazione);

            float prezzo = 0;
            t_lista_S * scali = NULL;

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
			
				if(strlen(destinazione) <= 100 && aeroportoEsistente(voli, destinazione)){
					t_grf * raggiungibili = bfs(voli, partenza);
					//bfs effettua una breadth first search e controlla che l'aeroporto di destinazione sia raggiungibile da quello di partenza
					if(aeroportoEsistente(raggiungibili, destinazione)){

					    gestisciPrenotazione(voli, utenteCorrente, partenza, destinazione);
	
					}else
						printf("\n%s non e' raggiungibile da %s", destinazione, partenza);
					
				}else{
					printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 si, altro no): ");
				
					fflush(stdin);
					scanf("%d", &altroTentativoDestinazione);
				}	
			}while(altroTentativoDestinazione == 1);
			
		}else{
			printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 si, altro no): ");
			
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

            int selettoreDestinazione = 0;
            int altroTentativoTratta = 0;

            do {
                selettoreDestinazione = altroTentativoTratta = 0;

                stampaMenuSelezioneDestinazione(&selettoreDestinazione, partenza);

                if (selettoreDestinazione == 1) {  //caso destinazione più economica

                    t_grf *origine = getVertice(voli, partenza);
                    //trovaPiuEconomico restituisce un puntatore ad arco verso la destinazione adiacente alla partenza più economica
                    t_grf *destinazione = getVertice(voli, trovaPiuEconomico(origine->archi)->nome);

                    t_grf *percorso = NULL;
                    percorso = aggiungiPercorsoInTesta(percorso, destinazione);
                    percorso = aggiungiPercorsoInTesta(percorso, origine);

                    float prezzo = 0;
                    t_lista_S *scali = NULL;

                    printf("\nIl volo piu' economico da %s e' l'aeroporto di %s\n", partenza, destinazione->nome);
                    gestisciPagamentoPartenzaDestinazione(voli, percorso, utenteCorrente, 1, partenza, destinazione->nome);

                } else if (selettoreDestinazione == 2) {   //caso destinazione più gettonata
                    //qui l'implementazione di tratta più gettonata
                } else if (selettoreDestinazione == 3){   //caso scelta destinazione tra quelle raggiungibili
                    int n, altroTentativo;

                    t_grf * raggiungibili = bfs(voli, partenza);
                    raggiungibili = eliminaAeroporto(raggiungibili, partenza);

                    do {
                        altroTentativo = 0;

						printf("\nDestinazioni raggiungibili da %s", partenza);
                        elencaGrafo(raggiungibili, 1);
                        printf("\nScegliere la destinazione desiderata, inserendo il numero a fianco all'aeroporto: ");
                        fflush(stdin);
                        scanf("%d", &n);
                        if (n < 1 || n > 9) {
                            altroTentativo = 1;
                            printf("\nInput invalido, riprovare? (1 si, altro no): ");
                            fflush(stdin);
                            scanf("%d", &altroTentativo);
                        }
                    } while (altroTentativo == 1);

                    t_grf * destinazione = getVerticeByPosizione(raggiungibili, n);

                    gestisciPrenotazione(voli, utenteCorrente, partenza, destinazione->nome);
                } else {
                    printf("\nDato inserito non rientra nelle opzioni, riprovare;\n");
                    altroTentativoTratta = 1;
                }
            } while (altroTentativoTratta == 1);
        } else {
            printf("\nAeroporto inserito non coperto dalla nostra compagnia, riprovare?(1 si, altro no): ");

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
	puts("");
	
    if(utenteCorrente->utente.prenotazioni){
    	mostraPrenotazioni(utenteCorrente->utente.prenotazioni);
	}
    else
        printf("\nL'utente %s non ha effettuato alcuna prenotazione\n", utenteCorrente->utente.nomeUtente);
}

//funzioni per la gestione del terzo case della gestisciCliente

void stampaMenuTickets(){
	printf("\nSeleziona azione da effettuare;\n\n"
		   "1)Vedi punti disponibili\n"
		   "2)Vedi tickets disponibili\n"
		   "3)Converti punti in tickets\n"
		   "4)Torna indietro\n\n"
	       "Inserire numero: ");
}

void mostraPunti(t_abr * utenteCorrente){
	printf("\nL'utente %s ha a disposizione %d punti!", utenteCorrente->utente.nomeUtente, utenteCorrente->utente.punti);
}

void mostraTickets(t_abr * utenteCorrente){
	int i, percentualeSconto;
	
	printf("\nL'utente %s ha a disposizione ", utenteCorrente->utente.nomeUtente);
	
	for(i = 0, percentualeSconto = 5; i<LUNGHEZZA_TICKETS - 2; i++, percentualeSconto+=5)
		printf("%d tickets da %d%%, ", utenteCorrente->utente.tickets[i], percentualeSconto);
	
	printf("%d tickets da 20%% e %d tickets da 25%%", utenteCorrente->utente.tickets[3], utenteCorrente->utente.tickets[4]);
}

void stampaRegoleConversione(){
	printf("\nDi seguito le regole di conversione;\n\n"
		   "1)E' possibile convertire punti in tickets a patto che il numero di punti sia compreso tra 50 e 250\n"
		   "2)I tickets di sconto ottenibili vanno dal 5%%, 10%%, ... fino a 25%%(aumentano di 5 in 5 da 5 fino a 25)\n"
		   "3)50 punti corrispondono a uno sconto del 5%%, 100 punti del 10%%,... fino a 250 che corrispondono a un ticket del 25%%\n"
		   "4)Inserire numeri diversi da 50, 100, 150, 200 o 250 e' inutile(con 80 punti non otterrete uno sconto dell'8%% ma del 5 e vi saranno sottratti solo 50 punti) ma non errato\n");
}

void convertiPunti(t_abr * utenteCorrente){
	int puntiDaConvertire, altroTentativo;

	do{
		puntiDaConvertire = altroTentativo = 0;	
		
		mostraPunti(utenteCorrente);
	
		stampaRegoleConversione();
	
		printf("\nInserire il numero di punti da convertire in tickets tenendo conto delle regole di conversione: ");
	
		fflush(stdin);
		scanf("%d", &puntiDaConvertire);
	
		if(puntiDaConvertire >= 50 && puntiDaConvertire <= 250 && puntiDaConvertire <= utenteCorrente->utente.punti){//50 punti servono per convertire in un buono da 5%, 100 da 10%,... e 250 da 25%
			int scontoTicket = 0;
			
			while(puntiDaConvertire > 0){
				puntiDaConvertire -= 50;
				scontoTicket++;
			}
			utenteCorrente->utente.tickets[scontoTicket]++;
			utenteCorrente->utente.punti -= puntiDaConvertire;
			printf("\nOperazione di conversione avvenuta con successo!");
		}else if(puntiDaConvertire < 50 || puntiDaConvertire > 250 )
			printf("\nPer convertire punti in tickets e' necessario attenersi alle regole di conversione, riprovare?(1 per si, altro per no): ");
		 else
			printf("\nPunti inseriti maggiori dei punti disponibili, riprovare?(1 per si, altro per no): ");
		
		fflush(stdin);
		scanf("%d", &altroTentativo);
		
	}while(altroTentativo == 1);	
}

void gestisciTickets(t_abr * utenteCorrente){
	int selettoreAzione;
	
	do{
		selettoreAzione = 0;
		
		stampaMenuTickets();
		
		fflush(stdin);
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
                mostraPunti(utenteCorrente);
                break;
                
            case 2:
            	mostraTickets(utenteCorrente);
                break;

            case 3:
                convertiPunti(utenteCorrente);
                break;

            case 4:
                break;

            default:
                printf("\nDato inserito non rientra nelle opzioni, riprovare;");    
		}
		puts("");
        fflush(stdin);
		
	}while(selettoreAzione != 4);
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
