#include "Librerie/gstmain.h"

int main(){
    int selettoreAzione;
    int esito;
    t_abr * utenteCorrente;

    t_grf * voli = NULL;
    voli = inizializzaGrafo(voli);

    t_abr *  utenti = inizializzaUtenti();

    do{
        selettoreAzione = 0;

        stampaMenuIniziale();

        scanf("%d", &selettoreAzione);

        switch(selettoreAzione){
            case 1:
                system("cls");
                printf("REGISTRAZIONE UTENTE\n");
                effettuaRegistrazione(utenti);
                system("cls");
                printf("Registrazione avvenuta con successo!\n*********************");
                break;

            case 2:
                system("cls");
                printf("LOGIN (ACCEDI COME UTENTE O COME ADMIN)\n");
                utenteCorrente = NULL;
                esito = eseguiAccesso(utenti, &utenteCorrente); //restituisce 0 se login fallito, 1 se le credenziali appartengono a un semplice cliente, 2 se appartengono a un admin. UtenteCorrente andrà a contenere l'utente che ha effettuato l'accesso
                gestisciUtente(esito, utenti, &voli, utenteCorrente);
                break;

            case 3:
                system("cls");
                printf("UTENTI REGISTRATI\n");
            	puts("");
                mostraUtenti(utenti);
                break;

            case 4:
                system("cls");
                terminaProgramma(&selettoreAzione);
                break;

            default:
                system("cls");
                printf("Dato inserito non rientra nelle opzioni, riprovare;\n*********************");
        }
        puts("\n");
        fflush(stdin);

    }while(selettoreAzione != 4);

    return 0;
}
