#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <algorithm>

using namespace std;


const int backLog = 3;
const int maxDataSize = 1460;
char rcvDataBuf[maxDataSize];


string convertToString(char* a, int size)
{
    string s = a;
    return s;
}


int getIndex(vector<int> v, int K)
{
   auto it = std::find(v.begin(), v.end(), K);

   int index = it - v.begin();
   return index;
}


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


   int ret = bind(serverSocketFd, (struct sockaddr *)&serverSockAddressInfo, sizeof(struct sockaddr)); 
   if(ret<0)
   {
      cout<<"Error binding socket"<<endl;
      close(serverSocketFd);
      exit(1);
   }

  
   ret = listen(serverSocketFd, backLog);
   if(!serverSocketFd)
   {
      cout<<"Error listening socket"<<endl;
      close(serverSocketFd);
      exit(1);
   }      

   return serverSocketFd;

}


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



int handle_connection(int clientFd)
{
   int flags = 0;
   int dataRecvd = 0;  

   memset(&rcvDataBuf, 0, maxDataSize);
   dataRecvd = recv(clientFd, &rcvDataBuf, maxDataSize, flags);
   
   return dataRecvd;
}


void send_data(string parentClientName, int clientFd)
{
   int flags = 0;
   int dataSent = 0;   
   string msg = "";

   if(parentClientName!="") msg = parentClientName+" :"; 
   msg.append(rcvDataBuf);
   char char_arr_msg[msg.length()+1];
   strcpy(char_arr_msg, msg.c_str());

   dataSent = send(clientFd, char_arr_msg, strlen(char_arr_msg), flags);
}


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


int main()
{


   uint16_t serverPort=3002; 
   string serverIpAddr = "127.0.0.1", sendDataStr; 
   int N;  
   vector<string> client_names;
   vector<int> list_of_clientfd;
   int max_socket_seen, bytes_recv;

   
   cout<<"------------------ Server ----------------------"<<endl;
   cout<<"IP address of the Server: ";
   cin>>serverIpAddr;
   cout<<"Port number of the Server: ";
   cin>>serverPort;
   cout<<"Max number of clients that can group chat: ";
   cin>>N;


   int serverSocketFd = server_setup(serverIpAddr,serverPort);
   max_socket_seen = serverSocketFd;

  
   fd_set current_sockets, ready_read_sockets;


   FD_ZERO(&current_sockets);
   FD_SET(serverSocketFd, &current_sockets); 

   
   while(1)
   {


      ready_read_sockets = current_sockets;

      
      if(select(FD_SETSIZE, &ready_read_sockets,NULL,NULL,NULL)< 0)
      {
         cout<<"Error"<<endl; 
         exit(1);
      }

      
      for (int i = 0; i <= max_socket_seen; ++i)
      {

         if(FD_ISSET(i, &ready_read_sockets)) 
         {
            if(i==serverSocketFd && list_of_clientfd.size()==N) 
            {
               cout<<"New connection request rejected as group chat is currently full"<<endl;
               int newClientFd = accept_connection(serverSocketFd);
               send(newClientFd, "#FULL", 6, 0);
               close(newClientFd);
               continue;
            }
            if(i==serverSocketFd)
            {
               int newClientFd = accept_connection(serverSocketFd);
               
               send(newClientFd, "Enter the name of user: ", 25, 0);
               
               memset(&rcvDataBuf, 0, maxDataSize); 
        
               recv(newClientFd, &rcvDataBuf, maxDataSize, 0); 
              
               send(newClientFd, "---------------------------------------", 41, 0); 
               
               client_names.push_back(convertToString(rcvDataBuf,sizeof(rcvDataBuf)/sizeof(char))); 
               cout<<rcvDataBuf<<" connected"<<endl;
               
               sendDataStr = "############## ";
               sendDataStr.append(rcvDataBuf); sendDataStr = sendDataStr+" connected ##############";
               
               memset(&rcvDataBuf, 0, maxDataSize); 
               
               strcpy(rcvDataBuf, sendDataStr.c_str());
               // broadcast
               broadcast_msg_to_all_clients("", serverSocketFd, list_of_clientfd,client_names);
              
               list_of_clientfd.push_back(newClientFd);
               FD_SET(newClientFd, &current_sockets); 
               if(newClientFd>max_socket_seen) max_socket_seen = newClientFd;
            }
            else
            {
               
               memset(&rcvDataBuf, 0, maxDataSize); 
               bytes_recv = handle_connection(i);

               if(bytes_recv==-1) continue;

               
               if(!strcmp(rcvDataBuf, "bye"))
               {
                  close(i);
                 
                  FD_CLR(i,&current_sockets);
                  int index_of_socket_i = getIndex(list_of_clientfd,i);
                  string leaving_client = client_names[getIndex(list_of_clientfd,i)];
                  
                  cout<<leaving_client<<" left the group chat"<<endl;
                 
                  list_of_clientfd.erase(list_of_clientfd.begin()+index_of_socket_i);
                  client_names.erase(client_names.begin()+index_of_socket_i);
                 
                  memset(&rcvDataBuf, 0, maxDataSize); 
                  broadcast_msg_to_all_clients(leaving_client+" left the group chat", 
                                               serverSocketFd, list_of_clientfd,client_names);
                  continue;
               }                  

               
               broadcast_msg_to_all_clients(client_names[getIndex(list_of_clientfd,i)], serverSocketFd, list_of_clientfd, client_names);            
            }
         }
      }

   }
}
