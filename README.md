# Floyd's All-Pairs Shortest Path Algorithm Parallelized with MPI

An implementation of Floyd's algorithm in C++ using MPI. It includes 3 files to demonstrate the speed of 3 different implementations:

1. a3.cpp - serial implementation
2. a3-a.cpp - parallelized implementation using 2d block mapping
   - 2d-block mapping parallelizes each k iteration
   - but processes can only work on one iteration at a time
   - meaning that this implementation is serial in its k iteration
   - and, at most, can only take $vertex^2$ number of processes
3. a3-b.cpp - parallelized implementation using pipelined 2d block mapping
   - similar to 2d block mapping but removing the limitation of 2d block mapping
   - processes are not synchronized in each k iteration 
