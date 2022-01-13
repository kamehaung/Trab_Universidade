#ifndef FUNCOES
#define FUNCOES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

#define MAX_CARTA 52    // quantidade de cartas no total
#define MAX_NUM 13      // quantidade de cartas de cada tipo
#define MAX_NAIPE 4     // quantidade naipes
#define MAX_AUX 4       // quantidade de espacos auxiliares
#define MAX_COLUNA 8    // quantidade de colunas


//funções relacionadas ao baralho

//struct de carta 
typedef struct carta{
    char naipe;		//naipe da carta
    char letra;		//letra valor que a carta recebe, se for letra
    int num; 	//numeração da carta de 1 a 13
    int cor;	//cor da carta
}Carta;

//struct de nó para pilha
typedef struct node{
    Carta *carta;
    struct node *prox;
}Node;

//struct de pilha
typedef struct pilha{
    struct node *topo;
}Pilha;

//struct da mesa
typedef struct mesa{
    Pilha *col[MAX_COLUNA];  //pilhas para mover
    Pilha *base[MAX_NAIPE];  //células base para por as cartas
    Pilha *temp[MAX_AUX];    //células temporarias para auxiliar
}Mesa;

//Aloca memória e seta elementos da pilha como null
//Entrada: nenhuma
//Retorno: pilha
//Pré-Condições: nenhuma
//Pós-Condições: memória alocada e topo da pilha setada
Pilha *criar_pilha();

//Colocar o valor, o naipe, a cor e o numero do naipe
//Entrada: valor e naipe da carta
//Retorno: carta criada com todos os atributos preenchidos
//Pré-Condições: nenhuma
//Pós-Condições: carta criada
Carta *criar_carta(int num, char naipe);

//Troca a posição da carta no vetor
//Entrada: vetor de cartas
//Retorno: nenhum
//Pré-Condições: existe 52 cartas
//Pós-Condições: posição do carta trocada
void embaralhar(Carta *c[]);

//Insere elemento no início da pilha
//Entrada: carta e topo da pilha atual
//Retorno: pilha atualizada
//Pré-Condições: existe carta
//Pós-Condições: pilha com o elemento inserido
Node *inserir(Carta *c, Node *n);

//Embaralha o vetor de cartas e coloca em uma lista
//Entrada: nenhuma
//Retorno: lista embaralhada
//Pré-Condições: nenhuma
//Pós-Condições: lista embaralhada criada
Node *criar_baralho_mix();

//Aloca memória e inicia elementos da mesa
//Entrada: nenhum
//Retorno: mesa com os elementos iniciados
//Pré-Condições: nenhuma
//Pós-Condições: topo das pilhas da mesa setados
Mesa *criar_mesa();

//Remove o primeiro elemento da lista
//Entrada: lista de elementos
//Retorno: nova lista sem o elemento
//Pré-Condições: existe elemento para ser removido
//Pós-Condições: nó removido
Node *remover_carta(Node *n);

//Divide a lista de elementos em 8 pilhas
//Entrada: lista e nó
//Retorno: nenhum
//Pré-Condições: lista deve ter as 52 cartas
//Pós-Condições: lista dividida em pilhas
void dividir_pilhas(Node *n, Mesa *jogo);

//Chama as funções para criar o baralho e dividir em pilhas
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: mesa com a memória para pilha alocada
//Pós-Condições: jogo criado e mesa posta
void por_mesa(Mesa *jogo);

//Inverte a lista
//Entrada: topo da pilha
//Retorno: retorna uma lista invertida
//Pré-Condições: existe pilha com elementos
//Pós-Condições: lista foi invetida
Node *inverter(Node *n);

//Libera todos os elementos
//Entrada: primeiro elemento da lista
//Retorno: nenhum
//Pré-Condições: nó possui memória alocada
//Pós-Condições: lista desalocada
void liberar(Node *n);

//Imprime a carta
//Entrada: carta a ser impressa
//Retorno: nenhum
//Pré-Condições: carta com os elementos com valores
//Pós-Condições: carta impresso no console
void imprime_carta(Carta *c);

//Imprime o primeiro elemento da pilha
//Entrada: pilha
//Retorno: nenhum
//Pré-Condições: nenhum
//Pós-Condições: topo da pilha impressa no console
void imprime_topo(Pilha *p);

//Imprime elementos da base e das células temporárias
//Entrada: mesa de jogo
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: base e células temporárias impressas no console
void imprime_BaseTemp(Mesa *jogo);

//Imprime as colunas do jogo
//Entrada: vetor de ponteiros de nós
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: colunas impressas no console, se for nula imprime espaço em branco
void imprime_colunas(Node *aux[]);

