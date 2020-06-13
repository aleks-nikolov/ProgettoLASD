#include "gstmain.h"

void stampaMenuIniziale(){

	printf("MENU INIZIALE\n"
		   "Selezionare azione da effettuare;\n\n"
		   "1)Effettua nuova registrazione\n"
		   "2)Esegui accesso\n"
		   "3)Visualizza utenti\n"
		   "4)Termina programma\n\n"
	       "Inserire numero: ");
}

void terminaProgramma(int * selettoreAzione){
	*selettoreAzione = 0;

		printf("E' stato selezionato il comando di terminazione del programma, si reinserisca 4 per confermare: ");
		fflush(stdin);
		scanf("%d" , selettoreAzione);
}

void stampaRegoleCredenziali(){
	printf("\n(Ricorda, nome utente e password non possono contenere spazi, e la loro lunghezza non deve superare i 20 caratteri!)\n*********************");
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

        if(strlen(nomeTmp) > 0){
            printf("REGISTRAZIONE UTENTE\n");
            printf("\nNome utente inserito: %s", nomeTmp);
        }
        else{
            printf("\n\nInserire nome nuovo utente: ");
            gets(nomeTmp);
            fflush(stdin);
        }

		if(!strchr(nomeTmp, ' ') && strlen(nomeTmp) <= 20){
			if(!contains_U(utenti, nomeTmp, NULL)){

				printf("\nInserire nuova password: ");
				gets(passwordTmp);
				fflush(stdin);

				if(!strchr(passwordTmp, ' ') && strlen(passwordTmp) <= 20){
					utenti = inserisciNodo_U(utenti, nomeTmp, passwordTmp, 0);
				}else{
				    system("cls");
					printf("La password non puo' contenere spazi e la lunghezza non deve superare i 20 caratteri, riprovare\n*********************\n");
					passwordAmmessa = 0;
				}
			}else{
			    system("cls");
				printf("Nome utente non disponibile, riprovare\n*********************\n");
				nomeAmmesso = 0;
			}
		}else{
		    system("cls");
			printf("Il nome utente non puo' contenere spazi e la lunghezza non deve superare i 20 caratteri, riprovare\n*********************\n");
			nomeAmmesso = 0;
		}
	}while(nomeAmmesso == 0 || passwordAmmessa == 0);
}

int eseguiAccesso(t_abr * utenti, t_abr ** contenitore){//ritorna 0 se l'accesso fallisce, 1 se l'accesso avvenuto è di un utente, 2 se l'accesso avvenuto è di un admin. Contenitore andrà a contenere l'utente che ha fatto l'accesso(se c'è)
	char nomeTmp[LUNGHEZZA_NOME_UTENTE];
	char passwordTmp[LUNGHEZZA_PASSWORD];
	t_abr * utenteTmp;
	int esito = 0;
	int altroTentativo = 0;

	fflush(stdin);

	printf("\nInserire nome utente: ");
	gets(nomeTmp);
	fflush(stdin);

	if(strlen(nomeTmp) <= 20 && contains_U(utenti, nomeTmp, &utenteTmp)){
		do{
            if(altroTentativo == 1 && strlen(nomeTmp) > 0){
                printf("LOGIN (ACCEDI COME UTENTE O COME ADMIN)\n");
                printf("\nNome utente inserito: %s", nomeTmp);
            }
			printf("\nInserire password: ");
			gets(passwordTmp);
			fflush(stdin);

			if(strlen(passwordTmp) <= 20 && strcmp(utenteTmp->utente.password, passwordTmp) == 0){
                altroTentativo = 0;
				if(utenteTmp->utente.admin == 0)
					esito = 1;
				else
					esito = 2;
                system("cls");
				printf("Accesso eseguito con successo, benvenuto %s!\n*********************\n", nomeTmp);
				if(contenitore)
				*contenitore = utenteTmp;
			}else{
				printf("\n*********************\nPassword errata, si desidera riprovare? (1 per si, altro per no): ");
				scanf("%d", &altroTentativo);
				fflush(stdin);
				system("cls");
			}
		}while(altroTentativo == 1);
	}else{
	    system("cls");
		printf("Nome utente non riconosciuto, riprovare o creare un nuovo account\n*********************");
	}
	return esito;
}

void gestisciUtente(int esito, t_abr * utenti, t_grf ** voli, t_abr * utenteCorrente){
	if(esito == 1){
		gestisciCliente(utenti, *voli, utenteCorrente);
	}
	else if(esito == 2){
		gestisciOpzioneAdmin(voli);
	}
}




