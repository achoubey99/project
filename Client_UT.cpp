#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>

#include "client.h"

CPPUNIT_TEST_SUITE_REGISTRATION( User );

void User::setUp()
{
	cname = "Abhishek kumar choubey";
	cphno = 8509374297;
	//email = achoubey99@gmail.com;
	age = 24;
	
    
}
/*
void User::getEmail_UT() {
		std::string email1 = "achoubey99@gmail.com";
		std::string email2= getEmail();
		
		CPPUNIT_ASSERT_EQUAL(email1,email2);
 }
 */
 void User::getAge_UT() {
		int age1 = 23;
		int age2 = getAge();
		
		CPPUNIT_ASSERT_EQUAL(age1, age2);
 }
 


void User::getCName_UT() {
		std::string Name = "Abhishek kumar choubey";
		std::string Name2 = getCName();
		
		CPPUNIT_ASSERT_EQUAL(Name, Name2);
 }
 

	void User::getCPhno_UT(){
		long int num=8509374297;
		long int num2 =getCPhno();
		CPPUNIT_ASSERT_EQUAL(num,num2 );
}
