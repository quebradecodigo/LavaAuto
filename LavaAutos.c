/*
	Exerc�cio:
	Elabore um programa em C que armazene em arquivo bin�rio os dados dos
	funcion�rios da empresa Lava Autos.
 	Este programa deve permitir ao usu�rio:
		-> cadastrar novos funcion�rios; (implementado!)
		-> alterar dados dos registros no arquivo; (implementado!)
		-> pesquisar, por nome, se um funcion�rio est� cadastrado; (implementado! MAS VOC� VAI MELHOR�-LO :) )
		-> excluir o registro de um funcion�rio; (implementado, mas vamos pensar! :) )
		-> excluir o arquivo fisicamente. (VOC� VAI IMPLEMENTAR! :) )
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/** 
 * Constante declarada para verificar qual � o sistema operacional utilizado.
 * Usa-se 0 para Linux e 1 para Windows
 * Ex.: #define SISTEMA 0 // Linux
 */
#ifdef __linux__
#define SISTEMA 0 // Linux
#endif

#ifdef _WIN32
#define SISTEMA 1 // Windows
#endif

#define MAX_NOME 50

// A constru��o do registro (modelo).
typedef struct {
	int matricula, status;
	char estadoCivil;
	char nome[51];
	float salario;
}dados;

// Prot�tipo das fun��es.
int menu();  // Apresenta o menu de op��es do programa.
int cadastraFunc(); // Cadastra dados do funcion�rio no arquivo f�sico.
void leDadosFunc(dados *funcLe); // L� os dados do funcion�rio para serem gravados no arquivo.
int imprimeFunc(); // Imprime os dados dos funcion�rios cadastrados no arquivo.
int pesquisaFunc(); // Verifica se um funcion�rio est� cadastrado, retornando a posi��o do registro no arquivo.
void consultaFunc(int posRegFunc); // Acessa os dados de um funcion�rio espec�fico.
void alteraFunc(int posRegFunc); // Altera os dados de um funcion�rio.
void confirmaAlteracoes(dados *func); // Fun��o que l� do usu�rios os campos a serem alterados.
void excluiFunc(int posRegFunc);
void pausa();
void limpaTela();
void coloreTela();
void excluirArquivo();

/*
Ajustes a serem feitos:
    - Pesquisa n�o exata
    - Exclus�o
    - Importa��o de dados
    - Perfil de usu�rios
    - Backup e restore
*/

// Fim do prot�tipo das fun��es.

// Declara��o das fun��es.
int main(){
	int opcaoMenu, resp, pos;

	// La�o que mant�m o programa em execu��o, com op��es de menu para o usu�rio.
	do{
		// Imprime o menu na tela e l� a op��o escolhida pelo usu�rio.
		opcaoMenu = menu();

		// Chama a fun��o de acordo com a op��o digitada pelo usu�rio.
		switch(opcaoMenu){

			// Cadastra um funcion�rio.
			case 1:
				resp = cadastraFunc();


				// Verifica se o arquivo foi aberto corretamente.
				if(resp){
					printf("\n\tCadastro realizado com sucesso!!!\n\n");
				}
				else{
					printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
				}
			break;

			// Altera dados de um funcion�rio.
			case 2:
				pos = pesquisaFunc();
				// Verifica se o arquivo foi aberto corretamente.
				if (pos >= 0){
					alteraFunc(pos);
					printf("\n\tO registro foi alterado com sucesso!\n\n");
				}
				else if(pos == -1){
					printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
				}
				else{
					printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
				}
			break;

			// Exclui dados de um funcion�rio.
			case 3:
				pos = pesquisaFunc();
				// Verifica se o arquivo foi aberto corretamente.
				if (pos >= 0){
					consultaFunc(pos);
					excluiFunc(pos);
					printf("\n\tO registro foi excluido com sucesso!\n\n");
				}
				else if(pos == -1){
					printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
				}
				else{
					printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
				}
			break;

			// Pesquisa dados de um funcion�rio.
			case 4:
				pos = pesquisaFunc();
				// Verifica se o arquivo foi aberto corretamente.
				if (pos >= 0){
					consultaFunc(pos);
				}
				else if(pos == -1){
					printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
				}
				else{
					printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
				}
			break;

			// Imprime todos os registros do arquivo.
			case 5:
				resp = imprimeFunc();

				// Verifica se o arquivo foi aberto corretamente.
				if(resp){
					printf("\n\tImpressao realizada com sucesso!!!\n\n");
				}
				else{
					printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
				}
			break;

			// Apaga fisicamente o arquivo.
			case 6:				
        		excluirArquivo();
			break;

			default:
				printf("\n\tObrigado por usar o sistema! Finalizando....\n\n");
		}
		pausa();
		limpaTela();

	}while(opcaoMenu != 0);
	return 0;
}


