// HashingLinear.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "string.h"
#include "stdlib.h"
#define TAM 70
#define TAMVETOR 211

typedef struct aluno {
	int matricula;
	char nome[TAM];
	char telefone[TAM];
	char email[TAM];
	char endereco[TAM];
 } TAluno;

void limpaTAluno(TAluno *aluno){
	(*aluno).matricula = 0;
	strcpy((*aluno).nome, " ");
	strcpy((*aluno).telefone, " ");
	strcpy((*aluno).email, " ");
	strcpy((*aluno).endereco, " ");
}

void sinalizaExclusaoTAluno(TAluno *aluno){
	(*aluno).matricula = -1;
	strcpy((*aluno).nome, " ");
	strcpy((*aluno).telefone, " ");
	strcpy((*aluno).email, " ");
	strcpy((*aluno).endereco, " ");
}

void inicializaVetor(TAluno **vetor){
	for(int i =0; i < TAMVETOR; i++){
		(*vetor)[i].matricula = 0;
		strcpy((*vetor)[i].nome, " ");
		strcpy((*vetor)[i].telefone, " ");
		strcpy((*vetor)[i].email, " ");
		strcpy((*vetor)[i].endereco, " ");
	}
}

int funcaoHashing(TAluno aluno, TAluno **vetor, int tipo, int ind, bool pesquisa){
	
	if(tipo == 0){
		ind = aluno.matricula % TAMVETOR;
	}
	if(((*vetor)[ind].matricula == 0)||((*vetor)[ind].matricula == -1)){
		printf("Ok, Vetor de indice %d eh nulo!!! \n", ind);
		if(pesquisa == true){
			if( (*vetor)[ind].matricula == -1 ){ // Caso o valor de matricula seja -1, ele segue na pesquisa pois -1 que dizer que o valor que estava ali foi apagado.
				ind = funcaoHashing(aluno, vetor, 1, (ind+1), true);
			}else{
				return NULL;// Na pesquisa, se ele retornar NULL, é pq o Aluno não existe no vetor
			}
		}
	}else{
		printf("O Vetor de indice %d nao eh nulo. \n", ind);
		//Caso o Indice ja esteja ocupado, tenta o índice da frente até encontrar.
		if(pesquisa == true){
			// Compara se é o escolhido.
			if(	((*vetor)[ind].matricula == aluno.matricula)	&& (	strcmp((*vetor)[ind].nome, aluno.nome)== 0	)	){
				return ind;
			}else{
				ind = funcaoHashing(aluno, vetor, 1, (ind+1), true);
			}
		}else{
			if(ind == TAMVETOR){
				// Nesse caso o vetor chegou ao fim, tentaremos inserir no inicio do vetor.
				ind = funcaoHashing(aluno, vetor, 1, 0, false);
			}else{
				ind = funcaoHashing(aluno, vetor, 1, (ind+1), false);
			}
		}
	}
	return ind;	
}

void tabelaHash(TAluno **vetor, FILE * arquivo){
	TAluno aluno;
	int cont = 0, ind = 0;
	char texto[TAM];
	while( (fgets(texto, sizeof(texto), arquivo))!=NULL ){
		cont ++;
		switch (cont%5){
			case 1:					
				aluno.matricula = atoi(texto); // atoi converte String para inteiro
				break;
			case 2:
				strcpy(aluno.nome,texto);
				break;
			case 3:
				strcpy(aluno.telefone,texto);
				break;
			case 4:
				strcpy(aluno.email,texto);
				break;
			case 0:
				strcpy(aluno.endereco,texto);

				//Direciona Ponteiro para a posição Correta
				ind = (funcaoHashing(aluno, &(*vetor), NULL, NULL, false));
				
				(*vetor)[ind] = aluno;
				printf("%d \n",(*vetor)[ind].matricula);
				printf("%s \n",(*vetor)[ind].nome);
				printf("%s \n",(*vetor)[ind].telefone);
				printf("%s \n",(*vetor)[ind].email);
				printf("%s \n\n\n",(*vetor)[ind].endereco);
				break;
		}				
	}
	printf("\n\n******************************\n\n");
}

int menu(TAluno **vetor){
	int resp = 0, ind = 0;
	TAluno aluno;
	limpaTAluno(&aluno);
	
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
			scanf("%d",&aluno.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.nome,TAM,stdin);

			printf("\nTelefone: ");
			fflush(stdin);fgets(aluno.telefone,TAM,stdin);

			printf("\nEmail: ");
			fflush(stdin);fgets(aluno.email,TAM,stdin);

			printf("\nEndereco: ");
			fflush(stdin);fgets(aluno.endereco,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL, NULL, false));
			(*vetor)[ind] = aluno;
			system("cls");
			printf("\n\n ALUNO ADICIONADO COM SUCESSO! \n\n");
			system("PAUSE");
			break;
		case 2:
			//Remove
			char confirma;
			system("cls");
			printf("\n\n\n****************REMOVER***************\n");

			printf("Matricula: ");
			scanf("%d",&aluno.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.nome,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL, NULL, true));

			if(ind != NULL){
				system("cls");
				printf("\n\n\n****************ALUNO ENCONTRADO!***************\n");
				printf("\nMatricula: %d", (*vetor)[ind].matricula);
				printf("\nNome: %s", (*vetor)[ind].nome);
				printf("\nTelefone: %s", (*vetor)[ind].telefone);
				printf("\nEmail: %s", (*vetor)[ind].email);
				printf("\nEndereço: %s", (*vetor)[ind].endereco);
				printf("\n****************************************************\n");
				printf("Deseja Excluir? S-Sim N-Nao \n");
				confirma = getchar();
				if(confirma == 'S' || confirma == 's'){
					//limpaTAluno(&(*vetor)[ind]);
					sinalizaExclusaoTAluno(&(*vetor)[ind]);
					system("cls");
					printf("\n\n ALUNO ADICIONADO COM SUCESSO! \n\n");
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
			scanf("%d",&aluno.matricula);

			printf("\nNome: ");
			fflush(stdin); fgets(aluno.nome,TAM,stdin);

			ind = (funcaoHashing(aluno, &(*vetor), NULL, NULL, true));

			if(ind != NULL){
				system("cls");
				printf("\n\n\n****************ALUNO ENCONTRADO!***************\n");
				printf("\nMatricula: %d", (*vetor)[ind].matricula);
				printf("\nNome: %s", (*vetor)[ind].nome);
				printf("\nTelefone: %s", (*vetor)[ind].telefone);
				printf("\nEmail: %s", (*vetor)[ind].email);
				printf("\nEndereço: %s", (*vetor)[ind].endereco);
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
	TAluno *vetor;
	vetor= (TAluno*) malloc(TAMVETOR *sizeof(TAluno));
	inicializaVetor(&vetor);
	
	FILE * arquivo;
	arquivo = fopen ("Alunos.txt","r");
	
	if(arquivo != NULL){
		printf("Arquivo Alunos.txt Encontrado! \n");
		printf("\n\n******************************\n\n");
		tabelaHash(&vetor, arquivo);
	}else{
		printf("Erro na abertura do Arquivo. \n");
		system("PAUSE");
	}

	while(resp != 0){
		resp = menu(&vetor);
	}

	free(vetor);
	fclose(arquivo);
	system("PAUSE");
	return 0;
}