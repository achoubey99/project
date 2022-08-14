#pragma once

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
#include <fstream>

using namespace std;


// global variables
const int backLog = 3;
const int maxDataSize = 1460;// max number of bytes that is sent


class User {
protected:
	char cname[20];
	long int cphno;
public:
	User() { strcpy(cname,"defaultName"); cphno=0; }
	User(char *n, long int p) { strcpy(cname,n); cphno=p; }

	void setValues(char *n, long int p) { strcpy(cname,n); cphno=p; }
	long int getCPhno() { return cphno; }
	char *getCName() { return cname; }

};

class login: public User
{
private:
	char l_passwd[20];
protected:
	char l_id[20];
public:
	login(){ strcpy(l_id,""); strcpy(l_passwd,""); }
	login(char *id, char *p){ strcpy(l_id,id); strcpy(l_passwd,p); }
	char *getlPasswd(){ return l_passwd; }
	char *getlId() { return l_id; }
	void setlId(char *id) { strcpy(l_id, id); }
	void setlPasswd(char *p) { strcpy(l_passwd, p); }
	
};

class signUp: public login 
{
	private:
	char p[20];
			
	public:
		
	void setDetails(char *rcvDataBuf)
		{	
			
			

			int count = 0;
			string rid,rpass;

			cout<<"\nEnter Name: ";
			cin>>cname;
			cout<<"\nEnter Phno: ";
			cin>>cphno;
			cout<<"\nEnter user id: ";
			cin>>l_id;
			
			strcpy(p,getpass("\nEnter password: "));
			setlPasswd(p);
			

			ifstream f("record.txt");
			while(f>>(char *)rid.c_str())
			{
			if((char *)rid.c_str() == l_id)
			{
				count =1;
			}
			}
			f.close();
			if(count==1)
			{
				cout<<"\n\n This Username is taken, please try another\n";			
			}
			else
			{
				ofstream f1("record.txt" , ios::app);
				f1<<cname<<' '<<cphno<<' '<<l_id<<' '<<p<<endl;
					
			}

							
		}

		void dispSignup()
		{
			cout<<cname<<endl;
			cout<<cphno<<endl;
		}


};






// converts char array to string
string convertToString(char* , int );


// finding index of value K in a vector v(K is always present in v)
int getIndex(vector<int> , int );


// define and return a TCP server socket after doing error checking and setting relevant attributes
// the returned socket would be listening for new connections
int server_setup(string ,int );


// this function accepts incoming connections to the socket given as input and does some error checking
// it returns the socket fd which the server will use for communicating with the client
int accept_connection(int );



// this function receives the data coming to the socket given as input
// it returns the number of bytes received
int handle_connection(int);
void send_data_s(string , int );
void broadcast_msg_to_all_clients(string , int , vector<int> , vector<string> );

bool is_number(const std::string&);

bool is_number(const std::string&);

bool lCompare(login*);

bool regWrite(signUp *);


void regRead(vector<signUp>&);