int validarOpcao(int opcao) {
    (opcao == 99 || opcao == 7 || opcao == -1) ? 0 : 1;
}


// Colore a tela do programa com fundo azul e texto em amarelo.		
void coloreTela() {
	if (SISTEMA == 1)
		system("COLOR 1E");
}


void limpaTela() {
	if (SISTEMA == 0)
		system("clear");
	else
		system("cls");
}


void pausa() {
	if (SISTEMA == 0)
		system("read -p \"Pressione <ENTER> para continuar...\"");
		//system("sleep 5 | echo Processando...");
	else
		system("pause");
}

void excluirArquivo() {

	char op;
	char nomeArq[] = "funcionarios.dat";
	FILE *fp = fopen(nomeArq, "r");

    if (fp == NULL) {
        printf("\n\tDesculpe! O arquivo nao foi encontrado.\n");
    } else {
    	getchar();
		printf("\n\tDeseja realmente excluir? (S=Sim/N=Nao): ");
		scanf("%c", &op);

		if ((op == 's') || (op == 'S')) {
			remove(nomeArq);
			printf("\n\tArquivo \"%s\" excluido! :-)\n\n", nomeArq);
		}
	}
}

// Monta o menu de op��es.
int menu(){
	int opcao;

	coloreTela();

	printf("\n\tMenu de Opcoes Sistema Lava Autos - Funcionarios");
	printf("\n\t\t1 - Cadastrar");
	printf("\n\t\t2 - Alterar");
	printf("\n\t\t3 - Excluir");
	printf("\n\t\t4 - Pesquisar");
	printf("\n\t\t5 - Imprimir Arquivo");
	printf("\n\t\t6 - Apagar Arquivo");
	printf("\n\t\t0 - Sair");
	printf("\n\tDigite a opcao desejada: ");
    scanf("%d", &opcao);

    if (!validarOpcao(opcao)) {
        printf("\n\tOpcao nao eh valida\n\n");
        pausa();
        limpaTela();
        menu();
    }

	return opcao;
}

// Abre o arquivo de funcion�rios, de acordo com o modo recebido como par�metro.
FILE *abrirArquivo(char *modo){
	FILE *fp = fopen("funcionarios.dat", modo);
    return fp;
}

// Cadastra um registro de funcion�rio.
int cadastraFunc(){
	// Declara��o da vari�vel do tipo registro.
	dados func;

	// Ponteiro para o arquivo.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "a+b";

	// Abre o arquivo bin�rio para leitura e grava��o.
	fp = abrirArquivo(modo);

	// Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da fun��o.
	if(fp == NULL){
		return 0; // Opera��o de abertura/cria��o do arquivo N�O foi realizada com sucesso.
	}

	// Faz a leitura dos dados a serem cadastrados.
	leDadosFunc(&func);

	// Grava as informa��es no arquivo.
	fwrite(&func, sizeof(func), 1, fp);

	// Fecha o arquivo.
	fclose(fp);

	// Opera��o realizada com sucesso.
	return 1;
}

// Fun��o que l� os dados do usu�rio para serem gravados no arquivo.
void leDadosFunc(dados *funcLe){
	// Lendo informa��es de um funcion�rio.
	printf("\n\tDigite a matricula: ");
	scanf("%d", &funcLe->matricula);

	getchar();
	printf("\n\tDigite o nome: ");
	scanf("%50[^\n]s", funcLe->nome);
	//gets(funcLe->nome); (DEPRECATED)

	getchar();
	printf("\n\tDigite a primeira letra do estado civil: ");
	scanf("%c", &funcLe->estadoCivil);

	printf("\n\tDigite o salario: ");
	scanf("%f", &funcLe->salario);

	// Ativa o status do registro
	funcLe->status = 1;
}

