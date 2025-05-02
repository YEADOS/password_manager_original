# Password Manager for UNI

Welcome to the **Password Manager** project! This project is a simple and secure password management tool designed to help users store and manage their passwords efficiently. The goal of this project was to implement encryption and hashing functions without external libraries.

## Features

- **Secure Storage:** Uses XOR encryption and Huffman Coding to store and retrieve passwords securely.
- **Command-Line Interface:** Easily manage passwords via simple terminal commands.
- **Lightweight and Efficient:** Written in C for optimal performance.

## Getting Started

### Prerequisites

To build and run this project, you will need:

- A C compiler (e.g., GCC)
- `make` for building the project

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/YEADOS/password_manager_original.git
   cd password_manager_original
   ```

2. Build the project using `make`:

   ```bash
   make
   ```

3. Run the program:

   ```bash
   ./password_manager
   ```

## Usage

- Follow the on-screen instructions to create, retrieve, or manage passwords.
- Ensure that your saved passwords are backed up securely.

## Project Structure

- **Source Code:** The primary logic is written in C.
- **Build System:** The project uses a `Makefile` for compilation and build automation.
