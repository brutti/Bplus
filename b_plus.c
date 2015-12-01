#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_plus.h"

nodo * cria_nodo() {
	nodo * aux;
	aux = malloc(sizeof(nodo));
	aux->dado =(data*) malloc( ordem * sizeof(data) );
	aux->num_data = 0;
	aux->pai = NULL;
	aux->prox = NULL;
	aux-> ant = NULL;
	aux->dado->quant_id = 0;
	return aux;
}

void verifica(nodo* arv){
	
	nodo* aux = arv;
	nodo* aux2 = NULL;
	if(aux->ant->pai == NULL){
		aux->pai = cria_nodo();
		aux->pai->dado[aux->pai->num_data].texto = aux->dado[0].texto;
		aux->pai->filho = aux;
		aux->pai->num_data++;
		aux->ant->pai = aux->pai;
		
	}
	else if(aux->ant->pai->num_data < ordem){
		aux->pai= aux->ant->pai;
		aux->pai->dado[aux->pai->num_data].texto = aux->dado[0].texto;
		aux->pai->num_data++;
	}
	
	else{
		aux->ant->pai->prox = cria_nodo();
		aux->pai = aux->ant->pai->prox;
		aux->pai->dado[aux->pai->num_data].texto = aux->dado[0].texto;
		aux->pai->num_data++;
		aux->pai->ant = aux->ant->pai;
		aux->pai->filho = aux;
		aux2 = aux->pai;
		if(aux2->ant->pai && aux2->ant->pai->num_data < ordem){
			aux2->pai = aux2->ant->pai;
			aux2->pai->dado[aux2->pai->num_data].texto = aux->dado[0].texto;
			aux2->pai->num_data++;
		}
		
		else{
			if(aux2->ant->pai){
				while(aux2->ant->pai){
					aux2->pai = cria_nodo();
					aux2->ant->pai->prox = aux2->pai;
					aux2->pai->dado[aux2->pai->num_data].texto = aux2->dado[0].texto;
					aux2->pai->ant = aux2->ant->pai;
					aux2->pai->filho = aux2;
					aux2->pai->num_data++;
					aux2 = aux2->pai;
					
				}
				
				aux2->pai = cria_nodo();
				aux2->ant->pai= aux2->pai;
				aux2->pai->dado[aux2->pai->num_data].texto = aux2->dado[0].texto;
				aux2->pai->filho = aux2;
				aux2->pai->num_data++;
			}
			else{
				aux2->pai = cria_nodo();
				aux2->pai->dado[aux2->pai->num_data].texto = aux2->dado[0].texto;
				aux2->pai->filho = aux2; 
				aux2->pai->num_data++;
				aux2->ant->pai = aux2->pai;
				
			}
		}
	}
}
			
nodo* insere(nodo *arv, int I[],int tam_vetor){
	int flag2 = 0;
	int i = 0;
	int j = 0;
	nodo* aux = arv;
	nodo* aux2 = NULL;
	if(arv == NULL){
		flag2 = 1;
		arv = cria_nodo();
		while(arv->num_data< ordem  && j!= tam_vetor){
			if(i>0 && strcmp(arv->dado[i-1].texto,vetor[I[j]].texto) == 0){
				arv->dado[i-1].id =(int*) realloc(arv->dado[i-1].id,(arv->dado[i-1].quant_id+1) * sizeof(int));
				arv->dado[i-1].id[arv->dado[i-1].quant_id] = vetor[I[j]].id[0];
				arv->dado[i-1].quant_id++;
				j++;
			}
			else{
				arv->dado[i]= vetor[I[j]];
				arv->num_data++;
				i++;
				j++;
			}
		}
	}
	i=0;
	aux = arv;
	int flag = 0;
	while(j<tam_vetor){
		flag2 = 0;
		flag = 0;
		if (i == 0){
			if(strcmp(aux->dado[aux->num_data - 1].texto,vetor[I[j]].texto) == 0){
				aux->dado[aux->num_data - 1].id = (int*)realloc(aux->dado[aux->num_data - 1].id,(aux->dado[aux->num_data-1].quant_id+1) * sizeof(int));
				aux->dado[aux->num_data - 1].id[aux->dado[aux->num_data - 1].quant_id] = vetor[I[j]].id[0];
				aux->dado[aux->num_data - 1].quant_id++;
				j++;
				flag = 1;
			}
			else{
				aux2 = cria_nodo();
			}
		}
		
		if(i >0 && !flag){
			if(strcmp(aux2->dado[aux2->num_data - 1].texto,vetor[I[j]].texto) == 0){
				aux2->dado[aux2->num_data - 1].id = (int*)realloc(aux2->dado[aux2->num_data - 1].id,(aux2->dado[aux2->num_data-1].quant_id+1) * sizeof(int));
				aux2->dado[aux2->num_data - 1].id[aux2->dado[aux2->num_data - 1].quant_id] = vetor[I[j]].id[0];
				aux2->dado[aux2->num_data - 1].quant_id++;
				j++;
				flag = 1;
			}
		}
		if(!flag && aux2->num_data <= ordem){
			aux2->dado[i] = vetor[I[j]];
			aux2->num_data++;
			i++;
			j++;
		}
		
		if(!flag && aux2->num_data == ordem){	
			aux2->ant = aux;
			aux->prox = (nodo*)malloc(sizeof(nodo));
			aux->prox = aux2;
			aux = aux2;
			aux2 = aux	->prox;
			verifica(aux);
			
			i = 0;
		}
	}
	if(!flag && !flag2 && i!=0){
		aux2->ant = aux;
		aux->prox = aux2;
		aux = aux2;
		aux2 = aux->prox;
		verifica(aux);
	}
	return arv;
		
	
}

