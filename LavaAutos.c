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
 *	- Proprietario
 *	- Gerente
 *	- Operador
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "LavaAutos.h"


/*
 * Constante DESENVOLVIMENTO declarada para verificar se o sistema está em fase de desenvolvimento.
 * Usa-se 0 para falso e 1 para verdadeiro
 * Ex.: #define DESENVOLVIMENTO 1 // projeto em fase de desenvolvimento
 */
#define DESENVOLVIMENTO 1


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
                        pausa();
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                        pausa();
                    }
                } else {
                    printf("Acesso negado!\n");
                    pausa();
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
                        pausa();
                    }else if(pos == -1){
                        printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
                        pausa();
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                        pausa();
                    }
                } else {
                    printf("Acesso negado!\n");
                    pausa();
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
                        pausa();
                    }else if(pos == -1){
                        printf("\n\tNao foi encontrado o funcionario no arquivo!\n\n");
                        pausa();
                    }else{
                        printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                        pausa();
                    }
                } else {
                    printf("Acesso negado!\n");
                    pausa();
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
                pausa();
            }else{
                printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                pausa();
            }
        break;

        // Imprime todos os registros do arquivo.
        case 5:
            resp = imprimeFunc();

            // Verifica se o arquivo foi aberto corretamente.
            if(resp){
                printf("\n\tImpressao realizada com sucesso!!!\n\n");
                pausa();
            }else{
                printf("\n\tErro ao abrir o arquivo! Verifique as configuracoes do arquivo!\n\n");
                pausa();
            }
        break;

        // Apaga fisicamente o arquivo.
        case 6:
            if (nivel == 1) {
                excluirArquivo();
            } else {
                printf("Acesso negado!\n");
                pausa();
            }
        break;

        case 7:
            if (nivel == 1) {
                restaurarBackup();
            } else {
                printf("Acesso negado!\n");
                pausa();
            }
        break;

        case 8:
            if (nivel == 1) {
                realizarBackup();
            } else {
                printf("Acesso negado!\n");
                pausa();
            }
        break;
        case 9:
            if (nivel == 1) {
                cadastroUsers();
            } else {
                printf("Acesso negado!\n");
                pausa();
            }
        break;

        case 10:
            if (nivel == 1) {
                importarDados();
            } else {
                printf("Acesso negado!\n");
                pausa();
            }
        break;

        case 0:
            limpaTela();
            printf("Saindo!!!\n");
            pausa();
        return 0;

        default:
            printf("\n\tOpção invalida. Digite uma das opções acima!\n\n");
            pausa();
        }

    } while(opcaoMenu != 0);

    return 0;
}
