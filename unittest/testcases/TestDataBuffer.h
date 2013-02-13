
#ifndef TESTDATABUFFER_H_
#define TESTDATABUFFER_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

#include "arch_types.h"

#define TST_BUF_SIZE 20

class TestDataBuffer : public CppUnit::TestFixture
{

public:

	static CppUnit::Test *suite()
	{

		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestDataBuffer" );

		printf("-------------------------------------------------- Testcase: Buffer Overflow\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestDataBuffer>( "Testcase: 000-0001", 	&TestDataBuffer::testOverflow ) );

		printf("-------------------------------------------------- Testcase: Buffer Size\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestDataBuffer>( "Testcase: 000-0002", 	&TestDataBuffer::testSize ) );

		printf("-------------------------------------------------- Testcase: Buffer Get everything \n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestDataBuffer>( "Testcase: 000-0003", 	&TestDataBuffer::testGetAll ) );

		printf("-------------------------------------------------- Testcase: Buffer Add & Get\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestDataBuffer>( "Testcase: 000-0004", 	&TestDataBuffer::testAddGet ) );

		return suiteOfTests;
	}

	void testOverflow();
	void testSize();
	void testGetAll();
	void testAddGet();

private:
	uint8_t testBuffer[TST_BUF_SIZE+1];
	void reset();
	void print();
};


#endif /* TESTDATABUFFER_H_ */
