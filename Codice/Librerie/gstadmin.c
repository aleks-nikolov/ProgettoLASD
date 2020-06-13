#include "gstadmin.h"

int scelta;
int pesoDiRiferimento;
char nomeaeroporto[LUNGHEZZA_NOME_AEROPORTO];
char nomepartenzavolo[LUNGHEZZA_NOME_AEROPORTO];
char nomearrivovolo[LUNGHEZZA_NOME_AEROPORTO];
float prezzo;
int durata;

void gestisciOpzioneAdmin(t_grf ** voli){

    do{
        printf("MENU ADMIN\n");
        stampaMenuAdmin();
        scanf("%d", &scelta);

        switch(scelta){

            case(1):
                system("cls");
                printf("NUOVA DESTINAZIONE\n\n");
                aggiuntaAeroporto(voli);
                break;

            case (2):
                system("cls");
                printf("NUOVA TRATTA\n\n");
                aggiuntaVolo(voli);
                break;

            case (3):
                system("cls");
                printf("RIMOZIONE AEROPORTO\n\n");
                rimozioneAeroporto(voli);
                break;

            case (4):
                system("cls");
                printf("RIMOZIONE TRATTA\n\n");
                rimozioneVolo(voli);
                break;

            case (5):
                system("cls");
                printf("QUESTE SONO TUTTE LE TRATTE DELL'AEROPORTO\n\n");
                stampaGrafo(*voli);
                printf("\n\n");
                break;

            case (6):
                system("cls");
                printf("*************\nLogout dalla pagina admin\n*************\n");
                break;

            default:
                system("cls");
                printf("Scelta inserita non valida\n*************\n");
                break;

        }

    }while(scelta != 6);
}

void stampaMenuAdmin(){
    printf("\nInserisci"
           "\n\t1 - Aggiungi una nuova destinazione."
           "\n\t2 - Aggiungi un nuovo volo"
           "\n\t3 - Rimuovi una destinazione"
           "\n\t4 - Rimuovi un volo"
           "\n\t5 - Stampa tutti i voli"
           "\n\t6 - Logout\n");
}

void aggiuntaAeroporto(t_grf ** g) {

    printf("Qual'e' il nuovo aeroporto che vuoi aggiungere alle destinazioni? ");
    scanf("%s", nomeaeroporto);
    fflush(stdin);

    *g = aggiungiAeroporto(*g, nomeaeroporto);
    system("cls");
    printf("Ho aggiunto %s alle destinazioni con successo!\n*************\n", nomeaeroporto);

}

void aggiuntaVolo(t_grf ** g) {

    printf("Qual'e' la partenza del nuovo volo che vuoi aggiungere? ");
    scanf("%s", nomepartenzavolo);
    fflush(stdin);

    if(!aeroportoEsistente(*g, nomepartenzavolo)) {
        system("cls");
        printf("L'aeroporto %s non esiste\n*************\n", nomepartenzavolo);
        return;
    }

    system("cls");
    printf("Qual'e' la destinazione del nuovo volo con partenza da %s? ", nomepartenzavolo);
    scanf("%s", nomearrivovolo);
    fflush(stdin);

    if(!aeroportoEsistente(*g, nomearrivovolo)) {
        system("cls");
        printf("L'aeroporto %s non esiste\n*************\n", nomearrivovolo);
        return;
    }
    if(voloEsistente(getVertice(*g, nomepartenzavolo)->archi, nomearrivovolo)) {
        system("cls");
        printf("Il volo da %s a %s esiste gia'\n*************\n", nomepartenzavolo, nomearrivovolo);
        return;
    }

    system("cls");
    printf("Qual'e' il prezzo del nuovo volo con partenza da %s e diretto a %s? ", nomepartenzavolo, nomearrivovolo);
    scanf("%f", &prezzo);
    fflush(stdin);

    system("cls");
    printf("Qual'e' la durata del nuovo volo con partenza da %s e diretto a %s? ", nomepartenzavolo, nomearrivovolo);
    scanf("%d", &durata);
    fflush(stdin);

    system("cls");
    if(prezzo > 0.0f && durata > 0) {
        *g = aggiungiVolo(*g, nomepartenzavolo, nomearrivovolo, prezzo, durata);
        printf("Il nuovo volo proveniente da %s e diretto a %s e' stato aggiunto con successo!\n*************\n", nomepartenzavolo, nomearrivovolo);
    }
    else
        printf("Dati di prezzo/durata non validi, inserire valori positivi\n*************\n");

}

void rimozioneAeroporto(t_grf ** g) {

    printf("Qual'e' il nome dell'aeroporto che vuoi rimuovere dalle destinazioni? ");
    scanf("%s", nomeaeroporto);
    fflush(stdin);

    system("cls");
    if(aeroportoEsistente(*g, nomeaeroporto)) {
        *g = eliminaAeroporto(*g, nomeaeroporto);
        *g = eliminaTuttiVoliAdAeroporto(*g, nomeaeroporto);
        printf("Ho eliminato %s dalle destinazioni!\n*************\n", nomeaeroporto);
    } else
        printf("L'aeroporto %s non esiste\n*************\n", nomeaeroporto);

}

void rimozioneVolo(t_grf ** g) {

    printf("Qual'e' la partenza del volo che vuoi eliminare? ");
    scanf("%s", nomepartenzavolo);
    fflush(stdin);
    if(!aeroportoEsistente(*g, nomepartenzavolo)) {
        system("cls");
        printf("L'aeroporto %s non esiste\n*************\n", nomearrivovolo);
        return;
    }

    system("cls");
    printf("Qual'e' la destinazione del volo con partenza da %s che vuoi eliminare? ", nomepartenzavolo);
    scanf("%s", nomearrivovolo);
    fflush(stdin);
        if(!aeroportoEsistente(*g, nomearrivovolo)) {
        system("cls");
        printf("L'aeroporto %s non esiste\n*************\n", nomearrivovolo);
        return;
    }

    if(!voloEsistente(getVertice(*g, nomepartenzavolo)->archi, nomearrivovolo)) {
        system("cls");
        printf("Il volo da %s a %s non esiste\n*************\n", nomepartenzavolo, nomearrivovolo);
        return;
    }

    *g = eliminaVolo(*g, nomepartenzavolo, nomearrivovolo);

}
