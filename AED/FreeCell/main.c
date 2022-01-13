#include "funcoes.h"
#include "freeCell.c"

int main(int argc,char *argv[]){

    setlocale(LC_ALL, "Portuguese");

    if(argc > 1)
        carregar_jogo(argv[1]);
    else
        novo_jogo();
    return 0;
}

//Chama funções para criar a mesa, por a mesa e iniciar o jogo
//Entrada: nenhuma
//Retorno: nenhuma
//Pré-Condições: nenhuma
//Pós-Condições: inicia jogo
void novo_jogo(){
    Mesa *jogo = criar_mesa();
    por_mesa(jogo);
    iniciar_jogo(jogo);
}

//Chama para imprimir a mesa e verifica comando para encerrar ou continuar
//Entrada: mesa do jogo
//Retorno: nenhuma
//Pré-Condições: mesa do jogo com os elementos com valores
//Pós-Condições: loop até que controle seja um valor nulo
void iniciar_jogo(Mesa *jogo){
    int controle = 1;
    while(controle){
        system("cls");
        imprime_mesa(jogo);
        controle = comando(jogo);
    }
}

//Verifica se o comando é válido
//Entrada: um char, o tipo de origem do movimento
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: cmdOrig com valor
//Pós-Condições: nenhuma
int tipoCmd(char cmdOrig){
    if(cmdOrig == 'T' || cmdOrig == 't')
        return 1;
    else if(cmdOrig == 'C'||cmdOrig == 'c')
        return 1;
    else if(cmdOrig == 'Q' || cmdOrig == 'q')
        return 1;
    else if(cmdOrig == 'B' || cmdOrig == 'b')
        return 1;
    else if(cmdOrig == 'S'|| cmdOrig == 's')
        return 1;
    else return 0;
}

//Lê o tipo de célula origem e direciona para um caso
//Entrada: mesa do jogo
//Retorno: 1 para verdadeiro, continua jogo; 0 para falso, encerra jogo
//Pré-Condições: mesa com valores setados
//Pós-Condições: nenhuma
int comando(Mesa *jogo){
    char cmdOrig, resp;
    int tipo;
    printf("Digite de onde deseja mover ou fazer: (Ex: C2, T1, Q - sair, S - salvar)\n");
    fflush(stdin);
    scanf("%c", &cmdOrig);

    //fica no loop até que o tipo seja válido
    while(!(tipo = tipoCmd(cmdOrig))){
        fflush(stdin);
        printf("Digite movimento válido.\n");
        scanf("%c", &cmdOrig);
    }

    switch(cmdOrig){
    case 'C': case 'c':
        mover_para(jogo, cmdOrig);
        break;
    case 'T': case 't':
        mover_para(jogo, cmdOrig);
        break;
    case 'S': case 's':
        salvar(jogo);
        printf("Deseja continuar? S/N\n");
        fflush(stdin);
        scanf("%c", &resp);
        switch(resp){
        case 'S': case 's':
            break;
        case 'N': case'n':
            return 0;
        }
        break;
    case 'Q': case 'q':
        printf("Deseja salvar? S/N\n");
        fflush(stdin);
        scanf("%c", &resp);
        switch(resp){
        case 'S': case 's':
            salvar(jogo);
            return 0;
        case 'N': case'n':
            return 0;
        }
    }
    return cond_vitoria(jogo);
}

//Lê a posição de origem, o tipo de célula e posição de destino
//Entrada: mesa de jogo, tipo de célula origem
//Retorno: nenhum
//Pré-Condições: cmdOrig com valor válido
//Pós-Condições: direciona ao caso de destino, se é base, coluna ou célula temporária
void mover_para(Mesa *jogo, char cmdOrig){
    char cmdDest;
    int celOrig, celDest, tipo;
    scanf("%d",&celOrig);
    printf("Para onde deseja mover? (Ex: C5, B1, T2)\n");
    fflush(stdin);
    scanf("%c", &cmdDest);
    scanf("%d", &celDest);

    while(!(tipo = tipoCmd(cmdDest))){
        fflush(stdin);
        printf("Digite ação válida\n");
        scanf("%c", &cmdDest);
    }

    switch(cmdDest){
    case 'c': case 'C':
        para_col(jogo, cmdOrig, celOrig, celDest);
        break;
    case 'b': case 'B':
        para_base(jogo, cmdOrig, celOrig, celDest);
        break;
    case 't': case 'T':
        para_cel_temp(jogo, cmdOrig, celOrig, celDest);
        break;
    default:
        break;
    }
}

