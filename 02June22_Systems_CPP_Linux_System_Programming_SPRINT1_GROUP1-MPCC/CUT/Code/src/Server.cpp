#include "Server.h"

char rcvDataBuf[maxDataSize];

// converts char array to string
string convertToString(char* a, int size)
{
    string s = a;
    return s;
}

// finding index of value K in a vector v(K is always present in v)
int getIndex(vector<int> v, int K)
{
   auto it = std::find(v.begin(), v.end(), K);
   // calculating the index of K
   int index = it - v.begin();
   return index;
}

// define and return a TCP server socket after doing error checking and setting relevant attributes
// the returned socket would be listening for new connections
int server_setup(string serverIpAddr,int serverPort)
{
   int serverSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(!serverSocketFd)
   {
      cout<<"Error creating socket"<<endl;
      exit(1);
   }

   struct sockaddr_in serverSockAddressInfo;
   serverSockAddressInfo.sin_family = AF_INET;
   serverSockAddressInfo.sin_port = htons(serverPort);
   inet_pton(AF_INET, serverIpAddr.c_str(), &(serverSockAddressInfo.sin_addr));

   memset(&(serverSockAddressInfo.sin_zero), '\0', 8);
   printf("Server listening on IP %x:PORT %d \n",serverSockAddressInfo.sin_addr.s_addr, serverPort);

   // bind socket to server information
   int ret = bind(serverSocketFd, (struct sockaddr *)&serverSockAddressInfo, sizeof(struct sockaddr)); 
   if(ret<0)
   {
      cout<<"Error binding socket"<<endl;
      close(serverSocketFd);
      exit(1);
   }

   // server socket is now open for receiving new connection
   ret = listen(serverSocketFd, backLog);
   if(!serverSocketFd)
   {
      cout<<"Error listening socket"<<endl;
      close(serverSocketFd);
      exit(1);
   }      

   return serverSocketFd;

}

// this function accepts incoming connections to the socket given as input and does some error checking
// it returns the socket fd which the server will use for communicating with the client
int accept_connection(int serverSocketFd)
{
   socklen_t sinSize = sizeof(struct sockaddr_in);
   struct sockaddr_in clientAddressInfo;

   memset(&clientAddressInfo, 0, sizeof(struct sockaddr_in));
   
   int newClientFd = accept(serverSocketFd, (struct sockaddr *)&clientAddressInfo, &sinSize);
   if (!newClientFd)
   {
      cout<<"Error with new client connection "<<endl;
      close(serverSocketFd);
      exit(1);
   }

   return newClientFd;
}


// this function receives the data coming to the socket given as input
// it returns the number of bytes received
int handle_connection(int clientFd)
{
   int flags = 0;
   int dataRecvd = 0;  

   memset(&rcvDataBuf, 0, maxDataSize);
   dataRecvd = recv(clientFd, &rcvDataBuf, maxDataSize, flags);
   
   return dataRecvd;
}

// this function sends the data present in rcvDataBuf global array, to the socket given as input. 
// Some text formating is done before sending the data to visualize which client is transmitting the data.
void send_data(string parentClientName, int clientFd)
{
   int flags = 0;
   int dataSent = 0;   
   string msg = "";

   if(parentClientName!="") 
   msg = parentClientName+" :"; // this additional text shows who sent the message
   msg.append(rcvDataBuf);
   char char_arr_msg[msg.length()+1];// 1 extra for the '/0' at the end in a char array
   strcpy(char_arr_msg, msg.c_str());// copy the contents of the string to the char arr

   dataSent = send(clientFd, char_arr_msg, strlen(char_arr_msg), flags);
}

// this function sends a message(present in rcvDataBuf) to all the connected clients(except the one which transmitted it)
void broadcast_msg_to_all_clients(string parentClientName, int serverSocketFd, vector<int> list_of_clientfd, vector<string> client_names)  
{

   for (int i = 0; i <list_of_clientfd.size(); ++i)
   {
      if(i!=serverSocketFd && (client_names[i]!=parentClientName))
      {
         send_data(parentClientName,list_of_clientfd[i]);
      }
   }
}


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool lCompare(login *L)
{
   string id,pass;

   int count=0;
 
   ifstream input("record.txt");
	while(input>>(char *)id.c_str()>>(char *)pass.c_str())
	{

   if((strcmp(L->getlId(), (char *)id.c_str()) == 0) && (strcmp(L->getlPasswd(), (char *)pass.c_str()) == 0))
	{
		count=1;		
	}
   
	}
	input.close();
	if(count==1)
	{
		return true;				
	}
	else
   {
		return false;	
	}
   
}

bool regWrite(signUp *S)
{
	ofstream fout("mainDB.txt", ios::out | ios::binary | ios::app);
    size_t size = sizeof(signUp);
    fout.write(reinterpret_cast<const char*>(S), size);
    fout.close();

	return true;
}

void regRead(vector<signUp >&vc)
{	
	signUp S;
	ifstream fin("mainDB.txt", ios::in| ios::binary );
    size_t size = sizeof(signUp);
	while(fin.read(reinterpret_cast<char *>(&S), size))
	{
		vc.push_back(S);
	}
    
    fin.close();
}
