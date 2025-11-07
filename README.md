# Password Manager for UNI

Welcome to the **Password Manager** project! This project is a simple and secure password management tool designed to help users store and manage their passwords efficiently. The goal of this project was to implement encryption and hashing functions without external libraries.

These were the only libraries allowed: 

- **#include <stdio.h>**
- **#include <stdlib.h>**
- **#include <string.h>**

## Features

- **Secure Storage:** Uses XOR encryption and Huffman Coding to store and retrieve passwords securely.
- **Two Interface Options:**
  - **Classic Text Mode:** Simple command-line interface
  - **Enhanced ncurses UI:** Beautiful terminal UI with colors, borders, and arrow-key navigation
- **Lightweight and Efficient:** Written in C for optimal performance.

## Getting Started

### Prerequisites

To build and run this project, you will need:

- A C compiler (e.g., GCC)
- `make` for building the project
- `ncurses` library (for the enhanced UI version)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/YEADOS/password_manager_original.git
   cd password_manager_original
   ```

2. Install ncurses library (if not already installed):

   ```bash
   # On Debian/Ubuntu
   sudo apt-get install libncurses5-dev libncursesw5-dev

   # On Fedora/RHEL
   sudo dnf install ncurses-devel

   # On macOS
   brew install ncurses
   ```

3. Build the project using `make`:

   ```bash
   # Build both versions
   make all

   # Or build individually:
   make password_manager.out        # Classic text interface
   make password_manager_ui.out     # Enhanced ncurses UI
   ```

4. Run the program:

   ```bash
   # Classic text interface
   ./password_manager.out

   # Enhanced ncurses UI (recommended)
   ./password_manager_ui.out
   ```

## Usage

### Enhanced ncurses UI (Recommended)
The enhanced UI provides a modern terminal experience with:
- **Colorful interface** with cyan and green accents
- **Arrow key navigation** through menus
- **Visual feedback** with highlighted selections
- **Beautiful ASCII art banner**
- Navigate using **UP/DOWN** arrow keys and **ENTER** to select

### Classic Text Interface
The original simple text-based interface:
- Type numbers to select menu options
- Straightforward command-line interaction

Both interfaces provide the same functionality:
1. **Add New Password** - Store a new password for a website
2. **Delete Password** - Remove a stored password
3. **View Single Password** - Search and view a specific password
4. **View All Passwords** - Display all stored passwords in a table
5. **Exit** - Close the application

All passwords are encrypted using XOR encryption and compressed using Huffman coding for secure storage.

## Project Structure

- **Source Code:** The primary logic is written in C
  - `password_manager.c` - Original text-based interface
  - `password_manager_ui.c` - Enhanced ncurses UI interface
  - `ui.c` / `ui.h` - ncurses UI implementation
  - Core functionality modules: `addPassword.c`, `deletePassword.c`, `getPassword.c`, `viewPasswords.c`, `updatePassword.c`
  - Encryption & compression: `encrypt.c`, `compress.c`, `decompress.c`
  - Utilities: `generatePassword.c`, `confirmation.c`, `exists.c`, `printMenu.c`
- **Build System:** The project uses a `Makefile` for compilation and build automation

## Recent Updates

- Fixed typo: `DEAULT_TABLE_LENGTH` → `DEFAULT_TABLE_LENGTH`
- Added beautiful ncurses-based terminal UI with colors and arrow-key navigation
- Enhanced user experience with visual feedback and modern interface design
