#include "liste.h"

//funzioni per la gestione della struttura t_lista_S

t_lista_S * creaNodo_S (char * nomeAeroporto){
	t_lista_S * tmp =(t_lista_S *) malloc (sizeof(t_lista_S));
	
	if(tmp){
		strcpy(tmp->scalo, nomeAeroporto);
	}else 
		printf("Memoria insufficiente per la creazione di un nuovo elemento");
	 
	return tmp;
}

t_lista_S * inserisciInTesta_S (t_lista_S * top, char * nomeAeroporto){
	t_lista_S * tmp = creaNodo_S(nomeAeroporto);
	
	if(tmp){
		tmp->next = top;
		return tmp;
	} 
	return top;
}

t_lista_S * inserisciInCoda_S (t_lista_S * top, char * nomeAeroporto){
	if(!top)
		top = inserisciInTesta_S(top, nomeAeroporto);
	else
		top->next = inserisciInCoda_S(top->next, nomeAeroporto);
	
	return top;
}

t_lista_S * rimuoviElemento_S(t_lista_S * top, char * nomeAeroporto){
	t_lista_S * tmp = top;
	
	if(tmp){
		if(strcmp(tmp->scalo, nomeAeroporto) == 0){
			top = tmp->next;
			free(tmp);
		}else
			top->next = rimuoviElemento_S(top->next, nomeAeroporto);
	}
	return top;
	
}

int contains_S (t_lista_S * top, char * nomeAeroporto){
	int result = 0;
	
	if(top){
		if(strcmp(top->scalo, nomeAeroporto) == 0)
			result = 1;
		else
			result = contains_S(top->next, nomeAeroporto);
	}
	return result;
}

void mostraScali(t_lista_S * top){
	if(top){
		printf("%s", top->scalo);
		
		if(top->next)
			printf(", ");
				
		mostraScali(top->next);
	}	
}

//funzioni per la gestione della struttura t_lista_P

t_lista_P * creaNodo_P (char * partenza, char * destinazione, t_lista_S * scali, float prezzo){
	t_lista_P * tmp = (t_lista_P *) malloc (sizeof(t_lista_P));
	
	if(tmp){
		strcpy(tmp->prenotazione.partenza, partenza);
		strcpy(tmp->prenotazione.destinazione, destinazione);
		tmp->prenotazione.scali = scali;
		tmp->prenotazione.prezzo = prezzo;
		tmp->next = NULL;
	}else 
		printf("Memoria insufficiente per la creazione di un nuovo elemento");
	 
	return tmp;
}

t_lista_P * inserisciInTesta_P (t_lista_P * top, char * partenza, char * destinazione, t_lista_S * scali, float prezzo){
	t_lista_P * tmp = creaNodo_P(partenza, destinazione, scali, prezzo);
	
	if(tmp){
		tmp->next = top;
		return tmp;
	} 
	return top;
}

t_lista_P * inserisciInCoda_P (t_lista_P * top, char * partenza, char * destinazione, t_lista_S * scali, float prezzo){
	if(!top)
		top = inserisciInTesta_P(top, partenza, destinazione, scali, prezzo);
	else
		top->next = inserisciInCoda_P(top->next, partenza, destinazione, scali, prezzo);
	
	return top;
}

t_lista_P * rimuoviElemento_P(t_lista_P * top, char * partenza, char * destinazione){
	t_lista_P * tmp = top;
	
	if(tmp){
		if(strcmp(tmp->prenotazione.partenza, partenza) == 0 && strcmp(tmp->prenotazione.destinazione, destinazione) == 0){
			top = tmp->next;
			free(tmp);
		}else
			top->next = rimuoviElemento_P(top->next, partenza, destinazione);
	}
	return top;
}

int contains_P(t_lista_P * top, char * partenza, char * destinazione){
	int result = 0;
	
	if(top){
		if(strcmp(top->prenotazione.partenza, partenza) == 0 && strcmp(top->prenotazione.destinazione, destinazione))
			result = 1;
		else
			result = contains_P(top->next, partenza, destinazione);
	}
	return result;
}


void mostraPrenotazioni(t_lista_P * top){
	if(top){
		printf("%s -> %s ", top->prenotazione.partenza, top->prenotazione.destinazione);
		if(top->prenotazione.scali){
			printf("con scali ");
			mostraScali(top->prenotazione.scali);  
		}
		printf(" e per un prezzo totale di %.2f euro\n", top->prenotazione.prezzo);
			
		mostraPrenotazioni(top->next);
	}
}


