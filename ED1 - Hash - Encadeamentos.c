#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct vetor_encadeamento_exterior *pointer;

struct vetor_encadeamento_exterior{
    union valores{
        int posicao;
        int chave;
    }valor;
    pointer *chaves;
    pointer *prox;
};

typedef struct struct_encadeamento_interior vetor_encadeamento_interior;

struct struct_encadeamento_interior{
    int chave;
    int prox;
};


// Encadeamento exterior
pointer cria_posicao_encadeamento_exterior(int valor, char tipo[]){
        pointer q = (pointer)malloc(sizeof(struct vetor_encadeamento_exterior));
        if(strcmp(tipo, "posicao") == 0)
            q->valor.posicao = valor;
        else
            q->valor.chave = valor;
        q->chaves = NULL;
        q->prox = NULL;
        return q;
}

void guarda_chaves_encadeamento_exterior(pointer *encadeamento_exterior, int chave, int posicao){
    pointer posicoes = (*encadeamento_exterior);
    
    // Caso ainda não exista o vetor dinamico, eh criado 
    if(posicoes == NULL){
        pointer q = cria_posicao_encadeamento_exterior(posicao, "posicao");
        q->chaves = cria_posicao_encadeamento_exterior(chave, "chave");
        *encadeamento_exterior = q;
    }

    // Caso contrário, busque a posicao desejada
    else{
        pointer anterior;
        while(posicoes != NULL){

            // Caso encontrada a posicao, chegue até o final das chaves
            if(posicoes->valor.posicao == posicao){
                pointer vetor_chaves = posicoes->chaves;
                while(vetor_chaves->prox != NULL){
                    vetor_chaves = vetor_chaves->prox;
                }
                vetor_chaves->prox = cria_posicao_encadeamento_exterior(chave, "chave");
                return;
            }
            anterior = posicoes;
            posicoes = posicoes->prox;
        }

        // Como nao encontrou a posicao, ela eh criada e adicionada ao vetor
        pointer q = cria_posicao_encadeamento_exterior(posicao, "posicao");;
        q->chaves = cria_posicao_encadeamento_exterior(chave, "chave");
        anterior->prox = q;
    }
}

void mostra_chaves_encadeamento_exterior(pointer encadeamento_exterior){
    pointer p = encadeamento_exterior;
    while(p != NULL){
        pointer r = p->chaves;
        printf("\nPosicao %d: ", p->valor.posicao);
        int first_pass = 1;
        while(r != NULL){
            if(first_pass){
                first_pass = 0;
            }
            else
                printf("-->");
            printf("| %2d |", r->valor.chave);
            r = r->prox;
        }
        printf("\n");
        p = p->prox;
    }
}
// Fim encadeamento exterior

//Encadeamento interior

void guarda_chaves_encadeamento_interior(vetor_encadeamento_interior encadeamento_interior[], int chave, int posicao, int M, int N){
    int i;
    if(M == N)
        M = 0;
    if(encadeamento_interior[posicao].chave == -1)
        encadeamento_interior[posicao].chave = chave;
    else{
        int posicao_atual = posicao, posicao_posterior = encadeamento_interior[posicao].prox;
        while(posicao_posterior != -1){
            posicao_atual = posicao_posterior;
            posicao_posterior = encadeamento_interior[posicao_atual].prox;
        }
        for(i=N-1; i>=M; i--)
            if(encadeamento_interior[i].chave == -1){
                encadeamento_interior[i].chave = chave;
                encadeamento_interior[posicao_atual].prox = i;
                break;
            }
    }
}

void mostra_chaves_encadeamento_interno(vetor_encadeamento_interior encadeamento_interior[], int N){
    int i;
    for(i=0; i<N; i++)
        if(encadeamento_interior[i].chave != -1)
            printf("\nPosicao %2d: | %2d | %2d |\n", i, encadeamento_interior[i].chave, encadeamento_interior[i].prox);
}
//Fim encadeamento interior

int main(){
    int n, i, chave, posicao, M, N;

    // ENCADEAMENTO INTERIOR
    vetor_encadeamento_interior encadeamento_interior[MAX];
    for(i=0; i<MAX; i++){
        encadeamento_interior[i].chave = -1;
        encadeamento_interior[i].prox = -1;
    }
    printf("\nENCADEAMENTO INTERIOR\n\n[INFO] Guarda de N-1 ate M as chaves sinonimas\n* M!=N: duas regioes\n* M==N: uma regiao\n\n");
    printf("Digite M e N (MAX %d): ", MAX);
    scanf("%d %d", &M, &N);
    printf("Digite quantas chaves serão armazenadas (MAX %d): ", MAX);
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("(%d) Digite a posicao e a chave: ", i+1);
        scanf("%d %d", &posicao, &chave);
        guarda_chaves_encadeamento_interior(encadeamento_interior, chave, posicao, M, N);
    }
    mostra_chaves_encadeamento_interno(encadeamento_interior, N);
    ////////////////////

    // ENCADEAMENTO EXTERIOR
    pointer encadeamento_exterior = NULL;
    printf("\nENCADEAMENTO EXTERIOR\n\nDigite a quantia de chaves a serem armazenadas (MAX %d): ", MAX);
    scanf("%d", &n);
    printf("\n");
    for(i=0; i<n; i++){
        printf("(%d) Digite a posicao e a chave: ", i+1);
        scanf("%d %d", &posicao, &chave);
        guarda_chaves_encadeamento_exterior(&encadeamento_exterior, chave, posicao);
    }
    printf("\nEncadeamento exterior:\n");
    mostra_chaves_encadeamento_exterior(encadeamento_exterior);
    ////////////////////
};