//Inverte as colunas e chama função para imprimir as colunas
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: o topo das pilhas de coluna apontam para algum valor
//Pós-Condições: colunas impressas no console
void imprime_corpo(Mesa *jogo);

//Imprime os elementos da mesa
//Entrada: mesa de jogo
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: elementos de mesa impresso
void imprime_mesa(Mesa *jogo);

//Verifica se os naipes das cartas são iguais
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int naipe_igual(Node *orig, Node *dest);

//Verifica se a cor das cartas são iguais
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int cor_igual(Node *orig, Node *dest);

//Verifica se o número da carta origem é um a mais que a de destino
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int um_a_mais(Node *orig, Node *dest);

//Verifica se o número da carta origem é um a menos que a de destino
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int um_a_menos(Node *orig, Node *dest);

//Verifica se o nó é nulo 
//Entrada: nó
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nenhuma
//Pós-Condições: nenhuma
int no_nulo(Node *n);

//Verifica se origem não é nulo, se destino é nulo e se as cores são iguais
//Entrada: nó origem e nó destino
//Retorno: 1 para origem não nulo, 0 para destino nulo e 1 para cores iguais
//Pré-Condições: nenhuma
//Pós-Condições: nenhuma
int teste(Node *orig, Node *dest);

//Mover para uma coluna
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para outra coluna
void para_col(Mesa *jogo, char cmdOrig, int celOrig, int celDest);

//Mover para uma base
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para base
void para_base(Mesa *jogo, char cmdOrig,int celOrig, int celDest);

//Mover para uma célula temporária
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para célula temporária
void para_cel_temp(Mesa *jogo, char cmdOrig, int celOrig, int celDest);


//funções relacionadas ao main

//Chama funções para criar a mesa, por a mesa e iniciar o jogo
//Entrada: nenhuma
//Retorno: nenhuma
//Pré-Condições: nenhuma
//Pós-Condições: inicia jogo
void novo_jogo();

//Chama para imprimir a mesa e verifica comando para encerrar ou continuar
//Entrada: mesa do jogo
//Retorno: nenhuma
//Pré-Condições: mesa do jogo com os elementos com valores
//Pós-Condições: loop até que controle seja um valor nulo
void iniciar_jogo(Mesa *jogo);

//Verifica se o comando é válido
//Entrada: um char, o tipo de origem do movimento
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: cmdOrig com valor
//Pós-Condições: nenhuma
int tipoCmd(char cmdOrig);

//Lê o tipo de célula origem e direciona para um caso
//Entrada: mesa do jogo
//Retorno: 1 para verdadeiro, continua jogo e 0 para falso, encerra jogo
//Pré-Condições: mesa com valores setados
//Pós-Condições: nenhuma
int comando(Mesa *jogo);

//Lê a posição de origem, o tipo de célula e posição de destino
//Entrada: mesa de jogo, tipo de célula origem
//Retorno: nenhum
//Pré-Condições: cmdOrig com valor válido
//Pós-Condições: direciona ao caso de destino, se é base, coluna ou célula temporária
void mover_para(Mesa *jogo, char cmdOrig);

//Verifica quantidade de nós
//Entrada: topo de uma pilha
//Retorno: quantidade de nós
//Pré-Condições: nenhuma
//Pós-Condições: quantidade de nós retornada
int verifica_tamanho(Node *n);

//Salva os elementos da pilha
//Entrada: pilha e arquivo
//Retorno: nenhum
//Pré-Condições: arquivo existe
//Pós-Condições: pilha salva
void salvar_pilha(Pilha *p, FILE *arq);

//Salva a mesa do jogo
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: arquivo existe, caso contrário cria
//Pós-Condições: jogo salvo
void salvar(Mesa *jogo);

//Carrega os elementos em pilha do arquivo
//Entrada: pilha, arquivo
//Retorno: nenhum
//Pré-Condições: arquivo existe
//Pós-Condições: pilha carregada
void carregar_pilha(Pilha *p, FILE *arq);

//Carrega as pilhas do jogo no arquivo
//Entrada: nenhuma
//Retorno: nenhum
//Pré-Condições: arquivo existe, caso contrário inicia novo jogo
//Pós-Condições: mesa de jogo carregada
void carregar_jogo(char const *nome_arq);

//Verifica se as bases estão preenchidas
//Entrada: mesa do jogo
//Retorno: inteiro 1 ou 0
//Pré-Condições: nenhuma
//Pós-Condições: se o total de cartas nas bases for 52 retorna 0, caso contrário retorna 1
int cond_vitoria(Mesa *jogo);

#endif // FUNCOES