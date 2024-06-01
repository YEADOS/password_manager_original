/* author of function: Nicholas Yeadon */
#include "password_manager.h"
#include <stdio.h> /* printf */
#include <string.h> /* strlen */

/* #define DEBUG */

/*
 * This function will encrypt a new password before storing it in the list.
 * This function also will decrypt a password to show the password to the user.  
 * Inputs are ... 
 * No outputs.
 */
void encrypt(char* str, char *key)
{
	#ifdef DEBUG
		printf("string before encryption: %s\n", str);
	#endif 
	
	int n = strlen(str);
	int keyLen = strlen(key);
	int i;
	for(i = 0; i < n; i++)
	{
		str[i] = str[i] ^ key[i % keyLen];
	} 

    #ifdef DEBUG
		printf("string after encryption: %s\n", str);
	#endif

}
