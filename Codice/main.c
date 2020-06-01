#include <stdio.h>
#include <stdlib.h>
#include "GestioneMain.h"

int main(){
	int selettoreAzione;
	
	//t_grafo * grafo = inizializzaGrafo(); //Non è detto che si inizializzerà in questo modo(magari hai na funzione che prende grafo come argomento, idk). Giù invece funzionerà così, ho già il metodo per gli abr dal vecchio progetto
	
	//t_abr *  utenti = inizializzaUtenti();
	
	do{
		selettoreAzione = 0;
		
		stampaMenuIniziale();
		
		scanf("%d", &selettoreAzione);
		
		switch(selettoreAzione){
			case 1:
			//effettuaRegistrazione();
			break;
				
			case 2:
			//int esito = eseguiAccesso(); //restituisce 0 se login fallito(credenziali non presenti nella struttura contenente gli utenti), 1 se le credenziali appartengono a un semplice cliente, 2 se appartengono a un admin
			//gestisciUtente(esito);
			break;
				
			case 3:
			terminaProgramma(&selettoreAzione);
			break;
			
			default:
			printf("\nDato inserito non rientra nelle opzioni, riprovare;");
		}
		puts("\n");
		fflush(stdin);
		
	}while(selettoreAzione != 3);

	return 0;
}
