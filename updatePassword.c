/* authors of function: Nicholas Yeadon and Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf, scanf */
#include <string.h> /* strcmp, strcpy */

/* #define DEBUG */

/*
 * This function will update an existing password from the list of stored
 * passwords.
 * Input: pointer to linked list and string of website name.
 * Output: none.
 */
void updatePassword(password_t** list, char* website)
{
	char username[MAX_STRING_LENGTH];
	char password[MAX_STRING_LENGTH];

    password_t *temp = *list; 

    printf("Would you like to update that password? (Enter Y/N)> ");
    char* confirm = confirmation();

    if(strcmp(confirm, "Y")==0) 
	/* user would like to update password */
	{
	    printf("Enter username: ");
        scanf(" %[^\n]", username);

        /* username can only be max 25 chars long */
		while(strlen(username)>=MAX_STRING_LENGTH)
		{
			printf("Username exceeds maximum length of %d characters.\n"
				"Enter valid username > ", MAX_STRING_LENGTH-1);
			scanf(" %[^\n]", username);
			
		}
		username[MAX_STRING_LENGTH-1] = '\0'; /* null terminate */

		printf("Want to generate a random password? (Y/N)> ");
		char* confirm = confirmation();
		if(strcmp(confirm, "Y")==0) 
		/* random password is generated and used for that account */
		{
			strcpy(password, generatePassword());

		} else {
			/* user has chosen to enter their own password instead of random one */
			printf("Password NOT generated. Enter your own password: ");
			scanf(" %[^\n]", password);
		}
        
		/* username can only be max 25 chars long */
		while(strlen(password)>=MAX_STRING_LENGTH)
		{
			printf("Password exceeds maximum length of %d characters.\n"
				"Enter valid password > ", MAX_STRING_LENGTH-1);
			scanf(" %[^\n]", password);
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

		while(temp!=NULL)
		{
            if(strcmp(temp->website, website)==0)
			{
				/* update username and password */
                temp->username = compressedUsername;
                temp->password = compressedPassword;
                *list = temp;
                break;
            }
            temp = temp->nextp;
        } 
		printf("Password updated.\n");
	} else {
		/* user does not want info updated */
	    printf("Password NOT updated.\n");
		return;
    }

	#ifdef DEBUG
	    printf("new password: %s\n", password);
        printf("new username: %s\n", username);
	#endif
}
