#include "grafovoli.h"

//Inizializza gli aeroporti con alcune tratte predefinite (per ora sono 10 per semplicità di testing, poi li incremento)
t_grf * inizializzaGrafo(t_grf * g) {
    //Inizializzazione aeroporti
    g = aggiungiAeroporto(g, "PALERMO");
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
    g = aggiungiAeroporto(g, "MALTA");
    g = aggiungiAeroporto(g, "ATENE");
    g = aggiungiAeroporto(g, "SOFIA");
    g = aggiungiAeroporto(g, "GINEVRA");
    g = aggiungiAeroporto(g, "COPENHAGEN");
    g = aggiungiAeroporto(g, "BRUXELLES");
    g = aggiungiAeroporto(g, "DUBLINO");
    g = aggiungiAeroporto(g, "STOCCOLMA");
    g = aggiungiAeroporto(g, "BUDAPEST");

    //Inizializzazione voli
    g = aggiungiVolo(g, "ATENE", "ROMA", 90.00f, 75);
    g = aggiungiVolo(g, "BARCELLONA", "ROMA", 30.00f, 45);
    g = aggiungiVolo(g, "BARCELLONA", "NAPOLI", 90.00f, 80);
    g = aggiungiVolo(g, "BRUXELLES", "PARIGI", 25.00f, 20);
    g = aggiungiVolo(g, "BUDAPEST", "MILANO", 20.00f, 25);
    g = aggiungiVolo(g, "COPENHAGEN", "LONDRA", 80.00f, 65);
    g = aggiungiVolo(g, "COPENHAGEN", "STOCCOLMA", 25.00f, 20);
	g = aggiungiVolo(g, "DUBLINO", "BRUXELLES", 30.00f, 25);
    g = aggiungiVolo(g, "GINEVRA", "PARIGI", 60.00f, 30);
    g = aggiungiVolo(g, "FRANCOFORTE", "MOSCA", 60.00f, 90);
    g = aggiungiVolo(g, "FRANCOFORTE", "BUDAPEST", 35.00f, 40);
    g = aggiungiVolo(g, "FRANCOFORTE", "SOFIA", 120.00f, 150);
    g = aggiungiVolo(g, "LONDRA", "DUBLINO", 20.00f, 25);
    g = aggiungiVolo(g, "LONDRA", "BRUXELLES", 60.00f, 40);
    g = aggiungiVolo(g, "MADRID", "BARCELLONA", 40.00f, 30);
    g = aggiungiVolo(g, "MALTA", "ATENE", 90.00f, 120);
    g = aggiungiVolo(g, "MILANO", "NAPOLI", 95.00f, 100);
    g = aggiungiVolo(g, "MILANO", "SCHIPOL", 35.00f, 100);
    g = aggiungiVolo(g, "MILANO", "MADRID", 65.00f, 50);
    g = aggiungiVolo(g, "MILANO", "GINEVRA", 40.00f, 20);
    g = aggiungiVolo(g, "MILANO", "SOFIA", 100.00f, 90);
    g = aggiungiVolo(g, "MOSCA", "STOCCOLMA", 60.00f, 65);
    g = aggiungiVolo(g, "NAPOLI", "ROMA", 50.00f, 45);
    g = aggiungiVolo(g, "NAPOLI", "PALERMO", 40.00f, 40);
    g = aggiungiVolo(g, "NAPOLI", "MALTA", 80.00f, 65);
    g = aggiungiVolo(g, "PALERMO", "MALTA", 30.00f, 35);
    g = aggiungiVolo(g, "PARIGI", "MADRID", 45.00f, 50);
    g = aggiungiVolo(g, "PARIGI", "COPENHAGEN", 45.00f, 50);
    g = aggiungiVolo(g, "ROMA", "MILANO", 65.00f, 50);
    g = aggiungiVolo(g, "SOFIA", "ATENE", 30.00f, 30);
    g = aggiungiVolo(g, "SOFIA", "MOSCA", 100.00f, 125);
    g = aggiungiVolo(g, "SCHIPOL", "PARIGI", 30.00f, 30);
    g = aggiungiVolo(g, "SCHIPOL", "COPENHAGEN", 40.00f, 30);
    g = aggiungiVolo(g, "SCHIPOL", "FRANCOFORTE", 30.00f, 45);
    g = aggiungiVolo(g, "STOCCOLMA", "LONDRA", 50.00f, 50);
    
    return g;
}

//Aggiunge un nuovo aeroporto in coda alla lista dei vertici
t_grf * aggiungiAeroporto(t_grf * g, char *nome) {
    if(grafoVuoto(g)){
        g = (t_grf *)malloc(sizeof(t_grf));
        strcpy(g->nome, strupr(nome));
        g->archi = NULL;
        g->popolarita = 0;
        g->next = NULL;
    } else{
        g->next = aggiungiAeroporto(g->next, nome);
    }

    return g;
}

//Elimina l'aeroporto di nome 'nome' dal grafo 'g'
t_grf * eliminaAeroporto(t_grf * g, char *nome) {
    if(!grafoVuoto(g)){
        g->next = eliminaAeroporto(g->next, nome);
        if(strcmp(g->nome, strupr(nome)) == 0) {
            t_grf * temp = g->next;
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

//Controlla se ci sono voli d'uscita da un aeroporto
int haVoli(t_grf * partenza) {
    if (arcoVuoto(partenza->archi))
        return 0;
    else
        return 1;
}

//Inizializza un nuovo arco e lo restituisce
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

//Dealloca un arco
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

//Restituisce il puntatore al vertice con nome 'nome' nel grafo 'g'
t_grf * getVertice(t_grf * g, char *nome) {
    if(strcmp(g->nome, nome) == 0)
        return g;
    else
        return getVertice(g->next, nome);
}

//Restituisce l'i-esimo vertice in una lista da 1 a lunghezzaGrafo
t_grf * getVerticeByPosizione(t_grf * g, int pos) {
    if (pos == 1)
        return g;
    else {
        pos--;
        return getVerticeByPosizione(g->next, pos);
    }
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

//Stampa i vertici del grafo con un indice iniziale
void elencaGrafo(t_grf * g, int contatore) {
    if(!grafoVuoto(g)){
        printf("\n%d) %s ", contatore, g->nome);
        contatore++;
        elencaGrafo(g->next, contatore);
    }
}

//Stampa il grafo come lista di adiacenze
void stampaGrafo(t_grf * g) {
    if(!grafoVuoto(g)){
        printf("\n%s ", g->nome);
        stampaArchi(g->archi);
        stampaGrafo(g->next);
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

//Restituisce il prezzo o durata di un arco 
int getPesoArco(t_grf * g, t_grf * h, int pesoDiRiferimento) {
    if (!grafoVuoto(g) && !grafoVuoto(h)) {
        t_arc * temp = g->archi;
        while (strcmp(temp->nome, h->nome) != 0)
            temp = temp->next;
        return (pesoDiRiferimento == 1) ? (int) temp->prezzo : temp->durata;
    } else {
        return 0;
    }
}