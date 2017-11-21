/*
	Exercício:
	Elabore um programa em C que armazene em arquivo binário os dados dos
	funcionários da empresa Lava Autos.
 	Este programa deve permitir ao usuário:
		-> cadastrar novos funcionários; (implementado!)
		-> alterar dados dos registros no arquivo; (implementado!)
		-> pesquisar, por nome, se um funcionário está cadastrado; (implementado! MAS VOCÊ VAI MELHORÁ-LO :) )
		-> excluir o registro de um funcionário; (implementado, mas vamos pensar! :) )
		-> excluir o arquivo fisicamente. (VOCÊ VAI IMPLEMENTAR! :) )
*/

/*
 * PERFIS DE USUÁRIOS DO SISTEMA:
 *	- Adminitrador
 *	- Gerente
 *	- Operador
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
 * Constante declarada para verificar qual é o sistema operacional utilizado.
 * Usa-se 0 para Linux e 1 para Windows
 * Ex.: #define SISTEMA 0 // Linux
 */
#ifdef __linux__
#define SISTEMA 0 // Linux
#endif

#ifdef _WIN32
#define SISTEMA 1 // Windows
#endif

/*
 * Constante DESENVOLVIMENTO declarada para verificar se o sistema está em fase de desenvolvimento.
 * Usa-se 0 para falso e 1 para verdadeiro
 * Ex.: #define SISTEMA 0 // Linux
 */
#define DESENVOLVIMENTO 0 

// A construção do registro (modelo).
typedef struct{
    int matricula, status;
    char estadoCivil;
    char nome[51];
    float salario;
} dados;

typedef struct{
    int nivel;
    char usuario[21];
    char senha[21];
} login;
//1 = Administrador
//2 = Gerente
//3 = Operador

// Protótipo das funções.
int menu(int *nivel);  // Apresenta o menu de opções do programa.
int cadastraFunc(); // Cadastra dados do funcionário no arquivo físico.
void leDadosFunc(dados *funcLe); // Lê os dados do funcionário para serem gravados no arquivo.
int imprimeFunc(); // Imprime os dados dos funcionários cadastrados no arquivo.
int pesquisaFunc(); // Verifica se um funcionário está cadastrado, retornando a posição do registro no arquivo.
void consultaFunc(int posRegFunc); // Acessa os dados de um funcionário específico.
void alteraFunc(int posRegFunc); // Altera os dados de um funcionário.
void confirmaAlteracoes(dados *func); // Função que lê do usuários os campos a serem alterados.
void excluiFunc(int posRegFunc);
void pausa();
void limpaTela();
void coloreTela();
void excluirArquivo();
int realizarBackup();
void restaurarBackup();
int leUsuarios(char user[], char pass[], int *nivel);
int loginUsers();
void cadastroUsers();
int importarDados();

/*
Ajustes a serem feitos:
    - Pesquisa não exata
    - Exclusão
    - Importação de dados
    - Perfil de usuários
    - Backup e restore
*/

// Fim do protótipo das funções.

