/*

Implemente uma lista sequencial de inteiros, utilizando o tipo vetor, de
inteiros com as seguintes operações:

1. Criação da lista vazia;
2. Verificar se a lista está vazia;
3. Verificar se a lista está cheia;
4. Obter o tamanho da lista;
5. Obter/modificar o valor do elemento de uma determinada
posição na lista;
6. Inserir um elemento em uma determinada posição;
7. Retirar um elemento de uma determinada posição.

As posições válidas de uma lista são 1 até o tamanho da lista, ou seja, se a
lista tem 3 elementos, as posições válidas são 1, 2 e 3. Não confunda com os
índices do vetor.


*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int tamAtual;
  int tamMax;
  int *dados;
} tLista;

tLista cria_lista(int tamMax);
int lista_vazia(tLista *lista);
int lista_cheia(tLista *lista);
int lista_tamanho(tLista *lista);
int obter_ou_modificar_elemento(tLista *lista, int novoValor, int posicao,
                                bool modificar);
int insere_elemento(tLista *lista, int novoElemento, int posicao);
int remove_elemento(tLista *lista, int posicao);
void print_lista(tLista lista);

int main(void) {

  tLista lista;
  int opcao;

  while (opcao != 0) {

    printf(
        "\n[1] - Criar lista\n[2] - Verifica Vazia\n[3] - Verifica Cheia\n[4] "
        "- Obter tamanho\n[5] - Obter/Modificar Valor\n[6] - Inserir "
        "ELemento\n[7] - Remover Elemento\n[8] - Imprime Lista\n[0] - Sair\n");
    printf("\nDigite a opção : ");
    scanf("\n\n%d", &opcao);

    fflush(stdin);   // limpa bufffer para windows
    __fpurge(stdin); // limpa buffer para linux

    switch (opcao) {
    case 1:
      printf("\nOpção 1 [Criar lista] escolhida\n");
      int tamanhoCriacao;
      printf("digite o tamanho: ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%d", &tamanhoCriacao);
      lista = cria_lista(tamanhoCriacao);
      break;

    case 2:
      printf("\nOpção 2 [Verifica Vazia] escolhida\n");
      int estaVazia = lista_vazia(&lista);
      if (estaVazia == 1) {
        printf("\nLista Vazia!!!\n");
      } else {
        printf("\nLista NÃO Vazia!!!\n");
      }
      break;

    case 3:
      printf("\nOpção 3 [Verifica Cheia] escolhida\n");
      int estaCheia = lista_cheia(&lista);
      if (estaCheia == 1) {
        printf("\nLista Cheia!!!\n");
      } else {
        printf("\nLista NÃO Cheia!!!\n");
      }
      break;

    case 4:
      printf("\nOpção 4 [Obter Tamanho] escolhida\n");
      int tamanhoLista = lista_tamanho(&lista);
      printf("\nTamanho da Lista: %d\n", tamanhoLista);
      break;

    case 5:
      printf("\nOpção 6 [Obter/Modificar Elemento] escolhida\n");
      int posicaoModificar;
      char simOuNao;
      int novoElementoModificado;
      bool modificar = false;

      printf("digite a posição: ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%d", &posicaoModificar);

      printf("deseja modificar o elemento (S/N)? ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%c", &simOuNao);

      if (simOuNao == 'S') {
        modificar = true;
        printf("digite o novo valor do elemento: ");
        fflush(stdin);
        __fpurge(stdin);
        scanf("%d", &novoElementoModificado);
      }
      obter_ou_modificar_elemento(&lista, novoElementoModificado,
                                  posicaoModificar, modificar);

      break;

    case 6:
      printf("\nOpção 6 [Insere Elemento] escolhida\n");
      int novoElemento;
      int posicaoInsercao;
      printf("digite elemento: ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%d", &novoElemento);
      printf("digite a posição: ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%d", &posicaoInsercao);
      insere_elemento(&lista, novoElemento, posicaoInsercao);
      break;

    case 7:
      printf("\nOpção 7 [Remove Elemento] escolhida\n");
      int posicaoRemocao;
      printf("digite a posição: ");
      fflush(stdin);
      __fpurge(stdin);
      scanf("%d", &posicaoRemocao);
      remove_elemento(&lista, posicaoRemocao);
      break;

    case 8:
      printf("\nOpção 8 [Imprime Lista] escolhida\n");
      print_lista(lista);
      break;

    case 0:
      printf("\nOpção 0 [Sair] escolhida\n");
      return 0;
      break;
    }
  }

  return 0;
}

/// 1) cria lista
tLista cria_lista(int tamMax) {
  tLista lista;

  lista.tamAtual = 0;
  lista.tamMax = tamMax;
  lista.dados = (int *)malloc(lista.tamMax * sizeof(int));

  printf("Lista criada com sucesso!!\n\n");
  return lista;
};

/// 2) verifica se lista esta vazia
int lista_vazia(tLista *lista) {
  if (lista->tamAtual == 0) {
    return 1;
  } else {
    return 0;
  }
}

// 3) verifica se a lista esta cheia
int lista_cheia(tLista *lista) {
  if (lista->tamAtual == lista->tamMax) {
    return 1;
  } else {
    return 0;
  }
}

// 4) informa tamanho da lista
int lista_tamanho(tLista *lista) { return (lista->tamAtual); }

// 5) obter/modificar elemento na lista
int obter_ou_modificar_elemento(tLista *lista, int novoValor, int posicao,
                                bool modificar) {

  // nao pode extrapolar os limites da lista
  if (posicao < 1 || posicao > lista->tamMax) {
    printf("\nNão é possível obter/modificar posições que extrapolem os "
           "limites da Lista\n");
    return 0;
  } else if (posicao > lista->tamAtual) {
    printf("\nSó é possível obter/modificar até a posição %d\n",
           lista->tamAtual + 1);
    return 0;
  }

  // se a flag vem como true, usuario deseja modificar o valor do elemento
  if (modificar) {
    lista->dados[posicao - 1] = novoValor;
    printf("\nElemento modificado com sucesso: %d\n",
           lista->dados[posicao - 1]);
    // senao, usuario so quer obter o elemento da posicao
  } else {
    printf("\nElemento da posição %d: %d\n", posicao,
           lista->dados[posicao - 1]);
  }

  return lista->dados[posicao - 1];
}

// 6) inserir um elemento em uma determinada posição
int insere_elemento(tLista *lista, int novoElemento, int posicao) {
  // nao pode inserir se a lista já está cheia
  if (lista_cheia(lista)) {
    printf("\nLista já se encontra cheia, impossível inserir elementos: \n");
    return 0;
    // nao pode inserir se a posição extrapolar limites da lista
  } else if (posicao < 1 || posicao > lista->tamMax) {
    printf("\nNão é possível inserir em posições que extrapolem os limites da "
           "Lista\n");
    return 0;
  } else if (posicao > (lista->tamAtual + 1)) {
    printf("\nSó é possível inserir até a posição %d\n", lista->tamAtual + 1);
    return 0;
  }

  for (int i = lista->tamAtual; i >= posicao; i--) {
    lista->dados[i] = lista->dados[i - 1];
  }

  lista->dados[posicao - 1] = novoElemento;
  lista->tamAtual++;

  printf("\nElemento inserido com sucesso: %d\n", lista->dados[posicao - 1]);
  return lista->dados[posicao - 1];
}

// 7) remover um elemento em uma determinada posição
int remove_elemento(tLista *lista, int posicao) {
  // nao pode remover se a lista está vazia
  if (lista_vazia(lista)) {
    printf("\nLista encontra-se vazia, impossível remover elementos \n");
    return 0;
    // nao pode inserir se a posição extrapolar limites da lista
  } else if (posicao < 1 || posicao > lista->tamMax) {
    printf("\nNão é possível remover em posições que extrapolem os limites da "
           "Lista\n");
    return 0;
  } else if (posicao > lista->tamAtual) {
    printf("\nSó é possível remover até a posição %d\n", lista->tamAtual);
    return 0;
  }

  int elementoRemovido = lista->dados[posicao - 1];

  for (int i = posicao - 1; i < lista->tamAtual - 1; i++) {
    lista->dados[i] = lista->dados[i + 1];
  }
  lista->tamAtual--;

  return elementoRemovido;
}

// 8) imprime a lista
void print_lista(tLista lista) {
  printf("Lista tamanho atual:  %d \n", lista.tamAtual);
  printf("Lista tamanho maximo: %d \n", lista.tamMax);

  for (int i = 0; i < lista.tamAtual; i++) {
    printf(" --> Elem(%d): %d\n", i + 1, lista.dados[i]);
  }
}