//Verifica quantidade de nós
//Entrada: topo de uma pilha
//Retorno: quantidade de nós
//Pré-Condições: nenhuma
//Pós-Condições: quantidade de nós retornada
int verifica_tamanho(Node *n){
    if(!n)
        return 0;
    return 1 + verifica_tamanho(n->prox);
}

//Salva os elementos da pilha
//Entrada: pilha e arquivo
//Retorno: nenhum
//Pré-Condições: arquivo existe
//Pós-Condições: pilha salva
void salvar_pilha(Pilha *p, FILE *arq){
    int tam, i;
    Node * aux = inverter(p->topo);
    tam = verifica_tamanho(p->topo);
    fwrite(&tam, sizeof(int), 1, arq);
    while(aux){
        fwrite(aux->carta, sizeof(Carta), 1, arq);
        aux = aux->prox;
    }
    liberar(aux);
}

//Salva a mesa do jogo
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: arquivo existe, caso contrário cria
//Pós-Condições: jogo salvo
void salvar(Mesa *jogo){
    int i;
    char nome_arq[255];
    printf("Digite o nome do arquivo para salvar\n");
    scanf("%s", nome_arq);
    FILE *arq = fopen(nome_arq, "wb+");
    for(i = 0; i < MAX_AUX; i++){
        salvar_pilha(jogo->temp[i], arq);
    }
    for(i = 0; i < MAX_NAIPE; i++){
        salvar_pilha(jogo->base[i], arq);
    }
    for(i = 0; i < MAX_COLUNA; i++){
        salvar_pilha(jogo->col[i], arq);
    }
    fclose(arq);
}

//Carrega os elementos em pilha do arquivo
//Entrada: pilha, arquivo
//Retorno: nenhum
//Pré-Condições: arquivo existe
//Pós-Condições: pilha carregada
void carregar_pilha(Pilha *p, FILE *arq){
    int tam, i;
    fread(&tam, sizeof(int), 1, arq);

    for(i = 0; i < tam; i++){
        Carta *c = (Carta*)malloc(sizeof(Carta));
        fread(c, sizeof(Carta), 1, arq);
        p->topo = inserir(c, p->topo);
    }
}

//Carrega as pilhas do jogo no arquivo
//Entrada: nenhuma
//Retorno: nenhum
//Pré-Condições: arquivo existe, caso contrário inicia novo jogo
//Pós-Condições: mesa de jogo carregada
void carregar_jogo(char const *nome_arq){
    int i;
    Mesa *jogo = criar_mesa();
    FILE *arq = fopen(nome_arq, "rb+");
   
    if(!arq){
        printf("Não há jogo salvo. Iniciando novo...\n");
        system("pause");
        return novo_jogo();
    }

    for(i = 0; i < MAX_AUX; i++){
        carregar_pilha(jogo->temp[i], arq);
    }
    for(i = 0; i < MAX_NAIPE; i++){
        carregar_pilha(jogo->base[i], arq);
    }
    for(i = 0; i < MAX_COLUNA; i++){
        carregar_pilha(jogo->col[i], arq);
    }
    fclose(arq);
    iniciar_jogo(jogo);
}

//Verifica se as bases estão preenchidas
//Entrada: mesa do jogo
//Retorno: inteiro 1 ou 0
//Pré-Condições: nenhuma
//Pós-Condições: se o total de cartas nas bases for 52 retorna 0 e encerra o jogo, caso contrário retorna 1
int cond_vitoria(Mesa *jogo){
    int ponto = 0, tam, i;
    for(i = 0; i < MAX_COLUNA; i++){
        tam = verifica_tamanho(jogo->base[i]->topo);
        ponto += tam;
    }
    if(ponto == MAX_CARTA){
        printf("Parabéns! Você ganhou!\n");
        return 0;
    }
    return 1;
}