#include "grafovoli.h"

//Trova il volo più economico (pesoDiRiferimento == 0) o breve (pesoDiRiferimento == 1) dall'aeroporto 'nome'
t_grf * dijkstra(t_grf * g, char nome[], int pesoDiRiferimento) {
    t_grf * q = NULL;
    t_grf * s = NULL;
    t_grf * sorgente = getVertice(g, nome);
    q = copiaGrafo(g, q);
    q = impostaPotenziale(q, sorgente->nome, 0);

    while(!grafoVuoto(q)) {
        t_grf * u = minimoPotenziale(q);
        if(u->potenziale == INT_MAX)
            break;
        t_arc * a = u->archi;
        if(strcmp(u->nome, sorgente->nome) != 0) {
            s = aggiungiAeroporto(s, u->nome);
            s = impostaPotenziale(s, u->nome, u->potenziale);
        }
        while(a != NULL) {
            if(aeroportoEsistente(q, a->nome)) {
                t_grf * temp = getVertice(q, a->nome);
                int potenzialeNuovo;
                if(pesoDiRiferimento == 0)
                    potenzialeNuovo = u->potenziale + (int)a->prezzo;
                else
                    potenzialeNuovo = u->potenziale + a->durata;

                if (potenzialeNuovo < temp->potenziale) {
                    temp->potenziale = potenzialeNuovo;
                    temp->prev = u;
                }
            }
            a = a->next;
        }

        q = eliminaAeroporto(q, u->nome);
    }

    free(q);
    if(grafoVuoto(s))
        return NULL;
    return minimoPotenziale(s);
}

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