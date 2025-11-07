# makefile for generating password_manager.out

CC = gcc
CFLAGS = -Wall -Werror -ansi -lm
NCURSES_FLAGS = -lncurses

# Default target builds both versions
all: password_manager.out password_manager_ui.out

# Original text-based version
password_manager.out: password_manager.o addPassword.o generatePassword.o updatePassword.o compress.o confirmation.o decompress.o deletePassword.o encrypt.o getPassword.o viewPasswords.o exists.o printMenu.o
	$(CC) $(CFLAGS) -o password_manager.out password_manager.o generatePassword.o addPassword.o updatePassword.o compress.o confirmation.o decompress.o deletePassword.o encrypt.o getPassword.o viewPasswords.o exists.o printMenu.o

# New ncurses UI version
password_manager_ui.out: password_manager_ui.o ui.o addPassword.o generatePassword.o updatePassword.o compress.o confirmation.o decompress.o deletePassword.o encrypt.o getPassword.o viewPasswords.o exists.o printMenu.o
	$(CC) $(CFLAGS) -o password_manager_ui.out password_manager_ui.o ui.o generatePassword.o addPassword.o updatePassword.o compress.o confirmation.o decompress.o deletePassword.o encrypt.o getPassword.o viewPasswords.o exists.o printMenu.o $(NCURSES_FLAGS)

password_manager.o: password_manager.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o password_manager.o password_manager.c

addPassword.o: addPassword.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o addPassword.o addPassword.c

updatePassword.o: updatePassword.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o updatePassword.o updatePassword.c

compress.o: compress.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o compress.o compress.c

confirmation.o: confirmation.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o confirmation.o confirmation.c

decompress.o: decompress.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o decompress.o decompress.c

deletePassword.o: deletePassword.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o deletePassword.o deletePassword.c

encrypt.o: encrypt.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o encrypt.o encrypt.c

getPassword.o: getPassword.c password_manager.h  
	$(CC) $(CFLAGS) -c  -o getPassword.o getPassword.c

generatePassword.o: generatePassword.c password_manager.h  
	$(CC) $(CFLAGS) -c  -o generatePassword.o generatePassword.c

viewPasswords.o: viewPasswords.c password_manager.h  
	$(CC) $(CFLAGS) -c  -o viewPasswords.o viewPasswords.c

exists.o: exists.c password_manager.h 
	$(CC) $(CFLAGS) -c  -o exists.o exists.c

printMenu.o: printMenu.c password_manager.h
	$(CC) $(CFLAGS) -c  -o printMenu.o printMenu.c

password_manager_ui.o: password_manager_ui.c password_manager.h ui.h
	$(CC) $(CFLAGS) -c  -o password_manager_ui.o password_manager_ui.c

ui.o: ui.c ui.h password_manager.h
	$(CC) $(CFLAGS) -c  -o ui.o ui.c

clean:
	rm -f addPassword.o updatePassword.o compress.o confirmation.o decompress.o deletePassword.o encrypt.o getPassword.o generatePassword.o viewPasswords.o exists.o printMenu.o password_manager.o password_manager_ui.o ui.o password_manager.out password_manager_ui.out

