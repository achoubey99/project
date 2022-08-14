#include "Client.h"

// define and return a TCP socket after doing error checking and setting relevant attributes
int client_setup(string clientIpAddr, int serverPort, string type_of_connection)
{
   int clientSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(!clientSocketFd)
   {
      cout<<"Error creating socket"<<endl;
      exit(1);
   }

return clientSocketFd; 

}

// given the client fd and server port and IP addr, connect the client to the server
void connect_to_server(int serverPort, string serverIpAddr, int clientSocketFd)
{
   struct sockaddr_in serverSockAddressInfo;
   serverSockAddressInfo.sin_family = AF_INET;
   serverSockAddressInfo.sin_port = htons(serverPort);
   //serverSockAddressInfo.sin_addr.s_addr = INADDR_ANY;
   inet_pton(AF_INET, serverIpAddr.c_str(), &(serverSockAddressInfo.sin_addr));

   memset(&(serverSockAddressInfo.sin_zero), '\0', 8);

   socklen_t sinSize = sizeof(struct sockaddr_in);
   int flags = 0;
   int dataRecvd = 0, dataSent = 0;
   struct sockaddr_in clientAddressInfo;
   char rcvDataBuf[maxDataSize], sendDataBuf[maxDataSize];
   string sendDataStr, rcvDataStr;

   int ret = connect(clientSocketFd, (struct sockaddr *)&serverSockAddressInfo, sizeof(struct sockaddr));
   if (ret<0)
   {
      cout<<"Error with server connection "<<endl;
      close(clientSocketFd);
      exit(1);
   }
   cin.ignore();   
   cout<<"Connected to server!"<<endl;

   return;
}

// this function received data from the server and stores it in rcvDataBuf array
void recv_data(int clientSocketFd, int flags)
{

   int dataRecvd;
   char rcvDataBuf[maxDataSize];

   while(1)
   {
      memset(&rcvDataBuf, 0, maxDataSize);
      dataRecvd = recv(clientSocketFd, rcvDataBuf, maxDataSize, flags);
      // if chatroom is full then exit
      if(!strcmp(rcvDataBuf,"#FULL"))
      {
         cout<<"Chatroom is full. Exiting"<<endl;
         close(clientSocketFd);
         exit(1);
      }
      if(dataRecvd>0) cout<<rcvDataBuf<<endl;
   }
}

// this function sends data taken from the terminal to the server
void send_data(int clientSocketFd, int flags)
{
   char sendDataBuf[maxDataSize];
   int dataSent;

   while(1)
   {
      memset(&sendDataBuf, 0, maxDataSize);
      cin.clear();
      cin.getline(sendDataBuf,maxDataSize);
      dataSent = send(clientSocketFd, sendDataBuf, strlen(sendDataBuf), flags);
      if(!strcmp(sendDataBuf, "bye"))
      {
         close(clientSocketFd);
         exit(1);
      }
   }
}

void WelComeMsg()
{
   system("clear");
   cout<<"\n\t\tWelcome to the Client-Server Application"<<endl;
}

void *Registration()//signUp *s)
{
   signUp *S = new signUp;
   S->setDetails();

   return S;
   //s->setDetails();
}

void *Login()//signUp *s)
{
   login *l = new login;
   l->setDetails();

   return l;
   //s->setDetails();
}


void *Action_M(int ch)
{
   void *buff;
   switch(ch)
   {
      case 1:
         cout<<"Registration Process"<<endl;
         //signUp s;// = new signUp;
         //s.setDetails();
         buff = Registration();
         break;
      case 2:
         cout<<"Login Process"<<endl;
         //Action_SM(subMenu());
         buff = Login();
         break;
      case 3:
         system("clear");
         cout<<"\n\n\n\t\t\t==========Exit=========\n\n\n"<<endl;
         exit(0);
         break;
      default:
         cout<<"Enter Correct Choice"<<endl;

   }

   return buff;

}

