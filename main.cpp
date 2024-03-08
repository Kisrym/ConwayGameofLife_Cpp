#include <iostream>
#include <vector>
#include <array>
#include<cstdlib>

std::vector<std::vector<char>> tabuleiro;

// constantes
const int SIZE = 10;
const char CEL_VIVA = '*';
const char CEL_MORTA = '.';

void initializeBoard(int random_cells = 0) {
    for (int k=0; k < SIZE; k++) {
        tabuleiro.push_back(std::vector<char>(SIZE, CEL_MORTA)); // adiciona as linhas com célula morta para cada coluna
    }
    if (random_cells != 0) {
        std::srand((unsigned) time(NULL));
        for (int i = 0; i < random_cells; i++){
            int x = std::rand() % 10; // valores randômicos entre 0 e 10
            int y = std::rand() % 10;

            tabuleiro[x][y] = CEL_VIVA;
        }
    }
}

void setInitialState() {
    std::vector<std::array<int, 2>> coordenadas;
    int x, y;

    std::cout << "Digite a coordenada que você quer a célular viva (x y).\nEscolha -1 -1 para parar\n";
    while (true) {
        std::cin.clear();

        if (!(std::cin >> x >> y)){
            throw std::invalid_argument("Entrada inválida: O input deve ser um inteiro");
        }

        if (x == -1 && y == -1){
            break;
        }

        // corrigindo o index do input
        x -= 1;
        y -= 1;

        std::array<int, 2> arr = {x, y};
        coordenadas.push_back(arr);
    }

    for (auto &v : coordenadas) {
        for (int x=0; x < tabuleiro.size(); x++) {
            for (int y=0; y < tabuleiro[x].size(); y++) {
                if (x == v[0] && y == v[1]) {
                    tabuleiro[x][y] = CEL_VIVA;
                }
            }
        }
    }
}

void printBoard() {
    std::cout << "-------------------" << std::endl;
    for (auto v : tabuleiro) {
        for (int c=0; c < v.size(); c++) {
            std::cout << v[c] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------" << std::endl;
}

bool next(int x_atual, int y_atual) {
    std::vector<std::vector<char>> newBoard = tabuleiro; // modificando a cópia em vez do tabuleiro real evita erros nas evoluções deste

    for (int x = x_atual; x < SIZE; x++) {
        for (int y = y_atual; y < SIZE; y++) {
            int count = 0;

            for (int x_char = -1; x_char <= 1; x_char++) { // percorre por todas as células adjacentes possíveis
                for (int y_char = -1; y_char <= 1; y_char++) { // (incluindo as diagonais)
                    int newX = x + x_char, newY = y + y_char;

                    if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && !(x_char == 0 && y_char == 0)) { // evita a nova coordenada estar fora do limite do tabuleiro e de ela ser a célula analisada
                        if (tabuleiro[newX][newY] == CEL_VIVA) {
                            count++; // conta os vizinhos
                        }
                    }
                }
            }
            if (count < 2 || count > 3) {
                newBoard[x][y] = CEL_MORTA;

            }
            else if (count == 3 && tabuleiro[x][y] == '.') {
                newBoard[x][y] = CEL_VIVA;
            }
        }
    }

    bool changed = tabuleiro != newBoard; // retorna se o tabuleiro foi modificado ou não
    tabuleiro = newBoard;
    return changed;
}

int main()
{
    initializeBoard(10);
    setInitialState();
    printBoard();

    int x = 0, y = 0;
    while(next(x, y)) {
        printBoard();
        x++;
        y++;
    }

    return 0;
}
