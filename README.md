# Simple Multithreader

This project demonstrates how to perform parallel computations using POSIX threads (`pthread`) in C++, including multithreaded matrix multiplication and vector addition using lambda functions and custom thread management.

## ✨ Features

* Generic `parallel_for` implementation for:

  * Vector operations: `parallel_for(int low, int high, lambda, numThreads)`
  * Matrix operations: `parallel_for(int low1, int high1, int low2, int high2, lambda, numThreads)`
* Uses modern C++ lambda expressions
* Measures execution time for each thread and the entire operation
* Simple and clean multithreading using `pthread`
* Automatic memory management and result validation using `assert`

## 📁 Project Structure

```
simple-multithreader/
├── simple-multithreader.h         # Core threading logic (header included in both demos)
├── matrix_mult.cpp                # Demonstrates multithreaded matrix multiplication
├── vector_add.cpp                 # Demonstrates multithreaded vector addition
├── README.md                      # This file
```

## ⚙️ Build Instructions

You can compile the project using `g++` with `-pthread` flag:

### For Matrix Multiplication:

```bash
g++ -o matrix_mult matrix_mult.cpp -pthread
```

### For Vector Addition:

```bash
g++ -o vector_add vector_add.cpp -pthread
```

## 🚀 Usage

### Run Matrix Multiplication

```bash
./matrix_mult <num_threads> <matrix_size>
```

Example:

```bash
./matrix_mult 4 1024
```

### Run Vector Addition

```bash
./vector_add <num_threads> <vector_size>
```

Example:

```bash
./vector_add 4 48000000
```

If no arguments are passed, defaults are used: 2 threads and size 1024 for matrix, 48 million for vector.

## 🧠 Concepts Demonstrated

* Thread creation with `pthread_create`
* Synchronization with `pthread_join`
* Lambda expressions as thread tasks
* Performance benchmarking with `clock()`
* Dynamic work partitioning and load balancing
* Memory allocation/deallocation for 1D and 2D arrays

## ✅ Sample Output

```bash
Execution time of Thread 0 : 0.123456 seconds
Execution time of Thread 1 : 0.124321 seconds
Execution time: 0.124800 seconds
Test Success.
```

## 📄 License

This project is open-source and available under the [MIT License](LICENSE) (add license file if needed).
