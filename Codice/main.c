#include <stdio.h>
#include <stdlib.h>
#include "gstmain.h"

int main(){
	int selettoreAzione;
	int esito;
	
	//t_grf * grafo = NULL;
    //grafo = inizializzaGrafo(grafo);
	
	t_abr *  utenti = inizializzaUtenti();
	
	do{
		selettoreAzione = 0;
		
		stampaMenuIniziale();
		
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
			effettuaRegistrazione(utenti);
			break;
				
			case 2:
			esito = eseguiAccesso(utenti); //restituisce 0 se login fallito(credenziali non presenti nella struttura contenente gli utenti), 1 se le credenziali appartengono a un semplice cliente, 2 se appartengono a un admin
			//gestisciUtente(esito, utenti, tratte);
			break;
				
			case 3:
			terminaProgramma(&selettoreAzione);
			break;
			
			case 4://inserito per questioni di testing
			puts("");
			mostraUtenti(utenti);
			break;
			
			default:
			printf("\nDato inserito non rientra nelle opzioni, riprovare;");
		}
		puts("\n");
		fflush(stdin);
		
	}while(selettoreAzione != 3);

	return 0;
}
