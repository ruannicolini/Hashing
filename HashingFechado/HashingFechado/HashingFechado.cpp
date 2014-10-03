// HashingFechado.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "stdlib.h"
#define TAM 70
#define TAMVETOR 211

typedef struct dados {
	int matricula;
	char nome[TAM];
	char telefone[TAM];
	char email[TAM];
	char endereco[TAM];
} TDados;

typedef struct aluno{
	TDados item;
	aluno *prox;
} TAluno;

//TAluno aluno;
void limpaTAluno(TAluno *aluno){
	aluno->item.matricula = 0;
	strcpy(aluno->item.nome, " ");
	strcpy(aluno->item.telefone, " ");
	strcpy(aluno->item.email, " ");
	strcpy(aluno->item.endereco, " ");
	aluno->prox = NULL;
}
void inicializaVetor(TAluno **vetor){
	for(int i =0; i < TAMVETOR; i++){
		vetor[i] = NULL;
	}
}

int funcaoHashing(TAluno aluno, TAluno **vetor, int ind){
	ind = (aluno.item.matricula % TAMVETOR);
	return ind;	
}

TAluno * inseriAluno(TAluno *listPosicaoVetor, TAluno aluno) {
	
	TAluno *aux = (TAluno*) malloc(sizeof(TAluno));
	aux->item = aluno.item;
	aux->prox = NULL;
		
	if(listPosicaoVetor == NULL) {
		listPosicaoVetor = aux;
	} else {
		TAluno *ponteiro;
		for(ponteiro = listPosicaoVetor; ponteiro->prox != NULL; ponteiro = ponteiro->prox);
		ponteiro->prox = aux;
	}
	return listPosicaoVetor;
	
}

void tabelaHash(TAluno **vetor, FILE * arquivo){
	TAluno *ponteiro = (TAluno *)malloc(sizeof(TAluno));
	ponteiro->prox = NULL;

	TAluno aluno;	

	int cont = 0, ind = 0;
	char texto[TAM];

	while( (fgets(texto, sizeof(texto), arquivo))!=NULL ){
		cont ++;
		switch (cont%5){
			case 1:					
				aluno.item.matricula = atoi(texto); // atoi converte String para inteiro
				break;
			case 2:
				strcpy(aluno.item.nome,texto);
				break;
			case 3:
				strcpy(aluno.item.telefone,texto);
				break;
			case 4:
				strcpy(aluno.item.email,texto);
				break;
			case 0:
				strcpy(aluno.item.endereco,texto);
				ind = (funcaoHashing(aluno, &(*vetor), NULL));
				vetor[ind] = inseriAluno(vetor[ind], aluno);
				break;
		}				
	}
	printf("\n\n******************************\n\n");
}

