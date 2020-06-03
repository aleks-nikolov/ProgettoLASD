#include "gstadmin.h"

int scelta;
char nomeaeroporto[LUNGHEZZA_NOME_AEROPORTO];
char nomepartenzavolo[LUNGHEZZA_NOME_AEROPORTO];
char nomearrivovolo[LUNGHEZZA_NOME_AEROPORTO];
float prezzo;
int durata;

void gestisciOpzioneAdmin(t_grf ** g){

    do{
        stampaMenuAdmin(&scelta);

        switch(scelta){

            case(1):
                aggiuntaAeroporto(g);
                break;

            case (2):
                aggiuntaVolo(g);
                break;

            case (3):
                rimozioneAeroporto(g);
                break;

            case (4):
                rimozioneVolo(g);
                break;

            case (5):
                printf("\nQuesti sono tutti i voli dell'aeroporto:\n\n");
                stampaGrafo(*g);
                break;

            case (6):
                printf("\n*************\nLogout dalla pagina admin\n*************\n");
                break;

            default:
                printf("\nScelta inserita non valida\n");
                break;

        }

    }while(scelta != 6);
}

void stampaMenuAdmin(int* scelta){
    printf("\nInserisci"
           "\n\t1 - Aggiungi una nuova destinazione."
           "\n\t2 - Aggiungi un nuovo volo"
           "\n\t3 - Rimuovi una destinazione"
           "\n\t4 - Rimuovi un volo"
           "\n\t5 - Stampa tutti i voli"
           "\n\t6 - Logout\n");

    scanf("%d", scelta);
}

void aggiuntaAeroporto(t_grf ** g) {

    printf("Qual'e' il nuovo aeroporto che vuoi aggiungere alle destinazioni?\n");
    scanf("%s", nomeaeroporto);
    fflush(stdin);

    *g = aggiungiAeroporto(*g, nomeaeroporto);
    printf("\nHo aggiunto %s alle destinazioni con successo!\n", nomeaeroporto);

}

void aggiuntaVolo(t_grf ** g) {

    printf("Qual'e' la partenza del nuovo volo che vuoi aggiungere?\n");
    scanf("%s", nomepartenzavolo);
    fflush(stdin);

    if(!aeroportoEsistente(*g, nomepartenzavolo)) {
        printf("\nL'aeroporto %s non esiste", nomepartenzavolo);
        return;
    }

    printf("Qual'e' la destinazione del nuovo volo con partenza da %s?\n", nomepartenzavolo);
    scanf("%s", nomearrivovolo);
    fflush(stdin);

    if(!aeroportoEsistente(*g, nomearrivovolo)) {
        printf("\nL'aeroporto %s non esiste", nomearrivovolo);
        return;
    }
    if(voloEsistente(getVertice(*g, nomepartenzavolo)->archi, nomearrivovolo)) {
        printf("\nIl volo da %s a %s esiste gia'", nomepartenzavolo, nomearrivovolo);
        return;
    }

    printf("Qual'e' il prezzo del nuovo volo con partenza da %s e diretto a %s?\n", nomepartenzavolo, nomearrivovolo);
    scanf("%f", &prezzo);
    fflush(stdin);

    printf("Qual'e' la durata del nuovo volo con partenza da %s e diretto a %s?\n", nomepartenzavolo, nomearrivovolo);
    scanf("%d", &durata);
    fflush(stdin);

    if(prezzo > 0.0f && durata > 0) {
        *g = aggiungiVolo(*g, nomepartenzavolo, nomearrivovolo, prezzo, durata);
        printf("\nIl nuovo volo proveniente da %s e diretto a %s e' stato aggiunto con successo!\n", nomepartenzavolo, nomearrivovolo);
    }
    else
        printf("\nDati di prezzo/durata non validi, inserire valori positivi");

}

void rimozioneAeroporto(t_grf ** g) {

    printf("Qual'e' il nome dell'aeroporto che vuoi rimuovere dalle destinazioni?\n");
    scanf("%s", nomeaeroporto);
    fflush(stdin);
    if(aeroportoEsistente(*g, nomeaeroporto)) {
        *g = eliminaAeroporto(*g, nomeaeroporto);
        *g = eliminaTuttiVoliAdAeroporto(*g, nomeaeroporto);
    } else
        printf("L'aeroporto %s non esiste", nomeaeroporto);

}

void rimozioneVolo(t_grf ** g) {

    printf("Qual'e' la partenza del volo che vuoi eliminare?\n");
    scanf("%s", nomepartenzavolo);
    fflush(stdin);
    if(!aeroportoEsistente(*g, nomepartenzavolo)) {
        printf("\nL'aeroporto %s non esiste", nomearrivovolo);
        return;
    }

    printf("Qual'e' la destinazione del volo con partenza da %s che vuoi eliminare?\n", nomepartenzavolo);
    scanf("%s", nomearrivovolo);
    fflush(stdin);
        if(!aeroportoEsistente(*g, nomearrivovolo)) {
        printf("\nL'aeroporto %s non esiste", nomearrivovolo);
        return;
    }

    if(!voloEsistente(getVertice(*g, nomepartenzavolo)->archi, nomearrivovolo)) {
        printf("\nIl volo da %s a %s non esiste", nomepartenzavolo, nomearrivovolo);
        return;
    }

    *g = eliminaVolo(*g, nomepartenzavolo, nomearrivovolo);

}