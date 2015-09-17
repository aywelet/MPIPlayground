#include <list>
#include "Operator.h"
#include "Common.h"

using namespace std;

int Operator::be_operator() const {
  int tag = 1;
  MPI_Status stat;
  list<MPIListNode*> messages;
  for(int i=1; i<NUMBER_OF_PROCESSORS ; ++i)
  {
    MPIListNode* node = new MPIListNode();
    MPI_Recv(&(node->buff), SIZE_OF_DATA+1, MPI_DOUBLE,MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &stat);
    node->src = stat.MPI_SOURCE;
    node->dest = (int)node->buff[1];
    messages.push_back(node);
	cout << "operator got message from " << node->src << " to " << node->dest << endl;
    MPI_Isend(&(node->buff), SIZE_OF_DATA+1, MPI_DOUBLE, node->dest, tag, MPI_COMM_WORLD, &(node->request));
  }

  for(list<MPIListNode*>::iterator it=messages.begin(); it!=messages.end(); ++it)
  {
    MPI_Request_free(&((*it)->request));
    delete (*it);
  }
    
  
  //sleep(1);
  return 0;
}