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
        printf("Entrez la ligne (1-9), la colonne (1-9) et la valeur (1-9): ");
        scanf("%d %d %d", &row, &col, &value);

        if (is_valid(&grid, row - 1, col - 1, value)) {
            grid.cells[row - 1][col - 1] = value;
        } else {
            printf("Valeur invalide ! Réessayez.\n");
        }
    }

    printf("Félicitations, vous avez complété la grille !\n");
}
