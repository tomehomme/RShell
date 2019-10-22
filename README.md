# CS 100 Programming Project RShell
### Fall 2019 
### Ajeet Kokatay (862083784), Paris Hom (862062330)


Intro: RShell is a C++ Command shell which can print a command prompt, chain commands using connectors and create multiple threads using system calls.

We will develop using the Kanban development pattern. Inputs are ingested through the ExecObject parse method that builds a vector of RBase pointers, representing the user’s argumentlist, connector, and executable. This vector is then passed to the ExecHandler class which handles the system calls. 
