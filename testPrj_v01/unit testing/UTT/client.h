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

using namespace std;




class User : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( User );
	CPPUNIT_TEST( getCName_UT);
	CPPUNIT_TEST( getCPhno_UT );
	CPPUNIT_TEST_SUITE_END();
protected:
	string cname;
	long int cphno;
public:
	void setUp();
	

	void setValues(char n,long int p) { cname=n; cphno=p; }
	long int getCPhno() { return cphno; }
	string getCName() { return cname; }

	protected:
	void getCName_UT();
	void getCPhno_UT();

};
