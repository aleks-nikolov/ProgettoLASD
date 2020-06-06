#include "gstpunti.h"

int utilizzaTickets(t_abr * utenteCorrente){
	int sconto = 5;

	
	return sconto;
}

int calcolaPuntiOttenuti(float prezzo){
	
	return prezzo / 10;
}

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
