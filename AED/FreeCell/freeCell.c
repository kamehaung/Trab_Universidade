#include "funcoes.h"

//Aloca memória e seta elementos da pilha como null
//Entrada: nenhuma
//Retorno: pilha
//Pré-Condições: nenhuma
//Pós-Condições: memória alocada e topo da pilha setada
Pilha *criar_pilha(){
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

//Colocar o valor, o naipe, a cor e o número do naipe
//Entrada: número e naipe da carta
//Retorno: carta criada com todos os atributos preenchidos
//Pré-Condições: nenhuma
//Pós-Condições: carta criada
Carta *criar_carta(int num, char naipe){
    Carta *aux = (Carta*)malloc(sizeof(Carta));
    aux->num = num; 
    aux->naipe = naipe;

    //dependendo do valor de num, as cartas recebem uma letra
    switch(num){
    case 1:
        aux->letra = 'A';
        break;
    case 11:
        aux->letra = 'J';
        break;
    case 12:
        aux->letra = 'Q';
        break;
    case 13:
        aux->letra = 'K';
        break;
    //qualquer outro numero além de 1, 11, 12, 13 recebe 0 como valor
    default:
        aux->letra = 0;
        break;
    }

    //se for O ou C, cor recebe 0 para vermelho
    if(aux->naipe == 'O' || aux->naipe == 'C'){
        aux->cor = 0;  
    }
    //caso contrário, cor recebe 1 para preto
    else{
        aux->cor = 1;
    }

    return aux;
}

//Troca a posição da carta no vetor
//Entrada: vetor de cartas
//Retorno: nenhum
//Pré-Condições: existe 52 cartas
//Pós-Condições: posição da carta trocada
void embaralhar(Carta *c[]){
    int i;
    //seed para função rand(), troca de acordo com o tempo
    srand(time(NULL));

    for (i = 0; i < MAX_CARTA; i++){
        // r recebe o valor aleatório gerado pela função rand()
        int r = rand() % (MAX_CARTA);
        Carta *aux = c[i];
        c[i] = c[r];
        c[r] = aux;
    }
}

//Insere elemento no início da pilha
//Entrada: carta e topo da pilha atual
//Retorno: pilha atualizada
//Pré-Condições: existe carta
//Pós-Condições: pilha com o elemento inserido
Node *inserir(Carta *c, Node *n){
    Node *aux = (Node*)malloc(sizeof(Node));
    aux->carta = c;
    aux->prox = n;
    return aux;
}

//Embaralha o vetor de cartas e coloca em uma lista
//Entrada: nenhuma
//Retorno: lista embaralhada
//Pré-Condições: nenhuma
//Pós-Condições: lista embaralhada criada
Node *criar_baralho_mix(){
    int i, j;
    //vetor com os numeros de carta
    int numeros[MAX_NUM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    //vetor com os existentes naipes
    char naipes[MAX_NAIPE] = {'O', 'P', 'C', 'E'};
    Node *no = NULL;
    Carta *aux[MAX_CARTA];

    for(i = 0, j = 0; i < MAX_CARTA; i++, j++){
        //j é um contador que alterna o valor do naipe,
        //j zera quando chega no 4, o vetor naipes não possui mais de 4 valores
        if(j == 4) j = 0;
        //cria a cartas, variando com o i
        aux[i] = criar_carta(numeros[i % MAX_NUM], naipes[j]);
    }

    embaralhar(aux);

    //coloca as cartas em uma lista de nós
    for(i = 0; i < MAX_CARTA; i++){
        no = inserir(aux[i], no);
    }

    return no;
}

//Aloca memória e inicia elementos da mesa
//Entrada: nenhum
//Retorno: mesa com os elementos iniciados
//Pré-Condições: nenhuma
//Pós-Condições: topo das pilhas da mesa setados
Mesa *criar_mesa(){
    int i;
    Mesa *mesa = (Mesa*)malloc(sizeof(Mesa));

    for(i = 0; i < MAX_AUX; i++){
        mesa->base[i] = criar_pilha();
        mesa->temp[i] = criar_pilha();
        mesa->col[i] = criar_pilha();
        mesa->col[i+4] = criar_pilha();
    }

    return mesa;
}

//Remove o primeiro elemento da lista
//Entrada: lista de elementos
//Retorno: nova lista sem o elemento
//Pré-Condições: existe elemento para ser removido
//Pós-Condições: nó removido
Node *remover_carta(Node *n){
    Node *aux = n;
    //n recebe próximo nó da lista
    n = n->prox;
    free(aux);

    return n;
}

//Divide a lista de elementos em 8 pilhas
//Entrada: lista e nó
//Retorno: nenhum
//Pré-Condições: lista deve ter as 52 cartas
//Pós-Condições: lista dividida em pilhas
void dividir_pilhas(Node *n, Mesa *jogo){
    int i = 0, j;
    while(i < MAX_COLUNA){
        Node *no = NULL;
        //cria as 4 últimas colunas
        if(i >= 4){
            for(j = 0; j < MAX_COLUNA-2; j++){
                no = inserir(n->carta, no);
                jogo->col[i]->topo = no;
                if(n != NULL){
                    n = remover_carta(n);
                }
            }
        }
        //cria as 4 primeiras colunas
        else{
            for(j = 0; j < MAX_COLUNA-1; j++){
                no = inserir(n->carta, no);
                jogo->col[i]->topo = no;
                n = remover_carta(n);
            }
        }
        i++;
    }
}

//Chama as funções para criar o baralho e dividir em pilhas
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: mesa com a memória para pilha alocada
//Pós-Condições: jogo criado e mesa posta
void por_mesa(Mesa *jogo){
    //cartas recebe uma lista com todas as 52 cartas
    Node *cartas = criar_baralho_mix();
    dividir_pilhas(cartas, jogo);
}


//Inverte a lista
//Entrada: topo da pilha
//Retorno: retorna uma lista invertida
//Pré-Condições: existe pilha com elementos
//Pós-Condições: lista foi invetida
Node *inverter(Node *n){
    int i;
    Node *aux = NULL;
    for (i = 0; n; i++){
        aux = inserir(n->carta, aux);
        n = n->prox;
    }
    return aux;
}

//Libera todos os elementos
//Entrada: primeiro elemento da lista
//Retorno: nenhum
//Pré-Condições: nó possui memória alocada
//Pós-Condições: lista desalocada
void liberar(Node *n){
    if(n){
        liberar(n->prox);
        free(n);
    }
}

//Imprime a carta
//Entrada: carta a ser impressa
//Retorno: nenhum
//Pré-Condições: carta com os elementos com valores
//Pós-Condições: carta impresso no console
void imprime_carta(Carta *c){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO infoCons;
    WORD atrib_salvo;
    //pega os atributos do console atual
    GetConsoleScreenBufferInfo(hConsole, &infoCons);
    //salva atributos
    atrib_salvo = infoCons.wAttributes;

    //muda a cor a ser impresso para vermelho se a variável cor for 0
    if (!c->cor)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    
    //se a variável letra possui valor
    if(c->letra){
        printf("[%c %c] \t", c->letra, c->naipe);
    //se variável letra for igual a 0
    }
    else{
        printf("[%d %c] \t", c->num, c->naipe);
    }

    //volta aos atributos originais do console
    SetConsoleTextAttribute(hConsole, atrib_salvo);
}

//Imprime o primeiro elemento da pilha
//Entrada: pilha
//Retorno: nenhum
//Pré-Condições: nenhum
//Pós-Condições: topo da pilha impressa no console
void imprime_topo(Pilha *p){
    if(!p->topo){
        printf("[   ] \t");
    }
    else{
        imprime_carta(p->topo->carta);
    }
}

//Imprime elementos da base e das células temporárias
//Entrada: mesa de jogo
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: base e células temporárias impressas no console
void imprime_BaseTemp(Mesa *jogo){
    int i;
    printf("\t");

    //itera as pilhas temporárias
    for(i = 0; i < MAX_AUX; i++){
        imprime_topo(jogo->temp[i]);
    }

    printf("\t\t");
    
    //itera as pilhas de base
    for(i = 0; i < MAX_AUX; i++)
        imprime_topo(jogo->base[i]);

    printf("\n\t");

    //imprime coodenada das células temporárias
    for(i = 0; i < MAX_AUX; i++)
        printf(" T%d \t", i);

    printf("\t\t");

    //imprime coordenada das células bases
    for(i = 0; i < MAX_AUX; i++)
        printf(" B%d \t", i);

    printf("\n\n");
}

//Imprime as colunas do jogo
//Entrada: vetor de ponteiros de nós
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: colunas impressas no console, se for nula imprime espaço em branco
void imprime_colunas(Node *aux[]){
    int i, prox;

    printf("\t\t");

    //itera quantidade de colunas
    for(i = prox = 0; i < MAX_COLUNA; i++){
        if(!aux[i]){
            printf("      \t");
        }
        else{
            imprime_carta(aux[i]->carta);
            //verifica se possui próximo nó
            if(aux[i]->prox){
                prox++;
            }
            //próximo nó de cada lista
            aux[i] = aux[i]->prox;
        }
    }

    printf("\n");
    if(prox){
        imprime_colunas(aux);
    }

}

//Inverte as colunas e chama função para imprimir as colunas
//Entrada: mesa do jogo
//Retorno: nenhum
//Pré-Condições: o topo das pilhas de coluna apontam para algum valor
//Pós-Condições: colunas impressas no console
void imprime_corpo(Mesa *jogo){
    int i = 0;
    Node *aux[MAX_COLUNA] = {NULL};

    for(i = 0; i < MAX_COLUNA; i++){
        //cada elemento do vetor recebe uma lista, que é a pilha invertida
        aux[i] = inverter(jogo->col[i]->topo);
    }

    imprime_colunas(aux);

    printf("\n");
    printf("\t\t");

    //imprime coordenada das colunas
    for(i = 0; i < MAX_COLUNA; i++)
        printf(" C%d \t", i);

    printf("\n\n");

    //libera as listas auxiliares
    for(i = 0; i < MAX_COLUNA; i++)
        liberar(aux[i]);
}

//Imprime os elementos da mesa
//Entrada: mesa de jogo
//Retorno: nenhum
//Pré-Condições: nenhuma
//Pós-Condições: elementos de mesa impresso
void imprime_mesa(Mesa *jogo){
    imprime_BaseTemp(jogo);
    imprime_corpo(jogo);
}

//Verifica se os naipes das cartas são iguais
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int naipe_igual(Node *orig, Node *dest){
    if (orig->carta->naipe == dest->carta->naipe)
        return 1;
    printf("Naipes diferentes\n");
    system("pause");
    return 0;
}

//Verifica se a cor das cartas são iguais
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int cor_igual(Node *orig, Node *dest){
    return (orig->carta->cor == dest->carta->cor);        
}

//Verifica se o número da carta origem é um a mais que a de destino
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int um_a_mais(Node *orig, Node *dest){
    if (orig->carta->num == dest->carta->num + 1)
        return 1;
    printf("Carta de origem um a mais que a de destino\n");
    system("pause");
    return 0;
}

//Verifica se o número da carta origem é um a menos que a de destino
//Entrada: nó de origem e nó de destino
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nós não nulos
//Pós-Condições: nenhuma
int um_a_menos(Node *orig, Node *dest){
    if (orig->carta->num == dest->carta->num -1)
        return 1;
    printf("Carta de origem um a menos que a de destino\n");
    system("pause");
    return 0;
}

//Verifica se o nó é nulo 
//Entrada: nó
//Retorno: 1 para verdadeiro e 0 para falso
//Pré-Condições: nenhuma
//Pós-Condições: nenhuma
int no_nulo(Node *n){
    if (n == NULL){
        printf("Não há cartas para mover.\n");
        system("pause");
        return 1;
    }
    return 0;
}

//Verifica se origem não é nulo, se destino é nulo e se as cores são iguais
//Entrada: nó origem e nó destino
//Retorno: 1 para origem não nulo, 0 para destino nulo e 1 para cores iguais
//Pré-Condições: nenhuma
//Pós-Condições: nenhuma
int teste(Node *orig, Node *dest){

    if(no_nulo(orig))
        return 1;

    if(!dest) 
        return 0; 

    if(cor_igual(orig, dest)){
        printf("As cores precisam ser alternadas\n");
        system("pause");
        return 1;
    }
    return 0;
}

//Mover para uma coluna
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para outra coluna
void para_col(Mesa *jogo, char cmdOrig, int celOrig, int celDest){
    Node *aux = NULL;
    Node *orig = NULL;
    Node *dest = NULL;
    switch(cmdOrig){
    //se orig for coluna
    case 'c': case 'C':
        aux = jogo->col[celOrig]->topo->prox;
        orig = jogo->col[celOrig]->topo;
        dest = jogo->col[celDest]->topo;

        if(teste(orig, dest)){
            break;
        }

        else{
            if(!dest){
                jogo->col[celDest]->topo = orig;
                jogo->col[celOrig]->topo = aux;
                orig->prox = NULL;
            }
            else if(um_a_menos(orig, dest)){
                jogo->col[celDest]->topo = orig;
                jogo->col[celOrig]->topo = aux;
                orig->prox = dest;
            }
        }
        break;
    //se orig for célula temporária
    case 't': case 'T':
        orig = jogo->temp[celOrig]->topo;
        dest = jogo->col[celDest]->topo;

        if(teste(orig, dest)){
            break;
        }
        if(!dest){
            jogo->col[celDest]->topo = orig;
            jogo->temp[celOrig]->topo = NULL;
        }
        else{
            if(um_a_menos(orig, dest)){
                jogo->col[celDest]->topo = orig;
                jogo->temp[celOrig]->topo = NULL;
                orig->prox = dest;
            }
        }
        break;
    }
}

//Mover para uma base
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para base
void para_base(Mesa *jogo, char cmdOrig, int celOrig, int celDest){
    Node *aux = NULL;
    Node *orig = NULL;
    Node *dest = NULL;
    switch(cmdOrig){
    //se orig for coluna
    case 'c': case 'C':
        aux = jogo->col[celOrig]->topo->prox;
        orig = jogo->col[celOrig]->topo;
        dest = jogo->base[celDest]->topo;

        if(no_nulo(orig)){
            break;
        }

        if(!dest){
            if(orig->carta->num == 1){
                jogo->base[celDest]->topo = orig;
                jogo->col[celOrig]->topo = aux;
                orig->prox = NULL;
            }
            else{
                printf("A carta precisa ser um A");
                system("pause");
            }
        }else{
            if(cor_igual(orig, dest) && naipe_igual(orig, dest)){
                if(um_a_mais(orig, dest)){
                    jogo->base[celDest]->topo = orig;
                    jogo->col[celOrig]->topo = aux;
                    orig->prox = dest;
                }
            }
        }
        break;
    //se orig for célula temporária
    case 't': case 'T':
        orig = jogo->temp[celOrig]->topo;
        dest = jogo->base[celDest]->topo;
        if(no_nulo(orig)){
            break;
        }
        if(!dest){
            if(orig->carta->num == 1){
                jogo->base[celOrig]->topo = orig;
                jogo->temp[celDest]->topo = NULL;
                orig->prox = NULL;
            }
        }else{
            if(cor_igual(orig, dest) && naipe_igual(orig, dest)){
                if(um_a_mais(orig, dest)){
                    jogo->base[celDest]->topo = orig;
                    jogo->temp[celOrig]->topo = NULL;
                    orig->prox = dest;
                }
            }
        }
        break;
    }
}

//Mover para uma célula temporária
//Entrada: mesa do jogo, célula de origem, posição origem, posição de destino
//Retorno: nenhum
//Pré-Condições: cmdOrig, celOrig e celDest possuem valores válidos
//Pós-Condições: carta movida para célula temporária
void para_cel_temp(Mesa *jogo, char cmdOrig, int celOrig, int celDest){
    Node *aux = NULL;
    Node *orig = NULL;
    Node *dest = NULL;
    switch(cmdOrig){
    //se orig for coluna
    case 'c': case 'C':
        aux = jogo->col[celOrig]->topo->prox;
        orig = jogo->col[celOrig]->topo;
        dest = jogo->temp[celDest]->topo;
        if(no_nulo(orig)){
            break;
        }
        if(!dest){
            jogo->temp[celDest]->topo = orig;
            jogo->col[celOrig]->topo = aux;
            orig->prox = NULL;
        }else{
            printf("Celula preechida.\n");
            system("pause");
        }
        break;
    //se orig for célula temporária
    case 't': case 'T':
        orig = jogo->temp[celOrig]->topo;
        dest = jogo->temp[celDest]->topo;

        if(no_nulo(orig)){
            break;
        }
        if(orig == dest){
            printf("Mesma carta.\n");
            system("pause");
        }
        if(!dest){
            jogo->temp[celDest]->topo = orig;
            jogo->temp[celOrig]->topo = NULL;
        }else{
            printf("Celula preechida.\n");
            system("pause");
        }
        break;
    }
}