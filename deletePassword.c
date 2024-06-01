/* author of function: Nicholas Yeadon and Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */

/*
 * This function removes a password in the list of existing passwords
 * upon user request.
 * Inputs are pointer to linked list of all passwords and a string which is
 * the name of the website associated with password to be deleted.
 * No output.
 */
void deletePassword(password_t **list, char* website) 
{
	password_t *temp = *list;
	password_t *prev = NULL;  

	while(temp != NULL)
	{
		if(strcmp(temp->website, website)==0) /* password found */
		{
			printf("Want to delete password for \"%s\"? (Enter Y/N)> \n", website);
			char* confirm = confirmation();
			if(strcmp(confirm, "Y")==0) 
			/* user confirms they would like to delete password */
			{
				if(prev==NULL) /* password is first in list */
				{
					*list = temp->nextp; 
					free(temp);
					printf("Password for website \"%s\" deleted.\n", website); 
					return; 
				}
				/* password NOT first in list */
				prev->nextp = temp->nextp;
				printf("Password for website \"%s\" deleted.\n", website); 
				return; 
			}
			printf("Password for website \"%s\" NOT deleted.\n", website); 
			return;
		}
		/* password not found yet, continue traversing list */
		prev = temp; 
		temp = temp->nextp; 
	}

    /* if we reach here, whole list has been traversed with no website found
	matching input */
	printf("Password Deletetion Error.\n");
	printf("Password for this website does not exist.\n");
}
