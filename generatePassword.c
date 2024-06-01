/* author of function: Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, rand, srand */
#include <time.h> /* time */

/* #define DEBUG */

/* Function to generate a random uppercase letter.
 * No input, output is random uppercase letter.
 */
char randomUppercase()
{
    #ifdef DEBUG
        printf("random uppercase generated.\n");
    #endif
    return 'A' + rand() % 26;
}

/* Function to generate a random lowercase letter.
 * No input, output is random lowercase letter.
 */
char randomLowercase()
{
    #ifdef DEBUG
        printf("random lowercase generated.\n");
    #endif
    return 'a' + rand() % 26;
}

/* Function to generate a random digit.
 * No input, output is random digit.
 */
char randomDigit()
{
    #ifdef DEBUG
        printf("random digit generated.\n");
    #endif
    return '0' + rand() % 10;
}

/* Function to generate a random special character.
 * No input, output is random special character.
 */
char randomSpecial()
{
    char specialChars[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    #ifdef DEBUG
        printf("random special generated.\n");
    #endif 
    return specialChars[rand() % (sizeof(specialChars) - 1)];
}

/* Function to generate a random password.
 * No input, output is the generated password.
 */
char* generatePassword()
{
    srand(time(0)); 
    /* seeds the random number generator with the current time to ensure
    it is different every time the program runs */

    char* password = (char*)malloc(sizeof(char)*MAX_STRING_LENGTH);
    /* allocate memory for password */

    /* generate a random password */
    /* passwords often require at least one uppercase, lowercase,
    number and special character, therefore will do one of each first
    to ensure this is the case, making rest of password random
	(not the most ideal method) */
    password[0] = randomUppercase();
    password[1] = randomLowercase();
    password[2] = randomDigit();
    password[3] = randomSpecial();
    
    int i;
    for(i=4; i<MAX_STRING_LENGTH-1; i++)
    {
        int randomInt = rand() % 4; /* different for each iteration of loop */

        #ifdef DEBUG
            printf("random value: %d\n", randomInt);
        #endif 

        if(randomInt==0) 
        {
            password[i] = randomUppercase();
        } else if(randomInt==1)
        {
            password[i] = randomLowercase();
        } else if(randomInt==2)
        {
            password[i] = randomDigit();
        } else if(randomInt==3)
        {
            password[i] = randomSpecial();
        }
    }
    password[MAX_STRING_LENGTH-1] = '\0'; /* null-terminate the string */

    /* print the generated password for user to see */
    printf("Generated Password: %s\n", password);
    return password;
}

