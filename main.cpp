#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Common.h"
#include "Operator.h"
#include "Server.h"

#define IS_OPERATOR_EXIST true
#define NUMBER_OF_RUNS 100

using namespace std;

int main(int argc, char **argv)
{
  int node,size;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &node);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(0 == node)
  {
	 double begin = MPI_Wtime();
	 
	 if (IS_OPERATOR_EXIST) {
	   for (int i = 0; i < NUMBER_OF_RUNS ; ++i)
           { 
             Operator oper(size);
	     oper.be_operator();
           }
	 }
	 else {
	   for (int i = 0; i < NUMBER_OF_RUNS ; ++i)
           {  
             Server server(node,size,IS_OPERATOR_EXIST);
	     server.be_server();
           }  		 
	 }
	   
	 double sec = (MPI_Wtime() - begin);
         ofstream file;
         ostringstream fileName;
         fileName << (IS_OPERATOR_EXIST ?  "Operator" : "Server1");
         fileName << size << ".txt";
         file.open(fileName.str().c_str());
         file << "Time taken " <<  sec << " seconds " << endl;
         file.close();
  }
  else
  {
    for (int i = 0; i < NUMBER_OF_RUNS ; ++i)
    {
      Server server(node,size,IS_OPERATOR_EXIST);
      server.be_server();
    }  
  }
	
  MPI_Finalize();
}
