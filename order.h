/**
 * @file 
 * @brief Creates the order matrix and includes functions
 * to initialize, update and clear orders
 */


#define NUMBER_OF_FLOORS 4
#define NUMBER_OF_BUTTONS 3

int orders[NUMBER_OF_FLOORS][NUMBER_OF_BUTTONS];

/**
 * @brief initialize the orders matrix as a 4 by 3 matrix filled with zeros
 * 
 */
void order_initialize();

/**
 * @brief looks for new button pushes and adds them to the orders as a 1 at the location of the button [f][b],
 * where f is the floor and b is the button type, up, down or hallbutton. 
 * 
 */
void order_update_orders();

/**
 * @brief searches through the orders to look for entries
 * @return the floor @p f where the entry was found. -1 if nothing is found.
 * 
 */
int order_find_entry();

/**
 * @brief clears all button orders in a specific floor. (Clears one row in the order matrix)
 * @param floor which is to be cleared
 * 
 */
void order_clear_row(int floor);

/**
 * @brief helper function that prints the orders matrix
 * 
 */
void order_print_orders();