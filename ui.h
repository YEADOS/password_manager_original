#ifndef UI_H
#define UI_H

#include "password_manager.h"

/* Color pairs */
#define COLOR_TITLE 1
#define COLOR_MENU 2
#define COLOR_SELECTED 3
#define COLOR_BORDER 4
#define COLOR_SUCCESS 5
#define COLOR_ERROR 6
#define COLOR_INFO 7

/* UI function prototypes */
void initUI(void);
void cleanupUI(void);
int showMainMenu(void);
void showMessage(const char* message, int color);
void drawBorder(int y, int x, int height, int width);
void drawTitle(void);
char* getInput(const char* prompt, char* buffer, int maxlen);
int getChoice(const char* prompt);
void showPasswordTable(password_t* list);
void displayAddPassword(password_t** list);
void displayGetPassword(password_t* list);
void displayDeletePassword(password_t** list);

#endif
