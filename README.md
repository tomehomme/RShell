# CS 100 Programming Project: RShell
### Fall 2019 
### Ajeet Kokatay (862083784), Paris Hom (862062330)


## Intro 
RShell is a C++ Command shell which can print a command prompt, chain commands using connectors and create multiple threads using system calls.

Our project will utilize a Composite Design pattern. In our composite, our base class is called RBase. Using RBase class, each subsequent inheriting class will be able to access our input(string executable), parse and execute function. Inputs are ingested through the Executer, which then calls its parse method that builds a vector of RBase pointers called commandList, representing the user’s inputted commands. Then, our execute function will then be called on this Executer class, which uses recursive composition to then call each RBase's execute function in the vector. The RBase is a pure virtual class, and the user's commands are actually being represented and carried through our leaf class, Command. The Command class calls it's execute function and returns true or false depending on whether the command was successfully executed. Connectors (&&, ||) is represented by our class Connector, which also inherits from RBase and uses Command to carry out functionality.

## Diagram
![OMT Diagram](https://github.com/cs100/assignment-pajeet/blob/master/images/OMT%20diagram.png?raw=true)
## Classes

- RBase: composite base class with pure virtual parse function and pure virtual execute function. Used to allow for the inherited classes to interact and use each other's functions. Allows for our composite function to use recursive composition.
  - Executer: Contains a vector of RBase pointers. When calling execute, this class will loop through the vector and call every RBase pointers in the vector's execute functions. This will represent calling the functions from left to right.
  - Command: Is the actual "leaf" in the composite class. Will do the actual execution of the user's commands and returns true if the execution was successful, and false if the execution of the command was not. Calls fork, waitpid, and execvp in order to carry out the system calls. Command also contains a bool Test() function which allows us to use the "test" command as well as its symbolic equivalent [ ] to check if a file or directory exists. 
  - Connector: Base class for the && || ; commands. Has an RBase* left and RBase* right that allows for the connectors to function how they are meant to.
    - And: Inherited from Connector. Handles the && command. Only executes the second command (RBase* right) if the first command (RBase* left) executes and passes.
    - Or: Inherited from Connector. Handles the || command. Only executes the second command (RBase* right) if the first command (RBase* left) executes and fails. 
    - Paren: Inherited from Connector. Handels the precedence () comamnd. Constructor has an RBase* left and RBase* right. Takes in an Executer* as it's left, and a nullpointer as its right. Will build a tree using the Executer* passed in, which allows us to create precedence during execution.
    - WriteFile : Inherited from Connector. Handles the Write file redirection ie, the > command. Will write to a file given the inputs. If the file has not been created, will create the file with the specified name.
    - WriteFileAppend : Inherited from Connector. Handles the Write Append file redirection ie, the >> command. Will append to a file given the inputs. If the file has not been created, will create the file with the specified name.
    - ReadFile : Inherited from Connector. Handles the Read redirection ie, the < command. Will change the input from stinput to the given argument.


Note: inheritance is denoted by indentation


## Prototypes/Research
### System call research
- fork() creates a new process (child) that runs the same code as the parent process after the fork instruction executes.
  - fork returns a value. 0 means that the child process is running; -1 means the child process failed to create
  - to allow the child to run a different set of instructions, we can use execvp()
    - we pass in two parameters to execvp(): the name of a program file, and a pointer to an array of characters.
- waitpid() suspends the execution of the calling process (parent) until its child changes states.
  - this allows us to call fork(), and then ensure that the child process completes its execution before resuming the parent process.
  - waitpid(pid_t pid, int* status, int options) execution of the calling process (usually parent) is stalled until a child specified by pid argument has changed state (status)
- in our prototype, we called fork() to create a new process. We checked to see which process was running using the fork return type. Then, we called execvp() to make the child process run the ls shell command. We used waitpid() to allow the child process to execute and complete before resuming our parent process, which was a simple counter.
### Parse function research

#### Connectors
##### Connector types
```
//Will run the first command then the second, unconditionally:
command1 ; command2  
//Will run the first command then the second, if command1 has no errors:
command1 && command2  
//Will run the second command only if the first fails:
command1 || command2  
//Will run the command in the background:
command1 & 
```

##### Connector order of operations
We must choose what the program should do when it encounters chains of connectors. Ie, connectors must have a set order of operations. We looked to the bash shell for inspiration.

According to the bash man page:
```
Of these list operators, ‘&&’ and ‘||’ have equal precedence, followed by ‘;’ and ‘&’, which have equal precedence.
```

We have decided to model our shell in the same way.


## Compilation Instructions
Clone the repository and run 
```
$ cmake .
$ make
```
An rshell executible should appear in the directory.
Run it using ``` ./rshell ```.

## Development and Testing Roadmap

| Week | Issue                                            | Person |
|------|--------------------------------------------------|--------|
| 1    | Create RBase class and pure virtual functions    | Ajeet  |
| 1    | Create basic main interface                      | Paris  |
| 2    | Create all program classes                       | Paris  |
| 3    | Create parser function                           | Ajeet  |
| 3    | Create Unit Tests                                | Ajeet  |
| 3    | Create Integration Tests                         | Paris  |
| 5    | Add in more parsing capabilities                 | Ajeet  |
| 5    | Create more classes to encompass new enchantments| Paris  |
| 6    | Create unit tests for new functions              | Paris  |
| 6    | Create integration tests                         | Ajeet  |
