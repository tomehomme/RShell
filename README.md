# CS 100 Programming Project RShell
### Fall 2019 
### Ajeet Kokatay (862083784), Paris Hom (862062330)


## Intro 
RShell is a C++ Command shell which can print a command prompt, chain commands using connectors and create multiple threads using system calls.

We will develop using the Kanban development pattern. Inputs are ingested through the ExecObject parse method that builds a vector of RBase pointers, representing the user’s argumentlist, connector, and executable. This vector is then passed to the ExecHandler class which handles the system calls. 

## Classes

- RBase: base class with pure virtual parse function
  - ExecBase: base class for ExectObj and ExectHandler to interact after parsing the string input 
    - ExecObj: Parse function generates vector fo RBases to create an object representation of a command from a string. We can represent the entirety of the user’s string input as vector of the ADTs listed below. 
    - ExecHandler: Handles multithreading and system calls, takes in an ExecObject and executes it.
  - Args: ADT for storing Arguments from string input
  - Connector: ADT for storing connectors.
  - Executable: ADT for storing the part of the command that is executable 

Note: inheritance is denoted by indentation
