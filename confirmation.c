/* author of function: Daria Ivica */
#include "password_manager.h"
#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* malloc */

/* #define DEBUG */

/*
 * This function ask user for confirmation before completing an action,
 * such as updating/deleting passwords.
 * Input: none.
 * Output: string containing confirmation from user.
 */
char* confirmation() 
{
    /* confirm Y/N to update password */
	char* confirmation = malloc(sizeof(char)*2);

	scanf("%s", confirmation);
	int valid = 0; /* 0=false, 1=true */
	if((confirmation[0]=='Y') || (confirmation[0]=='N'))
	{
        valid = 1;
	}

    while(!valid)
	{
	    printf("Enter valid response. (Enter Y/N)> \n");
		scanf("%s", confirmation);
		if((confirmation[0]=='Y') || (confirmation[0]=='N'))
		{
		    valid = 1;
		}
	}

	#ifdef DEBUG
	    printf("confirmation from user: %s ", confirmation);
		if(valid)
		{
			printf("was declared valid\n");
		} else {
			printf("was declared invalid\n");
		}
	#endif

	return confirmation;
}
