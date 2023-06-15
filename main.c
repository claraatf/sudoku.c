#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

// Estrutura para armazenar estatísticas do jogador
typedef struct {
    char nome[50];
    int numJogos;
    int numVitorias;
    int numJogadas;
} EstatisticasJogador;

// Função para exibir o tabuleiro do Sudoku com grades
void exibirTabuleiro(int tabuleiro[SIZE][SIZE]) {
    int i, j;
    
    for (i = 0; i < SIZE; i++) {
        // Imprime a linha horizontal superior da grade
        if (i % 3 == 0) {
            printf("-------------------------\n");
        }
        
        for (j = 0; j < SIZE; j++) {
            // Imprime a linha vertical da grade
            if (j % 3 == 0) {
                printf("| ");
            }
            
            // Imprime o valor do tabuleiro
            printf("%d ", tabuleiro[i][j]);
        }
        
        // Imprime a linha vertical da grade e quebra de linha
        printf("|\n");
    }
    
    // Imprime a linha horizontal inferior da grade
    printf("-------------------------\n");
}

// Função para verificar se o valor é válido em uma determinada posição
int verificarValor(int tabuleiro[SIZE][SIZE], int linha, int coluna, int valor) {
    int i, j;

    // Verificar a linha e coluna
    for (i = 0; i < SIZE; i++) {
        if (tabuleiro[linha][i] == valor || tabuleiro[i][coluna] == valor) {
            return 0;
        }
    }

    // Verificar o bloco 3x3
    int blocoLinha = linha - (linha % 3);
    int blocoColuna = coluna - (coluna % 3);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[blocoLinha + i][blocoColuna + j] == valor) {
                return 0;
            }
        }
    }

    return 1;
}

// Função para preencher o tabuleiro do Sudoku
void preencherTabuleiro(int tabuleiro[SIZE][SIZE]) {
    // Lógica para preencher o tabuleiro inicial (pode ser substituída por sua própria lógica de geração)
    // O exemplo abaixo preenche o tabuleiro com valores de 1 a 9 nas posições diagonais
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i == j) {
                tabuleiro[i][j] = i + 1;
            } else {
                tabuleiro[i][j] = 0;
            }
        }
    }
}

// Função para atualizar as estatísticas do jogador
void atualizarEstatisticas(EstatisticasJogador *estatisticas, int vitoria, int numJogadas) {
    estatisticas->numJogos++;
    if (vitoria) {
        estatisticas->numVitorias++;
    }
    estatisticas->numJogadas += numJogadas;
}

// Função para exibir as estatísticas do jogador
void exibirEstatisticas(EstatisticasJogador estatisticas) {
    printf("Estatísticas do Jogador:\n");
    printf("Nome: %s\n", estatisticas.nome);
    printf("Número de Jogos: %d\n", estatisticas.numJogos);
    printf("Número de Vitórias: %d\n", estatisticas.numVitorias);
    printf("Número de Jogadas: %d\n", estatisticas.numJogadas);
}

int main() {
    int tabuleiro[SIZE][SIZE];
    int linha, coluna, valor;
    int numJogadas = 0;
    EstatisticasJogador estatisticas;
    
    printf("Digite o nome do jogador: ");
    fgets(estatisticas.nome, sizeof(estatisticas.nome), stdin);
    estatisticas.nome[strcspn(estatisticas.nome, "\n")] = '\0';

    preencherTabuleiro(tabuleiro);
    
    while (1) {
        exibirTabuleiro(tabuleiro);
        
        printf("Digite a linha, coluna e valor (separados por espaço): ");
        scanf("%d %d %d", &linha, &coluna, &valor);
        
        if (verificarValor(tabuleiro, linha, coluna, valor)) {
            tabuleiro[linha][coluna] = valor;
            numJogadas++;
        } else {
            printf("Valor inválido! Tente novamente.\n");
        }
        
        // Verificar se o tabuleiro está completo
        int completo = 1;
        for (linha = 0; linha < SIZE; linha++) {
            for (coluna = 0; coluna < SIZE; coluna++) {
                if (tabuleiro[linha][coluna] == 0) {
                    completo = 0;
                    break;
                }
            }
            if (!completo) {
                break;
            }
        }
        
        if (completo) {
            printf("Parabéns! Você completou o Sudoku.\n");
            atualizarEstatisticas(&estatisticas, 1, numJogadas);
            break;
        }
    }
    
    exibirEstatisticas(estatisticas);
    
    return 0;
}
