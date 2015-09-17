
#ifndef __Server__
#define __Server__

#define SLEEP_TIME 60

class Server
{
  private:
    
	// Members
	bool _isOperatorExist;
	int _node;
	
	// Methods
    int get_send_list() const;
	int get_recv_list() const;
	
	void send_list(double* buff,int op, int tag) const;
	void recv_list(double* buff,int op, int tag) const;
  
  public:
    Server(int node, bool isOperatorExist); 
    int be_server() const;
};


#endif