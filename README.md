# Task Management System 📋🗂️

This project is an enhanced version of a **Task Management System** where tasks are stored in a **Binary Search Tree (BST)** based on their **Task ID**. The system allows you to manage tasks efficiently with various options for adding, deleting, searching, viewing, and restructuring tasks based on different attributes.

## Features ✨

1. **Load Tasks File** 📂: Load tasks from a file (`tasks.txt`), which contains at least 50 tasks.
2. **Add a New Task** ➕: Add a new task to the system.
3. **Delete a Task** ❌: Remove a specific task from the system.
4. **Search for a Task** 🔍: Search for a task by its Task Name.
5. **Perform a Task** ✔️: Mark a task as performed without removing it from the system.
6. **View Unperformed Tasks** 👀: Display all unperformed tasks, sorted by Task name.
7. **View Performed Tasks** ✅: Display all performed tasks, sorted by Task ID.
8. **Restructure the Tasks BST** 🔄: Rebuild the tree based on one of the task attributes (Task Name, Task Date, Task Duration).
9. **View the Tasks BST Info** 🧑‍💻: Display tree statistics such as height, size, number of leaves, and internal nodes.
10. **Exit** 🚪: Close the program.

## Requirements ⚙️

- **C programming language**.
- A file named `tasks.txt` containing at least 50 tasks with the following information for each task:
  - Task ID
  - Task Name
  - Task Date
  - Task Duration (in hours)

## Task File Format (`tasks.txt`) 📄

Each line in the `tasks.txt` file should represent one task, with fields separated by spaces or commas:

