/* GRUPO:
 * GABRIEL ALVES DOS SANTOS;
 * MARIO GUILHERME DE ANDRADE RODRIGUES;
 * NICOLAS JIRO HIGA TAKEMOTO
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> // Biblioteca para função sleep

struct no {
    int info;
    struct no *proximo;
};

struct no * inserirNoInicio(struct no *L, int val) {
    struct no *p;

    // Alocar espaço de memoria para o novo nó
    p = (struct no *) malloc(sizeof(struct no)); // Malloc retorna ponteiro sem tipo, precisando fazer un cast no inicio

    // Colocar a informação no novo nó
    p -> info = val;
    // Fazer o encadeamento do novo nó no ínicio da Lista
    p -> proximo = L; // Faz o novo nó apontar para o antigo primeiro nó da lista
    L = p; // Faz a Lista apontar para o novo nó que passa a ser o primeiro da lista

    return L;
}

void imprimirLista(struct no *L) {
    struct no *p;

    if(L == NULL){
        printf("Lista vazia.");
        return;
    }
    p = L; // Aponta p para o primeiro nó da Lista
    while(p != NULL){
        printf("%i ", p -> info); // Imprime a informação do nó
        p = p -> proximo; // Anda o p para o próximo nó
        if(p != NULL){
            printf("-> ");
        }
    }
}

struct no * inserirNoFim(struct no *L, int val) {
    struct no *n, *p;

    n = (struct no *) malloc(sizeof(struct no)); // Aloca espaço de memória
    n -> info = val; // Coloca a informação no novo nó
    // Coloca NULL no proximo, pois este novo nó será o último da Lista
    n -> proximo = NULL;

    if(L == NULL){ // Caso especial de Lista vazia
        L = n; // Faz a Lista apontar para o novo nó
    } else { // Se a Lista não é vazia
        // Localizar o último nó da Lista para fazer o encadeamento
        p = L;
        while(p -> proximo != NULL)
            p = p -> proximo; // Anda o p para o próximo nó

        p -> proximo = n; // Faz o encadeamento, ou seja, faz o último nó apontar para o novo nó que passará a ser o último
    }

    return L;
}

struct no * removerDoInicio(struct no *L, int *val) {
    struct no *p;

    p = L;
    // Pega a informação do nó a ser removido e coloca no val
    *val = p -> info; // Nó do início
    // Fazer o L apontar para o segundo nó, o qual passará a ser o primeiro
    L = p -> proximo;
    // Libera o espaço de memória do nó sendo removido
    free(p);

    return L;
}

struct no * removerDoFinal(struct no *L, int *val) {
    struct no *p,*q;

    // Posicionar  p no ultimo nó da Lista
    p = L;
    while(p -> proximo != NULL){
        p = p -> proximo;
    }
    // Pega a informação do nó a ser removido e coloca no val
    *val = p -> info; // Nó do final

    if(L -> proximo == NULL){ // A lista só tem um nó
        L = NULL;
    } else { // Se a lista tem dois ou mais nós
        // Posiciona o q no nó anterior ao p
        q = L;
        while(q -> proximo != p){
            q = q -> proximo;
        }
        // Coloca NULL no nó que será o ultimo
        q -> proximo = NULL;
    }
     // Libera espaço de memória do nó sendo removido
    free(p);

    return L; // Atualiza o Lista no programa principal
}

struct no * inserirOrdemCrescente(struct no *L, int val) {
    struct no *n, *p, *q;

    // Localizar a posição onde o novo nó será inserido
    p = L;
    while((p != NULL) && (p -> info <= val)){
        p = p -> proximo;
    }
    if(p == NULL){ // O novo valor é maior que todos, então inserir no final
        L = inserirNoFim(L, val);
    } else { // Neste caso, o p aponta para um nó que possui um valor maior que o que será inserido, então inserir antes desse nó
        if(p == L){ // Inserir no início
            L = inserirNoInicio(L, val);
        } else { // Inserir entre dois nós
            // Posicionar o q antes do p
            q = L;
            while(q -> proximo != p){
                q = q -> proximo;
            }
            // Alocar espaço de memória para o novo nó
            n = (struct no *) malloc(sizeof(struct no));
            // Colocar a informação no novo nó
            n -> info = val;
            // Faz o novo nó apontar para o nó apontado por p
            n -> proximo = p;
            // Faz o nó apontado por q apontar para o novo nó
            q -> proximo = n;
        }
    }

    return L;
}

int localizarValorNaLista(struct no *L, int v) {
    struct no *p;
    int posicao = 1;

    p = L;
    while((p != NULL) && (p -> info != v)){
        p = p -> proximo;
        posicao++;
    }


    if(p == NULL){
        return 0; // Não localizou
    } else {
        return posicao; // Localizou o valor
    }
}

int qntdDeNos(struct no *L) {
    struct no *p;
    int cont = 0;

    p = L; // Aponta p para o primeiro elemento da Lista
    while(p != NULL){
        cont++;
        p = p -> proximo; // Anda o p para o próximo nó
    }

    return cont;
}

int somaPar(struct no *L) {
    struct no *p;
    int soma = 0;

    p = L; // Aponta p para o primeiro elemento da Lista
    while(p != NULL){
        if(p -> info % 2 == 0){
            soma = p -> info + soma; // Soma os números pares
        }
        p = p -> proximo; // Anda o p para o próximo nó
    }

    return soma;
}

struct no * clonaImparDaLista(struct no *L) {
    struct no *p, *n;

    p = L; // Aponta p para o primeiro nó da Lista
    while(p != NULL){
        if(p -> info % 2 != 0){
            // Alocar espaço de memoria para o novo nó
            n = (struct no *) malloc(sizeof(struct no)); // Malloc retorna ponteiro sem tipo, precisando fazer un cast no inicio

            // Colocar a informação no novo nó
            n -> info = p -> info; // Copia o valor
            n -> proximo = p -> proximo; // Copia o endereço do próximo nó

            p -> proximo = n; // Aponta o p para o novo nó criado
            p = p -> proximo; // Anda o p para o novo nó clonado
        }
        p = p -> proximo; // Anda o p para o próximo nó diferente

    }

    printf("\nLista -> ");
    imprimirLista(L); // Exibe a Lista com os valores clonados

    return L;
}

void push(struct no **P, int v) {
    struct no *n;

    // Alocar espaço de memoria para o novo nó
    n = (struct no *) malloc(sizeof(struct no)); // Malloc retorna ponteiro sem tipo, precisando fazer un cast no inicio

    // Colocar a informação no novo nó
    n -> info = v;

    // Fazer o encadeamento do novo nó no ínicio da Pilha
    n -> proximo = *P; // Faz o novo nó apontar para o antigo primeiro nó da pilha
    *P = n; // Faz a Lista apontar para o novo nó que passa a ser o primeiro da pilha
}

int pop(struct no **P) {
    struct no *q;
    int v;

    q = *P;

    // Pega a informação do nó a ser removido e coloca no val
    v = q -> info; // Nó do início

    // Fazer o L apontar para o segundo nó, o qual passará a ser o primeiro
    *P = q -> proximo;

    // Libera o espaço de memória do nó sendo removido
    free(q);

    return v;
}

void mostrarPilha(struct no **P) {
    struct no *Paux = NULL;
    int val;

    if(*P == NULL){
        printf("Pilha vazia.");
        return;
    }

    val = pop(P); // Retira da Pilha original
    printf("%i\n", val); // Mostra
    push(&Paux, val); // Guarda na Pilha Auxiliar

    while(*P != NULL){
        val = pop(P); // Retira da Pilha original
        printf("         %i\n", val); // Mostra
        push(&Paux, val); // Guarda na Pilha Auxiliar
    }

    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
    }
}

int acimaMedia(struct no **P) {
    struct no *Paux = NULL;
    int val, cont = 0, soma = 0;
    float media = 0;

    // Soma os valores para calcular a Média
    val = pop(P); // Retira da Pilha original
    soma = val + soma;
    cont++;
    push(&Paux, val); // Guarda na Pilha Auxiliar

    while(*P != NULL){
        val = pop(P); // Retira da Pilha original
        soma = val + soma;
        cont++;
        push(&Paux, val); // Guarda na Pilha Auxiliar
    }

    // Calcula a média
    media = (float) soma / cont;

    cont = 0;
    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
        if(val > media){
            cont++;
        }
    }

    return cont;
}

int localizaNaPilha(struct no **P, int v) {
    struct no *Paux = NULL;
    int posicao = 0, val, achou = 0;

    while((*P != NULL) && (achou == 0)){
        val = pop(P); // Retira da Pilha original
        push(&Paux, val); // Guarda na Pilha Auxiliar
        posicao++;
        if(val == v){ // Achei o valor na Pilha
            achou = 1;
        }
    }

    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
    }

    if(achou == 0){
        return 0; // valor Não localizado
    }else{
        return posicao;
    }
}

void duplicaParPilha(struct no **P) {
    struct no *Paux = NULL;
    int val;

    while(*P != NULL){
        val = pop(P); // Retira da Pilha original
        push(&Paux, val); // Guarda na Pilha Auxiliar
        if(val % 2 == 0){ // Verifica se o valor é par
            push(&Paux, val); // Duplica o valor par
        }
    }

    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
    }

    printf("\nLista -> ");
    mostrarPilha(P); // Exibe a Pilha duplicada
}

int somaImparesPilha(struct no **P) {
    struct no *Paux = NULL;
    int soma = 0, val;

    while(*P != NULL){
        val = pop(P); // Retira da Pilha original
        push(&Paux, val); // Guarda na Pilha Auxiliar
        if(val % 2 != 0){ // Verifica se o valor é ímpar
            soma =  soma + val; // Soma os valores ímpares
        }
    }

    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
    }

    return soma;
}

struct no * copiaPilhaParaLista(struct no **P, struct no *L) {
    struct no *Paux = NULL;
    int val;

    // Lê os elementos da Pilha
    while(*P != NULL){
        val = pop(P); // Retira da Pilha original
        push(&Paux, val); // Guarda na Pilha Auxiliar
        L = inserirNoFim(L, val); // Copia o valor para a Lista
    }

    // Retornar valores para a Pilha original
    while(Paux != NULL){
        val = pop(&Paux); // Retira da Pilha Auxiliar
        push(P, val); // Coloca na Pilha original
    }

    return L;
}

void main() {
    struct no *Pilha, *Lista;
    int val, num, posicao, soma, opcao;

    Pilha = NULL;
    Lista = NULL;

    do {
        // Asterisco (*) marcam as novas funções solicitadas no trabalho
        printf("\n##==========================================##");
        printf("\n||             Listas e Pilhas              ||");
        printf("\n##==========================================##");
        printf("\n|| A) Listas                                ||");
        printf("\n||    1)  Inserir no Inicio da Lista        ||");
        printf("\n||    2)  Inserir no Final da Lista         ||");
        printf("\n||    3)  Imprimir a Lista                  ||");
        printf("\n||    4)  Remover do Inicio da Lista        ||");
        printf("\n||    5)  Remover do Final da Lista         ||");
        printf("\n||    6)  Inserir em Ordem Crescente        ||");
        printf("\n||    7)  Buscar posicao da informacao      ||");
        printf("\n||    8)  Quantidade de nos na Lista        ||");
        printf("\n||    9)  *Soma de elementos pares da Lista ||");
        printf("\n||    10) *Clonar impares da Lista          ||");
        printf("\n||                                          ||");
        printf("\n|| B) Pilhas                                ||");
        printf("\n||    11) Push() - Inserir na Pilha         ||");
        printf("\n||    12) Pop() - Remover da Pilha          ||");
        printf("\n||    13) Mostrar Pilha                     ||");
        printf("\n||    14) Qtnd de itens acima da media      ||");
        printf("\n||    15) Localizar um valor na Pilha       ||");
        printf("\n||    16) *Duplicar pares da Pilha          ||");
        printf("\n||    17) *Somar impares da Pilha           ||");
        printf("\n||                                          ||");
        printf("\n||    18) *Copiar Pilha para Lista          ||");
        printf("\n||                                          ||");
        printf("\n|| 0) Sair                                  ||");
        printf("\n##==========================================##");

        do {
            printf("\n// Opcao -> ");
            fflush(stdin); scanf("%i", &opcao);

            switch(opcao) {
                case 1: // Inserir no inicio da Lista
                    printf("\nDigite o Valor: ");
                    fflush(stdin); scanf("%i", &val);
                    Lista = inserirNoInicio(Lista, val);
                    printf("\nValor inserido com sucesso!\n");
                    break;
                case 2: // Inserir no fim da Lista
                    printf("\nDigite o Valor: ");
                    fflush(stdin); scanf("%i", &val);
                    Lista = inserirNoFim(Lista, val);
                    printf("\nValor inserido com sucesso!\n");
                    break;
                case 3: // Imprime os valores na Lista
                    printf("\nLista -> ");
                    imprimirLista(Lista);
                    Sleep(1000);
                    break;
                case 4: // Remover do Inicio da Lista
                    if(Lista == NULL){
                        printf("\nLista vazia. Impossivel remover.");
                        Sleep(1000);
                    } else {
                        Lista = removerDoInicio(Lista, &val);
                        printf("\nValor removido: %i", val);
                        Sleep(1000);
                    }
                    break;
                case 5: // Remover do Final da Lista
                    if(Lista == NULL){
                        printf("\nLista vazia. Impossivel remover.");
                        Sleep(1000);
                    } else {
                        Lista = removerDoFinal(Lista, &val);
                        printf("\nValor removido: %i", val);
                        Sleep(1000);
                    }
                    break;
                case 6: // Inserir dados em ordem crescente
                    printf("\nDigite o Valor: ");
                    fflush(stdin); scanf("%i", &val);
                    Lista = inserirOrdemCrescente(Lista, val);
                    printf("\nValor inserido com sucesso na Lista!\n");
                    break;
                case 7: // Buscar posição da informação na Lista
                    printf("\nDigite o Valor Desejado: ");
                    fflush(stdin); scanf("%i", &val);
                    num = localizarValorNaLista(Lista, val);
                    if(num == 0){
                        printf("\nValor nao encontrado na Lista! Tente novamente.");
                        Sleep(1000);
                    } else {
                        printf("\nO valor se encontra na posicao %i na Lista", num);
                        Sleep(1000);
                    }
                    break;
                case 8: // Buscar qntd de nós na lista
                    printf("\nQuantidade de elementos na Lista: %i", qntdDeNos(Lista));
                    Sleep(1000);
                    break;
                case 9: // Somar todos os elementos pares da Lista
                    if(Lista == NULL){
                        printf("\nLista vazia!");
                    }else{
                        soma = somaPar(Lista);
                        if(soma == 0){
                            printf("\nNao ha elementos pares na Lista!");
                            Sleep(1000);
                        }else{
                            printf("\nSoma dos elementos pares: %i", soma);
                            Sleep(1000);
                        }
                    }
                    break;

                case 10: // Clona os elementos ímpares da Lista
                    if(Lista == NULL){
                        printf("\nLista vazia!");
                    }else{
                        Lista = clonaImparDaLista(Lista);
                        printf("\nOperacao realizada com sucesso!");
                    }
                    break;

                case 11: // Push() - Inserir no Topo da Pilha
                    printf("\nDigite o Valor: ");
                    fflush(stdin); scanf("%i", &val);
                    push(&Pilha, val);
                    printf("\nValor empilhado com sucesso!\n");
                    break;
                case 12: // Pop - remover do Topo da Pilha
                    if(Pilha == NULL){
                        printf("\nPilha Vazia!");
                    } else {
                        val = pop(&Pilha);
                        printf("\nValor removido: %i", val);
                        Sleep(1000);
                    }
                    break;
                case 13: // Imprime os valores da Pilha
                    printf("\nPilha -> ");
                    mostrarPilha(&Pilha);
                    Sleep(1000);
                    break;
                case 14: // Calcula media dos valores na pilha
                    if(Pilha == NULL){
                        printf("\nPilha Vazia!");
                    } else {
                        printf("\nQtde de itens acima da Media: %i", acimaMedia(&Pilha));
                    }
                    Sleep(1000);
                    break;
                case 15: // Verifica se um dado existe na pilha e retorna uma posição
                    printf("\nDigite o valor o valor a ser localizado na Pilha: ");
                    fflush(stdin); scanf("%i", &val);
                    posicao = localizaNaPilha(&Pilha, val);
                    if(posicao == 0){
                        printf("\nO valor %i NAO foi localizado na Pilha!", val);
                        Sleep(1000);
                    }else{
                        printf("\nO valor %i foi localizado na posicao %i da Pilha!", val, posicao);
                        Sleep(1000);
                    }
                    break;

                case 16: // Duplicar os valores pares da Lista
                    duplicaParPilha(&Pilha);
                    printf("\nOperacao realizada com sucesso!");
                    break;

                case 17: // Soma todos os elementos ímpares da Lista
                    if(Pilha == NULL){
                        printf("\nPilha Vazia!");
                    } else {
                        soma = somaImparesPilha(&Pilha);
                        if(soma == 0){
                            printf("\nNao ha elementos impares na Pilha!");
                        }else{
                            printf("\nSoma dos elementos impares: %i", soma);
                            Sleep(1000);
                        }
                    }
                    break;

                case 18: // Copia Pilha para Lista
                    Lista = copiaPilhaParaLista(&Pilha, Lista);
                    printf("\nLista -> ");
                    imprimirLista(Lista);
                    printf("\nPilha -> ");
                    mostrarPilha(&Pilha);
                    printf("\nOperacao realizada com sucesso!");
                    Sleep(1000);
                    break;

                case 0: // Sair do programa
                    printf("\nAte mais!");
                    break;

                default: // Opções inválidas
                    printf("\nOpcao invalida! Tente novamente.");
                    break;
            }
        } while ((opcao != 1)&&(opcao != 2)&&(opcao != 3)&&(opcao != 4)&&(opcao != 5)&&
                 (opcao != 6)&&(opcao != 7)&&(opcao != 8)&&(opcao != 9)&&(opcao != 10)&&
                 (opcao != 11)&&(opcao != 12)&&(opcao != 13)&&(opcao != 14)&&(opcao != 15)&&
                 (opcao != 16)&&(opcao != 17)&&(opcao != 18)&&(opcao != 0)); //Repete o scanf caso digite uma opção inválida

        Sleep(1000); // Espera 1 segundos antes de exibir o menu novamente
    } while(opcao != 0); //Repete o menu, caso não queira sair
}
