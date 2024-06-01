/* author of function: Nicholas Yeadon */
#include "password_manager.h"
#include <stdio.h> /* printf, sprintf */
#include <string.h> /* strlen, strcpy */

/* #define DEBUG */

/*
 * This function will retrieve all existing password from the list of stored
 * passwords for the user to view and use.
 * Input: Linked list.
 * Output: none.
 */
void viewPasswords(password_t* list)
{
    password_t *temp = list;
    password_t *max = list; 

    int maxWebName = DEAULT_TABLE_LENGTH;
    int maxUserName = DEAULT_TABLE_LENGTH;
    int maxPassName = DEAULT_TABLE_LENGTH;
    
    while(max != NULL)
    {
        char username[MAX_LENGTH];
        strcpy(username, max->username.str);
		encrypt(username, cryptkey);
        #ifdef DEBUG
            printf("compressed unencrypted username code: %s\n", 
            username);
        #endif
        strcpy(username, decompress(max->username.tree, username));
        #ifdef DEBUG
            printf("decompressed unencrypted username: %s\n", 
            username);
        #endif

        char password[MAX_LENGTH];
		strcpy(password, max->password.str);
		encrypt(password, cryptkey);
        #ifdef DEBUG
            printf("compressed unencrypted password code: %s\n", 
            password);
        #endif
        strcpy(password, decompress(max->password.tree, password));
        #ifdef DEBUG
            printf("decompressed unencrypted password: %s\n", 
            password);
        #endif
        
        /* update max lengths */
        if(strlen(max->website) > maxWebName)
        {
            maxWebName = strlen(max->website);
        }
        if(strlen(username) > maxUserName) 
        {
            maxUserName = strlen(username);
        }
        if(strlen(password) > maxPassName) 
        {
            maxPassName = strlen(password);
        }
        max = max->nextp;
    }
    #ifdef DEBUG
        printf("Reset of table length successfully completed.\n");
    #endif

    char formatHeader[MAX_TABLE_LENGTH];
    char formatData[MAX_TABLE_LENGTH];
    sprintf(formatHeader, "| %%-%ds | %%-%ds | %%-%ds |\n", 
    maxWebName, maxUserName, maxPassName);
    sprintf(formatData, "| %%-%ds | %%-%ds | %%-%ds |\n", 
    maxWebName, maxUserName, maxPassName);
    
    /* Print header */
    printf(formatHeader, "Website", "Username", "Password");
    printf("+");
    int i;
    for(i = 0; i < maxWebName + 2; i++) printf("-");
    printf("+");
    for(i = 0; i < maxUserName + 2; i++) printf("-");
    printf("+");
    for(i = 0; i < maxPassName + 2; i++) printf("-");
    printf("+\n");

    #ifdef DEBUG
        printf("Header printed successfully.\n");
    #endif
    
    while(temp != NULL)
    {
        char username[MAX_LENGTH];
        strcpy(username, temp->username.str);
		encrypt(username, cryptkey);
        #ifdef DEBUG
            printf("compressed unencrypted username code: %s\n", 
            username);
        #endif
        strcpy(username, decompress(temp->username.tree, username));
        #ifdef DEBUG
            printf("decompressed unencrypted username: %s\n", 
            username);
        #endif

        char password[MAX_LENGTH];
		strcpy(password, temp->password.str);
		encrypt(password, cryptkey);
        #ifdef DEBUG
            printf("compressed unencrypted password code: %s\n", 
            password);
        #endif
        strcpy(password, decompress(temp->password.tree, password));
        #ifdef DEBUG
            printf("decompressed unencrypted password: %s\n", 
            password);
        #endif
        
        /* Print data */
        printf(formatData, temp->website, username, password);
        temp = temp->nextp;
    }
}
