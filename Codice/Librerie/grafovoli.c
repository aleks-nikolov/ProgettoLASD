#include "grafovoli.h"

//Inizializza gli aeroporti con alcune tratte predefinite (per ora sono 10 per semplicità di testing, poi li incremento)
t_grf * inizializzaGrafo(t_grf * g) {
    g = aggiungiAeroporto(g, "NAPOLI");
    g = aggiungiAeroporto(g, "ROMA");
    g = aggiungiAeroporto(g, "MILANO");
    g = aggiungiAeroporto(g, "LONDRA");
    g = aggiungiAeroporto(g, "PARIGI");
    g = aggiungiAeroporto(g, "SCHIPOL");
    g = aggiungiAeroporto(g, "FRANCOFORTE");
    g = aggiungiAeroporto(g, "MOSCA");
    g = aggiungiAeroporto(g, "MADRID");
    g = aggiungiAeroporto(g, "BARCELLONA");

    g = aggiungiVolo(g, "NAPOLI", "ROMA", 50.00f, 45);
    g = aggiungiVolo(g, "ROMA", "MILANO", 65.00f, 50);
    g = aggiungiVolo(g, "ROMA", "FRANCOFORTE", 100.00f, 160);
    g = aggiungiVolo(g, "MILANO", "NAPOLI", 95.00f, 100);
    g = aggiungiVolo(g, "MILANO", "LONDRA", 110.00f, 140);
    g = aggiungiVolo(g, "MILANO", "SCHIPOL", 55.00f, 115);
    g = aggiungiVolo(g, "MILANO", "FRANCOFORTE", 90.00f, 90);
	g = aggiungiVolo(g, "MILANO", "MADRID", 65.00f, 50);
	g = aggiungiVolo(g, "FRANCOFORTE", "MOSCA", 80.00f, 80);
    g = aggiungiVolo(g, "MADRID", "BARCELLONA", 40.00f, 30);
	g = aggiungiVolo(g, "BARCELLONA", "MILANO", 75.00f, 45);
    g = aggiungiVolo(g, "MOSCA", "SCHIPOL", 120.00f, 140);
	g = aggiungiVolo(g, "LONDRA", "PARIGI", 60.00f, 35);
	g = aggiungiVolo(g, "PARIGI", "MADRID", 55.00f, 40);

    return g;
}

//Aggiunge un nuovo aeroporto in coda alla lista dei vertici
t_grf * aggiungiAeroporto(t_grf * g, char *nome) {
    if(grafoVuoto(g)){
        g = (t_grf *)malloc(sizeof(t_grf));
        strcpy(g->nome, strupr(nome));
        g->archi = NULL;
        g->next = NULL;
    } else{
        g->next = aggiungiAeroporto(g->next, nome);
    }

    return g;
}

//Aggiunge un nuovo aeroporto in testa alla lista dei vertici (usato solo negli algoritmi di Dijkstra)
t_grf * aggiungiAeroportoInTesta(t_grf * g, char *nome) {
    t_grf * temp = (t_grf *)malloc(sizeof(t_grf));
    strcpy(temp->nome, strupr(nome));
    g->archi = NULL;
    if(!grafoVuoto(g)) {
        temp->next = g;
        return temp;
    } else {
        temp->next = NULL;
        return temp;
    }
}

//Elimina l'aeroporto di nome 'nome' dal grafo 'g'
t_grf * eliminaAeroporto(t_grf * g, char *nome) {
    if(!grafoVuoto(g)){
        g->next = eliminaAeroporto(g->next, nome);
        if(strcmp(g->nome, strupr(nome)) == 0) {
            t_grf * temp = g->next;
            printf("\nHo eliminato %s dalle destinazioni!", g->nome);
            free(g);
            return temp;
        }
    }

    return g;
}

//Aggiunge un nuovo volo da 'uscita' a 'entrata' con il relativo prezzo e durata, effettuando vari controlli
t_grf * aggiungiVolo(t_grf * g, char *uscita, char *entrata, float prezzo, int durata) {
    t_grf * temp;

    uscita = strupr(uscita);
    entrata = strupr(entrata);

    if(grafoVuoto(g))
        printf("\nERRORE: Il grafo non risulta inizializzato");
    else if (strcmp(uscita, entrata) == 0)
        printf("\nATTENZIONE: Impossibile aggiungere un volo da un aeroporto a se stesso");
    else if (!aeroportoEsistente(g, uscita) || !aeroportoEsistente(g, entrata))
        printf("\nATTENZIONE: Almeno uno degli aeroporti inseriti non risulta presente");
    else if (voloEsistente(getVertice(g, uscita)->archi, entrata)) {
        printf("\nATTENZIONE: Il volo che si tenta di inserire esiste gia'");
    } else {
        temp = getVertice(g, uscita);
        temp->archi = inizializzaArco(temp->archi, entrata, prezzo, durata);
    }

    return g;
}