// Declaração das funções.
int main(){
    int opcaoMenu, resp, pos;
    int nivel=1;

    // Laço que mantém o programa em execução, com opções de menu para o usuário.
    //Casso não tenha o arquivo de usuarios comente o codigo dentro de Main e uso somente essa linha para cadastrar usuarios!
    //cadastroUsers();

    if (!DESENVOLVIMENTO) {
        nivel = loginUsers();
    }

    do{
        // Imprime o menu na tela e lê a opção escolhida pelo usuário.
          
        opcaoMenu = menu(&nivel);
                  
        switch(opcaoMenu) {

            // Cadastra um funcionário.
            case 1:

                if (nivel == 1 || nivel == 2) {            
                    resp = cadastraFunc();

                    // Verifica se o arquivo foi aberto corretamente.
                    if(resp){
                        printf("\n\tCadastro realizado com sucesso!!!\n\n");
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                    }
                } else {
                    printf("Acesso negado!\n");
                }

            break;

            // Altera dados de um funcionário.
            case 2:

                if (nivel == 1 || nivel == 2) {  
                    pos = pesquisaFunc();
                    // Verifica se o arquivo foi aberto corretamente.
                    if (pos >= 0){
                        alteraFunc(pos);
                        printf("\n\tO registro foi alterado com sucesso!\n\n");
                    }else if(pos == -1){
                        printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                    }
                } else {
                    printf("Acesso negado!\n");
                }

            break;

            // Exclui dados de um funcionário.
            case 3:

                if (nivel == 1 || nivel == 2) { 
                    pos = pesquisaFunc();
                    // Verifica se o arquivo foi aberto corretamente.
                    if (pos >= 0){
                        consultaFunc(pos);
                        excluiFunc(pos);
                        printf("\n\tO registro foi excluido com sucesso!\n\n");
                    }else if(pos == -1){
                        printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                    }
                } else {
                    printf("Acesso negado!\n");
                }

            break;

        // Pesquisa dados de um funcionário.
        case 4:
            pos = pesquisaFunc();
            // Verifica se o arquivo foi aberto corretamente.
            if (pos >= 0){
                consultaFunc(pos);
            }else if(pos == -1){
                printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
            }else{
                printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
            }
        break;

        // Imprime todos os registros do arquivo.
        case 5:
            resp = imprimeFunc();

            // Verifica se o arquivo foi aberto corretamente.
            if(resp){
                printf("\n\tImpressao realizada com sucesso!!!\n\n");
            }else{
                printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
            }
        break;

        // Apaga fisicamente o arquivo.
        case 6:
            if (nivel == 1) { 
                excluirArquivo();
            } else {
                printf("Acesso negado!\n");
            }
        break;

        case 7:
            if (nivel == 1) { 
                restaurarBackup();
            } else {
                printf("Acesso negado!\n");
            }
        break;

        case 8:
            if (nivel == 1) { 
                realizarBackup();
            } else {
                printf("Acesso negado!\n");
            }
        break;
        case 9:
            if (nivel == 1) {
                cadastroUsers();
            } else {
                printf("Acesso negado!\n");
            }
        break;

        case 10:
            if (nivel == 1) {
                importarDados();
            } else {
                printf("Acesso negado!\n");
            }            
        break;

        case 0:
            limpaTela();
            printf("Saindo!!!\n");
            pausa();
        return 0;

        default:
            printf("\n\tOpção invalida. Digite uma das opções acima!\n\n");
        }

    } while(opcaoMenu != 0);
    
    return 0;
}

int loginUsers(){
    char user[21], pass[21];
    int verifica;
    int nivel2;

    limpaTela();
    printf("Digite seu Usuario: \n");
    scanf("%s", user);
    printf("Digite sua Senha: \n");
    scanf("%s", pass);

    verifica = leUsuarios(user,pass,&nivel2);
    if (verifica == 1){
        printf("Bem Vindo!\n");
        pausa();
        limpaTela();
        return nivel2;
    }else{
        printf("Senha Errada !!\n");
        pausa();
        limpaTela();
        loginUsers();
    }
}

void cadastroUsers(){

    login loginU;
    FILE *f = fopen("users.dat", "a+b");

    printf("Informe o nome de Usuario: \n");
    scanf("%s",loginU.usuario);

    printf("Informe a senha: \n");
    scanf("%s",loginU.senha);

    printf("Nivel de acesso 1 = Administrador - 2 = Gerente - 3 = Operador: \n");
    scanf("%d", &loginU.nivel);

    //1 = Administrador
    //2 = Gerente
    //3 = Operador

    fwrite(&loginU, sizeof(login), 1, f);
    fclose(f);

}

