#include "Client.h"

char Menu[]="\n\t\tPress\n\n\t\t1. Registration\n\n\t\t2. Login \
         \n\n\t\t3. Exit";

char SubMenu[]="\n\t\tPress   \n\t\t1. Process Data  \n\t\t2. Search \
         \n\t\t3. GoBack to Main Menu";




int main()
{

   // declaring and defining the server port and IP address

   uint16_t serverPort=3002;
   string serverIpAddr = "127.0.0.1", clientIpAddr = "127.0.0.1", type_of_connection="TCP";

   // declaring buffers for sending and receiving data
   char rcvDataBuf[maxDataSize], sendDataBuf[maxDataSize]; 

   int flags = 0;
   system("clear");
   cout<<"------------------ Client ----------------------"<<endl;
   cout<<"IP address of the Server:  "<<serverIpAddr<<endl;
   cout<<"Port number of the Server: "<<serverPort<<endl;
   
   // setup the client and connect to the server

   int clientSocketFd = client_setup(serverIpAddr, serverPort, type_of_connection);
   connect_to_server(serverPort, serverIpAddr, clientSocketFd);
   WelComeMsg();
   cout<<Menu<<endl;

   cout<<"\n\n\t\tChoice: ";
   int ch;
   cin>>ch;

   void *buff;
   signUp *S;
   login *L;

   switch(ch)
   {
      case 1:
         cout<<"Send the Registration buff"<<endl;
         send(clientSocketFd, "1", 2, 0);

         memset(&rcvDataBuf, 0, maxDataSize);

         recv(clientSocketFd, rcvDataBuf, sizeof(rcvDataBuf), 0);
         cout<<"From Server: "<<rcvDataBuf<<endl;
         
         if(strcmp(rcvDataBuf,"Ack")==0)
         {
            buff = Action_M(ch);
            S = (signUp *)buff;
            send(clientSocketFd, S, sizeof(signUp), 0);
         }
        
         break;

      case 2:
         cout<<"Send the Login buff"<<endl;
         send(clientSocketFd, "2", 2, 0);

         memset(&rcvDataBuf, 0, maxDataSize);

         recv(clientSocketFd, rcvDataBuf, sizeof(rcvDataBuf), 0);
         cout<<"From Server: "<<rcvDataBuf<<endl;

         if(strcmp(rcvDataBuf,"Ack")==0)
         {
            buff = Action_M(ch);
            L = (login *)buff;

            send(clientSocketFd, L, sizeof(login), 0);
            memset(&rcvDataBuf, 0, maxDataSize);
            recv(clientSocketFd, rcvDataBuf, sizeof(rcvDataBuf), 0);

            if(strcmp(rcvDataBuf,"Success")==0){
               cout<<"\n\n\t\tLogin "<<rcvDataBuf<<endl;
            }
            else
               cout<<"\n\n\t\tLogin "<<rcvDataBuf<<endl;
              
         }

         break;

      case 3:
         break;

      default:
         cout<<"please select the correct choice given above Menu"<<endl;

   }

   // beginning threads to asynchronously send and receive data from the server
   thread worker_r(recv_data, clientSocketFd, flags);

    // this thread is responsible to constantly checking if server 
    // has sent some data or not and then print data in the console.

   thread worker_s(send_data, clientSocketFd, flags); 
   // this thread is responsible for taking input from the terminal
   // at any point of time and sending it to the server
   // stop the threads
   
   worker_r.join();
   worker_s.join();

   return 0;

}   
