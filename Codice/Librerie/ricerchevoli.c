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

//Trova il volo più economico (pesoDiRiferimento == 1) o breve (pesoDiRiferimento == 2) dall'aeroporto 'da' a 'a'
void dijkstra(t_grf ** g, char *da, char *a, int pesoDiRiferimento) {
    t_grf * sorgente = getVertice(*g, da);
    t_grf * destinazione = getVertice(*g, a);
    t_grf * q = NULL;  //Vertici non visitati
    t_grf * u;  //Tiene traccia del vertice corrente

    q = copiaGrafo(*g, q);
    *g = impostaPotenzialeATutti(*g, INT_MAX);
    *g = impostaPotenziale(*g, sorgente->nome, 0);
    *g = impostaPrecedenteATutti(*g, NULL);

    q = impostaPotenzialeATutti(q, INT_MAX);
    q = impostaPotenziale(q, sorgente->nome, 0);
    q = impostaPrecedenteATutti(q, NULL);

    while(!grafoVuoto(q)) {

        u = minimoPotenziale(q);
        if (u->potenziale == INT_MAX)
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
                    potenzialeNuovo = u->potenziale + (int) arc->prezzo;
                else if (pesoDiRiferimento == 2)
                    potenzialeNuovo = u->potenziale + arc->durata;

                if (potenzialeNuovo < temp->potenziale) {
                    temp->potenziale = potenzialeNuovo;
                    temp->prev = getVertice(*g, u->nome);
                    q = impostaPotenziale(q, temp->nome, potenzialeNuovo);
                }
            }
            arc = arc->next;
        }
        q = eliminaAeroporto(q, u->nome);
    }

    free(q);
}

/*t_grf * dijkstra(t_grf * g, char *da, char *a, int pesoDiRiferimento) {
    t_grf * sorgente = getVertice(g, da);
    t_grf * destinazione = getVertice(g, a);
    t_grf * q = NULL;  //Vertici non visitati
    t_grf * u;  //Tiene traccia del vertice corrente

    q = copiaGrafo(g, q);
    g = impostaPotenzialeATutti(g, INT_MAX);
    g = impostaPotenziale(g, sorgente->nome, 0);
    g = impostaPrecedenteATutti(g, NULL);

    q = impostaPotenzialeATutti(q, INT_MAX);
    q = impostaPotenziale(q, sorgente->nome, 0);
    q = impostaPrecedenteATutti(q, NULL);

    while(!grafoVuoto(q)) {

        u = minimoPotenziale(q);
        if (u->potenziale == INT_MAX)
            break;

        if (strcmp(u->nome, destinazione->nome) == 0)
            break;

        t_arc * arc = u->archi;
        while (arc != NULL) {
            //Se il seguente vertice adiacente ad u non è stato ancora visitato
            if (aeroportoEsistente(q, arc->nome)) {
                t_grf * temp = getVertice(g, arc->nome);
                int potenzialeNuovo = 0;
                if (pesoDiRiferimento == 1)
                    potenzialeNuovo = u->potenziale + (int) arc->prezzo;
                else if (pesoDiRiferimento == 2)
                    potenzialeNuovo = u->potenziale + arc->durata;

                if (potenzialeNuovo < temp->potenziale) {
                    temp->potenziale = potenzialeNuovo;
                    temp->prev = getVertice(g, u->nome);
                    q = impostaPotenziale(q, temp->nome, potenzialeNuovo);
                }
            }
            arc = arc->next;
        }
        q = eliminaAeroporto(q, u->nome);
    }

    free(q);
    return g;
}*/

//Copia il grafo originale in uno nuovo ausiliario 'q'
t_grf * copiaGrafo(t_grf * g, t_grf * q) {
    if(!grafoVuoto(g)) {
        q = (t_grf *)malloc(sizeof(t_grf));
        strcpy(q->nome, g->nome);
        q->potenziale = INT_MAX;
        q->archi = g->archi;
        q->prev = NULL;
        q->next = copiaGrafo(g->next, q->next);
    } else {
        q = NULL;
    }

    return q;
}

//Imposta il potenziale del vertice 'nome' nel grafo 'q'
t_grf * impostaPotenziale(t_grf * q, char *nome, int potenziale) {
    if(!grafoVuoto(q)) {
        if(strcmp(q->nome, nome) == 0)
            q->potenziale = potenziale;
        else
            q->next = impostaPotenziale(q->next, nome, potenziale);
    }

    return q;
}

t_grf * impostaPotenzialeATutti(t_grf * g, int potenziale) {
    if (!grafoVuoto(g)) {
        g->potenziale = potenziale;
        g->next = impostaPotenzialeATutti(g->next, potenziale);
    }

    return g;
}

//Imposta il precedente del vertice 'nome' nel grafo 'q'
t_grf * impostaPrecedente(t_grf * q, char *nome, t_grf * precedente) {
    if(!grafoVuoto(q)) {
        if(strcmp(q->nome, nome) == 0)
            q->prev = precedente;
        else
            q->next = impostaPrecedente(q->next, nome, precedente);
    }

    return q;
}

t_grf * impostaPrecedenteATutti(t_grf * g, t_grf * precedente) {
    if (!grafoVuoto(g)) {
        g->prev = precedente;
        g->next = impostaPrecedenteATutti(g->next, precedente);
    }

    return g;
}

//Restituisce un puntatore al vertice con il minor potenziale
t_grf * minimoPotenziale(t_grf * q) {
    if(!grafoVuoto(q->next)) {
        if(q->potenziale < (minimoPotenziale(q->next))->potenziale)
            return q;
        else
            return minimoPotenziale(q->next);
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
        if(!grafoVuoto(percorso->next))
            printf("%s --(%d)--> ", percorso->nome, getPesoArco(getVertice(g, percorso->nome), getVertice(g, percorso->next->nome), pesoDiRiferimento));
        else
            printf("%s", percorso->nome);
        stampaPercorso(g, percorso->next, pesoDiRiferimento);
    }
}