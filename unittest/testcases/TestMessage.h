/*
 * TestMessage.h
 *
 *  Created on: Feb 13, 2013
 *      Author: tieto
 */

#ifndef TESTMESSAGE_H_
#define TESTMESSAGE_H_


#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

#include "arch_types.h"

class TestMessage : public CppUnit::TestFixture
{

public:
	static CppUnit::Test *suite()
	{
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestMessage" );

		printf("-------------------------------------------------- Testcase: ????\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessage>( "Testcase: 001-0001", 	&TestMessage::enqueueTx() ) );

		return suiteOfTests;
	}

	void enqueueTx();
	void enqueueRx();
	void dequeueTx();
	void dequeueRx();

};

#endif /* TESTMESSAGE_H_ */