int leUsuarios(char user[], char pass[], int *nivel){
    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    login loginU;
    int veri=0;
    // Ponteiro para o arquivo.
    FILE *fp = fopen("users.dat", "rb");
    //printf("%s %s\n",user,pass);
    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL){
        printf("Abertura do arquivo não foi realizada com sucesso!\n"); // Operação de abertura do arquivo NÃO foi realizada com sucesso.
    }
    while (fread(&loginU, sizeof(login), 1, fp)){
        if((!strcmp(user, loginU.usuario)) && (!strcmp(pass,loginU.senha))){
            veri = 1;
            *nivel=loginU.nivel;
            return veri;
        }
    }

    veri = 0;
    return veri;

    fclose(fp);
}


/**
 * função para importar dados de arquivo TXT
 */
int importarDados() {

    char nome[21];
    char linha[80];
    dados func;

    //getchar();
    //printf("Informe o nome do arquivo TXT para a importação:\n");
    //scanf("%20[^\n]", &nome);

    // Ponteiros para os arquivos.
    FILE *fp = fopen("funcionarios.dat", "a+b");
    FILE *fi = fopen("dados-importaveis.txt", "r");

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL || fi == NULL){
        return 0; // Operação de abertura/criação do arquivo NÃO foi realizada com sucesso.
    }

    fseek(fp, 0, SEEK_END);

    // Faz a leitura dos dados a serem cadastrados.
    while (fgets(linha,sizeof(dados), fi)) {

        sscanf (strtok(linha, ";"), "%d", &func.matricula);

        //func.matricula = strtok(linha, ";");
        //func.status = strtok(NULL, ";");
        //func.nome = strtok(NULL, ";");
        //func.estadoCivil = strtok(NULL, ";");
        //func.salario = strtok(NULL, ";");

        // exibe na tela os dados dos funcionarios importados
        printf("-----------------------------------------------\n");
        printf("MATRICULA = %d\n", func.matricula);
        printf("STATUS = %d\n", func.status);
        printf("NOME = %s\n", func.nome);
        printf("ESTADO CIVIL = %c\n", func.estadoCivil);
        printf("SALARIO = %f\n", func.salario);
        
        // Grava as informações no arquivo.
        fwrite(&func, sizeof(func), 1, fp);
    }


    // Fecha os arquivos.
    fclose(fp);
    fclose(fi);

    // Operação realizada com sucesso.
    return 1;

}


// Colore a tela do programa com fundo azul e texto em amarelo.
void coloreTela(){
    if (SISTEMA == 1)
        system("COLOR 1E");
}


void limpaTela(){
    if (SISTEMA == 0)
        system("clear");
    else
        system("cls");
}


void pausa(){
    if (SISTEMA == 0)
        system("read -p \"Pressione <ENTER> para continuar...\"");
    //system("sleep 5 | echo Processando...");
    else
        system("pause");
}


void excluirArquivo(){

    char op;
    char nomeArq[] = "funcionarios.dat";
    FILE *fp = fopen(nomeArq, "r");

    if (fp == NULL){
        printf("\n\tDesculpe! O arquivo nao foi encontrado.\n");
    }else{
        getchar();
        printf("\n\tDeseja realmente excluir? (S=Sim/N=Nao): ");
        scanf("%c", &op);

        if ((op == 's') || (op == 'S')){
            remove(nomeArq);
            printf("\n\tArquivo \"%s\" excluido! :-)\n\n", nomeArq);
        }
    }
}

int realizarBackup(){

    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;
    int tam;

    // Ponteiros paras os arquivos.
    FILE *fp = fopen("funcionarios.dat", "rb");
    FILE *fbkp = fopen("funcionarios_bkp.dat", "wb+");

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL){
        printf("Arquivo de funcionarios nao existe!\n");
        return 0; // Operação de abertura do arquivo NÃO foi realizada com sucesso.
    }

    fseek(fp, 0, SEEK_END);
    tam = ftell(fp);
    rewind(fp);
    
    if(tam == 0){
      printf("Arquivo de funcionarios vazio!\n");
      return 0;
    }    

    while(fread(&func, sizeof(dados), 1, fp)) {
        fwrite(&func, sizeof(dados), 1, fbkp);
    }

    rewind(fbkp);
    fseek(fbkp, 0, SEEK_END);

    if(ftell(fbkp) == 0) {
        printf("Erro ao realizar backup!\n");  
        return 0;     
    }

    fclose(fp);
    fclose(fbkp);

    return 1;
}



