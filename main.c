#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_plus.h"
	
	int main(int argc, char **argv) {
	vetor = NULL;	
    FILE *fp = fopen("tt.csv", "r");
    char linha[MAX], *tmp = NULL;
    int na = 0, nc = 0;
    int i =0;
	int c = 0;
    if(!fp) {
        printf("Arquivo não encontrado.\n");
        return 0;
    }

    na = atoi(argv[1]); //Número da coluna
    nc = atoi(argv[2]); //Número de caracteres
    ordem = atoi(argv[3]);
   
    
    //Lê o atributo definido pelo usuário
    while(fgets(linha, MAX, fp)) {
		if(c>0){
			I[i]=i;
			tmp = strdup(linha); /* Aloca o tamanho correto para a String */
			split(tmp, na, nc,i+1); //Split na coluna definida pelo usuário;
			free(tmp);
			i++;
		}
		c++;
    }
    i = 0;
    c = 0;
    rewind(fp);
    while(fgets(linha, MAX, fp)) {
		if(c>0){
			tmp = strdup(linha);
			splitid(tmp,i);
			free(tmp);
			i++;
		}
		c++;
	}
    fclose(fp);
	nodo* arv = NULL;
	insertion_sort(vetor,i);
	arv = insere(arv,I,i);
	int n = 0;
	printf("Elementos do documento csv inseridos\n\n");
	while(n != 4){
		printf("               Menu\n\n");
		printf("Para remover os arquivos do citados no documento de entrada digite 1!\n");
		printf("Para visualizar a arvore digite 2!\n");
		printf("Para gerar o rank digite 3!\n");
		printf("Para sair digite 4!\n");
		
		scanf("%d",&n);
		if(n == 1){
			FILE *ids = NULL;
			int ii=0;
			ids = fopen("entrada.txt","r");
	
			if(!ids){
				printf("\nArquivo de entrada não encontrado no diretório atual !!! \n\n");
				return 0;
			}
			
			while(fscanf(ids, "%d\n", &ii) != EOF){
				remove_id(arv,ii);
			}
	
		}
		else if(n == 2){
			print(arv);
		}
		else if(n == 3){
			rank(arv);
		}
		else if(n == 4){
			limpa_arvore(arv);
			printf("Saiu\n\n");
		}
		else{
			printf("Valor digitado está incorreto!");
		}
			
	}
	return 0;
}
