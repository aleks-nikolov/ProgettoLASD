#include "grafovoli.h"

//Restituisce l'arco che punta alla destinazione più economica ricevendo le destinazioni adiacenti dalla partenza
t_arc * trovaPiuEconomico(t_arc * a) {
    if(!arcoVuoto(a->next)) {
        if(a->prezzo < (trovaPiuEconomico(a->next))->prezzo)
            return a;
        else
            return trovaPiuEconomico(a->next);
    }
    return a;
}

t_grf * trovaPiuGettonato(t_grf * g) {
    if(!grafoVuoto(g->next)) {
        if(g->popolarita > (trovaPiuGettonato(g->next))->popolarita)
            return g;
        else
            return trovaPiuGettonato(g->next);
    }
    return g;
}

//Trova il volo più economico (pesoDiRiferimento == 1) o breve (pesoDiRiferimento == 2) dall'aeroporto 'da' a 'a'
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

t_grf * impostaPopolarita(t_grf * g, char *nome, int popolaritaNuova) {
    if(!grafoVuoto(g)) {
        if(strcmp(g->nome, nome) == 0)
            g->popolarita = popolaritaNuova;
        else
            g->next = impostaPopolarita(g->next, nome, popolaritaNuova);
    }

    return g;
}

//Incrementa la popolarità dell'aeroporto 'nome' di 1
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

t_grf * costruisciPercorso(t_grf ** g, char * entrata) {
    t_grf * percorso = NULL;
    t_grf * temp = getVertice(*g, entrata);

    do {
        percorso = aggiungiPercorsoInTesta(percorso, temp);
        temp = temp->prev;
    } while(temp != NULL);

    return percorso;
}

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
