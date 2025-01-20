#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/grid.h"

static bool can_place(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[start_row + i][start_col + j] == num) {
                return false;
            }
        }
    }

    return true;
}

static bool fill_grid(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (row == GRID_SIZE) return true;
    if (col == GRID_SIZE) return fill_grid(grid, row + 1, 0);

    if (grid[row][col] != 0) return fill_grid(grid, row, col + 1);

    for (int num = 1; num <= GRID_SIZE; ++num) {
        if (can_place(grid, row, col, num)) {
            grid[row][col] = num;
            if (fill_grid(grid, row, col + 1)) return true;
            grid[row][col] = 0;
        }
    }

    return false;
}

static void shuffle(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i += 3) {
        for (int j = 0; j < 3; ++j) {
            int swap = rand() % 3;
            for (int col = 0; col < GRID_SIZE; ++col) {
                int temp = grid[i + j][col];
                grid[i + j][col] = grid[i + swap][col];
                grid[i + swap][col] = temp;
            }
        }
    }
}

static void generate_full_grid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = 0;
        }
    }

    fill_grid(grid, 0, 0);
    shuffle(grid);
}

static void remove_numbers(SudokuGrid *grid, int difficulty) {
    int cells_to_remove;
    switch (difficulty) {
        case 1: cells_to_remove = 30; break;
        case 2: cells_to_remove = 45; break;
        case 3: cells_to_remove = 60; break;
        default: cells_to_remove = 45;
    }

    while (cells_to_remove > 0) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        if (grid->cells[row][col] != 0) {
            grid->cells[row][col] = 0;
            grid->fixed[row][col] = false;
            cells_to_remove--;
        }
    }
}

void generate_grid(SudokuGrid *grid, int level) {
    srand(time(NULL));

    int temp_grid[GRID_SIZE][GRID_SIZE];
    generate_full_grid(temp_grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid->cells[i][j] = temp_grid[i][j];
            grid->fixed[i][j] = (temp_grid[i][j] != 0);
        }
    }

    remove_numbers(grid, level);
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
