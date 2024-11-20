# Assignment Details 
- We know that a lot of programming efforts are required if we want to parallelize 
an algorithm using Pthreads. For example, the parallel version of the simple array sum 
has around 3x lines of code than its corresponding sequential implementation. 
 
- In this code, we have helped the Pthread programmers by abstracting away some of the essential 
programming efforts into a header-file-only implementation (“simple-multithreader.h”) that the programmer 
can include and use in their program. We have provided two C++ sample programs with this assignment that 
use the SimpleMultithreader. The SimpleMultithreader provides C++11 lambda expressions-based APIs. You 
can  read  about  C++11  lambda  expressions  from  these  easy-to-understand  links  (only  look  for  C++11-
supported lambda): 
 
- A  sample  declaration  and  usage  of  C++11  lambda  expressions  are  also  demonstrated  inside  the  simple-
multithreader.h file provided along with this assignment. Makefile is also provided herewith to help you in the 
compilation. 


# Implementation 
1. SimpleMultithreader do not use any concept of task/thread pool. SimpleMultithreader simply 
creates Pthreads whenever parallel_for APIs are invoked in the user program. We have implemented
SimpleMultithreader in C++ inside the header file provided herewith.  
2.  SimpleMultithreader runtime execution have the exact number of threads specified by the 
programmer including the main thread of execution. 
3.  Every call to SimpleMultithreader interfaces (parallel_for) will create a new set of Pthreads and they will 
terminate as soon as the scope of that interfaces has ended.  
4. SimpleMultithreader must also print the total execution time for each call of a parallel_for

# Assumptions 
- Printing total exection time for each thread
- Test case only contains vector.cpp and matrix.cpp
- If large value of size is input, vscode terminates as overloading too much on system.
- we have uploaded 2 different header file, one is optimised but doesn't work for large value for matrix.cpp and other one does extra computation but works for large value

## Contribution
- Satvik Arya(2023493) : Implementation for vector.cpp and matrix.cpp and time calculating using `clock()` and executing optimised approach for matrix multiplication.
- Sanjeev(2023483) : Implementation for for_parallel function by passing valid arguements after calculating them.
### How to run 
- for vector file : ```make && ./vector```
- for matrix file : ``` make && ./matrix```

#### Github Link - (https://github.com/Satvik1924/SimpleMultithreader?tab=readme-ov-file)
