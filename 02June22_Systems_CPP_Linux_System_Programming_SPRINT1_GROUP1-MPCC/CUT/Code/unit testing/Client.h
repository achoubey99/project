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
#include <thread>
#include <vector>
#include <algorithm>
#include <cppunit/extensions/HelperMacros.h>


// global variables
using namespace std;
const int backLog = 3;
const int maxDataSize = 1460;


class User : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( User );
	CPPUNIT_TEST( getCName_UT);
	CPPUNIT_TEST( getCPhno_UT );
	CPPUNIT_TEST_SUITE_END();
protected:
	char cname[20];
	long int cphno;
public:
	void setUp();
	User() { strcpy(cname,""); cphno=0; }
	User(char *n, int p) { strcpy(cname,n); cphno=p; }

	void setValues(char *n, int p) { strcpy(cname,n); cphno=p; }
	int getCPhno() { return cphno; }
	char *getCName() { return cname; }

	protected:
	void getCName_UT();
	void getCPhno_UT();

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
	void setDetails() 
	{
		system("clear");
		cout<<"\n\n\t\tEnter Login details"<<endl;
		cout<<"\n\n\t\tLogin ID: ";
		cin>>l_id;
		//cout<<"Password: ";
		strcpy(l_passwd,getpass("\n\n\t\tPassword: "));
		setlPasswd(l_passwd);
	}
	
};

class signUp: public login 
{
private:
	char p[20];
			
	public:
		
	void setDetails()
		{
			system("clear");
			cout<<"\n\n\t\tEnter personal details"<<endl;
			cout<<"\n\t\tEnter Name: ";
			cin>>cname;
			cout<<"\n\t\tEnter Phno: ";
			cin>>cphno;
			cout<<"\n\t\tEnter user id: ";
			cin>>l_id;
			//cout<<"\n\t\tEnter password: ";
			strcpy(p,getpass("\n\t\tEnter password: "));
			setlPasswd(p);
			
		}
};


// define and return a TCP socket after doing error checking and setting relevant attributes
int client_setup(string , int , string );


// given the client fd and server port and IP addr, connect the client to the server
void connect_to_server(int , string , int );


// this function received data from the server and stores it in rcvDataBuf array
void recv_data(int , int );


// this function sends data taken from the terminal to the server
void send_data(int , int );


// converts char array to string
string convertToString(char* , int );


// finding index of value K in a vector v(K is always present in v)
int getIndex(vector<int> , int );
void WelComeMsg();
void *Action_M(int);

void *Registration();
void *Login();