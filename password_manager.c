/* Group Number: 58
 * Lab Number: 05
 * Authors: Daria Ivica and Nicholas Yeadon
 */
#include "password_manager.h"
#include <stdio.h> /* printf, scanf, fgets, getchar */
#include <stdlib.h> /* atoi */
#include <string.h> /* strlen */

char* cryptkey = "I3<achgg5@#nb\\ksz";  

/*
 * Main
 */
int main(void)
{
    password_t* passwords = NULL; 
    int input = 0;

	/* Toggle is a boolean variable used to ensure the program will clear the 
    input buffer if required. If the program uses scanf before using the fgets
    the buffer needs to be cleared, otherwise the program should keep the 
    buffer input as is */
	int toggle = 0; /* 0 = do nothing, 1 = clear buffer; */ 

    while(input != 5) 
    {
		printMenu();
		
		char num[MAX_LENGTH];
		do {
			if (toggle == 1) {
				clearInput();
			}
			fgets(num, MAX_LENGTH, stdin);
			formatString(num);
			if (containInts(num) != 1) {
				printf("Invalid input. Enter an integer.\n");
				printf("Enter your choice> \n");
			}
		}
		while (containInts(num) != 1);
		
		toggle = 1;

		/* Convert string to int */ 
		input = atoi(num);

		switch(input) 
		{
			case 1: 
				addPassword(&passwords);
				break;
			case 2:
				if(passwords==NULL)
				{
					/* no passwords saved to list so nothing to be deleted */
					printf("No passwords saved yet.\n");

				} else {
					printf("Enter website of password you want to delete: ");
					char website[MAX_LENGTH]; 
					scanf("%s", website);
					deletePassword(&passwords, website);
				}
				break; 
			case 3:
				if(passwords==NULL)
				{
					/* no passwords saved to list, so none to be retrieved */
					printf("No passwords saved yet.\n");
				} else {
					getPassword(passwords); 
				}
				break;
			case 4:
				if (passwords == NULL) 
				{
					printf("No passwords saved yet.\n");
				} else {
					viewPasswords(passwords);
				}
				toggle = 0;
				break;
			case 5:
				printf("Exiting program.\n");
				break;
			default: 
				printf("Invalid input. Please select again.\n");
		}
    }

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

