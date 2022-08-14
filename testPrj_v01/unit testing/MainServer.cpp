#include "Server.h"

extern char rcvDataBuf[maxDataSize];

int main()
{

   // declaring and defining the server port
   uint16_t serverPort=3002; 
   string serverIpAddr = "127.0.0.1", sendDataStr; //  server ip address(here it is the loop back address)
   int N; // stores max number of clients 
   vector<string> client_names; // stores the username of different clients
   vector<int> list_of_clientfd;
   int max_socket_seen, bytes_recv;
   signUp *S;
   login *l;

   // take input from the terminal to set the server port and server ip address
   cout<<"------------------ Server ----------------------"<<endl;
   cout<<"IP address of the Server: "<<serverIpAddr<<endl;
   //cin>>serverIpAddr;
   cout<<"Port number of the Server: "<<serverPort<<endl;
   //cin>>serverPort;
   cout<<"Max number of clients that can group chat: ";
   cin>>N;

   // setup the server process
   int serverSocketFd = server_setup(serverIpAddr,serverPort);
   max_socket_seen = serverSocketFd;

   // declaring fd_set to keep track of open sockets and readable sockets
   fd_set current_sockets, ready_read_sockets;

   //initialize
   FD_ZERO(&current_sockets);
   FD_SET(serverSocketFd, &current_sockets); // add server socket to current socket

   // keep looping untill either server or client closes connection
   while(1)
   {

      // select is destructive so we need to use the copy of current_sockets
      ready_read_sockets = current_sockets;

      // use select() API to check which socket is currently readable
      if(select(FD_SETSIZE, &ready_read_sockets,NULL,NULL,NULL)< 0)
      {
         cout<<"Error"<<endl; 
         exit(1);
      }

      // iterate through the available sockets to check for their status
      for (int i = 0; i <= max_socket_seen; ++i)
      {

         if(FD_ISSET(i, &ready_read_sockets)) // check if the ith socket is ready for reading
         {
            if(i==serverSocketFd && list_of_clientfd.size()==N) // chatroom full
            {
               cout<<"New connection request rejected as group chat is currently full"<<endl;
               int newClientFd = accept_connection(serverSocketFd);
               send(newClientFd, "#FULL", 6, 0);// signal that chatroom is full
               close(newClientFd);
               continue;
            }
            if(i==serverSocketFd)// new connection and space available
            {
               int newClientFd = accept_connection(serverSocketFd);
               
               int dataRecvd;
               memset(&rcvDataBuf, 0, maxDataSize);
               dataRecvd = recv(newClientFd, rcvDataBuf, maxDataSize, 0);
      
               if(dataRecvd>0) {
                  if(is_number(rcvDataBuf)){
                     //cout<<"Number"<<endl;
                     switch(atoi(rcvDataBuf))
                     {
                        case 1:
                              //Registration Process
                              //send_data(clientSocketFd, 0);
                              send(newClientFd, "Ack", 4, 0);
                              S = new signUp;
                              bzero(S, sizeof(signUp));
                              recv(newClientFd, S, sizeof(signUp), 0);
                              //cout<<"Msg Received: "<<S->getlId()<<endl;
                             // cout<<"Registration Exit"<<endl;
                              break;
                        case 2:
                              //Login Process
                              //send_data(clientSocketFd, 0);
                              send(newClientFd, "Ack", 4, 0);
                              l = new login;
                              bzero(l, sizeof(login));
                              recv(newClientFd, l, sizeof(login), 0);
                              //cout<<"Msg Received: "<<l->getlPasswd()<<endl;
                              //make comparision test for login and send success or failure
                              if(lCompare(l) == true){

                                 send(newClientFd, "Success", strlen("Success"), 0);
                                 
                                 // ask the client for username
                                 //char b[] = "\n\n\tEnter the name of user: ";
                                 //send(newClientFd, "3", 2, 0);
                                 // reset the rcv buffer before storing new data
                                 memset(&rcvDataBuf, 0, maxDataSize); 
                                 // receive username from client
                                 //recv(newClientFd, &rcvDataBuf, maxDataSize, 0); 
                                 // for indicate start of conversation at the client
                                 char b[] = "\n\n\t-----------Welcome ";
                                 strcat(b, l->getlId());
                                 strcat(b, " ------------");
                                 send(newClientFd, b, strlen(b), 0); 
                                 strcpy(rcvDataBuf,l->getlId());
                                 // after the above step, the rcvDataBuf contains the new clients name
                                 // add the name to the vector
                                 client_names.push_back(convertToString(rcvDataBuf,sizeof(rcvDataBuf)/sizeof(char))); 
                                 cout<<rcvDataBuf<<" connected"<<endl;
                                 // prepare msg to be broadcasted for all other clients to let them know a new client has joined
                                 sendDataStr = "############## ";
                                 sendDataStr.append(rcvDataBuf); sendDataStr = sendDataStr+" connected ##############";
                                 // reset the rcv buffer
                                 memset(&rcvDataBuf, 0, maxDataSize); 
                                 // convert string to char array
                                 strcpy(rcvDataBuf, sendDataStr.c_str());
                                 // broadcast
                                 broadcast_msg_to_all_clients("", serverSocketFd, list_of_clientfd,client_names);
                                 // add the newClient to the list of active clients
                                 list_of_clientfd.push_back(newClientFd);
                                 FD_SET(newClientFd, &current_sockets); // add the new client to the watch list
                                 if(newClientFd>max_socket_seen) max_socket_seen = newClientFd;


                              }
                              else
                                 send(newClientFd, "Failure", strlen("Failure"), 0);

                              //cout<<"Login Exit"<<endl;
                              break;
                        default:
                              cout<<"Not correct choice"<<endl;
                     }
                  }
               }
               
               
               
               
            }
            else
            {
               //TASK 1: handle connection for client socket i i.e. read from whoever wants to speak
               memset(&rcvDataBuf, 0, maxDataSize); // reset the rcv buffer
               bytes_recv = handle_connection(i);

               if(bytes_recv==-1) continue;

               // check if the client i wants to leave the group chat
               if(!strcmp(rcvDataBuf, "bye"))
               {
                  close(i);
                  // remove the socket i from watch list
                  FD_CLR(i,&current_sockets);
                  int index_of_socket_i = getIndex(list_of_clientfd,i);
                  string leaving_client = client_names[getIndex(list_of_clientfd,i)];
                  // display msg on server showing that a client has left
                  cout<<leaving_client<<" left the group chat"<<endl;
                  // remove the client
                  list_of_clientfd.erase(list_of_clientfd.begin()+index_of_socket_i);
                  client_names.erase(client_names.begin()+index_of_socket_i);
                  // broadcast the leaving msg on all active clients
                  memset(&rcvDataBuf, 0, maxDataSize); 
                  broadcast_msg_to_all_clients(leaving_client+" left the group chat", 
                                               serverSocketFd, list_of_clientfd,client_names);
                  continue;
               }                  

               //TASK 2: Then broadcast this msg to all the clients
               broadcast_msg_to_all_clients(client_names[getIndex(list_of_clientfd,i)], serverSocketFd, list_of_clientfd, client_names);            
            }
         }
      }

   }

   return 0;
}