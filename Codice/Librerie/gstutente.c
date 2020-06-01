#include "gstutente.h"

void toUpper_String(char * string){
	int i;
	
	for(i=0; string[i];i++){
		string[i] = toupper(string[i]);
	}
}
