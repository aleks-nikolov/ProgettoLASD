#include "gstmain.h"

void stampaMenuIniziale(){
	
	printf("Selezionare azione da effettuare;\n\n");
	printf("1)Effettua nuova registrazione\n");
	printf("2)Esegui accesso\n");
	printf("3)Termina programma\n\n");
	printf("4)Visualizza utenti\n\n");
	printf("Inserire numero: ");
}

void terminaProgramma(int * selettoreAzione){
	*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di terminazione del programma, si reinserisca 3 per confermare: ");
			
		scanf("%d" , selettoreAzione);
}

void stampaRegoleCredenziali(){
	printf("\nNome utente e password non possono contenere spazi!");
}

void effettuaRegistrazione(t_abr * utenti){
	char nomeTmp[LUNGHEZZA_NOME_UTENTE];
	char passwordTmp[LUNGHEZZA_PASSWORD];
	int nomeAmmesso;
	int passwordAmmessa;
	
	fflush(stdin);
	
	stampaRegoleCredenziali();
	do{
		nomeAmmesso = 1;
		passwordAmmessa = 1;
		
		printf("\n\nInserire nome nuovo utente: ");
		gets(nomeTmp);
		
		if(!strchr(nomeTmp, ' ')){
			if(!contains_U(utenti, nomeTmp)){
				
				printf("\nInserire nuova password: ");
				gets(passwordTmp);
				
				if(!strchr(passwordTmp, ' '))
					utenti = inserisciNodo_U(utenti, nomeTmp, passwordTmp);
				else{
					printf("\nLa password non può contenere spazi, riprovare");
					passwordAmmessa = 0;
				}
			}else{
				printf("\nNome utente non disponibile, riprovare");
				nomeAmmesso = 0;
			}
		}else{
			printf("\nIl nome utente non può contenere spazi, riprovare");
			nomeAmmesso = 0;
		}
	}while(nomeAmmesso == 0 || passwordAmmessa == 0);
}

int eseguiAccesso(){
	int esito = 0;
	
	
	
	return esito;
}

gestisciUtente(int esito){
	
}

*/


