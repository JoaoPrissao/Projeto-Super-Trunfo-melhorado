#ifndef CARTAS_H
#define CARTAS_H

#include <stdbool.h>

#define MAX_CARTAS 100

typedef struct {
    char nome[50];
    char letra;
    int numero;
    float ataque;
    float defesa;
    float velocidade;
    float hp;
    bool superTrunfo;
} Carta;


extern Carta deck[MAX_CARTAS];
extern int totalCartas;

void listarCartas();
void inserirCarta();
void carregarCartasDoCSV();
void salvarCartasBinario();
void carregarCartasBinario();
void alterarCarta();
void excluirCarta();
void pesquisarCarta();



#endif
