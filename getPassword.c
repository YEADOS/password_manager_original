/* authors of function: Nicholas Yeadon */
#include "password_manager.h"
#include <stdio.h> /* printf, scanf */
#include <string.h> /* strcpy, strcmp */

/* #define DEBUG */

/*
 * This function will retrieve an existing password from the list of stored
 * passwords for the user to then use.
 * Input: Linked list.
 * Output: none.
 */
void getPassword(password_t* list)
{
	printf("Retrieving Password...\n");

	/* Get user input for website of password they want to see*/
	char website[MAX_LENGTH];
	printf("Enter website associated with password: ");
    scanf("%s", website);

	if(exists(list, website) != 1)
	{
		printf("No password saved for this website.");
		return; 
	}

	password_t *temp = list; 
	char password[MAX_LENGTH];
	char username[MAX_LENGTH];
    while(temp != NULL)
	{
		if(strcmp(temp->website, website)==0)
		{
			/* once website is found, decompress and decrypt password and username */
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

			break; 
		}
        temp = temp->nextp;
    }

    /* set lengths */
	int lenWebsite = strlen(website);
    int lenUsername = strlen(username);
    int lenPassword = strlen(password);

	if(lenWebsite < 7) {lenWebsite = 7;}
	if(lenUsername < 8) {lenUsername = 8;}
	if(lenPassword < 8) {lenPassword = 8l;}

    char formatHeader[MAX_TABLE_LENGTH];
    char formatData[MAX_TABLE_LENGTH];
    sprintf(formatHeader, "| %%-%ds | %%-%ds | %%-%ds |\n", 
    lenWebsite, lenUsername, lenPassword);
    sprintf(formatData, "| %%-%ds | %%-%ds | %%-%ds |\n", 
    lenWebsite, lenUsername, lenPassword);

	/* print header */
	printf("\n");
    printf(formatHeader, "Website", "Username", "Password");
    printf("+");
    int i;
    for(i = 0; i < lenWebsite + 2; i++) printf("-");
    printf("+");
    for(i = 0; i < lenUsername + 2; i++) printf("-");
    printf("+");
    for(i = 0; i < lenPassword + 2; i++) printf("-");
    printf("+\n");

    /* print data */
	printf(formatData, temp->website, username, password);
	printf("\n");

    /* see if user wants to update details for this website */
	updatePassword(&list, website);
}