void restaurarBackup(){

    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;
    int tam;
    char nomeArq[] = "funcionarios_bkp.dat";
    // Ponteiro para o arquivo.
    FILE *fbkp = fopen(nomeArq, "rb");

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fbkp == NULL){
      printf("Arquivo de backup nao existe!\n");
        return; // Operação de abertura do arquivo NÃO foi realizada com sucesso.
    }

    tam = ftell(fbkp);

    if(tam == 0){
      printf("Arquivo de Backup vazio!\n");
      return;
    }
    FILE *fp = fopen("funcionarios.dat", "wb");

    while (fread(&func, sizeof(func), 1, fbkp))
        fwrite(&func, sizeof(func), 1, fp);

    tam = ftell(fp);

    if(tam == 0)
      printf("Erro ao realizar a restauracao!\n");
      else
        printf("Restauracao realizada com sucesso!\n");

    fclose(fbkp);
    fclose(fp);

}

// Monta o menu de opções.
int menu(int *nivel) {

    int opcao;

    coloreTela();

    if (*nivel == 1) {
        printf("\n\tMenu de Opcoes Sistema Lava Autos - Administrador");
        printf("\n\t\t 1 - Cadastrar");
        printf("\n\t\t 2 - Alterar");
        printf("\n\t\t 3 - Excluir");
        printf("\n\t\t 4 - Pesquisar");
        printf("\n\t\t 5 - Imprimir Arquivo");
        printf("\n\t\t 6 - Apagar Arquivo");
        printf("\n\t\t 7 - Restaurar Backup");
        printf("\n\t\t 8 - Realizar Backup");
        printf("\n\t\t 9 - Cadastrar Usuarios");
        printf("\n\t\t10- Importar dados");
        printf("\n\t\t 0 - Sair");
    } else if (*nivel == 2) {
        printf("\n\tMenu de Opcoes Sistema Lava Autos - Gerente");
        printf("\n\t\t 1 - Cadastrar");
        printf("\n\t\t 2 - Alterar");
        printf("\n\t\t 3 - Excluir");
        printf("\n\t\t 4 - Pesquisar");
        printf("\n\t\t 5 - Imprimir Arquivo");
        printf("\n\t\t 0 - Sair");
    } else {
        printf("\n\tMenu de Opcoes Sistema Lava Autos - Operador");
        printf("\n\t\t 4 - Pesquisar");
        printf("\n\t\t 5 - Imprimir Arquivo");
        printf("\n\t\t 0 - Sair");
    }
    
    printf("\n\tDigite a opcao desejada: ");
    scanf("%d", &opcao);

    limpaTela();

    return opcao;
}

// Abre o arquivo de funcionários, de acordo com o modo recebido como parâmetro.
FILE *abrirArquivo(char *modo){
    FILE *fp = fopen("funcionarios.dat", modo);
    return fp;
}

// Cadastra um registro de funcionário.
int cadastraFunc(){
    // Declaração da variável do tipo registro.
    dados func;

    // Ponteiro para o arquivo.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "a+b";

    // Abre o arquivo binário para leitura e gravação.
    fp = abrirArquivo(modo);

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL){
        return 0; // Operação de abertura/criação do arquivo NÃO foi realizada com sucesso.
    }

    // Faz a leitura dos dados a serem cadastrados.
    leDadosFunc(&func);

    // Grava as informações no arquivo.
    fwrite(&func, sizeof(func), 1, fp);

    // Fecha o arquivo.
    fclose(fp);

    // Operação realizada com sucesso.
    return 1;
}

