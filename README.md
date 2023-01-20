# dbxshell
This project represents a shell which expose the functionalities of [dbxcli](https://github.com/dropbox/dbxcli).
The project presents a certain amount of OS notions as:
- **Pipe** (redirects the **stderr** of *dbxcli* to a string for custom error handling)
- **Process fork** (each command inside the shell is executed in a propper fork or child process)
---
## How do we start the project?
We will need to go and compile the dbxcli utility using the propper tools provided by the README.md documentation from [dbxcli](https://github.com/dropbox/dbxcli).
After we compile it we will need to edit ```utils.h``` and edit the path of the dbxcli executable.

**WARNING! Put the complete file path to the dbxcli exec.**
```cpp
const string dbxcliPath = "complete/path/to/dbxcli";
```
Project developed by *Vrinceanu Radu-Tudor* (g. 242) for [OS course @ FMI UniBuc](https://os.cs.unibuc.ro)
