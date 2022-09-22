/*

Implemente uma lista encadeada de inteiros, utilizando alocação dinâmica de
memória, com as seguintes operações:

1. Criação da lista vazia;
2. Verificar se a lista está vazia;
3. Obter o tamanho da lista;
4. Obter/modificar o valor do elemento de uma determinada posição na lista;
5. Inserir um elemento em uma determinada posição;
6. Retirar um elemento de uma determinada posição.
7. Imprimir os elementos de toda a lista.

Observações de implementação:

- As posições válidas de uma lista são 1 até o tamanho da lista, ou seja, se a
lista tem 3 elementos, as posições válidas são 1, 2 e 3.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;                // valor que quero armazenar
  struct elemento *proximo; // ponteiro para o proximo elem
} No;

typedef struct {
  No *inicio;
  No *fim;
  int tamanho;
} Lista;

Lista *cria_lista();
int lista_vazia(Lista *lista);
int obtem_tamanho(Lista *lista);
int modifica_elemento(Lista *lista, int valor, int posicao);
int insere_elemento(Lista *lista, int valor, int posicao);
int remove_elemento(Lista *lista, int posicao);
int imprime_lista(Lista *lista);

// 1) cria lista vazia
Lista *cria_lista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));

  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
  printf("Lista criada com sucesso!!\n\n");

  return lista;
}

// 2) verifica se a lista está vazia
int lista_vazia(Lista *lista) {
  if (lista->inicio == NULL) {
    return 1;
  } else {
    return 0;
  }
}

// 3) obtem tamanho (e imprime lista)
int obtem_tamanho(Lista *lista) {
  // condições de falha
  if (lista == NULL) {
    printf("Lista Inexistente\n");
    return -1;
  } else if (lista->inicio == NULL) {
    printf("Lista Vazia\n");
    return -1;
  }

  // imprime tamanho da lista
  printf("\nTamanho atual da lista: %d\n", lista->tamanho);

  /*
  // atual aponta para inicio da lista
  No *atual = lista->inicio;
  int index = 1; // indice do nó na lista
  // percorre a lista imprimindo cada valor
  while (atual != NULL) {
    printf("No %d - Valor: %d\n", index, atual->valor);
    index++;
    atual = atual->proximo;
  }*/

  // imprime os elementos da lista para usuario conferir se o tamanho informado
  // procede
  imprime_lista(lista);

  return 0;
}

// 4) modifica elemento na posicao da lista
int modifica_elemento(Lista *lista, int valor, int posicao) {
  // condições de falha
  if (lista == NULL) {
    printf("Lista Inexistente\n");
    return -1;
  } else if (lista->inicio == NULL) {
    printf("Lista Vazia\n");
    return -1;
  }

  // escrever funcao de obter

  // só permite alteração em posição válida na lista
  if ((posicao < 1) || (posicao > lista->tamanho)) {
    printf("Posição %d inválida para modificação\n", posicao);
    return -1;
  }

  // atual aponta para inicio da lista
  No *atual = lista->inicio;

  // percorre as posicoes ate chegar no elemento que sera alterado
  for (int i = 1; i < posicao; i++) {
    atual = atual->proximo;
  }

  int valorAntigo = atual->valor;

  // altera o valor propriamente dito
  atual->valor = valor;

  printf("Valor anterior: %d\nNovo valor: %d\n", valorAntigo, atual->valor);

  return 0;
}

// 5) insere elemento na posicao da lista
int insere_elemento(Lista *lista, int valor, int posicao) {
  // condições de falha
  if (lista == NULL) {
    printf("Lista Inexistente\n");
    return -1;
  }

  // só permite inserção em posição válida na lista
  if ((posicao < 1) || (posicao > lista->tamanho + 1)) {
    printf("Posição %d inválida para inserção\n", posicao);
    return -1;
  }

  // aloca memoria para novo nó na lista
  No *novo = (No *)malloc(sizeof(No));
  // testa falha na alocação de memória
  if (novo == NULL) {
    return -1;
  }
  // atribui o valor para atributo do nó
  novo->valor = valor;

  // caso a lista esteja vazia
  if (lista->inicio == NULL) {
    novo->proximo = NULL; // proximo do novo elemento eh NULL
    lista->inicio = novo; // inicio da lista aponta para no criado
    lista->fim = novo;    // lista so tem um elemento

    // insere na posição da lista
  } else {
    // atual aponta para inicio da lista
    No *atual = lista->inicio;

    // inserir no inicio
    if (posicao == 1) {
      lista->inicio = novo;
      novo->proximo = atual;

      // insere no meio ou final
    } else {
      // percorre as posicoes ate chegar no elemento ANTERIOR aa posicao de
      // insercao
      for (int i = 1; i < posicao - 1; i++) {
        atual = atual->proximo;
      }

      // auxiliar vai guardar o elemento da posicao a ser inserida
      No *aux = atual->proximo;
      // proximo do atual passa a ser o novo elemento inserido
      atual->proximo = novo;
      // proximo do novo passa a ser o auxliar guardado antes
      novo->proximo = aux;

      // se a insercao é apos o ultim elemento da lista, atualiza fim
      if (posicao == lista->tamanho + 1) {
        lista->fim = novo;
      }
    }
  }

  lista->tamanho++;
  return 0;
}