int menu(TAluno **vetor){
	int teste = 0;
	int resp = 0, ind = 0;
	TAluno aluno;
	limpaTAluno(&aluno);

	TAluno *anterior = NULL;

	TAluno *ponteiro = (TAluno *)malloc(sizeof(TAluno)); // ponteiro faz papel de atual no Excluir
	ponteiro->prox = NULL;
	
	system("cls");
	printf("\n\n\n******************************\n");
	printf("1-Adicionar \n2-Remover \n3-Pesquisar \n0-Sair \n");
	printf("******************************\n");
	scanf("%d",&resp);

	switch (resp){
		case 1:
			// ADD
			system("cls");
			printf("\n\n\n****************ADD***************\n");
			printf("Matricula: ");
			scanf("%d",&aluno.item.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.item.nome,TAM,stdin);

			printf("\nTelefone: ");
			fflush(stdin);fgets(aluno.item.telefone,TAM,stdin);

			printf("\nEmail: ");
			fflush(stdin);fgets(aluno.item.email,TAM,stdin);

			printf("\nEndereco: ");
			fflush(stdin);fgets(aluno.item.endereco,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL));
			vetor[ind] = inseriAluno(vetor[ind], aluno);

			system("cls");
			printf("\n\n ALUNO ADICIONADO COM SUCESSO! \n\n");
			system("PAUSE");
			break;
		case 2:
			//Remove
			char confirma;
			anterior = NULL;
			
			system("cls");
			printf("\n\n\n****************DELETAR***************\n");

			printf("Matricula: ");
			scanf("%d",&aluno.item.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.item.nome,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL));
			ponteiro = vetor[ind]; 

			if(ponteiro == NULL){
				teste = 0;
			}else{
				if (ponteiro->prox != NULL){
					while ((ponteiro->prox != NULL)&&(teste == 0)){
					   
					   if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado!
					   }else{
							anterior = ponteiro;
							ponteiro = ponteiro->prox;
							// OBS: Pode ser que o ponteiro->prox seja NULL, por isso faremos a verificação aqui tbm!
							if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado!
							}
					   }
					} 
				}else{
					if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado logo no primeiro teste!
					   }
				}
			}

			if(teste == 1){
				system("cls");
				printf("\n\n\n****************ALUNO ENCONTRADO!***************\n");
				printf("\nMatricula: %d", ponteiro->item.matricula);
				printf("\nNome: %s", ponteiro->item.nome);
				printf("\nTelefone: %s", ponteiro->item.telefone);
				printf("\nEmail: %s", ponteiro->item.email);
				printf("\nEndereco: %s", ponteiro->item.endereco);
				printf("\n****************************************************\n");
				printf("Deseja Excluir? S-Sim N-Nao \n");
				confirma = getchar();
				if(confirma == 'S' || confirma == 's'){

					if(anterior == NULL){
						if(ponteiro->prox == NULL){
							// Unico elemento da lista
							vetor[ind] = NULL;
						}else{
							 //Exclusão do Primeiro Elemento da Lista
							vetor[ind] = vetor[ind]->prox;
						}
					}else{
						
						anterior->prox = ponteiro->prox;
						free(ponteiro);
					}
					system("cls");
					printf("\n\n ALUNO REMOVIDO COM SUCESSO! \n\n");
					system("PAUSE");
				}
			}else{
				system("cls");
				printf("\n\n\n****************ALUNO NAO ENCONTRADO!***************\n\n\n");
				system("PAUSE");
			}
			break;
		case 3:
			//Pesquisar
			system("cls");
			printf("\n\n\n****************PESQUISAR***************\n");

			printf("Matricula: ");
			scanf("%d",&aluno.item.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.item.nome,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL));

			ponteiro = vetor[ind];
			if(ponteiro == NULL){
				teste = 0;
			}else{
				if(ponteiro->prox != NULL){
					while ((ponteiro->prox != NULL)&&(teste == 0)){
					   
					   if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado!
					   }else{
							ponteiro = ponteiro->prox;

							// OBS: Pode ser que o ponteiro->prox seja NULL, por isso faremos a verificação aqui tbm!
							if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado!
							}
					   }
					} 
				}else{
					if(( ponteiro->item.matricula == aluno.item.matricula) && (strcmp(ponteiro->item.nome, aluno.item.nome) == 0)){
							   teste = 1;
							   // Aqui ja´achamos quem foi procurado logo no primeiro teste!
					   }
				}
			}
			if(teste == 1){
				system("cls");
				printf("\n\n\n****************ALUNO ENCONTRADO!***************\n");
				printf("\nMatricula: %d", ponteiro->item.matricula);
				printf("\nNome: %s", ponteiro->item.nome);
				printf("\nTelefone: %s", ponteiro->item.telefone);
				printf("\nEmail: %s", ponteiro->item.email);
				printf("\nEndereco: %s", ponteiro->item.endereco);
				system("PAUSE");
			}else{
				system("cls");
				printf("\n\n\n****************ALUNO NAO ENCONTRADO!***************\n\n\n");
				system("PAUSE");
			}
			break;
		case 0:
			return resp;
			break;
	}
	return resp;
}



int _tmain(int argc, _TCHAR* argv[])
{
	int resp = 1;
	TAluno **vetor = (TAluno **) malloc(TAMVETOR * sizeof(TAluno));
	//TAluno **vetor = (TAluno*) malloc(TAMVETOR *sizeof(TAluno));
	inicializaVetor(&*vetor);
	

	FILE * arquivo;
	arquivo = fopen ("Alunos.txt","r");
	
	if(arquivo != NULL){
		printf("Arquivo Alunos.txt Encontrado! \n");
		printf("\n\n******************************\n\n");
		tabelaHash(&*vetor, arquivo);
	}else{
		printf("Erro na abertura do Arquivo. \n");
		system("PAUSE");
	}

	while(resp != 0){
		resp = menu(&*vetor);
	}
	free(vetor);
	fclose(arquivo);	
	system("PAUSE");
	return 0;
}


