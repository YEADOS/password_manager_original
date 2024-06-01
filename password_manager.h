#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#define MAX_LENGTH 256
#define MAX_STRING_LENGTH 31
#define MAX_TABLE_LENGTH 100
#define DEAULT_TABLE_LENGTH 15
/* #define DEBUG */

extern char* cryptkey;

/* structure used to define a node */
typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char data;
} *node; /* node is used to declare pointers to node_t */

struct compressedString{
	struct node_t tree; /* root of tree */
	char str[MAX_LENGTH];
};
typedef struct compressedString compressedString_t;

/* structure for creating linked list of nodes */
typedef struct ListNode {
    struct node_t *node;
    struct ListNode *next;
} ListNode_t;

struct password{
	char website[MAX_LENGTH];
	/*char username[MAX_LENGTH];*/
	compressedString_t username;
	compressedString_t password;
	struct password *nextp;
};
typedef struct password password_t;

/* function prototypes */
void printMenu(void);
int addPassword(password_t** list);
void updatePassword(password_t **list, char* website);
void deletePassword(password_t **list, char* website);
void getPassword(password_t* list);
void viewPasswords(password_t* list);
void encrypt(char* password, char *key);

int containInts(char string[]);
void formatString(char* string);
void clearInput();

compressedString_t compress(char* input);
char* decompress(struct node_t tree, char* str);
int exists(password_t* list, char* website);
char* confirmation();
char* encode(const char* input, unsigned int *freq);
void importString(char* str, unsigned int *freq);
void buildCode(node n, char *s, int len);
node removeNode();
void insertNode(node n);
node newNode(int freq, char c, node a, node b);

char randomUppercase();
char randomLowercase();
char randomDigit();
char randomSpecial();
char* generatePassword();

#endif