//Elimina il volo da 'uscita' a 'entrata', effettuando vari controlli
t_grf * eliminaVolo(t_grf * g, char *uscita, char *entrata) {
    t_grf * temp;

    uscita = strupr(uscita);
    entrata = strupr(entrata);

    if(grafoVuoto(g))
        printf("\nERRORE: Il grafo non risulta inizializzato");
    else if (!aeroportoEsistente(g, uscita) || !aeroportoEsistente(g, entrata))
        printf("\nATTENZIONE: Almeno uno degli aeroporti inseriti non risulta presente");
    else if (!voloEsistente(getVertice(g, uscita)->archi, entrata)) {
        printf("\nATTENZIONE: Il volo che si tenta di eliminare non esiste");
    } else {
        temp = getVertice(g, uscita);
        temp->archi = eliminaArco(temp->archi, entrata);
        printf("\nIl volo proveniente da %s e diretto a %s e' stato eliminato con successo!\n", temp->nome, entrata);
    }

    return g;
}

//Inizializza un nuovo arco e lo restituisce (usata dalla funzione aggiungiVolo)
t_arc * inizializzaArco(t_arc * a, char *nome, float prezzo, int durata) {
    if(arcoVuoto(a)) {
        a = (t_arc *) malloc(sizeof(t_arc));
        strcpy(a->nome, strupr(nome));
        a->prezzo = prezzo;
        a->durata = durata;
        a->next = NULL;
        return a;
    } else {
        a->next = inizializzaArco(a->next, nome, prezzo, durata);
    }

    return a;
}

//Dealloca un arco, usata dalla funzione eliminaVolo
t_arc * eliminaArco(t_arc * a, char *nome) {
    if(!arcoVuoto(a)){
        a->next = eliminaArco(a->next, nome);
        if(strcmp(a->nome, nome) == 0) {
            t_arc * temp = a->next;
            free(a);
            return temp;
        }
    }

    return a;
}

//Elimina tutti i voli verso un aeroporto, usata nel caso di eliminazione di un aeroporto dal grafo
t_grf * eliminaTuttiVoliAdAeroporto(t_grf * g, char *nome) {
    nome = strupr(nome);
    if(!grafoVuoto(g)) {
        g->archi = eliminaArco(g->archi, nome);
        g->next = eliminaTuttiVoliAdAeroporto(g->next, nome);
    }

    return g;
}

//Restituisce il puntatore al vertice con nome 'nome'
t_grf * getVertice(t_grf * g, char *nome) {
    if(strcmp(g->nome, nome) == 0)
        return g;
    else
        return getVertice(g->next, nome);
}

//Controlla se esiste il volo dal campo 'archi' di un vertice a 'entrata'
int voloEsistente(t_arc * a, char *entrata) {
    if(!arcoVuoto(a)) {
        if(strcmp(a->nome, strupr(entrata)) == 0)
            return 1;
        else
            return voloEsistente(a->next, entrata);
    }

    return 0;
}

//Controlla l'esistenza di un aeroporto nel grafo
int aeroportoEsistente(t_grf * g, char *nome) {
    if(!grafoVuoto(g)) {
        if(strcmp(g->nome, strupr(nome)) == 0)
            return 1;
        else
            return aeroportoEsistente(g->next, nome);
    }
    return 0;
}

//Restituisce la dimensione del grafo
int lunghezzaGrafo(t_grf * g) {
    if(grafoVuoto(g))
        return 0;
    else
        return 1 + lunghezzaGrafo(g->next);
}

void stampaGrafo(t_grf * G) {
    if(!grafoVuoto(G)){
        printf("\n%s ", G->nome);
        stampaArchi(G->archi);
        stampaGrafo(G->next);
    }
}

void stampaArchi(t_arc * a) {
    if(!arcoVuoto(a)) {
        printf("--(%.2f euro)(%d min)--> %s ", a->prezzo, a->durata, a->nome);
        stampaArchi(a->next);
    }
}

int grafoVuoto(t_grf * g) {
    return (g == NULL);
}

int arcoVuoto(t_arc * a) {
    return (a == NULL);
}