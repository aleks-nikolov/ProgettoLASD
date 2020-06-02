#include "Librerie/gstmain.h"
#include "Librerie/gstadmin.h"

int main(){
    int selettoreAzione;
    int esito;
    t_abr * utenteCorrente;

    t_grf * grafo = NULL;
    grafo = inizializzaGrafo(grafo);

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
            	utenteCorrente = NULL;
                esito = eseguiAccesso(utenti, &utenteCorrente); //restituisce 0 se login fallito, 1 se le credenziali appartengono a un semplice cliente, 2 se appartengono a un admin. UtenteCorrente andrà a eseguire l'utente che ha effettuato l'accesso
                //gestisciUtente(esito, utenti, tratte, &utenteCorrente);
                if (esito == 1)
                    printf("\nAccesso come utente");
                else if (esito == 2)
                    gestisciOpzioneAdmin(&grafo);
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
