#include "gestioneApplicativo.h"

 void toUpper_String(char * string){
	int i;
	
	for(i=0; string[i];i++){
		string[i] = toupper(string[i]);
	}
}

void stampaMenuIniziale(){
	
	printf("Selezionare azione da effettuare;\n\n");
	printf("1)Effettua nuova registrazione\n");
	printf("2)Esegui accesso\n");
	printf("3)Termina programma\n\n");
	printf("Inserire numero: ");
}

void terminaProgramma(int * selettoreAzione){
	*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di terminazione del programma, si reinserisca 3 per confermare: ");
			
		scanf("%d" , selettoreAzione);
}

/*void stampaRegoleCredenziali(){
	printf("\nNome utente e password non possono contenere spazi!);
}

void effettuaRegistrazione(t_abr * utenti){
	char nomeTmp[LUNGHEZZA_NOME_UTENTE];
	char passTmp[LUNGHEZZA_PASSWORD];
	int nomeAmmesso;
	int passwordAmmessa;
	
	fflush(stdin);
	
	stampaRegoleCredenziali();
	
	do{
		nomeAmmesso = 1;
		passwordAmmessa = 1;
		
		printf("\n\nInserire nuovo nome utente");
		gets(nomeTmp);
		
		if(!strchr(nomeTmp, ' ')){
			if(!contains_U(utenti, nomeTmp)){
			
			}else{
				printf("\nNome utente non disponibile, riprovare");
				nomeAmmesso = 0;
			}
		}
		
	}while(!nomeAmmesso || !passwordAmmessa);
}

int eseguiAccesso(){

}

gestisciUtente(esito){
	
}

*/
