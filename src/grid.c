#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/grid.h"

void generate_grid(SudokuGrid *grid, int level) {
    // Exemple simple de génération de grille (peut être amélioré)
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid->cells[i][j] = 0;
            grid->fixed[i][j] = false;
        }
    }
    // Ajouter des nombres fixes en fonction du niveau
    // Exemple : fixer quelques cases
    grid->cells[0][0] = 5;
    grid->fixed[0][0] = true;
    grid->cells[1][1] = 6;
    grid->fixed[1][1] = true;
}

void display_grid(const SudokuGrid *grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid->cells[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", grid->cells[i][j]);
            }
        }
        printf("\n");
    }
}

bool is_valid(const SudokuGrid *grid, int row, int col, int value) {
    if (grid->fixed[row][col] || grid->cells[row][col] != 0) {
        return false;
    }

    for (int i = 0; i < GRID_SIZE; ++i) {
        if (grid->cells[row][i] == value || grid->cells[i][col] == value) {
            return false;
        }
    }

    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid->cells[start_row + i][start_col + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool is_complete(const SudokuGrid *grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid->cells[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
