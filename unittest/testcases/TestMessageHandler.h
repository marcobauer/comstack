
#ifndef TEST_MESSAGEHANDLER_H_
#define TEST_MESSAGEHANDLER_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

#include "arch_types.h"
#include <MessageHandler.h>

#include "TestMessageImpl.h"

using namespace ComStack;


class TestMessageHandler : public CppUnit::TestFixture
{

public:
	static CppUnit::Test *suite()
	{
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestMsgHandler" );

		printf("-------------------------------------------------- Testcase: lock and unlock\n");
		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageHandler>( "Testcase: 001-0002", 	&TestMessageHandler::lock_unlock ) );

//		printf("-------------------------------------------------- Testcase: dequeue tx messages\n");
//		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageHandler>( "Testcase: 001-0003", 	&TestMessageHandler::dequeueTx ) );
//
//		printf("-------------------------------------------------- Testcase: enqueue rx messages\n");
//		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageHandler>( "Testcase: 001-04", 	&TestMessageHandler::enqueueRx ) );


		return suiteOfTests;
	}

	void lock_unlock();

	MessageHandlerImpl messageHandler;

};

#endif /* TEST_MESSAGEHANDLER_H_ */
