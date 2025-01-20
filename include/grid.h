#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define GRID_SIZE 9

typedef struct {
    int cells[GRID_SIZE][GRID_SIZE];
    bool fixed[GRID_SIZE][GRID_SIZE];
} SudokuGrid;

void generate_grid(SudokuGrid *grid, int level);
void display_grid(const SudokuGrid *grid);
bool is_valid(const SudokuGrid *grid, int row, int col, int value);
bool is_complete(const SudokuGrid *grid);

#endif // GRID_H