// Função que lê os dados do usuário para serem gravados no arquivo.
void leDadosFunc(dados *funcLe){
    // Lendo informações de um funcionário.
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

// Função que imprime os dados de todos os funcionários cadastrados.
int imprimeFunc(){
    // Variável que conta o número de registros.
    int qtdeReg = 0;

    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;

    // Ponteiro para o arquivo.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "rb";

    // Abre o arquivo binário para leitura.
    fp = abrirArquivo(modo);

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL){
        return 0; // Operação de abertura do arquivo NÃO foi realizada com sucesso.
    }

    // Lê as informações do arquivo, para inicializar o laço.
    fread(&func, sizeof(func), 1, fp);

    // Laço de leitura do arquivo. Pode-se usar o do..while também!
    while(!feof(fp)){
        if(func.status == 1){
            // Imprime as informações dos registros ativos no sistema.
            printf("\n\n\t###### Dados do %do funcionario ######", ++qtdeReg);
            printf("\n\t\tMatricula: %d", func.matricula);
            printf("\n\t\tNome: %s", func.nome);
            printf("\n\t\tEstado civil: %c", func.estadoCivil);
            printf("\n\t\tSalario: %0.2f\n\n", func.salario);
        }

        // Lê as informações do próximo registro no arquivo, enquanto não se chegar ao final do arquivo.
        fread(&func, sizeof(func), 1, fp);
    }

    // Fecha o arquivo após as operações.
    fclose(fp);

    // Operação realizada com sucesso.
    return 1;
}

// Função que pesquisa, por nome, se existe o registro de determinado funcionário no arquivo.
int pesquisaFunc(){
    // Variável auxiliar que indica se o registro procurado existe no arquivo.
    int achou = -1;

    // Variável que armazena a posição do registro procurado dentro do arquivo.
    int posRegFunc = 0;

    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;

    // Variável auxiliar que recebe o nome a ser pesquisado no arquivo.
    char nomeAux[51];

    // Ponteiro para o arquivo físico.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "rb";

    // Abre o arquivo binário para leitura.
    fp = abrirArquivo(modo);

    // Verifica se o arquivo foi aberto corretamente. Caso negativo, sai da função.
    if(fp == NULL){
        return 0; // Operação de abertura do arquivo NÃO foi realizada com sucesso.
    }

    // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
    getchar();
    printf("\n\tDigite o nome do funcionario a ser pesquisado: ");
    scanf("%50[^\n]s", nomeAux);
    //gets(nomeAux); (DEPRECATED)

    // Lê as informações do arquivo, para inicializar o laço.
    fread(&func, sizeof(func), 1, fp);

    // Laço de leitura do arquivo.
    while(!feof(fp) && (achou == -1)){
        if( (strcmp(func.nome, nomeAux) == 0) && (func.status == 1) ){
            achou = 1;
        }

        // Lê as informações do próximo registro no arquivo.
        fread(&func, sizeof(func), 1, fp);

        if(achou == -1){
            posRegFunc++;
        }
    }

    if(achou == -1){
        return -1;
    }

    // Fecha o arquivo após as operações.
    fclose(fp);

    // Retorna a posição do registro procurado no arquivo.
    return posRegFunc;
}

// Função que imprime os dados de um registro que foi consultado e existe no arquivo.
void consultaFunc(int posRegFunc){
    // Variável que conta o número de registros.
    int qtdeReg = 0;

    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;

    // Ponteiro para o arquivo físico.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "r+b";

    // Abre o arquivo binário para leitura.
    fp = abrirArquivo(modo);

    // Acessa o registro específico, com base na posição recebida pela função.
    fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

    // Lê as informações do arquivo, para inicializar o laço.
    fread(&func, sizeof(func), 1, fp);

    // Imprime as informações do registro pesquisado.
    printf("\n\t###### Dados do funcionario pesquisado ######");
    printf("\n\t\tMatricula: %d", func.matricula);
    printf("\n\t\tNome: %s", func.nome);
    printf("\n\t\tEstado civil: %c", func.estadoCivil);
    printf("\n\t\tSalario: %0.2f\n\n", func.salario);

    // Fecha o arquivo após as operações.
    fclose(fp);
}

