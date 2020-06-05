#include "gstadmin.h"

int scelta;
int pesoDiRiferimento;
char nomeaeroporto[LUNGHEZZA_NOME_AEROPORTO];
char nomepartenzavolo[LUNGHEZZA_NOME_AEROPORTO];
char nomearrivovolo[LUNGHEZZA_NOME_AEROPORTO];
float prezzo;
int durata;

void gestisciOpzioneAdmin(t_grf ** g){

    do{
        stampaMenuAdmin();
        scanf("%d", &scelta);

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
            case (7):
                printf("\nVolo piu' economico");
                printf("\nInserire aeroporto di partenza ");
                scanf("%s", nomepartenzavolo);
                fflush(stdin);
                if (!aeroportoEsistente(*g, nomepartenzavolo)) {
                    printf("\nL'aeroporto inserito non esiste");
                    break;
                }

                //Cerca volo più economico
                t_arc * destArc = trovaPiuEconomico(getVertice(*g, nomepartenzavolo)->archi);
                printf("\nLa destinazione piu' economica da %s e' %s", nomepartenzavolo, destArc->nome);

                break;

            case (8):
                printf("\nTest Dijsktra");
                printf("\nInserire aeroporto di partenza ");
                scanf("%s", nomepartenzavolo);
                fflush(stdin);
                if (!aeroportoEsistente(*g, nomepartenzavolo)) {
                    printf("\nL'aeroporto inserito non esiste");
                    break;
                }
                printf("\nInserire destinazione ");
                scanf("%s", nomearrivovolo);
                fflush(stdin);
                if (!aeroportoEsistente(*g, nomearrivovolo)) {
                    printf("\nL'aeroporto inserito non esiste");
                    break;
                }

                //bfs effettua una breadth first search e controlla che l'aeroporto di destinazione è raggiungibile da quello di partenza
                t_grf* raggiungibili = bfs(*g, nomepartenzavolo);
                if (!aeroportoEsistente(raggiungibili, nomearrivovolo)) {
                    printf("\n%s non e' raggiungibile da %s", nomearrivovolo, nomepartenzavolo);
                    break;
                }

                //scelta tra tratta più economica e più breve
                printf("\nTratta preferita"
                       "\n1) Piu' economica"
                       "\n2) Piu' breve\n");
                scanf("%d", &pesoDiRiferimento);
                fflush(stdin);
                if (pesoDiRiferimento < 1 || pesoDiRiferimento > 2) {
                    printf("\nInput invalido");
                    break;
                }

                dijkstra(g, nomepartenzavolo, nomearrivovolo, pesoDiRiferimento);

                //costruisce e stampa il percorso
                t_grf * percorso = costruisciPercorso(g, nomearrivovolo);
                printf("\n");
                stampaPercorso(*g, percorso, pesoDiRiferimento);
                free(percorso);
                break;

            default:
                printf("\nScelta inserita non valida\n");
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
           "\n\t6 - Logout\n"
           "\nRoba per testare, non fara' parte del progetto finale"
           "\n\t7 - Volo piu' economico data una partenza"
           "\n\t8 - Test Dijkstra\n");
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
        printf("\nHo eliminato %s dalle destinazioni!", nomeaeroporto);
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