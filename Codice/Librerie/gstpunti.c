#include "gstpunti.h"

void stampaMenuSelezioneTicket(){
	printf("\n\nE' possibile utilizzare un massimo di %d tickets per prenotazione, selezionare primo ticket;\n"
		   "1)Ticket da 5%%\n"
		   "2)Ticket da 10%%\n"
		   "3)Ticket da 15%%\n"
		   "4)Ticket da 20%%\n"
		   "5)Ticket da 25%%\n\n"
	       "Inserire numero: ", MAX_TICKETS_UTILIZZABILI);
}

int calcolaPuntiOttenuti(float prezzo){//la generazione di punti sarebbe di gran lunga inferiore in ambiente reale, ma in questo modo facilitiamo il testing
	int puntiOttenuti = prezzo;
	
	return puntiOttenuti;
}

void stampaMenuTickets(){
	printf("\nGESTIONE TICKETS"
		   "\nSeleziona azione da effettuare;\n\n"
		   "1)Vedi punti disponibili\n"
		   "2)Vedi tickets disponibili\n"
		   "3)Converti punti in tickets\n"
		   "4)Torna indietro\n\n"
	       "Inserire numero: ");
}

void mostraPunti(t_abr * utenteCorrente){
	system("cls");
	printf("\nL'utente %s ha a disposizione %d punti!", utenteCorrente->utente.nomeUtente, utenteCorrente->utente.punti);
}

void mostraTickets(t_abr * utenteCorrente){
	int i, percentualeSconto;
	
	system("cls");
	printf("\nL'utente %s ha a disposizione ", utenteCorrente->utente.nomeUtente);
	
	for(i = 0, percentualeSconto = 5; i<LUNGHEZZA_TICKETS - 2; i++, percentualeSconto+=5)
		printf("\n%d tickets da %d%%", utenteCorrente->utente.tickets[i], percentualeSconto);
	
	printf("\n%d tickets da 20%%\n%d tickets da 25%%", utenteCorrente->utente.tickets[3], utenteCorrente->utente.tickets[4]);
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
			
			scontoTicket = puntiDaConvertire / 50;
			
			utenteCorrente->utente.tickets[scontoTicket - 1]++;
			utenteCorrente->utente.punti -= scontoTicket * 50;
			
			printf("\nOperazione di conversione avvenuta con successo!");
			altroTentativo = 0;
			
		}else if(puntiDaConvertire < 50 || puntiDaConvertire > 250 ){
			printf("\nPer convertire punti in tickets e' necessario attenersi alle regole di conversione, riprovare?(1 per si, altro per no): ");
			
			fflush(stdin);
			scanf("%d", &altroTentativo);
		}else{
			printf("\nPunti inseriti maggiori dei punti disponibili, riprovare?(1 per si, altro per no): ");
		
			fflush(stdin);
			scanf("%d", &altroTentativo);
		}	
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
				system("cls");
                break;

            default:
                printf("\nDato inserito non rientra nelle opzioni, riprovare;");    
		}
		puts("");
        fflush(stdin);
		
	}while(selettoreAzione != 4);
}

void restituisciTickets(t_abr * utenteCorrente, int * ticketsUtilizzati){
	int i;
	
	for(i=0;i<MAX_TICKETS_UTILIZZABILI;i++){
		if(ticketsUtilizzati[i] != -1)
		utenteCorrente->utente.tickets[ticketsUtilizzati[i]]++;
	}
}

void inizializzaTicketsUtilizzati(int * ticketsUtilizzati){
	int i;
	
	for(i=0;i<MAX_TICKETS_UTILIZZABILI;i++)
		ticketsUtilizzati[i] = -1;
}