// Função que permite alterar os dados de um registro do arquivo.
void alteraFunc(int posRegFunc){
    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;

    // Ponteiro para o arquivo físico.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "r+b";

    // Abre o arquivo binário para leitura e escrita.
    fp = abrirArquivo(modo);

    // Acessa o registro específico, com base na posição recebida pela função.
    fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

    // Lê as informações do registro a ser alterado.
    fread(&func, sizeof(func), 1, fp);

    // Função auxiliar que realiza as alterações no registro.
    confirmaAlteracoes(&func);

    // Acessa o registro específico, para atualizá-lo.
    fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

    // Grava as informações do registro após as alterações.
    fwrite(&func, sizeof(func), 1, fp);

    // Fecha o arquivo após as operações.
    fclose(fp);
}

// Função que lê do usuários os campos a serem alterados.
void confirmaAlteracoes(dados *func){
    // Variável auxiliar para confirmar alteração de cada campo.
    char op;

    // Imprime as informações do registro pesquisado.
    printf("\n\t###### Dados do funcionario a serem alterados ######");
    printf("\n\tMatricula atual: %d", func->matricula);
    getchar();
    printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
    scanf("%c", &op);

    if((op == 's') || (op == 'S')){
        printf("\tDigite a nova matricula: ");
        scanf("%d", &func->matricula); // Altera a matrícula do funcionário.
    }

    getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
    printf("\n\tNome atual: %s", func->nome);
    printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
    scanf("%c", &op);

    if((op == 's') || (op == 'S')){
        getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
        printf("\tDigite o novo nome: ");
        scanf("%50[^\n]s", func->nome); // Altera o nome do funcionário.
        // gets(func->nome); (DEPRECATED)
    }

    printf("\n\tEstado civil atual: %c", func->estadoCivil);
    printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
    getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
    scanf("%c", &op);

    if((op == 's') || (op == 'S')){
        getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
        printf("\tDigite o novo estado civil: ");
        scanf("%c", &func->estadoCivil); // Altera o estado civil do funcionário.
    }

    printf("\n\tSalario atual: %0.2f", func->salario);
    printf("\n\tDeseja alterar? (S=Sim/N=Nao): ");
    getchar(); // Limpa o buffer do teclado para evitar "saltos" na leitura de dados.
    scanf("%c", &op);

    if((op == 's') || (op == 'S')){
        printf("\tDigite o novo salario: ");
        scanf("%f", &func->salario); // Altera o salário do funcionário.
    }
}

// Função que altera o valor do campo status para zero ("exclui")
void excluiFunc(int posRegFunc){
    // Variável do tipo registro que recebe os dados de cada funcionário, gravados no arquivo.
    dados func;

    // Ponteiro para o arquivo físico.
    FILE *fp;

    // Define o modo de abertura do arquivo.
    char modo[] = "r+b";

    // Abre o arquivo binário para leitura e escrita.
    fp = abrirArquivo(modo);

    // Acessa o registro específico, com base na posição recebida pela função.
    fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

    // Lê as informações do registro a ser alterado.
    fread(&func, sizeof(func), 1, fp);

    // Altera o campo status para zero, "excluindo" o registro.
    func.status = 0;

    // Acessa o registro específico, para atualizá-lo.
    fseek(fp, posRegFunc * sizeof(func), SEEK_SET);

    // Grava as informações do registro após as alterações.
    fwrite(&func, sizeof(func), 1, fp);

    // Fecha o arquivo após as operações.
    fclose(fp);
}
