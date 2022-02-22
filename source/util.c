#include "util.h"

void print_matrix(int matrix[4][3]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}