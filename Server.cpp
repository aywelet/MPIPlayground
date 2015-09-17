#include "Server.h"
#include "Common.h"
#include <unistd.h>

using namespace std;

int Server::get_send_list() const {
  //list<int> listi;
  if (!_isOperatorExist)
  {
	  return (_node+1)%NUMBER_OF_PROCESSORS;
  }
  int nextNode = _node%(NUMBER_OF_PROCESSORS - 1) + 1;
  return nextNode;
}

int Server::get_recv_list() const {
  //list<int> listi;
  if (!_isOperatorExist)
  {
	  return (_node-1)%NUMBER_OF_PROCESSORS;
  }
  int nextNode = (_node-2)%(NUMBER_OF_PROCESSORS - 1) + 1;
  return nextNode;
}

void Server::send_list(double* buff,int op, int tag) const {
  int sendList = get_send_list();
  buff[0] = _node;
  buff[1] = sendList;
  int toSend = _isOperatorExist ? op : sendList;
  MPI_Ssend(buff, SIZE_OF_DATA+1, MPI_DOUBLE, toSend, tag , MPI_COMM_WORLD);
}

void Server::recv_list(double* buff,int op, int tag) const {
  MPI_Status stat;
  int toRecv = _isOperatorExist ? op : get_recv_list();
  MPI_Recv(buff, SIZE_OF_DATA+1, MPI_DOUBLE,toRecv, tag, MPI_COMM_WORLD, &stat);
  cout << _node << " got message from " << (int)buff[0] << endl;
}


Server::Server(int node, bool isOperatorExist):_isOperatorExist(isOperatorExist),_node(node) {
	
}

int Server::be_server() const {
  int op = 0,tag=1;
  sleep(SLEEP_TIME);
  double buff[SIZE_OF_DATA+1] = {0};
  if (!_isOperatorExist && 0 != _node)
  {
	  recv_list(buff,op,tag);
	  send_list(buff,op,tag);
	  return 0;
  }
  
  send_list(buff,op,tag);
  recv_list(buff,op,tag);
  return 0;  
  
}