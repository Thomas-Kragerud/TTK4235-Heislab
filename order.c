/**
 * @file order.c
 * @brief Implements the order matrix and its functions.
 * 
 */


#include "order.h"
#include <stdio.h>
#include <stdlib.h>


int orders[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];


void order_initialize() {
    for (int i = 0; i < NUMBER_OF_FLOORS; ++i) {
        for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
            orders[i][j] = 0;
        }
    }
}

void order_update_orders() {
    for (int f = 0; f < NUMBER_OF_FLOORS; ++f) {
        for (int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
            int btnPressed = elevio_callButton(f, b);//f is floor and b is buttontype [up, down, hb]
            if (btnPressed == 1) {
                orders[f][b] = btnPressed;
            }
        }
    }
}

int order_find_entry() {
    for (int f = 0; f < NUMBER_OF_FLOORS; ++f) {
        for (int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
            if (orders[f][b] == 1) {
                return f;
            }
        }
    }
    return -1;
}

void order_clear_row(int floor) {
    for (int b = 0; b < NUMBER_OF_BUTTONS; ++b) {
        orders[floor][b] = 0;

    }
}

void order_print_orders() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", orders[i][j]);
        }
        printf("\n");
    }
}
