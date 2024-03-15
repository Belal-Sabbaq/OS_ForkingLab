# OS_ForkingLab
Requirement:
Due to the large number of students enrolled in the course of Operating Systems this year, the process of
evaluating whether each student should pass or not has become extremely difficult. As a result, our
department decided to hire N teaching assistants such that each TA is responsible only for evaluating a single
group of students. Each TA is required to decide whether a student should pass the course or not by
calculating the grades of the student in the midterm and the final exam respectively. If the total grades is equal
to or exceeds the minimum passing grade P, then the student passes the course. Otherwise, he fails the
course. Finally, each TA should report the number of passing students from their assigned group. The
department committee should receive the count of passing students from each TA
Write a C program that simulates this scenario using forking concepts with a single parent process
(department committee) and N children processes (TAs).
The program accepts three arguments from the command line:
1. A file path indicating the grades of all students enrolled in the course. All grades are non-negative
integer values.
2. N: The number of TAs (N>0)
3. P: The minimum pass grade. (P>0)
Input File Format:
- The first line in the file indicates the number of students (S) in the list. - Each line in the following S lines represents the grades of a single student. It consists of two integers
separated by a space. The first integer is the grade of the student in the midterm exam and the second integer
is the grade of the student in the final exam.
Output Format:
- The program should output ONE line ONLY as follows:
1. The output line consists of N integers separated by a space such that each integer represents the number of
passing students in the TA’s assigned group. The first TA is assigned the first ⌊S/N⌋ students, the second
is TA is assigned the second ⌊S/N⌋ students, and so on. The output should be ordered correctly. The
number of TAs is not necessarily divisible by the number of students. In this case, the overflowing
students are assigned to the N-th TA (or the last one).
Example:
gcc passCounter.c -o passCounter.o
./ passCounter.o “test.txt” 3 40
Example for “test.txt”:
9
12 25
18 34
10 66
20 10
13 20
7 45
8 52
0 41
1 5

CMPS303 Operating Systems

2

Expected output:
2 1 2