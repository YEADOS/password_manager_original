/* author of this function: Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf */

/*
 * This function prints the initial menu with all options of functions
 * the program can do.
 * Inputs: none.
 * Outputs: none.
 */
void printMenu(void)
{
    printf("\nPassword Manager\n"
    	"1. Add password\n"
    	"2. Delete password\n"
    	"3. Access password\n"
    	"4. View All Passwords\n"
		"5. Exit the program\n"
		"Enter your choice> \n");
}
