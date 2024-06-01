/* author of functions: Daria Ivica */
/* includes all functions relating to/needed for compression */
#include "password_manager.h"
#include <stdio.h> /* printf */
#include <string.h> /* strcat, strlen, strcpy */
#include <stdlib.h> /* malloc */

/* #define DEBUG */

/* global variables */
int nNodes, end; 
/* keep track of number of nodes and end of the queue */
node *queue;
/* pointer to priority queue, initialised as first element of nodesp array */
char *code[128] = {0}; 
/* array of strings for huffman codes for each character */

ListNode_t *allNodesHead;/* head of the linked list of all nodes */

/* Function to compress input string. 
 * Inputs: input string.
 * Outputs: compressed string struct, which includes encoded string 
 * and huffman tree for the string.
 */
compressedString_t compress(char* str)
{
	node nodesp[MAX_LENGTH]; 
	/* array of pointers to nodes - remember: node declares pointer to node_t */

	/* reset global variables */
	queue=nodesp;
	allNodesHead = NULL;
	nNodes=0; 
	end=1; 

	unsigned int freq[MAX_LENGTH/2] = {0}; 
	/* frequency of the letters - no. of ascii characters is 128 */
	importString(str,freq); /* import the string and fill frequency array */
	#ifdef DEBUG
		printf("string imported.\n");
	#endif

	/* encode input string and save the encoded string */
	char* encodedString = encode(str,freq);
	#ifdef DEBUG
	    printf("huffman code: %s\n", encodedString);
	#endif

	compressedString_t compressed;
	strcpy(compressed.str, encodedString);
	compressed.tree = *queue[1]; /* root of tree */

    #ifdef DEBUG
	    printf("root of huffman tree (freq): %d\n", compressed.tree.freq);
	#endif

	return compressed;
}

/* Function to importing an input string and build a Huffman tree for it.
 * Inputs: input string and int array for frequency of characters in string.
 * Outputs: none.
 */
void importString(char* str, unsigned int *freq)
{
	char s[MAX_STRING_LENGTH]={0}; /* empty string that will become huffman code */

	int i = 0;
	while(str[i] != '\0') /* while character in string is not null */
	{
        freq[(int)str[i]]++; /* increment the frequency of that character */
		i++;
    }
	for(i=0; i<MAX_LENGTH/2; i++) 
	{
        if(freq[i]){ /* if there is a frequency for a character */
            /* create new node for character and add into priority queue */
            insertNode(newNode(freq[i], i, 0, 0));
			#ifdef DEBUG
				printf("node was inserted for character %c\n", (char)i);
			#endif
        }
    }

	#ifdef DEBUG
		printf("before building huffman tree: end = %d\n", end);
	#endif
	if(end==2)
	{

	}
	while(end>2)
	{
        /* priority queue now contains all nodes, and has more than 2 nodes */
		/* build the Huffman tree by removing nodes from queue and creating internal
		nodes with nodes of each character in string becoming leaves of the tree */
        insertNode(newNode(0, 0, removeNode(), removeNode())); 
		/* internal node is created first with no data value, and two nodes are 
		removed and placed left/right of internal node before it is inserted into 
		queue to create final tree */
    }
    #ifdef DEBUG
		printf("all internal and leaf nodes added to queue.\n");
		printf("before building huffman code: root = %d, data = %c\n", 
		queue[1]->freq, queue[1]->data);
	#endif

	buildCode(queue[1], s, 0);  /* build huffman code for the characters */
	#ifdef DEBUG
		printf("huffman code created.\n");
	#endif
}

/* Function to create a new node to then be added to queue.
 * Inputs are the frequency (int) of the character in the string,
 * the character itself, and two nodes for left and right of new node.
 * Output is a pointer to the new node that has been created.
 */
node newNode(int freq, char c, node a, node b)
{
	node n = (node)malloc(sizeof(struct node_t)); 
	/* allocate memory for new node */
	if(freq!=0)
	{
		n->data = c; /* assign the character as the data of the node */
		n->freq = freq;	/* assign frequency */
		/* this is a leaf node */
	} else { /* no frequency given */
		n->left = a;
		n->right = b;	
		n->freq = a->freq+b->freq;
		#ifdef DEBUG
			printf("left freq: %d. right freq: %d. ", a->freq, b->freq);
			printf("parent node freq: %d.\n", n->freq);
		#endif
		/* If there is no frequency provided, this is an internal node that will
		have no value, and its frequency is the frequency of its right/left branches
		combined. Nodes at the end of the queue are removed and added to left and 
		right of this node */
	}

	/* Add the new node to the linked list */
    ListNode_t *newListNode = (ListNode_t*)malloc(sizeof(ListNode_t));
    newListNode->node = n;
    newListNode->next = allNodesHead;
    allNodesHead = newListNode;

	return n;
}

