#include "grafovoli.h"

//Restituisce l'arco che punta alla destinazione più economica ricevendo le destinazioni adiacenti dalla partenza
t_grf * trovaPiuEconomico(t_grf * voli, char * partenza) {

    t_grf *origine = getVertice(voli, partenza);
    //trovaPiuEconomico restituisce un puntatore ad arco verso la destinazione adiacente alla partenza più economica
    t_grf *destinazione = getVertice(voli, getPrezzoMinimo(origine->archi)->nome);
    t_grf *percorso = NULL;
    percorso = aggiungiPercorsoInTesta(percorso, destinazione);
    percorso = aggiungiPercorsoInTesta(percorso, origine);

    return percorso;

}

//Restituisce il vertice del grafo raggiungibile dalla partenza e con l'intero popolarita più alto
t_grf * trovaPiuGettonato(t_grf * voli, char * partenza) {
    int condizioneUscita;
    t_grf * raggiungibili = bfs(voli, strupr(partenza));
    t_grf * destinazione = NULL;

    raggiungibili = eliminaAeroporto(raggiungibili, partenza);

    //Se per mancanza di dati non si riesce a stabilire la meta più gettonata
    if(nessunaGettonata(voli))
        return NULL;

    //Garantisce che la destinazione sia raggiungibile nel caso in cui sono avvenute modifiche successive dei tratti
    do {
        destinazione = getMassimaPopolarita(voli);

        if (aeroportoEsistente(raggiungibili, destinazione->nome))
            condizioneUscita = 0;
        else {
            voli = impostaPopolarita(voli, destinazione->nome, 0);
            condizioneUscita = 1;
        }

    } while (condizioneUscita == 1);

    return destinazione;
}

//Trova il volo più economico (pesoDiRiferimento == 1) o breve (pesoDiRiferimento == 2) dall'aeroporto 'da' a 'a'
//Usa un grafo di supporto q che contiene i vertici visitati
void dijkstra(t_grf ** g, char *da, char *a, int pesoDiRiferimento) {
    t_grf * sorgente = getVertice(*g, da);
    t_grf * destinazione = getVertice(*g, a);
    t_grf * q = NULL;  //Vertici non visitati
    t_grf * u;  //Tiene traccia del vertice corrente

    q = copiaGrafo(*g, q);
    *g = impostaCamminoMinimoATutti(*g, INT_MAX);
    *g = impostaCamminoMinimo(*g, sorgente->nome, 0);
    *g = impostaPrecedenteATutti(*g, NULL);

    q = impostaCamminoMinimoATutti(q, INT_MAX);
    q = impostaCamminoMinimo(q, sorgente->nome, 0);
    q = impostaPrecedenteATutti(q, NULL);

    while(!grafoVuoto(q)) {

        u = getVerticeByCamminoMinimo(q);
        if (u->camminoMinimo == INT_MAX)
            break;

        if (strcmp(u->nome, destinazione->nome) == 0)
            break;

        t_arc * arc = u->archi;
        while (arc != NULL) {
            //Se il seguente vertice adiacente ad u non è stato ancora visitato
            if (aeroportoEsistente(q, arc->nome)) {
                t_grf * temp = getVertice(*g, arc->nome);
                int potenzialeNuovo = 0;
                if (pesoDiRiferimento == 1)
                    potenzialeNuovo = u->camminoMinimo + (int) arc->prezzo;
                else if (pesoDiRiferimento == 2)
                    potenzialeNuovo = u->camminoMinimo + arc->durata;

                if (potenzialeNuovo < temp->camminoMinimo) {
                    temp->camminoMinimo = potenzialeNuovo;
                    temp->prev = getVertice(*g, u->nome);
                    q = impostaCamminoMinimo(q, temp->nome, potenzialeNuovo);
                }
            }
            arc = arc->next;
        }
        q = eliminaAeroporto(q, u->nome);
    }

    free(q);
}

//Copia il grafo originale in uno nuovo ausiliario 'q'
t_grf * copiaGrafo(t_grf * g, t_grf * q) {
    if(!grafoVuoto(g)) {
        q = (t_grf *)malloc(sizeof(t_grf));
        strcpy(q->nome, g->nome);
        q->camminoMinimo = INT_MAX;
        q->archi = g->archi;
        q->prev = NULL;
        q->next = copiaGrafo(g->next, q->next);
    } else {
        q = NULL;
    }

    return q;
}

//Modifica il camminoMinimo del vertice 'nome' nel grafo 'q'
t_grf * impostaCamminoMinimo(t_grf * q, char *nome, int camminoMinimoNuovo) {
    if(!grafoVuoto(q)) {
        if(strcmp(q->nome, nome) == 0)
            q->camminoMinimo = camminoMinimoNuovo;
        else
            q->next = impostaCamminoMinimo(q->next, nome, camminoMinimoNuovo);
    }

    return q;
}

//Modifica il camminoMinimo di tutti i vertici di 'g'
t_grf * impostaCamminoMinimoATutti(t_grf * g, int camminoMinimoNuovo) {
    if (!grafoVuoto(g)) {
        g->camminoMinimo = camminoMinimoNuovo;
        g->next = impostaCamminoMinimoATutti(g->next, camminoMinimoNuovo);
    }

    return g;
}