// Fun��o que imprime os dados de todos os funcion�rios cadastrados.
int imprimeFunc(){
	// Vari�vel que conta o n�mero de registros.
	int qtdeReg = 0;

	// Vari�vel do tipo registro que recebe os dados de cada funcion�rio, gravados no arquivo.
	dados func;

	// Ponteiro para o arquivo.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "rb";

	// Abre o arquivo bin�rio para leitura.
	fp = abrirArquivo(modo);

	// Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da fun��o.
	if(fp == NULL){
		return 0; // Opera��o de abertura do arquivo N�O foi realizada com sucesso.
	}

	// L� as informa��es do arquivo, para inicializar o la�o.
	fread(&func, sizeof(func), 1, fp);

	// La�o de leitura do arquivo. Pode-se usar o do..while tamb�m!
	while(!feof(fp)){
		if(func.status == 1){
			// Imprime as informa��es dos registros ativos no sistema.
			printf("\n\n\t###### Dados do %do funcionario ######", ++qtdeReg);
			printf("\n\t\tMatricula: %d", func.matricula);
			printf("\n\t\tNome: %s", func.nome);
			printf("\n\t\tEstado civil: %c", func.estadoCivil);
			printf("\n\t\tSalario: %0.2f\n\n", func.salario);
		}

		// L� as informa��es do pr�ximo registro no arquivo, enquanto n�o se chegar ao final do arquivo.
		fread(&func, sizeof(func), 1, fp);
	}

	// Fecha o arquivo ap�s as opera��es.
	fclose(fp);

	// Opera��o realizada com sucesso.
	return 1;
}

// Fun��o que pesquisa, por nome, se existe o registro de determinado funcion�rio no arquivo.
int pesquisaFunc(){
	// Vari�vel auxiliar que indica se o registro procurado existe no arquivo.
	int achou = -1;

	// Vari�vel que armazena a posi��o do registro procurado dentro do arquivo.
	int posRegFunc = 0;

	// Vari�vel do tipo registro que recebe os dados de cada funcion�rio, gravados no arquivo.
	dados func;

	// Vari�vel auxiliar que recebe o nome a ser pesquisado no arquivo.
	char nomeAux[51];

	// Ponteiro para o arquivo f�sico.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "rb";

	// Abre o arquivo bin�rio para leitura.
	fp = abrirArquivo(modo);

	// Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da fun��o.
	if(fp == NULL){
		return 0; // Opera��o de abertura do arquivo N�O foi realizada com sucesso.
	}

	// Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
	getchar();
	printf("\n\tDigite o nome do funcionario a ser pesquisado: ");
	scanf("%50[^\n]s", nomeAux);
	//gets(nomeAux); (DEPRECATED)

	// L� as informa��es do arquivo, para inicializar o la�o.
	fread(&func, sizeof(func), 1, fp);

	// La�o de leitura do arquivo.
	while(!feof(fp) && (achou == -1)){
		if( (strcmp(func.nome, nomeAux) == 0) && (func.status == 1) ){
			achou = 1;
		}

		// L� as informa��es do pr�ximo registro no arquivo.
		fread(&func, sizeof(func), 1, fp);

		if(achou == -1){
			posRegFunc++;
		}
	}

	if(achou == -1){
		return -1;
	}

	// Fecha o arquivo ap�s as opera��es.
	fclose(fp);

	// Retorna a posi��o do registro procurado no arquivo.
	return posRegFunc;
}

// Fun��o que imprime os dados de um registro que foi consultado e existe no arquivo.
void consultaFunc(int posRegFunc){
	// Vari�vel que conta o n�mero de registros.
	int qtdeReg = 0;

	// Vari�vel do tipo registro que recebe os dados de cada funcion�rio, gravados no arquivo.
	dados func;

	// Ponteiro para o arquivo f�sico.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "r+b";

	// Abre o arquivo bin�rio para leitura.
	fp = abrirArquivo(modo);

	// Acessa o registro espec�fico, com base na posi��o recebida pela fun��o.
	fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

	// L� as informa��es do arquivo, para inicializar o la�o.
	fread(&func, sizeof(func), 1, fp);

	// Imprime as informa��es do registro pesquisado.
	printf("\n\t###### Dados do funcionario pesquisado ######");
	printf("\n\t\tMatricula: %d", func.matricula);
	printf("\n\t\tNome: %s", func.nome);
	printf("\n\t\tEstado civil: %c", func.estadoCivil);
	printf("\n\t\tSalario: %0.2f\n\n", func.salario);

	// Fecha o arquivo ap�s as opera��es.
	fclose(fp);
}