/* Function to insert a node into the priority queue. Position in queue
 * is determined by frequency, with lowest frequency having highest priority.
 * Input is the node to be added to the queue.
 * No output.
 */
void insertNode(node n)
{
	#ifdef DEBUG
		printf("frequency of node to be inserted: %d\n", n->freq);
	#endif

    end++; /* end of queue is incremented as node is being added to it */
	int i;
	for(i = end-1; i>1 && queue[i-1]->freq >= n->freq; i--)
    {
        /* starting from end of the queue */
		/* shift nodes down to make room for the new node if any existing elements
		in queue have a higher frequency than the new node */
        queue[i] = queue[i-1];
    } 

	/* new node is inserted at position determined by the loop */
	queue[i]=n;
	#ifdef DEBUG
		printf("node inserted at index: %d\n", i);
	#endif
}

/* Function to remove a node with lowest frequency from the end of the queue
 * when creating a Huffman tree.
 * No inputs.
 * Output is a pointer to the removed node.
 */
node removeNode()
{
	node removedNode = queue[1]; /* node removed from beginning of queue */ 
	
	if(end<2) /* if there are less than two nodes in queue */
	{
		return 0; /* nothing to remove */
	}

    int i;
	for(i=1; i<end-1; i++)
    {
        /* starting from beginning of the queue */
		/* shift nodes up to replace removed node */
        queue[i] = queue[i+1];
    }
	end--; /* decrement end of queue */
	
	return removedNode; /* return the node */
}

/* Function to traverse huffman tree and assign the huffman codes for each 
 * character of input string (e.g. password).
 * Inputs: the node in tree that is being assigned a huffman code, a string
 * that will store huffman code for the character, and an int for length of 
 * that string (huffman code).
 * Outputs: none.
 */
void buildCode(node n, char *s, int len)
{
	static char buf[1024]; /* static buffer for Huffman codes */
    static char *out = buf;

	/* if the provided node is a leaf, and thus has a value for data */
	if(n->data)
	{
		#ifdef DEBUG
			printf("Leaf node found for \"%c\".\n", n->data);
		#endif

		s[len]='\0'; /* terminates huffman code currently stored in s */
		strcpy(out, s); /* huffman code copied to location pointed to by out */
		/* this will store huffman code for the character */

		code[(int)n->data]=out; 
		/* updates code array, with character's ASCII value used as index */
		#ifdef DEBUG
			printf("Code \"%s\" for \"%c\" added to code array at index %d.\n", 
			out, n->data, (int)n->data);
		#endif

		out += len+1; /* out pointer is incremented */
		return;
	}

    /* if node is an internal node, ie no data/character stored in node,
	traverse through huffman tree and append 0 or 1 to huffman code to represent
	direction of the tree */
	s[len] = '0';
	buildCode(n->left, s, len+1); /* tree traversal is recursive */
	#ifdef DEBUG
		printf("Left tree traversed.\n");
	#endif
	/* first traverses left side of tree */
	s[len] = '1';
	buildCode(n->right, s, len+1); 
	/* once left side has been traversed, right side is */
	#ifdef DEBUG
		printf("Right tree traversed.\n");
	#endif
}

/* Function to encode input string using huffman codes (stored in code array).
 * Inputs: input string and array of frequency of characters in input string.
 * Outputs: encoded string.
 */
char* encode(const char* input, unsigned int *freq)
{
	if(input == NULL || freq == NULL )
	{
        printf("Error: invalid input string or frequency.\n");
        return NULL;
    }

    int i, j=0; 
	/* j is index for temp array */
	int length = 0; /* length of string */
    
    /* calculate the total length of encoded string */
    for(i=0; i<MAX_LENGTH/2; i++) 
	{
        if(freq[i]) /* if there is a frequency for that character */
		{
			#ifdef DEBUG
				printf("frequency exists, code: %s, i=%d\n", code[i], i);
			#endif
            length+=(freq[i]*strlen(code[i])); /* increase length */
        }
    }

	char* output = (char*)malloc(sizeof(char)*length);
	/* allocate memory for pointer to encoded string */
	if(output == NULL)
	{
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
	/* encode string character by character */
	while(input[j] != '\0')
	{
		#ifdef DEBUG
			printf("code added to output: %s\n", code[(unsigned char)input[j]]);
		#endif
		strcat(output, code[(unsigned char)input[j]]);
		/* huffman code for current char is retrieved from code array 
		and added to end of output string */
		j++;
    }

	return output; /* return huffman code for input string */
}

