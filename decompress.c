/* author of function: Daria Ivica */
#include "password_manager.h"
#include <string.h> /* strcat, strlen */
#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

/* #define DEBUG */

/* Function to decompressed a compressed string. 
 * Inputs: pointer to compressed string struct, which includes huffman encoded
 * string and huffman tree for the string.
 * Outputs: decompressed string.
 */
char* decompress(struct node_t tree, char* str)
{
    node current = &tree; /* assign node as root of huffman tree */
	if(current==NULL)
	{
        /* tree is null, nothing to decompress */
		return NULL;
	}

    char* output = (char*)malloc(strlen(str)+1);  
	/* allocate memory for decoded string */

    int index = 0;  /* index for decoded string */

    /* traverse the Huffman tree based on the huffman encoded string */
    /* if there is no huffman code, but there is a frequency for root 
    of huffman tree, this means original string is only one character, 
    possibly multiples of that character e.g. dddddddddd */
    if(*str=='\0' && current->freq>0) 
    {
        #ifdef DEBUG
            printf("original string is only made up of same character.\n");
        #endif
        int i;
        for(i=0; i<current->freq; i++)
        {
            output[index] = current->data;
            index++;
        }
    }

    /* otherwise can traverse tree */
    const char* data;
    for(data = str; *data!='\0'; ++data)
	{
        if(*data=='0') 
		{
			if(current->left != NULL)
			{
                current = current->left; 
                /* for every 0 in encoded string, move to the left node in
                huffman tree, as long as there is a valid left node */
				strcat(output, "1");
            } else {
                /* no left node in huffman tree */
				free(output);  /* free allocated memory */
                return NULL;  /* Return NULL if left child is NULL */
            }
        } else if(*data=='1') 
		{
            if(current->right != NULL) 
			{
                current = current->right;
				strcat(output, "0");
            } else {
                free(output);  /* free allocated memory */
                return NULL;  /* Return NULL if right child is NULL */
            }
        }

        /* if leaf node is reached, append character 
		to decoded string and reset to root */
        if(current->left==NULL && current->right==NULL)
		{
            #ifdef DEBUG
				printf("leaf node found\n");
			#endif
            output[index++] = current->data;
            current = &tree; /* reset to root for next character */
        }
    }

    output[index] = '\0';  /* Null-terminate the decoded string */
    return output;
}

