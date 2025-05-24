# SQLite-replica

SQLite-replica is a lightweight SQLite-based database management tool written in C. It provides a minimalistic approach to handling database commands and interactions, enabling users to perform basic operations such as inserting data and selecting data.

## Features

- **Command-Line Interface**: Interact with the database using simple text commands.
- **Insert and Select Operations**: Perform basic CRUD operations like inserting data and selecting data from the database.
- **File-Based Storage**: Database operations are logged and stored in a local file (`data/data.txt`).
- **Extensible Framework**: Built in C with a modular design, making it easy to extend functionality.

## How It Works

- **Prompt-Based Input**: The application starts with a prompt (`db >`) where users can enter commands.
- **Supported Commands**:
  - `insert`: Inserts data into the database.
  - `select`: Retrieves and displays stored data.
  - `.exit`: Exits the application.

Invalid or unrecognized commands will prompt an error message.

## Usage

### Running the Program

1. Clone the repository:
   ```bash
   git clone https://github.com/saaya-code/SQLite-replica.git
   cd SQLite-replica
   ```

2. Compile the source code:
   ```bash
   gcc main.c -o sqlite-replica
   ```

3. Run the application:
   ```bash
   ./sqlite-replica
   ```

### Example Commands

- **Insert Data**:
  ```
  db > insert
  Check database!
  ```

- **Select Data**:
  ```
  db > select
  wrote to the database!
  ```

- **Exit the Application**:
  ```
  db > .exit
  ```

### Error Handling

- If an unrecognized command is entered, the program will display an error message:
  ```
  Unrecognized command 'your_command'
  ```

## Code Structure

The application is implemented in a single file (`main.c`) and relies on the following key components:

- **Input Handling**:
  - `InputBuffer` structure to read and process user input.
- **Commands**:
  - `prepare_statement` identifies valid commands like `insert` and `select`.
  - `do_meta_command` processes meta commands like `.exit`.
- **Execution**:
  - `execute_statement` writes to or reads from `data/data.txt` based on the command.
- **File Operations**:
  - Insert and select operations directly interact with a local text file.

## Contributing

Contributions are welcome! Feel free to fork the repository, submit issues, or create pull requests to improve the project.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

*Maintained by [saaya-code](https://github.com/saaya-code)*
