#include <stdio.h>
#include <time.h>
#include "Common.h"
#include "Operator.h"
#include "Server.h"

#define IS_OPERATOR_EXIST true

using namespace std;

int main(int argc, char **argv)
{
  int node;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &node);

  if(0 == node)
  {
	 double begin = MPI_Wtime();
	 
	 if (IS_OPERATOR_EXIST) {
	   Operator oper;
	   oper.be_operator();
	 }
	 else {
	   Server server(node,IS_OPERATOR_EXIST);
	   server.be_server();  		 
	 }
	   
	 double sec = (MPI_Wtime() - begin);
     cout << "Time taken " <<  sec << " seconds " << endl;
  }
  else
  {
	Server server(node,IS_OPERATOR_EXIST);
	server.be_server();  
  }
	
  MPI_Finalize();
}
