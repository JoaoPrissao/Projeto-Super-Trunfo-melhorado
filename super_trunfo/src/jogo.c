#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void jogarPartida(Carta deck[], int totalCartas) {
    if (totalCartas < 2) {
        printf("É necessário pelo menos 2 cartas para jogar!\n");
        return;
    }

    srand(time(NULL));

    int indiceJogador = rand() % totalCartas;
    int indiceComputador = rand() % totalCartas;
    while (indiceComputador == indiceJogador) {
        indiceComputador = rand() % totalCartas;
    }

    Carta jogador = deck[indiceJogador];
    Carta computador = deck[indiceComputador];

    printf("Sua carta: %s\n", jogador.nome);
    printf("Escolha um atributo para comparar: 1-Ataque, 2-Defesa, 3-Velocidade, 4-HP: ");
    int atributo;
    scanf("%d", &atributo);

    float valorJogador, valorComputador;
    switch (atributo) {
        case 1:
            valorJogador = jogador.ataque;
            valorComputador = computador.ataque;
            break;
        case 2:
            valorJogador = jogador.defesa;
            valorComputador = computador.defesa;
            break;
        case 3:
            valorJogador = jogador.velocidade;
            valorComputador = computador.velocidade;
            break;
        case 4:
            valorJogador = jogador.hp;
            valorComputador = computador.hp;
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("Carta do computador: %s\n", computador.nome);
    printf("Seu atributo: %.2f, Atributo do oponente: %.2f\n", valorJogador, valorComputador);

    if (valorJogador > valorComputador || jogador.superTrunfo) {
        printf("Você venceu!\n");
    } else if (valorComputador > valorJogador || computador.superTrunfo) {
        printf("Você perdeu!\n");
    } else {
        printf("Empate!\n");
    }
}
