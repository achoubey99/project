#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>

using namespace std;

void login();
void registration();
void forgot();




string encrypt(string str)
{
    int i;
    
    for(i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] + 2; //the key for encryption is 3 that is added to ASCII value

    
    return str;
}


string decrypt(string str)
{
    int i;
    
    for(i = 0; (i < 100 && str[i] != '\0'); i++)
         str[i] = str[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value

      return str;

}


int main()
{
	int choice;
	
	system("clear");

   cout<<"\t\t\t\t\t\t----------------------------\n\n\n";
   cout<<"\t\t\t\t\t\t....welcome to login page....\n\n\n";
   cout<<"\t\t\t\t\t\t-----------menu--------------\n\n\n";
   cout<<"                       \n\n";
   cout<<"\t press 1 to login"<<endl;
   cout<<"\t press 2 to register"<<endl;
   cout<<"\t press 3 to retrieve your password"<<endl;
   cout<<"\t press 4 to exit"<<endl;
   cout<<"\n\t\t\t please enter your choice:";
   cin>>choice;
   cout<<endl;

   switch(choice)
   {
	    case 1:
		   login();
		   break;
	    case 2:
		   registration();
		   break;
	    case 3:
		   forgot();
		   break;
        case 4:
		   cout<<"\t\t\t thank you\n\n";
		   break;
        default:
		   cout<<"\t\t\t please select from the options given above \n"<<endl;
		   sleep(5);
		   main();
   }
}
void login()
{
	int count;
	string userId,password,id,pass;
	
	

	cout<<"\t\t\t please enter the username and password:"<<endl;
	cout<<"\t\t\t username: ";
	cin>>userId;
	cout<<"\t\t\t password: ";
	cin>>password;


	ifstream input("record.txt");
	while(input>>id>>pass)
	{
	if(decrypt(id)==userId &&  decrypt(pass)==password)
	{
		count=1;

		
	}
	}
	input.close();
	if(count==1)
	{	
		
		cout<<userId<<" your login is successful!\nthanks for logging in \n";
		sleep(2);

		system("clear");

		//const char* args[]={"./client" , userId , NULL}
		execvp("./client", NULL/*args*/);
		
	}
	else{
		cout<<"\n login error !\n please check your username and password"<<endl;
		sleep(5);
		login();
	
	}
	}
	
void registration()
{
	
	int count = 0;
	string ruserId,rpassword,rid,rpass;

	string name,lname,email,gender;
	string age;
	string number;

	system("clear");

	cout<<"\t\t\t\t\t\t WELCOME TO THE REGISTRATION PAGE\n\n\n";

	cout<<"\t\t\tEnter your First name:";
	
	cin>>name;

	cout<<"\t\t\tEnter your last name:";

	cin>>lname;
			    
			    
	cout<<"\t\t\tEnter your Age:";
	cin>>age;
    

	cout<<"\t\t\tEnter your Gender:";
    cin>>gender;
    
				        
				        
    cout<<"\t\t\tEnter your Mobile Number:";
    cin>>number;
					      
					      
					      
	cout<<"\t\t\tEnter your Email-id:";
    cin>>email;
	

	cout<<"\t\t\tEnter any username:";
	cin>>ruserId;
	cout<<"\t\t\tEnter your password:";
	cin>>rpassword;

	ifstream f("record.txt");
	while(f>>rid)
	{
		if(decrypt(rid) == ruserId)
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
		f1<<encrypt(name)<<' '<<encrypt(lname)<<' '<<encrypt(age)<<' '<<encrypt(gender)<<' '<<encrypt(number)<<' '<<encrypt(email)<<' '<<encrypt(ruserId)<<' '<<encrypt(rpassword)<<endl;
		cout<<"\n\t\t\t registration is successful:\n";
		
	}

	
	
	
	
	sleep(2);
	system("clear");
	main();

}
void forgot()
{
	int option;
	
	system("clear");

	cout<<"\t\t\t  forgot password ? \n\n\n" <<endl;
	cout<<"press 1 to search your id by username"<<endl;
	cout<<"press 2 to go back to the main menu "<<endl;
	cout<<"\t\t\t enter your choice :";
	cin>>option;
	switch(option)
	{
 	case 1:{
		int count=0;
		string suserId,sId,spass;
		cout<<"\n\t\t\t enter your Username:";
		cin>>suserId;
		ifstream f2("record.txt");
		while(f2>>sId>>spass)
		{
		if(decrypt(sId)==suserId)
		{
			count=1;
		}
		}
		f2.close();
		if(count==1)
		{
			cout<<"\n\nYour account is found \n"<<"The password is : "<<decrypt(spass)<<endl;
			
			sleep(5);

			main();
			
		}
		else{
			cout<<"sorry! your account is not found!\n";

			sleep(5);
			main();
		}
		
		
		break;
		} 
	case 2:
		{
			main();
		}
	default:
		cout<<"\t\t\t wrong choice ! please try again"<<endl;
		forgot();
	}
}


