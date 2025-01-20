#include <stdio.h>
#include "../include/utils.h"

void clear_screen() {
    printf("\033[H\033[J");
}
