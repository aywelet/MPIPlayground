
#ifndef __Common__
#define __Common__

#include <mpi.h>

#define SIZE_OF_DATA 100

struct MPIListNode
{
  int dest;
  int src;
  double buff[SIZE_OF_DATA+1];
  MPI_Request request; 
};


#endif
