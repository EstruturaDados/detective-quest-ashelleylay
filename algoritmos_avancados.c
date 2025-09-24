#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Sala {
    char* nome;
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;
typedef struct Pista {
    char* texto;
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;
typedef struct Suspeito {
    char* nome;
    char* pista;
    struct Suspeito* proximo;
} Suspeito;

Sala* criarSala(char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->nome = nome;
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void explorarSala(Sala* sala) {
    if (sala != NULL) {
        printf("Você está na sala: %s\n", sala->nome);
    }
}

void moverEsquerda(Sala* sala) {
    explorarSala(sala->esquerda);
}

void moverDireita(Sala* sala) {
    explorarSala(sala->direita);
}

Pista* criarPista(char* texto) {
    Pista* novaPista = (Pista*)malloc(sizeof(Pista));
    novaPista->texto = texto;
    novaPista->esquerda = NULL;
    novaPista->direita = NULL;
    return novaPista;
}
Pista* inserirBST(Pista* raiz, Pista* novaPista) {
    if (raiz == NULL) {
        return novaPista;
    }
    if (strcmp(novaPista->texto, raiz->texto) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, novaPista);
    } else {
        raiz->direita = inserirBST(raiz->direita, novaPista);
    }
    return raiz;
}

void listarPistas(Pista* raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("%s\n", raiz->texto);
        listarPistas(raiz->direita);
    }
}

unsigned int hash(char* chave) {
    unsigned int hashValue = 0;
    while (*chave) {
        hashValue += *chave;
        chave++;
    }
    return hashValue % 10;
}

Suspeito* criarSuspeito(char* nome, char* pista) {
    Suspeito* novoSuspeito = (Suspeito*)malloc(sizeof(Suspeito));
    novoSuspeito->nome = nome;
    novoSuspeito->pista = pista;
    novoSuspeito->proximo = NULL;
    return novoSuspeito;
}

void inserirHash(Suspeito* tabela[], char* nome, char* pista) {
    unsigned int index = hash(nome);
    Suspeito* novo = criarSuspeito(nome, pista);
    novo->proximo = tabela[index];
    tabela[index] = novo;
}

void listarAssociacoes(Suspeito* tabela[]) {
    for (int i = 0; i < 10; i++) {
        Suspeito* atual = tabela[i];
        if (atual != NULL) {
            printf("Tabela[%d]:\n", i);
            while (atual != NULL) {
                printf("Nome: %s, Pista: %s\n", atual->nome, atual->pista);
                atual = atual->proximo;
            }
        }
    }
}

int main() {

    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    cozinha->esquerda = sotao;

    printf("Exploração do Mapa da Mansão:\n");
    explorarSala(hall);
    moverEsquerda(hall);
    moverDireita(hall);

    Pista* pistas = NULL;
    pistas = inserirBST(pistas, criarPista("Pista 1: Algo foi encontrado no Hall"));
    pistas = inserirBST(pistas, criarPista("Pista 2: A chave está na cozinha"));

    printf("\nPistas Coletadas:\n");
    listarPistas(pistas);


    Suspeito* tabela[10] = { NULL };

    inserirHash(tabela, "Suspeito 1", "Pista 1: Hall de Entrada");
    inserirHash(tabela, "Suspeito 2", "Pista 2: Cozinha");

    printf("\nSuspeitos e suas Pistas:\n");
    listarAssociacoes(tabela);

    return 0;
};

