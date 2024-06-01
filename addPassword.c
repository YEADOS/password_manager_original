/* authors of function: Nicholas Yeadon and Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy, strlen */

/* #define DEBUG */

/*
 * This function adds a new password to the list of existing passwords.
 * Input is a pointer to the linked lis of all passwords.
 * Output is an int that can be used to determine success/failure of 
 * adding the password.
 */
 int addPassword(password_t** list)
 {
	char username[MAX_STRING_LENGTH];
	char password[MAX_STRING_LENGTH];
	char website[MAX_LENGTH];

	/* Get user input for password, username, website */
	printf("Enter website: ");
    scanf(" %[^\n]", website);

	/* separate function to check if website exists */
	if(exists(*list, website) == 1)
	{
		printf("Password already stored for given website.\n");
		updatePassword(list, website);
		return 0;
	}

	printf("Enter username: ");
    scanf(" %[^\n]", username);
	#ifdef DEBUG
	    printf("username: %s\n", username);
	#endif

    /* username can only be max 25 chars long */
	while(strlen(username)>=MAX_STRING_LENGTH)
	{
		printf("Username exceeds maximum length of %d characters.\n"
		    "Enter valid username > ", MAX_STRING_LENGTH-1);
		scanf(" %[^\n]", username);
		#ifdef DEBUG
			printf("username: %s\n", username);
		#endif
	}
	username[MAX_STRING_LENGTH-1] = '\0'; /* null terminate */

    printf("Want to generate a random password? (Y/N)> ");
	char* confirm = confirmation();
	if(strcmp(confirm, "Y")==0) 
	/* random password is generated and used for that account */
	{
		strcpy(password, generatePassword());
	} else {
		/* user has chosen to enter their own password instead of make random one */
		printf("Password NOT generated. Enter your own password: ");
        scanf(" %[^\n]", password);
	}
	#ifdef DEBUG
	    printf("password: %s\n", password);
	#endif

    /* username can only be max 25 chars long */
	while(strlen(password)>=MAX_STRING_LENGTH)
	{
		printf("Password exceeds maximum length of %d characters.\n"
		    "Enter valid password > ", MAX_STRING_LENGTH-1);
		scanf(" %[^\n]", password);
		#ifdef DEBUG
			printf("password: %s\n", password);
		#endif
	}
	password[MAX_STRING_LENGTH-1] = '\0'; /* null terminate */

	/* compress password and username */
	compressedString_t compressedPassword = compress(password);
	compressedString_t compressedUsername = compress(username);
	#ifdef DEBUG
	    printf("compressed password code: %s\n", compressedPassword.str);
		printf("compressed username code: %s\n", compressedUsername.str);
	#endif

	/* encrypt password and username */
	encrypt(compressedPassword.str, cryptkey);
	encrypt(compressedUsername.str, cryptkey);

	#ifdef DEBUG
	    printf("encrypted password: %s\n", compressedPassword.str);
		printf("encrypted username: %s\n", compressedUsername.str);
	#endif
		
	/* Create new password_t struct node for list */
	password_t* newPass = (password_t*)malloc(sizeof(password_t));
	
	if (newPass == NULL)
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	/* assign values and assign next pointer to list */
	newPass->username = compressedUsername;
	newPass->password = compressedPassword;
	strcpy(newPass->website, website);
	newPass->nextp = NULL; /* initialise next to null */

	/* Traverse the list to find the correct position for insertion.
	List is organiseed alphabetically by website */
    password_t* prev = NULL;
    password_t* curr = *list;
    while(curr != NULL && strcmp(curr->website, website) < 0)
	{
        prev = curr;
        curr = curr->nextp;
    }

    /* insert the new node into the list */
    if(prev == NULL) /* new node is inserted at the beginning */
	{
        newPass->nextp = *list;
        *list = newPass;
    } else {
        prev->nextp = newPass;
        newPass->nextp = curr;
    }
	
	return 0;
 }
