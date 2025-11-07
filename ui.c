/* Enhanced UI for Password Manager using ncurses */
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

/*
 * Initialize ncurses and color settings
 */
void initUI(void) {
    initscr();              /* Start ncurses mode */
    cbreak();               /* Disable line buffering */
    noecho();               /* Don't echo input */
    keypad(stdscr, TRUE);   /* Enable function keys */
    curs_set(0);            /* Hide cursor */

    /* Initialize colors */
    start_color();
    init_pair(COLOR_TITLE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_MENU, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_SELECTED, COLOR_BLACK, COLOR_CYAN);
    init_pair(COLOR_BORDER, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_SUCCESS, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_ERROR, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_INFO, COLOR_YELLOW, COLOR_BLACK);
}

/*
 * Cleanup and exit ncurses mode
 */
void cleanupUI(void) {
    endwin();
}

/*
 * Draw a fancy title banner
 */
void drawTitle(void) {
    int row = 1;
    attron(COLOR_PAIR(COLOR_TITLE) | A_BOLD);

    mvprintw(row++, 2, "  ____                                     _   __  __                                 ");
    mvprintw(row++, 2, " |  _ \\  __ _  ___  ___ __      __  ___  | | |  \\/  |  __ _  _ __    __ _   __ _   ___  _ __ ");
    mvprintw(row++, 2, " | |_) |/ _` |/ __|/ __|\\ \\ /\\ / / / _ \\ | | | |\\/| | / _` || '_ \\  / _` | / _` | / _ \\| '__|");
    mvprintw(row++, 2, " |  __/| (_| |\\__ \\\\__ \\ \\ V  V / | (_) || | | |  | || (_| || | | || (_| || (_| ||  __/| |");
    mvprintw(row++, 2, " |_|    \\__,_||___/|___/  \\_/\\_/   \\___/ |_| |_|  |_| \\__,_||_| |_| \\__,_| \\__, | \\___||_|");
    mvprintw(row++, 2, "                                                                             |___/");

    attroff(COLOR_PAIR(COLOR_TITLE) | A_BOLD);

    attron(COLOR_PAIR(COLOR_INFO));
    mvprintw(row + 1, 2, " Secure Password Storage with XOR Encryption & Huffman Compression");
    attroff(COLOR_PAIR(COLOR_INFO));
}

/*
 * Draw a border around a region
 */
void drawBorder(int y, int x, int height, int width) {
    int i;
    attron(COLOR_PAIR(COLOR_BORDER));

    /* Top and bottom */
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y + height - 1, x, ACS_LLCORNER);
    mvaddch(y, x + width - 1, ACS_URCORNER);
    mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);

    for (i = 1; i < width - 1; i++) {
        mvaddch(y, x + i, ACS_HLINE);
        mvaddch(y + height - 1, x + i, ACS_HLINE);
    }

    /* Sides */
    for (i = 1; i < height - 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + width - 1, ACS_VLINE);
    }

    attroff(COLOR_PAIR(COLOR_BORDER));
}

/*
 * Show main menu and return selected option
 */
int showMainMenu(void) {
    int choice = 0;
    int key;
    const char* options[] = {
        "1. Add New Password",
        "2. Delete Password",
        "3. View Single Password",
        "4. View All Passwords",
        "5. Exit"
    };
    int num_options = 5;

    while (1) {
        clear();
        drawTitle();

        /* Draw menu border */
        int menu_y = 11;
        int menu_x = 30;
        int menu_height = 12;
        int menu_width = 50;

        drawBorder(menu_y, menu_x, menu_height, menu_width);

        attron(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
        mvprintw(menu_y, menu_x + 18, " MAIN MENU ");
        attroff(COLOR_PAIR(COLOR_BORDER) | A_BOLD);

        /* Display menu options */
        int i;
        for (i = 0; i < num_options; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(COLOR_SELECTED) | A_BOLD);
                mvprintw(menu_y + 2 + i * 2, menu_x + 5, "  %s  ", options[i]);
                attroff(COLOR_PAIR(COLOR_SELECTED) | A_BOLD);
            } else {
                attron(COLOR_PAIR(COLOR_MENU));
                mvprintw(menu_y + 2 + i * 2, menu_x + 5, "  %s  ", options[i]);
                attroff(COLOR_PAIR(COLOR_MENU));
            }
        }

        attron(COLOR_PAIR(COLOR_INFO));
        mvprintw(LINES - 2, 2, " Use UP/DOWN arrows to navigate, ENTER to select");
        attroff(COLOR_PAIR(COLOR_INFO));

        refresh();

        key = getch();

        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + num_options) % num_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % num_options;
                break;
            case 10: /* Enter key */
            case KEY_ENTER:
                return choice + 1;
        }
    }
}

