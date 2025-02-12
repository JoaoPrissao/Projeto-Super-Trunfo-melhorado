#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "cartas.h"
#include "io.h"
#include "utils.h"

int main() {
    int escolha;
    carregarDeck();

    do {
        printf("\n===== SUPER TRUNFO =====\n");
        printf(" 1. Listar Cartas\n");
        printf(" 2. Inserir Carta\n");
        printf(" 3. Alterar Carta\n");
        printf(" 4. Excluir Carta\n");
        printf(" 5. Pesquisar Carta\n");
        printf(" 6. Jogar Partida\n");
        printf(" 7. Exportar para CSV\n");
        printf(" 8. Salvar e Sair\n");
        printf("========================\n");
        printf("Escolha: ");

        scanf("%d", &escolha);
        limparBuffer();

        switch (escolha) {
            case 1:
                listarCartas();
                break;
            case 2:
                inserirCarta();
                break;
            case 3:
                alterarCarta();
                break;
            case 4: {
                char confirmacao;
                printf("Tem certeza que deseja excluir uma carta? (s/n): ");
                scanf(" %c", &confirmacao);
                limparBuffer();
                if (confirmacao == 's' || confirmacao == 'S') {
                    excluirCarta();
                } else {
                    printf("Exclusão cancelada.\n");
                }
                break;
            }
            case 5:
                pesquisarCarta();
                break;
            case 6:
                jogarPartida(deck, totalCartas);
                break;
            case 7:
                exportarParaCSV();
                break;
            case 8:
                salvarCartasBinario();
                printf("Deck salvo! Saindo...\n");
                break;
            default:
                printf("Opção inválida! Escolha um número entre 1 e 8.\n");
        }
    } while (escolha != 8);

    return 0;
}
