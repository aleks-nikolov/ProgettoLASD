#include "abr.h"

void inizializzaTickets (int * tickets){
	int i;
	
	for(i=0;i<LUNGHEZZA_TICKETS;i++)
		tickets[i] = 0;
}

t_abr * creaNodo_U(char * nomeUtente, char * password, int admin){
	t_abr * tmp =(t_abr *) malloc(sizeof(t_abr));
	
	if(tmp){
		tmp->sinistro = tmp->destro = NULL;
		strcpy(tmp->utente.nomeUtente, nomeUtente);
		strcpy(tmp->utente.password, password);
		tmp->utente.admin = admin;
		tmp->utente.prenotazioni = NULL;
		tmp->utente.punti = 0;
		inizializzaTickets(tmp->utente.tickets);
	}else 
		printf("Memoria non disponibile\n");
	return tmp;
}

t_abr * inserisciNodo_U(t_abr * radice, char * nomeUtente, char * password, int admin){
	
	if(!radice){
		radice = creaNodo_U(nomeUtente, password, admin);
	}
	else if (strcmp(radice->utente.nomeUtente, nomeUtente) > 0)
		radice->sinistro = inserisciNodo_U(radice->sinistro, nomeUtente, password, admin);
	else if (strcmp(radice->utente.nomeUtente, nomeUtente) < 0)
		radice->destro = inserisciNodo_U(radice->destro, nomeUtente, password, admin);
		
	return radice;
}

int contains_U(t_abr * radice, char * nomeUtente, t_abr ** contenitore){//verifica se è presente un utente con nomeUtente uguale a quello passato come argomento all'interno dell'albero passato per argomento. Se presente, *contenitore è posto uguale al puntatore a quell'elemento;
	int result = 0;
	
	if(radice){
		if(strcmp(radice->utente.nomeUtente, nomeUtente) != 0){
			
			if(strcmp(radice->utente.nomeUtente, nomeUtente) > 0)
				result = contains_U(radice->sinistro, nomeUtente, contenitore);
			else 
				if(strcmp(radice->utente.nomeUtente, nomeUtente) < 0)
					result = contains_U(radice->destro, nomeUtente, contenitore);
				
		}else{
			result = 1;
			if(contenitore)
				*contenitore = radice;
		}	
	}
	return result;
}

void mostraUtenti(t_abr * radice){
	
	if(radice){
		mostraUtenti(radice->sinistro);
		if(radice->utente.admin == 1)
			printf("%s (admin), password: %s\n", radice->utente.nomeUtente, radice->utente.password);
		else
			printf("%s (cliente), password: %s\n", radice->utente.nomeUtente, radice->utente.password);
		mostraUtenti(radice->destro);
	}
}

t_abr * inizializzaUtenti(){//metodo lanciato a inizio programma per inizializzare 3 utenti admin e 2 utenti clienti
	t_abr * tmp = NULL;
	
	tmp = inserisciNodo_U(tmp,"admin1", "passwordA1", 1);
	tmp = inserisciNodo_U(tmp, "admin2", "passwordA2", 1);
	tmp = inserisciNodo_U(tmp, "admin3", "passwordA3", 1);
	tmp = inserisciNodo_U(tmp, "cliente1", "passwordC1", 0);
	tmp = inserisciNodo_U(tmp, "cliente2", "passwordC2", 0);
	
	return tmp;
}