// 6) remove elemento na posição específica
int remove_elemento(Lista *lista, int posicao) {

  // condições de falha
  if (lista == NULL) {
    printf("Lista Inexistente\n");
    return -1;
  } else if (lista->inicio == NULL) {
    printf("Lista Vazia\n");
    return -1;
  }

  // só permite remoção em posição válida na lista
  if ((posicao < 1) || (posicao > lista->tamanho)) {
    printf("Posição %d inválida para remoção\n", posicao);
    return -1;
  }

  ///  1 2 3 4

  ///  ()

  // atual aponta para inicio da lista
  No *atual = lista->inicio;

  // remover do inicio
  if (posicao == 1) {
    // inicio da lista passa a ser proximo elemento
    lista->inicio = atual->proximo;
    // libera memoria eliminando elemento
    free(atual);

    // remove no meio ou final
  } else {
    // percorre as posicoes ate chegar no elemento ANTERIOR aa posicao de
    // remoção
    for (int i = 1; i < posicao - 1; i++) {
      atual = atual->proximo;
    }

    // auxiliar vai guardar o elemento da posicao a ser removida
    No *aux = atual->proximo;

    // o ponteiro proximo do elemento atual passa a apontar para o proximo do
    // que sera removido
    atual->proximo = aux->proximo;

    // libera memoria do elemento a ser removido
    free(aux);

    // se a remocao é o ultimo elemento, atualiza fim para o atual
    if (posicao == lista->tamanho) {
      lista->fim = atual;
    }
  }

  lista->tamanho--;
  return 0;
}

// 7) imprime lista
int imprime_lista(Lista *lista) {
  if (lista == NULL) {
    printf("\nLista Inexistente\n");
    return 0;
  }

  if (lista->inicio == NULL) {
    printf("\nLista Vazia\n");
    return 0;
  }

  printf("\nElementos da Lista:\n");

  // atual aponta para inicio da lista
  No *atual = lista->inicio;

  int index = 1; // indice do nó na lista
  // percorre a lista imprimindo cada valor
  while (atual != NULL) {
    printf("No %d - Valor: %d\n", index, atual->valor);
    index++;
    atual = atual->proximo;
  }
  return 0;
}

 

int main(void) {

  // declaração de variáveis
  Lista *lista;
  int opcao;
  int valor;
  int posicao;
  int resultado;

  while (opcao != 0) {

    printf("\n[1] - Criar lista\n[2] - Verifica lista vazia\n[3] - Obter "
           "tamanho \n[4] - Modificar Elemento\n[5] - Inserir elemento\n[6] - "
           "Remover Elemento\n[7] - Imprimir\n[0] - Sair\n");
    printf("\nDigite a opção: ");
    scanf("\n\n%d", &opcao);

    fflush(stdin);   // limpa bufffer para windows
    __fpurge(stdin); // limpa buffer para linux

    switch (opcao) {
    case 1:
      printf("\nOpção 1 [Criar lista] escolhida\n");
      lista = cria_lista();
      break;

    case 2:
      printf("\nOpção 2 [Verifica Vazia] escolhida\n");
      int estaVazia = lista_vazia(lista);
      if (estaVazia == 1) {
        printf("\nLista Vazia!!!\n");
      } else {
        printf("\nLista NÃO Vazia!!!\n");
      }
      break;

    case 3:
      printf("\nOpção 3 [Obter tamanho] escolhida\n");
      obtem_tamanho(lista);
      break;

    case 4:
      printf("\nOpção 4 [Modificar Elemento] escolhida\n");
      printf("Digite a posição a modificar: \n");
      scanf("%d", &posicao);
      printf("Digite o valor a ser alterado: \n");
      scanf("%d", &valor);
      resultado = modifica_elemento(lista, valor, posicao);
      if (resultado == 0) {
        printf("Elemento alterado com sucesso\n");
      } else {
        printf("Elemento não alterado\n");
      }
      break;

    case 5:
      printf("Digite o valor a ser inserido: \n");
      scanf("%d", &valor);
      printf("Digite a posição: \n");
      scanf("%d", &posicao);

      resultado = insere_elemento(lista, valor, posicao);
      if (resultado == 0) {
        printf("Elemento inserido com sucesso\n");
      } else {
        printf("Elemento não inserido\n");
      }
      break;

    case 6:
      printf("Digite a posição para remover: ");
      scanf("%d", &posicao);
      resultado = remove_elemento(lista, posicao);
      if (resultado == 0) {
        printf("Elemento removido com sucesso\n");
      } else {
        printf("Elemento não removido\n");
      }
      break;

    case 7:
      imprime_lista(lista);
      break;
    }
  }

  return 0;
}
