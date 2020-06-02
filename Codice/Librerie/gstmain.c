#include "gstmain.h"

void stampaMenuIniziale(){
	
	printf("Selezionare azione da effettuare;\n\n"
		   "1)Effettua nuova registrazione\n"
		   "2)Esegui accesso\n"
		   "3)Termina programma\n"
		   "4)Visualizza utenti\n\n"
	       "Inserire numero: ");
}

void terminaProgramma(int * selettoreAzione){
	*selettoreAzione = 0;																
	
		printf("\nE' stato selezionato il comando di terminazione del programma, si reinserisca 3 per confermare: ");
			
		scanf("%d" , selettoreAzione);
}

void stampaRegoleCredenziali(){
	printf("\nRicorda, nome utente e password non possono contenere spazi!");
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
		fflush(stdin);
		
		if(!strchr(nomeTmp, ' ')){
			if(!contains_U(utenti, nomeTmp, NULL)){
				
				printf("\nInserire nuova password: ");
				gets(passwordTmp);
				fflush(stdin);
				
				if(!strchr(passwordTmp, ' '))
					utenti = inserisciNodo_U(utenti, nomeTmp, passwordTmp, 0);
				else{
					printf("\nLa password non puo' contenere spazi, riprovare");
					passwordAmmessa = 0;
				}
			}else{
				printf("\nNome utente non disponibile, riprovare");
				nomeAmmesso = 0;
			}
		}else{
			printf("\nIl nome utente non puo' contenere spazi, riprovare");
			nomeAmmesso = 0;
		}
	}while(nomeAmmesso == 0 || passwordAmmessa == 0);
}

int eseguiAccesso(t_abr * utenti){//ritorna 0 se l'accesso fallisce, 1 se l'accesso avvenuto è di un utente, 2 se l'accesso avvenuto è di un admin
	char nomeTmp[LUNGHEZZA_NOME_UTENTE];
	char passwordTmp[LUNGHEZZA_PASSWORD];
	t_abr * utenteTmp;
	int esito = 0;
	int altroTentativo;
	
	fflush(stdin);
	
	printf("\nInserire nome utente: ");
	gets(nomeTmp);
	fflush(stdin);
	
	if(contains_U(utenti, nomeTmp, &utenteTmp)){
		do{
			int altroTentativo = 0;
			
			printf("\nInserire password: ");
			gets(passwordTmp);
			fflush(stdin);
			
			if(strcmp(utenteTmp->utente.password, passwordTmp) == 0){
				if(utenteTmp->utente.admin == 0)
					esito = 1;
				else
					esito = 2;
			}else{
				printf("\nPassword errata, si desidera riprovare? (1 per si, altro per no)");
				scanf("%d", &altroTentativo);
			} 
		}while(altroTentativo == 1);
	}else
		printf("\nNome utente non riconosciuto, riprovare o creare un nuovo account");
	
	return esito;
}

/*gestisciUtente(int esito, t_abr * utenti, t_grf * tratte){
	
}

*/


