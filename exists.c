/* author of function: Nicholas Yeadon */
#include "password_manager.h"
#include <string.h> /* strcmp */

/*
 * Function to determine if a website/password exist within the linked list
 * already.
 * Inputs are the linked list and a string for the website name to check.
 * Output is an int depending on is website in list or not (0=false, 1=true).
 */
int exists(password_t* list, char* website)
{
    password_t *temp = list;
    while(temp!=NULL)
    {
        if(strcmp(temp->website, website)==0)
        {
            return 1;
        }
        temp = temp->nextp;
    }

    return 0;
}