// Fun��o que permite alterar os dados de um registro do arquivo.
void alteraFunc(int posRegFunc){
	// Vari�vel do tipo registro que recebe os dados de cada funcion�rio, gravados no arquivo.
	dados func;

	// Ponteiro para o arquivo f�sico.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "r+b";

	// Abre o arquivo bin�rio para leitura e escrita.
	fp = abrirArquivo(modo);

	// Acessa o registro espec�fico, com base na posi��o recebida pela fun��o.
	fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

	// L� as informa��es do registro a ser alterado.
	fread(&func, sizeof(func), 1, fp);

	// Fun��o auxiliar que realiza as altera��es no registro.
	confirmaAlteracoes(&func);

	// Acessa o registro espec�fico, para atualiz�-lo.
	fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

	// Grava as informa��es do registro ap�s as altera��es.
	fwrite(&func, sizeof(func), 1, fp);

	// Fecha o arquivo ap�s as opera��es.
	fclose(fp);
}

// Fun��o que l� do usu�rios os campos a serem alterados.
void confirmaAlteracoes(dados *func){
	// Vari�vel auxiliar para confirmar altera��o de cada campo.
	char op;

	// Imprime as informa��es do registro pesquisado.
	printf("\n\t###### Dados do funcionario a serem alterados ######");
	printf("\n\tMatricula atual: %d", func->matricula);
	printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
	scanf("%c", &op);
	if((op == 's') || (op == 'S')){
		printf("\tDigite a nova matricula: ");
		scanf("%d", &func->matricula); // Altera a matr�cula do funcion�rio.
	}

	getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
	printf("\n\tNome atual: %s", func->nome);
	printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
	getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
	scanf("%c", &op);
	if((op == 's') || (op == 'S')){
		getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
		printf("\tDigite o novo nome: ");
		scanf("%50[^\n]s", func->nome); // Altera o nome do funcion�rio.
		// gets(func->nome); (DEPRECATED)
	}

	printf("\n\tEstado civil atual: %c", func->estadoCivil);
	printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
	getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
	scanf("%c", &op);
	if((op == 's') || (op == 'S')){
		getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
		printf("\tDigite o novo estado civil: ");
		scanf("%c", &func->estadoCivil); // Altera o estado civil do funcion�rio.
	}

	printf("\n\tSalario atual: %0.2f", func->salario);
	printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
	getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
	scanf("%c", &op);
	if((op == 's') || (op == 'S')){
		printf("\tDigite o novo salario: ");
		scanf("%f", &func->salario); // Altera o sal�rio do funcion�rio.
	}
}

// Fun��o que altera o valor do campo status para zero ("exclui")
void excluiFunc(int posRegFunc){
	// Vari�vel do tipo registro que recebe os dados de cada funcion�rio, gravados no arquivo.
	dados func;

	// Ponteiro para o arquivo f�sico.
	FILE *fp;

	// Define o modo de abertura do arquivo.
	char modo[] = "r+b";

	// Abre o arquivo bin�rio para leitura e escrita.
	fp = abrirArquivo(modo);

	// Acessa o registro espec�fico, com base na posi��o recebida pela fun��o.
	fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

	// L� as informa��es do registro a ser alterado.
	fread(&func, sizeof(func), 1, fp);

	// Altera o campo status para zero, "excluindo" o registro.
	func.status = 0;

	// Acessa o registro espec�fico, para atualiz�-lo.
	fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

	// Grava as informa��es do registro ap�s as altera��es.
	fwrite(&func, sizeof(func), 1, fp);

	// Fecha o arquivo ap�s as opera��es.
	fclose(fp);
}
