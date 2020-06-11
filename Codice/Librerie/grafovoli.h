#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LUNGHEZZA_NOME_AEROPORTO 100

typedef struct arco{
    char nome[LUNGHEZZA_NOME_AEROPORTO];    //nome dell'aeroporto a cui punta l'arco

    float prezzo;     //peso prezzo dell'arco
    int durata;       //peso durata dell'arco

    struct arco *next;
} t_arc;


typedef struct grafo {
    char nome[LUNGHEZZA_NOME_AEROPORTO];    //nome dell'aeroporto

    struct arco *archi;
    struct grafo *next;

    int popolarita;   //usato nella ricerca della destinazione più gettonata

    int camminoMinimo;    //il peso totale del cammino fino a questo vertice
    struct grafo *prev;   //puntatore al vertice che precede nel cammino minimo
} t_grf;

//NOTA: le implementazioni delle funzioni sono divise nei file grafovoli.c, ricerchevoli.c e bfs.c per fini organizzativi
//Operazioni sui vertici
t_grf * inizializzaGrafo(t_grf * g);
t_grf * aggiungiAeroporto(t_grf * g, char *nome);
t_grf * eliminaAeroporto(t_grf * g, char *nome);

//Operazioni sugli archi
t_arc * inizializzaArco(t_arc * a, char *nome, float prezzo, int durata);
t_grf * aggiungiVolo(t_grf * g, char *uscita, char *entrata, float prezzo, int durata);
t_grf * eliminaVolo(t_grf * g, char *uscita, char *entrata);
t_arc * eliminaArco(t_arc * a, char *nome);
t_grf * eliminaTuttiVoliAdAeroporto(t_grf * g, char *nome);
int haVoli(t_grf * partenza);

//Stampe
void elencaGrafo(t_grf * g, int contatore);
void stampaGrafo(t_grf * g);
void stampaArchi(t_arc * a);

//Utilità
t_grf * getVertice(t_grf * g, char *nome);
t_grf * getVerticeByPosizione(t_grf * g, int pos);
int voloEsistente(t_arc * a, char *entrata);
int aeroportoEsistente(t_grf * g, char *nome);
int lunghezzaGrafo(t_grf * g);
int grafoVuoto(t_grf * g);
int arcoVuoto(t_arc * a);
int getPesoArco(t_grf * g, t_grf * h, int pesoDiRiferimento);

//Ricerce voli
t_grf * trovaPiuEconomico(t_grf * voli, char * partenza);
t_grf * trovaPiuGettonato(t_grf * voli, char * partenza);
void dijkstra(t_grf ** g, char *da, char *a, int pesoDiRiferimento);
t_grf * copiaGrafo(t_grf * g, t_grf * q);
t_grf * impostaCamminoMinimo(t_grf * q, char *nome, int camminoMinimoNuovo);
t_grf * impostaCamminoMinimoATutti(t_grf * g, int camminoMinimoNuovo);
t_grf * impostaPrecedente(t_grf * q, char *nome, t_grf * precedente);
t_grf * impostaPrecedenteATutti(t_grf * g, t_grf * precedente);
t_grf * impostaPopolarita(t_grf * g, char *nome, int popolaritaNuova);
t_grf * incrementaPopolarita(t_grf * g, char * nome);
t_grf * getMassimaPopolarita(t_grf * g);
t_grf * azzeraPopolarita(t_grf * g);
t_arc * getPrezzoMinimo(t_arc * a);
int nessunaGettonata(t_grf * g);
t_grf * getVerticeByCamminoMinimo(t_grf * q);
t_grf * costruisciPercorso(t_grf ** g, char * entrata);
t_grf * aggiungiPercorsoInTesta(t_grf * g, t_grf * daAggiungere);
void stampaPercorso(t_grf * g, t_grf * percorso, int pesoDiRiferimento);

//BFS
t_grf * bfs(t_grf * g, char *origine);
