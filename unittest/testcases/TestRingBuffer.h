
#ifndef TEST_RINGBUFFER_H_
#define TEST_RINGBUFFER_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

#include "arch_types.h"
#include <RingBuffer.h>

using namespace ComStack;

class TestRingBuffer : public CppUnit::TestFixture
{

public:

	static CppUnit::Test *suite()
	{

		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestRingBuffer" );

		printf("-------------------------------------------------- Testcase: Buffer Overflow\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestRingBuffer>( "Testcase: 000-0001", 	&TestRingBuffer::testOverflow ) );

		printf("-------------------------------------------------- Testcase: Buffer Size\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestRingBuffer>( "Testcase: 000-0002", 	&TestRingBuffer::testSize ) );

		printf("-------------------------------------------------- Testcase: Buffer Get everything \n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestRingBuffer>( "Testcase: 000-0003", 	&TestRingBuffer::testGetAll ) );

		printf("-------------------------------------------------- Testcase: Buffer Add & Get\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestRingBuffer>( "Testcase: 000-0004", 	&TestRingBuffer::testAddGet ) );

		printf("-------------------------------------------------- Testcase: Buffer iterator\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestRingBuffer>( "Testcase: 000-0005", 	&TestRingBuffer::testIterator ) );

		return suiteOfTests;
	}

	void testOverflow();
	void testSize();
	void testGetAll();
	void testAddGet();
	void testIterator();

	void write( size_t, RingBuffer &, byte );
	void read( size_t, RingBuffer & );

private:
	uint8_t testBuffer[BUFFER_SIZE];
	void reset();
	void print( size_t );
};


#endif /* TEST_RINGBUFFER_H_ */
