#include "cartas.h"
#include "utils.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Carta deck[MAX_CARTAS];
int totalCartas = 0;

void listarCartas() {
    if (totalCartas == 0) {
        printf("Deck vazio!\n");
        return;
    }
    for (int i = 0; i < totalCartas; i++) {
        printf("%d - %s | Ataque: %.2f | Defesa: %.2f | Velocidade: %.2f | HP: %.2f | %s\n",
       i + 1, deck[i].nome, deck[i].ataque, deck[i].defesa, deck[i].velocidade, deck[i].hp,
       deck[i].superTrunfo ? "Super Trunfo" : "Normal");

    }
}

void inserirCarta() {
    if (totalCartas >= MAX_CARTAS) {
        printf("O deck está cheio! Não é possível adicionar mais cartas.\n");
        return;
    }

    Carta novaCarta;
    int temp;  // Variável temporária para armazenar a entrada do Super Trunfo

    printf("Nome da carta: ");
    scanf(" %[^\n]", novaCarta.nome);

    printf("Ataque: ");
    scanf("%f", &novaCarta.ataque);

    printf("Defesa: ");
    scanf("%f", &novaCarta.defesa);

    printf("Velocidade: ");
    scanf("%f", &novaCarta.velocidade);

    printf("HP: ");
    scanf("%f", &novaCarta.hp);

    printf("É Super Trunfo? (1-Sim / 0-Não): ");
    scanf("%d", &temp);
    novaCarta.superTrunfo = (temp == 1);

    // Se a carta for um Super Trunfo, remover qualquer outro Super Trunfo existente
    if (novaCarta.superTrunfo) {
        for (int i = 0; i < totalCartas; i++) {
            if (deck[i].superTrunfo) {
                deck[i].superTrunfo = 0;  // Remove o status de Super Trunfo da carta anterior
                printf("A carta '%s' perdeu o status de Super Trunfo.\n", deck[i].nome);
                break;  // Garante que apenas um Super Trunfo exista
            }
        }
    }

    // Adiciona a nova carta ao deck
    deck[totalCartas++] = novaCarta;
    printf("Carta '%s' adicionada com sucesso!\n", novaCarta.nome);
    salvarDeck();
}

void carregarCartasDoCSV() {
    FILE *arquivo = fopen("data/cartas.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo CSV!\n");
        return;
    }

    char linha[100];
    totalCartas = 0;

    // Pula a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (totalCartas >= MAX_CARTAS) {
            printf("Número máximo de cartas atingido!\n");
            break;
        }

        Carta novaCarta;
        int superTrunfo;

        int resultado = sscanf(linha, "%49[^,],%f,%f,%f,%f,%d",
                               novaCarta.nome, 
                               &novaCarta.ataque, &novaCarta.defesa,
                               &novaCarta.velocidade, &novaCarta.hp,
                               &superTrunfo);

        if (resultado == 6) {  
            novaCarta.superTrunfo = (superTrunfo == 1);
            deck[totalCartas++] = novaCarta;
        } else {
            printf("Erro ao ler a linha: %s\n", linha);
        }
    }

    fclose(arquivo);
    printf("Cartas carregadas com sucesso! Total: %d\n", totalCartas);
}

void salvarCartasBinario() {
    FILE *arquivo = fopen("data/cartas.bin", "wb");
    if (!arquivo) {
        printf("Erro ao salvar o deck!\n");
        return;
    }
    fwrite(&totalCartas, sizeof(int), 1, arquivo);
    fwrite(deck, sizeof(Carta), totalCartas, arquivo);
    fclose(arquivo);
    printf("Deck salvo com sucesso!\n");
}

void carregarCartasBinario() {
    FILE *arquivo = fopen("data/cartas.bin", "rb");
    if (!arquivo) {
        printf("Arquivo binário não encontrado. Iniciando um novo deck.\n");
        return;
    }
    fread(&totalCartas, sizeof(int), 1, arquivo);
    fread(deck, sizeof(Carta), totalCartas, arquivo);
    fclose(arquivo);
}

void alterarCarta() {
    listarCartas();
    if (totalCartas == 0) {
        return;
    }

    int indice;
    char entrada[50];  // Buffer para leitura segura de entrada do usuário
    
    printf("\nDigite o número da carta que deseja alterar (1 a %d): ", totalCartas);
    if (!fgets(entrada, sizeof(entrada), stdin) || sscanf(entrada, "%d", &indice) != 1) {
        printf("Entrada inválida!\n");
        return;
    }

    if (indice < 1 || indice > totalCartas) {
        printf("Número inválido!\n");
        return;
    }

    Carta *carta = &deck[indice - 1];

    printf("Nome da carta: ");
    if (!fgets(carta->nome, sizeof(carta->nome), stdin)) {
        printf("Erro ao ler o nome!\n");
        return;
    }
    carta->nome[strcspn(carta->nome, "\n")] = 0;  // Remove o '\n'

    // Função auxiliar para validar entradas numéricas
    float valor;
    
    printf("Ataque: ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%f", &valor) == 1) {
            carta->ataque = valor;
            break;
        }
        printf("Entrada inválida! Digite um número: ");
    }

    printf("Defesa: ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%f", &valor) == 1) {
            carta->defesa = valor;
            break;
        }
        printf("Entrada inválida! Digite um número: ");
    }

    printf("Velocidade: ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%f", &valor) == 1) {
            carta->velocidade = valor;
            break;
        }
        printf("Entrada inválida! Digite um número: ");
    }

    printf("HP: ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%f", &valor) == 1) {
            carta->hp = valor;
            break;
        }
        printf("Entrada inválida! Digite um número: ");
    }

    int escolha;
    printf("É Super Trunfo? (1-Sim / 0-Não): ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) && sscanf(entrada, "%d", &escolha) == 1 && (escolha == 0 || escolha == 1)) {
            carta->superTrunfo = escolha;
            break;
        }
        printf("Entrada inválida! Digite 1 para Sim ou 0 para Não: ");
    }

    printf("Carta alterada com sucesso!\n");
}

void excluirCarta() {
    listarCartas();
    if (totalCartas == 0) {
        return;
    }

    int indice;
    printf("\nDigite o número da carta que deseja excluir (1 a %d): ", totalCartas);
    scanf("%d", &indice);
    limparBuffer();

    if (indice < 1 || indice > totalCartas) {
        printf("Número inválido!\n");
        return;
    }

    for (int i = indice - 1; i < totalCartas - 1; i++) {
        deck[i] = deck[i + 1];
    }

    totalCartas--;
    printf("Carta excluída com sucesso!\n");
}

void pesquisarCarta() {
    char nomeBusca[50];

    printf("\nDigite o nome da carta para pesquisar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;  // Remove o '\n' lido pelo fgets

    printf("Nome buscado: '%s'\n", nomeBusca);  // Debug para verificar a entrada

    int encontrado = 0;
    for (int i = 0; i < totalCartas; i++) {
        if (strcmp(deck[i].nome, nomeBusca) == 0) {
            encontrado = 1;  // Agora ele registra que encontrou a carta
            printf("Carta encontrada:\n");
            printf("%d - %s | Ataque: %.2f | Defesa: %.2f | Velocidade: %.2f | HP: %.2f | %s\n",
                   i + 1, deck[i].nome, deck[i].ataque, deck[i].defesa, deck[i].velocidade, deck[i].hp,
                   deck[i].superTrunfo ? "Super Trunfo" : "Normal");
        }
    }

    if (!encontrado) {
        printf("Carta não encontrada.\n");
    }
}


