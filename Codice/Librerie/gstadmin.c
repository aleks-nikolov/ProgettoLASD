#include "gstadmin.h"

int sceltaAdmin;


void menuAdmin(int* scelta;){
    printf("Inserisci\n"
           "\t1 - Aggiungi una nuova destinazione."
           "\t2 - Aggiungi un nuovo volo"
           "\t3 - Rimuovi una destinazione"
           "\t4 - Rimuovi un volo"
           "\t5 - Stampa tutti i voli"
           "\t6 - Logout");

    scanf("%d", *scelta);
}

t_grf* gestisciopzione(t_grf* g){
    int scelta;
    char* nomeaeroporto;
    char* nomepartenzavolo;
    char* nomearrivovolo;
    float prezzo;
    int durata;


    do{
        menuAdmin(&scelta);

        switch(scelta){

            case(1):

                printf("Qual'è il nuovo aeroporto che vuoi aggiungere alle destinazioni?\n");
                scanf("%s", nomeaeroporto);
                fflush(stdin);

                g = aggiungiAeroporto(g, nomeaeroporto);
                printf("\nHo aggiunto %s alle destinazioni con successo!\n", nomeaeroporto);

                break;

            case (2):

                printf("Qual'e' la partenza del nuovo volo che vuoi aggiungere?\n");
                scanf("%s", nomepartenzavolo);
                fflush(stdin);

                printf("Qual'e' la destinazione del nuovo volo con partenza da %s?", nomepartenzavolo);
                scanf("%s", nomearrivovolo);
                fflush(stdin);

                printf("Qual'e' il prezzo del nuovo volo con partenza da %s e diretto a %s?", nomepartenzavolo, nomearrivovolo);
                scanf("%f", prezzo);
                fflush(stdin);

                printf("Qual'e' la durata del nuovo volo con partenza da %s e diretto a %s?", nomepartenzavolo, nomearrivovolo);
                scanf("%d", durata);
                fflush(stdin);


                g = aggiungiVolo(g, nomepartenzavolo, nomearrivovolo, prezzo, durata);

                printf("\nIl nuovo volo proveniente da %s e diretto a %s e' stato aggiunto con successo!\n", nomepartenzavolo, nomearrivovolo);

                break;

            case (3):

                printf("Qual'è il nome dell'aeroporto che vuoi rimuovere dalle destinazioni?\n");
                scanf("%s", nomeaeroporto);
                fflush(stdin);

                g = eliminaAeroporto(g, nomeaeroporto);

                printf("Ho eliminato %s dalle destinazioni!\n", nomeaeroporto);

                break;

            case (4):

                printf("Qual'e' la partenza del volo che vuoi eliminare?\n");
                scanf("%s", nomepartenzavolo);
                fflush(stdin);

                printf("Qual'e' la destinazione del volo con partenza da %s che vuoi eliminare?", nomepartenzavolo);
                scanf("%s", nomearrivovolo);
                fflush(stdin);

                eliminaVolo(g, nomepartenzavolo, nomearrivovolo);

                printf("\nIl volo proveniente da %s e diretto a %s e' stato eliminato con successo!\n", nomepartenzavolo, nomearrivovolo);

                break;

            case (5):

                printf("\nQuesti sono tutti i voli dell'aeroporto:\n\n")
                stampaGrafo(g);

            case (6):

                printf("\n*************\nLogout dalla pagina admin\n*************\n")
                break;

            default:

                printf("\nScelta inserita non valida\n");
                break;

        }


    }while(scelta != 5);

    return tempg;
}
