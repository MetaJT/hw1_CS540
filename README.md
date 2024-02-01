**HW1 for CS540**

**Task**: Write a program that utilizes the shell or system function to execute various shell commands.

**Use the following list of shell commands in your program**:
- dir (list directory contents, Windows equivalent of ls)
- cd (print directory)
- mkdir (create a new directory)
- echo (display a message)
- type (concatenate and display content of files, Windows equivalent of cat)

**This program interacts with the computers terminal using system() in C++**

I added some additional features such as:
- Creating a file
- Removing files and directories
- The ability to add text to text file

**Directions: Input the number related to the command you want to execute**
------------------------------------------------------
|                  TERMINAL COMMANDS                   |
|------------------------------------------------------|
| (1) -> List directory contents                       |
| (2) -> Print working directory                       |
| (3) -> Create a new directory                        |
| (4) -> Create a new file                             |
| (5) -> Remove an existing file or directory          |
| (6) -> Display a message                             |
| (7) -> Concatenate and display content of a file     |
| (0) -> Exit                                          |

**When finished enter 0 to exit**


I did my best to address error handling so that it continues to run when there is an invalid input
