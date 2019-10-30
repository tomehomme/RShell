# CS 100 Programming Project: RShell
### Fall 2019 
### Ajeet Kokatay (862083784), Paris Hom (862062330)


## Intro 
RShell is a C++ Command shell which can print a command prompt, chain commands using connectors and create multiple threads using system calls.

We will develop using the Kanban development pattern. Our project will utilize a Composite Design pattern. In our composite, our base class is called RBase. Using RBase class, each subsequent inheriting class will be able to access our input and parse function. Inputs are ingested through the ExecObject parse method that builds a vector of RBase pointers, representing the user’s argumentlist, connector, and executable. This vector of RBase pointers is then passed to the ExecHandler class which handles the system calls. 

## Diagram
![OMT Diagram](https://github.com/cs100/assignment-pajeet/blob/master/images/omt%20diagram.png?raw=true)
## Classes

- RBase: composite base class with pure virtual parse function
  - ExecBase: base class for ExecObj and ExecHandler to interact after parsing the string input. ExecHandler uses the ExecBase class pointer to take in an ExecObject
    - ExecObj: Executes the Parse function, which generates a vector of RBases to create an object representation of a command from a string input. We can represent the entirety of the user’s string input as vector of the ADTs listed below after parsing. ExecObj will then pass this information(vector) onto ExecHandler
    - ExecHandler: Handles multithreading and system calls, takes in an ExecObject and executes it.
  - Args: ADT for storing Arguments from string input. Is used in ExecBase vector<RBase*>objects.
  - Connector: ADT for storing connectors. Is used in ExecBase vector<RBase*>objects.
  - Executable: ADT for storing the part of the command that is executable. Is used in ExecBase vector<RBase*>objects.

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

### General shell research
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


## Parse function protoype usage / explanation
Compile prototype/shellproto.cpp using g++ and c++ 11.
Running the resulting executable will bring you to the shell.
The parse method protoype utilizes stringstream to break up the user input (from getline) into space delimited strings.
The first string is the executible to run, while the rest of the strings are arguments to be sent to the executible.
## Development and Testing Roadmap

| Week | Issue                                            | Person |
|------|--------------------------------------------------|--------|
| 1    | Create RBase class and pure virtual functions    | Ajeet  |
| 1    | Create basic main interface                      | Paris  |
| 2    | Create ADTs (Args, Connector, Executable)        | Ajeet  |
| 3    | Create ExecBase class and pure virtual functions | Paris  |
| 4    | Create ExecObj class and functions               | Ajeet  |
| 5    | Create unit tests for ExecHandler functions      | Paris  |
| 5    | Create ExecHandler and functions                 | Ajeet  |
| 6    | Create unit tests for ExecObj functions          | Paris  |
| 6    | Create integration tests                         | Ajeet  |
