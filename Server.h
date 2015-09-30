
#ifndef __Server__
#define __Server__

class Server
{
  private:
  
    static const int SLEEP_TIME = 60;
    
    // Members
    bool _isOperatorExist;
    int _node, _size;
	
    // Methods
    int get_send_list() const;
    int get_recv_list() const;
	
    void send_list(double* buff,int op, int tag) const;
    void recv_list(double* buff,int op, int tag) const;
  
  public:
    Server(int node, int size, bool isOperatorExist); 
    int be_server() const;
};


#endif