//Modifica il precedente del vertice 'nome' nel grafo 'q'
t_grf * impostaPrecedente(t_grf * q, char *nome, t_grf * precedente) {
    if(!grafoVuoto(q)) {
        if(strcmp(q->nome, nome) == 0)
            q->prev = precedente;
        else
            q->next = impostaPrecedente(q->next, nome, precedente);
    }

    return q;
}

//Modifica il precedente di tutti i vertici di 'g'
t_grf * impostaPrecedenteATutti(t_grf * g, t_grf * precedente) {
    if (!grafoVuoto(g)) {
        g->prev = precedente;
        g->next = impostaPrecedenteATutti(g->next, precedente);
    }

    return g;
}

//Modifica il valore di popolarita del vertice di nome 'nome' nel grafo g
t_grf * impostaPopolarita(t_grf * g, char *nome, int popolaritaNuova) {
    if(!grafoVuoto(g)) {
        if(strcmp(g->nome, nome) == 0)
            g->popolarita = popolaritaNuova;
        else
            g->next = impostaPopolarita(g->next, nome, popolaritaNuova);
    }

    return g;
}

//Incrementa il valore di popolarità dell'aeroporto 'nome' di 1
t_grf * incrementaPopolarita(t_grf * g, char * nome) {
    if(!grafoVuoto(g)) {
        if(strcmp(g->nome, nome) == 0) {
            g->popolarita++;
            return g;
        }
        else
            g->next = incrementaPopolarita(g->next, nome);
    }

    return g;
}

//Imposta la popolarità di tutti gli aeroporti a 0
t_grf * azzeraPopolarita(t_grf * g) {
    if(!grafoVuoto(g)) {
        g->popolarita = 0;
        g->next = azzeraPopolarita(g->next);
    }

    return g;
}

//Restituisce il vertice la cui popolarita è maggiore
t_grf * getMassimaPopolarita(t_grf * g) {
    if(!grafoVuoto(g->next)) {
        if(g->popolarita > (getMassimaPopolarita(g->next))->popolarita)
            return g;
        else
            return getMassimaPopolarita(g->next);
    }
    return g;
}

t_arc * getPrezzoMinimo(t_arc * a) {
    if(!arcoVuoto(a->next)) {
        if(a->prezzo < (getPrezzoMinimo(a->next))->prezzo)
            return a;
        else
            return getPrezzoMinimo(a->next);
    }
    return a;
}

//Ritorna 1 se tutti i valori di popolarita degli aeroporti sono 0
int nessunaGettonata(t_grf * g) {
    if(!grafoVuoto(g)) {
        if(g->popolarita == 0)
            return nessunaGettonata(g->next);
        else
            return 0;
    }

    return 1;
}

//Restituisce un puntatore al vertice con il minor camminoMinimo
t_grf * getVerticeByCamminoMinimo(t_grf * q) {
    if(!grafoVuoto(q->next)) {
        if(q->camminoMinimo < (getVerticeByCamminoMinimo(q->next))->camminoMinimo)
            return q;
        else
            return getVerticeByCamminoMinimo(q->next);
    }
    return q;
}

//Costruisce un percorso partendo dal vertice di destinazione scorrendo il campo prev
t_grf * costruisciPercorso(t_grf ** g, char * entrata) {
    t_grf * percorso = NULL;
    t_grf * temp = getVertice(*g, entrata);

    do {
        percorso = aggiungiPercorsoInTesta(percorso, temp);
        temp = temp->prev;
    } while(temp != NULL);

    return percorso;
}

//Aggiunge un t_grf in testa a un percorso in modo che l'ultimo elemento sia la destinazione
t_grf * aggiungiPercorsoInTesta(t_grf * g, t_grf * daAggiungere) {
    t_grf * temp = (t_grf *) malloc(sizeof(t_grf));
    strcpy(temp->nome, daAggiungere->nome);
    temp->archi = daAggiungere->archi;
    if(!grafoVuoto(g)) {
        temp->next = g;
        return temp;
    } else {
        temp->next = NULL;
        return temp;
    }

}

//Stampa il percorso con il relativo peso
void stampaPercorso(t_grf * g, t_grf * percorso, int pesoDiRiferimento) {
    if(!grafoVuoto(percorso)){
        if(!grafoVuoto(percorso->next)){
        	if(pesoDiRiferimento == 1)
            	printf("%s --(%d euro)--> ", percorso->nome, getPesoArco(getVertice(g, percorso->nome), getVertice(g, percorso->next->nome), pesoDiRiferimento));
            else if(pesoDiRiferimento == 2)
            	printf("%s --(%d minuti)--> ", percorso->nome, getPesoArco(getVertice(g, percorso->nome), getVertice(g, percorso->next->nome), pesoDiRiferimento));
		}else
            printf("%s", percorso->nome);
        stampaPercorso(g, percorso->next, pesoDiRiferimento);
    }
}
