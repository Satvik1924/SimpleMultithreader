#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>

int user_main(int argc, char **argv);

/* Demonstration on how to pass lambda as parameter.
 * "&&" means r-value reference. You may read about it online.
 */
void demonstration(std::function<void()> && lambda) {
  lambda();
}

typedef struct                              // struct for vector file
{
  int low;
  int high;
  std::function<void(int)> lambda;
} vectorThreadArgs;

typedef struct                             // struct for matrix file
{
  int low1;
  int high1;
  int low2;
  int high2;
  std::function<void(int, int)> lambda;
} matrixThreadArgs;

void *vectorThreadFunction(void *ptr)                 // handling computation for vector file
{
  vectorThreadArgs *t = ((vectorThreadArgs *)ptr);
  for (int i = t->low; i < t->high; i++) // implementation of vector multiplication
  {
    t->lambda(i);
  }
  return nullptr;
};

void *matrixThreadFunction(void *ptr)                // handling computation for matrix file
{
  matrixThreadArgs *t = ((matrixThreadArgs *)ptr);
  for (int i = t->low1; i < t->high1; i++)  // implementation of matrix multiplication
  {
    for (int j = t->low2; j < t->high2; j++)
    {
      t->lambda(i, j);
    }
  }
  return nullptr;
};

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads)       // implementation for vector file 
{
  clock_t start = clock();

  pthread_t tid[numThreads];         //  array to hold thread id

  vectorThreadArgs args[numThreads];  // array to hold arguement for each thread

  int chunk = (high - low) / numThreads;    // calculate size for each thread to take
  int remainder = (high - low) % numThreads; // remaining work if any

  for (int i = 0; i < numThreads; ++i)   // looping
  {
    args[i].low = low + i * chunk;  // calculating lower bound 

    if (i == numThreads - 1)  // calculating upper bound
    {
      args[i].high = args[i].low + chunk + remainder;
    }
    else
    {
      args[i].high = args[i].low + chunk;
    }

    args[i].lambda = lambda;  // adding lambda function in arguements

    int thread_create = pthread_create(&tid[i], NULL, vectorThreadFunction, (void *)&args[i]);  // creating thread by passing required function

    if (thread_create != 0)  // error handling 
    {
      printf("Error creating thread %d. Error code: %d\n", i, thread_create);
      exit(1);
    }
  }

  for (int i = 0; i < numThreads; ++i)  // looping 
  {
    int thread_join = pthread_join(tid[i], NULL);  //wating for each thread to complete 

    if (thread_join != 0) // error handling 
    {
      printf("Error joining thread %d. Error code: %d\n", i, thread_join);
      exit(1);
    }

    clock_t threadEnd = clock();                                                // calculating time per thread
    double executionTime1 = ((double)(threadEnd - start)) / CLOCKS_PER_SEC;
    printf("Execution time of Thread %d : %f seconds\n", i, executionTime1);
  }

  clock_t functionEnd = clock();         // calculating time for each for_parallel call
  double executionTime = ((double)(functionEnd - start)) / CLOCKS_PER_SEC;
  printf("Execution time: %f seconds\n", executionTime);
}

void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int numThreads) // implement for matrix file
{
  clock_t start = clock();

  pthread_t tid[numThreads];  // array to hold thread ids
  matrixThreadArgs args[numThreads];  // array to hold arguements for each thread
  int chunk = (high1 - low1) / numThreads; // calculating size for each thread work
  int remainder = (high1 - low1) % numThreads; // remaing work

  for (int i = 0; i < numThreads; ++i)
  {

    args[i].low1 = low1 + i * chunk; // calulating first lower bound 
    if (i == numThreads - 1)  // calculating first upper bound
    {
      args[i].high1 = args[i].low1 + chunk + remainder;
    }
    else
    {
      args[i].high1 = args[i].low1 + chunk;
    }
    args[i].low2 = low2;  // setting second lower bound
    args[i].high2 = high2; // setting second upper bound

    args[i].lambda = lambda; // passing lambda function 

    int thread_create = pthread_create(&tid[i], NULL, matrixThreadFunction, (void *)&args[i]); // thread creation by passsing required function
    if (thread_create != 0) // error handling
    {
      printf("Error creating thread %d. Error code: %d\n", i, thread_create);
      exit(1);
    }
  }

  for (int i = 0; i < numThreads; ++i) // looping 
  {
    int thread_join = pthread_join(tid[i], NULL); // wating for thread to complete
    if (thread_join != 0) // error handling 
    {
      printf("Error joining thread %d. Error code: %d\n", i, thread_join);
      exit(1);
    }
    clock_t threadEnd = clock();                                                // calculating time for each thread
    double executionTime1 = ((double)(threadEnd - start)) / CLOCKS_PER_SEC;
    printf("Execution time of Thread %d : %f seconds\n", i, executionTime1);
  }

  clock_t functionEnd = clock();                                            // calculating time for each parallel_for call
  double executionTime = ((double)(functionEnd - start)) / CLOCKS_PER_SEC;
  printf("Execution time: %f seconds\n", executionTime);
};

int main(int argc, char **argv)
{
  /*
   * Declaration of a sample C++ lambda function
   * that captures variable 'x' by value and 'y'
   * by reference. Global variables are by default
   * captured by reference and are not to be supplied
   * in the capture list. Only local variables must be
   * explicity captured if they are used inside lambda.
   */
  int x = 5, y = 1;
  // Declaring a lambda expression that accepts void type parameter
  auto /*name*/ lambda1 = /*capture list*/ [/*by value*/ x, /*by reference*/ &y](void)
  {
    /* Any changes to 'x' will throw compilation error as x is captured by value */
    y = 5;
    std::cout << "====== Welcome to Assignment-" << y << " of the CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  // Executing the lambda function
  demonstration(lambda1); // the value of x is still 5, but the value of y is now 5

  int rc = user_main(argc, argv);

  auto /*name*/ lambda2 = [/*nothing captured*/]()
  {
    std::cout << "====== Hope you enjoyed CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main


