#include "liste.h"

t_lista * creaNodo_P (char * partenza, char * destinazione, int numeroScali, float prezzo){
	t_lista * tmp = (t_lista *) malloc (sizeof(t_lista));
	
	if(tmp){
		strcpy(tmp->prenotazioni.partenza, partenza);
		strcpy(tmp->prenotazioni.destinazione, destinazione);
		tmp->prenotazioni.numeroScali = numeroScali;
		tmp->prenotazioni.prezzo = prezzo;
		tmp->next = NULL;
	}else 
		printf("Memoria insufficiente per la creazione di un nuovo elemento");
	 
	return tmp;
}

t_lista * inserisciInTesta_P (t_lista * top, char * partenza, char * destinazione, int numeroScali, float prezzo){
	t_lista * tmp = creaNodo_P(partenza, destinazione, numeroScali, prezzo);
	
	if(tmp){
		tmp->next = top;
		return tmp;
	} 
	return top;
}

t_lista * rimuoviElemento_P(t_lista * top, char * partenza, char * destinazione){
	t_lista * tmp = top;
	
	if(tmp){
		if(strcmp(tmp->prenotazioni.partenza, partenza) == 0 && strcmp(tmp->prenotazioni.destinazione, destinazione) == 0){
			top = tmp->next;
			free(tmp);
		}else
			top->next = rimuoviElemento_P(top->next, partenza, destinazione);
	}
	return top;
}

int contains_P(t_lista * top, char * partenza, char * destinazione){
	int result = 0;
	
	if(top){
		if(strcmp(top->prenotazioni.partenza, partenza) == 0 && strcmp(top->prenotazioni.destinazione, destinazione))
			result = 1;
		else
			result = contains_P(top->next, partenza, destinazione);
	}
	return result;
}