void remove_id(nodo* arv, int id){
	nodo* aux = arv;
	int i = 0,j=0;
	int flag = 0;
	while(aux){
		while(i<aux->num_data){
			while(j < ordem){
				if(aux->dado[i].id[j] == id){
					flag = 1;
					break;
				}
				if(flag) break;
				j++;
			}
			if(flag) break;
			i++;
			j = 0;
		}
		if(flag) break;
		else aux = aux->prox;
		i=0;
	}
	if(!aux) return;
	if(aux->dado[i].quant_id > 1){
		aux->dado[i].id[j] = 0;
		aux->dado[i].quant_id--;
	}
	
	else if(!aux->ant && !aux->prox){
		aux->dado[i].texto = "zzz";
		insertion_sort(aux->dado,aux->num_data);
		aux->dado[aux->num_data-1].id = NULL;
		aux->dado[aux->num_data-1].quant_id = 0;
		aux->dado[aux->num_data-1].texto = NULL;
		aux->num_data--;
		
	}
	else{
		if(aux->num_data > ordem/2){
			aux->dado[i].texto = "zzz";
			insertion_sort(aux->dado,aux->num_data);
			aux->dado[aux->num_data-1].texto = NULL;
			aux->dado[aux->num_data-1].quant_id = 0;
			aux->dado[aux->num_data-1].id = NULL;
			aux->num_data--;
		}
		else{
			if(aux->ant){	
				if(aux->ant->num_data > ordem/2){
					printf("%d\n",id);
					aux->dado[i] = aux->ant->dado[aux->ant->num_data-1];
					insertion_sort(aux->dado,aux->num_data);
					printf("%s\n",aux->ant->dado[aux->ant->num_data-1].texto);
					aux->ant->dado[aux->ant->num_data-1].texto = NULL;
					aux->ant->dado[aux->ant->num_data-1].id = NULL;
					aux->ant->dado[aux->ant->num_data-1].quant_id = 0;
					aux->ant->num_data--;
				}
			}
			else{
				if(aux->prox->num_data > ordem/2){
					aux->dado[i] = aux->prox->dado[0];
					insertion_sort(aux->dado,aux->num_data);
					aux->ant->dado[0].texto = "zzz";
					insertion_sort(aux->ant->dado,aux->ant->num_data);
					aux->ant->dado[0].texto = NULL;
					aux->ant->dado[0].id = NULL;
					aux->ant->dado[0].quant_id = 0;
					aux->prox->num_data--;
				}

				else{
					if(aux->ant){
						aux->ant->prox = aux->prox;
						i = 0;
						while(aux->num_data > 0){
							aux->ant->dado[aux->ant->num_data] = aux->dado[i];
							aux->dado[i].texto = NULL;
							aux->dado[i].id = NULL;
							aux->dado[i].quant_id = 0;
							aux->num_data--;
							aux->ant->num_data++;
							i++;
						}
						i = 0;
					}
					else{
						i = 0;
						while(aux->num_data > 0){
							aux->dado[i].texto = NULL;
							aux->dado[i].id = NULL;
							aux->dado[i].quant_id = 0;
							aux->num_data--;
							i++;
						}
					}
				}
			}
		}	
	}
					
}
void print(nodo * arv){
	int i = 0;
	int cont  = 1;
	int cont2 = 1;
	int cont3 = 0;
	nodo* aux = arv;
	nodo* aux2 = NULL;
	while(aux){
		if(aux->pai)aux= aux->pai;
		else break;
		cont3++;
	}
	aux2=aux;
	while(cont3>=0){
		while(aux){
			while(aux->num_data > i ){
				if(aux->dado[i].quant_id>0)printf("%s ",aux->dado[i].texto);
			
				if(i+1 != aux->num_data)printf("-");
				i++;
			}
			printf("|");
			i=0;
			aux=aux->prox;
		}
		printf("\n");
		aux = aux2;
		if(cont3 > 0){
			while(cont >0){
				if(aux->filho){
					aux = aux->filho;
					cont--;
				}
				else break;
			}
			cont2++;
			cont = cont2;
			while(aux){
				if(aux->ant)aux = aux->ant;
				else break;
			}
		}
		cont3--;
	}
}

