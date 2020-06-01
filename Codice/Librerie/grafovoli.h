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

    int potenziale;       //il peso totale del cammino
    struct grafo *prev;   //puntatore al vertice che precede nel cammino minimo
} t_grf;

//NOTA: le implementazioni delle funzioni sono divise nei file grafovoli.c e dijkstra.c per fini organizzativi
//Operazioni sui vertici
t_grf * inizializzaGrafo(t_grf * g);
t_grf * aggiungiAeroporto(t_grf * g, char *nome);
t_grf * aggiungiAeroportoInTesta(t_grf * g, char *nome);
t_grf * eliminaAeroporto(t_grf * g, char *nome);

//Operazioni sugli archi
t_arc * inizializzaArco(t_arc * a, char *nome, float prezzo, int durata);
t_grf * aggiungiVolo(t_grf * g, char *uscita, char *entrata, float prezzo, int durata);
t_grf * eliminaVolo(t_grf * g, char *uscita, char *entrata);
t_arc * eliminaArco(t_arc * a, char *nome);
t_grf * eliminaTuttiVoliAdAeroporto(t_grf * g, char *nome);

//Stampe
void stampaGrafo(t_grf * G);
void stampaArchi(t_arc * a);

//Utilità
t_grf * getVertice(t_grf * g, char *nome);
int voloEsistente(t_arc * a, char *entrata);
int aeroportoEsistente(t_grf * g, char *nome);
int lunghezzaGrafo(t_grf * g);
int grafoVuoto(t_grf * g);
int arcoVuoto(t_arc * a);
void toUpperString(char * string);

//Dijkstra
t_grf * dijkstra(t_grf * g, char nome[], int pesoDiRiferimento);
t_grf * copiaGrafo(t_grf * g, t_grf * q);
t_grf * impostaPotenziale(t_grf * q, char *nome, int potenziale);
t_grf * impostaPrecedente(t_grf * q, char *nome, t_grf * precedente);
t_grf * minimoPotenziale(t_grf * q);