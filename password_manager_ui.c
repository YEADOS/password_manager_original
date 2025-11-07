/* Group Number: 58
 * Lab Number: 05
 * Authors: Daria Ivica and Nicholas Yeadon
 * Enhanced UI Version with ncurses
 */
#include "password_manager.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* cryptkey = "I3<achgg5@#nb\\ksz";

/*
 * Main function with ncurses UI
 */
int main(void)
{
    password_t* passwords = NULL;
    int input = 0;

    /* Initialize the UI */
    initUI();

    while (input != 5)
    {
        /* Show menu and get selection */
        input = showMainMenu();

        switch(input)
        {
            case 1:
                displayAddPassword(&passwords);
                break;
            case 2:
                displayDeletePassword(&passwords);
                break;
            case 3:
                displayGetPassword(passwords);
                break;
            case 4:
                showPasswordTable(passwords);
                break;
            case 5:
                /* Exit */
                break;
            default:
                showMessage("Invalid selection. Please try again.", COLOR_ERROR);
        }
    }

    /* Cleanup UI */
    cleanupUI();
    printf("Thank you for using Password Manager!\n");

    return 0;
}

/*
 * Function to check that an input is an integer (for when a user selects
 * an option from the program's menu).
 * Input: string.
 * Output: integer (0 - false, 1 - true).
 */
int containInts(char string[]) {
    int len = strlen(string);
    int i;
    for(i = 0; i < len; i++) {
        if (string[i] < '0' || string[i] > '9') {
            return 0; /* False */
        }
    }
    return 1; /* True */
}

/*
 * Function to format a string.
 * Input is string to be formatted.
 * No outputs.
 */
void formatString(char* string) {
    int len = strlen(string);
    /* if string is shorter than MAX_NAME_SIZE remove the new line character and
    replace it with null character */
    if (len > 0 && string[len-1] == '\n') {
        string[len-1] = 0;
    }
    /* If the input is greater than the string buffer we want to remove any left
    over input in the standard input. This is necessary so that the next
    variable doesn't take these characters as values. */
    else {
        clearInput();
    }
}

/*
 * Function to clear input (stdin).
 * No inputs or outputs.
 */
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