/*
 * Display a message with specified color
 */
void showMessage(const char* message, int color) {
    attron(COLOR_PAIR(color) | A_BOLD);
    mvprintw(LINES - 4, 2, "%s", message);
    attroff(COLOR_PAIR(color) | A_BOLD);
    mvprintw(LINES - 3, 2, "Press any key to continue...");
    refresh();
    getch();
}

/*
 * Get input from user with a prompt
 */
char* getInput(const char* prompt, char* buffer, int maxlen) {
    clear();
    drawTitle();

    int input_y = 12;
    int input_x = 10;
    int input_width = 80;

    drawBorder(input_y, input_x, 6, input_width);

    attron(COLOR_PAIR(COLOR_INFO) | A_BOLD);
    mvprintw(input_y + 2, input_x + 3, "%s", prompt);
    attroff(COLOR_PAIR(COLOR_INFO) | A_BOLD);

    mvprintw(input_y + 3, input_x + 3, "> ");

    refresh();

    echo();
    curs_set(1);
    getnstr(buffer, maxlen - 1);
    noecho();
    curs_set(0);

    /* Remove newline if present */
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

/*
 * Get a yes/no choice from user
 */
int getChoice(const char* prompt) {
    int choice = 0;
    int key;
    const char* options[] = {"Yes", "No"};

    clear();
    drawTitle();

    int choice_y = 12;
    int choice_x = 25;
    int choice_width = 60;

    drawBorder(choice_y, choice_x, 8, choice_width);

    attron(COLOR_PAIR(COLOR_INFO) | A_BOLD);
    mvprintw(choice_y + 2, choice_x + 3, "%s", prompt);
    attroff(COLOR_PAIR(COLOR_INFO) | A_BOLD);

    while (1) {
        int i;
        for (i = 0; i < 2; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(COLOR_SELECTED) | A_BOLD);
                mvprintw(choice_y + 4, choice_x + 15 + i * 15, "  %s  ", options[i]);
                attroff(COLOR_PAIR(COLOR_SELECTED) | A_BOLD);
            } else {
                attron(COLOR_PAIR(COLOR_MENU));
                mvprintw(choice_y + 4, choice_x + 15 + i * 15, "  %s  ", options[i]);
                attroff(COLOR_PAIR(COLOR_MENU));
            }
        }

        refresh();

        key = getch();

        switch (key) {
            case KEY_LEFT:
            case KEY_RIGHT:
                choice = 1 - choice;
                break;
            case 10: /* Enter */
            case KEY_ENTER:
                return choice == 0 ? 1 : 0;
        }
    }
}

/*
 * Display all passwords in a nice table
 */
void showPasswordTable(password_t* list) {
    clear();
    drawTitle();

    if (list == NULL) {
        showMessage("No passwords saved yet.", COLOR_INFO);
        return;
    }

    int start_y = 10;
    int start_x = 5;

    /* Just call the original viewPasswords function but in raw mode */
    mvprintw(start_y, start_x, "Stored Passwords:");
    refresh();

    /* Switch to cooked mode temporarily to use original function */
    def_prog_mode();
    endwin();
    printf("\n\n");
    viewPasswords(list);
    printf("\n\nPress Enter to continue...");
    getchar();
    reset_prog_mode();
    refresh();
}

/*
 * Display interface for adding password
 */
void displayAddPassword(password_t** list) {
    clear();
    drawTitle();

    /* Switch to normal mode for complex input */
    def_prog_mode();
    endwin();
    printf("\n\n");
    addPassword(list);
    printf("\nPress Enter to continue...");
    getchar();
    reset_prog_mode();
    refresh();
}

/*
 * Display interface for getting a password
 */
void displayGetPassword(password_t* list) {
    clear();
    drawTitle();

    if (list == NULL) {
        showMessage("No passwords saved yet.", COLOR_INFO);
        return;
    }

    /* Switch to normal mode */
    def_prog_mode();
    endwin();
    printf("\n\n");
    getPassword(list);
    printf("\nPress Enter to continue...");
    getchar();
    reset_prog_mode();
    refresh();
}

/*
 * Display interface for deleting password
 */
void displayDeletePassword(password_t** list) {
    char website[MAX_LENGTH];

    if (*list == NULL) {
        showMessage("No passwords saved yet.", COLOR_INFO);
        return;
    }

    getInput("Enter website of password you want to delete:", website, MAX_LENGTH);

    /* Switch to normal mode for delete operation */
    def_prog_mode();
    endwin();
    deletePassword(list, website);
    printf("\nPress Enter to continue...");
    getchar();
    reset_prog_mode();
    refresh();
}
