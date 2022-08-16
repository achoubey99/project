#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>

#include "client.h"

CPPUNIT_TEST_SUITE_REGISTRATION( User );

void User::setUp()
{
	cname = "Abhishek kumar choubey";
	cphno = 8509374297;

    
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
