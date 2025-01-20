#include <stdio.h>
#include "../include/game.h"
#include "../include/utils.h"

void start_game() {
    SudokuGrid grid;
    int level;

    printf("Choose Level 1 for easy, 2 for medium, 3 for hard: ");
    scanf("%d", &level);

    generate_grid(&grid, level);
    while (!is_complete(&grid)) {
        clear_screen();
        display_grid(&grid);

        int row, col, value;
        printf("Enter the row 1-9, column 1-9 and value 1-9 ");
        scanf("%d %d %d", &row, &col, &value);

        if (is_valid(&grid, row - 1, col - 1, value)) {
            grid.cells[row - 1][col - 1] = value;
        } else {
            printf("Invalid value\n");
        }
    }
    printf("Well, you have completed the grid !\n");
}
