#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>
#include <list>

#define SLEEP_TIME 1
#define NUMBER_OF_PROCESSORS 3 
#define SIZE_OF_DATA 10

int be_server(int node);
int be_operator();
int get_send_list(int node);

struct MPIListNode
{
  int dest;
  int src;
  double buff[SIZE_OF_DATA+1];
  MPI_Request request; 
};

using namespace std;

int main(int argc, char **argv)
{
  int node;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &node);

  if(node > 0)
  {
    be_server(node);
  }
  else
  {
    clock_t start = clock();
    be_operator();
    clock_t diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
}

  MPI_Finalize();
}

int be_server(int node)
{
  int op = 0,tag=1;
  sleep(SLEEP_TIME);
  int sendList = get_send_list(node);
  double buff[SIZE_OF_DATA+1] = {sendList,0};
  MPI_Ssend(&buff, SIZE_OF_DATA+1, MPI_DOUBLE, op, tag , MPI_COMM_WORLD);
  MPI_Status stat;
  MPI_Recv(&buff, SIZE_OF_DATA+1, MPI_DOUBLE,op, tag, MPI_COMM_WORLD, &stat);
  printf("%d got message from %d\n",node,(int)buff[0]);
  return 0;
}

int be_operator()
{
  int tag = 1;
  MPI_Status stat;
  list<MPIListNode*> messages;
  for(int i=1; i<NUMBER_OF_PROCESSORS ; ++i)
  {
    MPIListNode* node = new MPIListNode();
    MPI_Recv(&(node->buff), SIZE_OF_DATA+1, MPI_DOUBLE,MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &stat);
    node->src = stat.MPI_SOURCE;
    node->dest = (int)node->buff[0];
    messages.push_back(node);
    printf("operator got message from %d to %d\n",node->src,node->dest);
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

int get_send_list(int node)
{
  //list<int> listi;
  int nextNode = node%(NUMBER_OF_PROCESSORS-1)+1;
  return nextNode;
}
