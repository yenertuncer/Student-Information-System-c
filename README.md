Student Information System



This is a console-based Student Information System developed in C. The system allows management of students, courses, professors, enrollments, and grades with full data persistence using CSV files .





&nbsp;Project Structure





src/: Contains all source code (.c) and header files (.h).





data/: Contains database files in CSV format.





tests/: Contains unit tests and automated test results.





docs/: Contains the Project Report and User Manual.







&nbsp;Compilation and Execution



The system is managed via a Makefile for easy compilation in Linux environments.



Build the Main Program

Bash



make clean

make

./StudentSystem

Run Automated Tests

Bash



make test



The test results will be saved to tests/test\_results.txt automatically.





&nbsp;Memory Verification



Memory management has been rigorously tested with Valgrind to ensure zero memory leaks .





Bash



valgrind --leak-check=full ./StudentSystem





Features



Full Student, Course, and Professor CRUD operations .



Prerequisite checking before enrollment.



GPA calculation and automated transcript generation .



Multi-semester data support.



Data backup and recovery options.

