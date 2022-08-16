#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>

#include "client.h"

CPPUNIT_TEST_SUITE_REGISTRATION( User );

void User::setUp()
{
	userid="ramani";
	password="123";
	
	
    
}

 void User::getPassword_UT_sunny() {
		string password = "123";
		string password2 = getPassword();
		
		CPPUNIT_ASSERT_EQUAL(password, password2);
 }
 

void User::getPassword_UT_rainy() {
		string password = "345";
		string password2 = getPassword();
		
		CPPUNIT_ASSERT_EQUAL(password, password2);
 }



void User::getUserid_UT_sunny() {
		std::string Name = "ramani";
		std::string Name2 = getUserid();
		
		CPPUNIT_ASSERT_EQUAL(Name, Name2);
 }
 

void User::getUserid_UT_rainy() {
		std::string Name = "jahnavi";
		std::string Name2 = getUserid();
		
		CPPUNIT_ASSERT_EQUAL(Name, Name2);
 }






/*
	void User::getCPhno_UT(){
		long int num=8509374297;
		long int num2 =getCPhno();
		CPPUNIT_ASSERT_EQUAL(num,num2 );
}*/
