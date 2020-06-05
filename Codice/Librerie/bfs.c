#include "grafovoli.h"

t_grf * bfs(t_grf * g, char *origine) {
    t_grf * visitati = NULL;
    t_grf * daVisitare = NULL;

    daVisitare = aggiungiAeroporto(daVisitare, origine);

    while (!grafoVuoto(daVisitare)) {
        t_grf * corrente = getVertice(g, daVisitare->nome);
        t_arc * a = corrente->archi;

        visitati = aggiungiAeroporto(visitati, corrente->nome);
        daVisitare = eliminaAeroporto(daVisitare, corrente->nome);

        while (a != NULL) {
            if(!aeroportoEsistente(daVisitare, a->nome) && !aeroportoEsistente(visitati, a->nome))
                daVisitare = aggiungiAeroporto(daVisitare, a->nome);
            a = a->next;
        }

    }

    return visitati;
}