int cmp_nome(const void *a, const void *b) {	
	int i = *(int *)a, j = *(int *)b;
    return strcmp(vetor[i].texto, vetor[j].texto);
}

void rank(nodo * arv){
	FILE * rank = NULL;
	rank = fopen("rank.txt","a");
	nodo * aux = arv;
	int i = 0;
	int j = 0;
	while(aux){
		while(i < aux->num_data){
			if(aux->dado[i].texto)fprintf(rank,"%s: ", aux->dado[i].texto);
			while(j<aux->dado[i].quant_id){
				if(aux->dado[i].id[j] !=0){
					
					fprintf(rank,"%d", aux->dado[i].id[j]);
					if(j+1 == aux->dado[i].quant_id)fprintf(rank,".");
					else fprintf(rank,", ");
				}
				j++;
			}
			fprintf(rank,"\n");
			i++;
			j = 0;
		}
		i = 0;
		if(aux->prox){
			aux= aux->prox;
		}
		else break;
	}
	fclose(rank);
}					


void limpa_arvore(nodo * arv){
	nodo* aux = NULL;
	int cont3 = 0;
	while(arv){
		if(arv->pai)arv= arv->pai;
		else break;
		cont3++;
	}
	while(cont3>0){
		while(arv){
			free(arv->dado);
			aux = arv;
			if(arv->prox)arv = arv->prox;
			else arv = arv->filho;
			free(aux);
		}
		while(arv){
			if(arv->ant)arv = arv->ant;
			else break;
		}
		cont3--;
		
		
	}
}

void insertion_sort(data * a, int n){
	int i,j;
	data aux;
	for(i = 1;i<n;i++){
		aux = a[i];
		for(j=i;j>0&& aux.texto && strcmp(aux.texto,a[j-1].texto)<0;j--){
			a[j] = a[j-1];
		}
		a[j] = aux;
	}
}


void split_lim(char *token, int numCar,int j) {
    char *tmp = NULL;
    int i;
    if(strlen(token)){
		for(i = 0; i <= numCar; token++) {
			if(*token != 34) {
				tmp = (char *) realloc(tmp, (++i) * sizeof(char));
				tmp[i - 1] = *token;
			}	
		}
		tmp = (char *) realloc(tmp, (i + 1) * sizeof(char));
		tmp[i] = '\0';
		vetor = (data*)realloc(vetor,j*(sizeof(data)));
		vetor[j-1].texto = (char *) malloc((strlen(tmp)+1) * sizeof(char));
		strcpy(vetor[j-1].texto, tmp);
		vetor[j-1].texto[strlen(tmp)+1] = '\0';
		free(tmp);
	}
}

void split(char *linha, int numCol, int numCar,int i) {
    char *token = NULL;
    int flag=0;
    for(token = strtok(linha, ","); token && *token; token = 
                                              strtok(NULL, ",")) {
        if(!--numCol) {
			flag=1;
            split_lim(token, numCar-1,i);
        }
    }
    if(!token&& !flag){
		vetor = (data*)realloc(vetor,i*(sizeof(data)));
		vetor[i-1].texto = (char *) malloc(3 * sizeof(char));
		vetor[i-1].texto = "VAZIO";
		
	}
}

void splitid(char *linha,int i) {
	char aux[MAX];
	int c = 0, c2 = 0;
	while(linha[c] != ',') {
		if(linha[c] != 34) {
			aux[c2] = linha[c];
			c2++;
		}
		c++;
	}
	aux[c2] = '\0';
	int ret = atoi(&(*aux));
	vetor[i].id = (int*)malloc(1*sizeof(int));
	vetor[i].id[0] = 0;
	vetor[i].id[0] = ret;
	vetor[i].quant_id = 0;	
	vetor[i].quant_id++;
}

