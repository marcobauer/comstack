
#ifndef TEST_MESSAGEIMPL_H_
#define TEST_MESSAGEIMPL_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

#include "arch_types.h"
#include <TxMessage.h>
#include <RxMessage.h>

#include "MessageHandlerImpl.h"

using namespace ComStack;

class TestMessageImpl : public CppUnit::TestFixture
{

public:
	static CppUnit::Test *suite()
	{
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestMsgHandler" );

		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageImpl>( "Testcase: 001-0001", 	&TestMessageImpl::counter ) );

		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageImpl>( "Testcase: 001-0002", 	&TestMessageImpl::msgOverflow ) );

//		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageImpl>( "Testcase: 001-0003", 	&TestMessageImpl::msgError ) );

		suiteOfTests->addTest( new CppUnit::TestCaller<TestMessageImpl>( "Testcase: 001-0004", 	&TestMessageImpl::findMessage ) );

		return suiteOfTests;
	}

	void counter();
	void msgOverflow();
	void msgError();
	void findMessage();
private:
	MessageHandlerImpl messageHandler;
//	size_t 	pushMessage( MessageImpl &, Message::Type, Message::Id, byte, size_t );
	void 	popMessage( Message &, size_t );
//	void 	pushErrorHead( MessageImpl &, Message::Type );
//	void 	pushErrorContent( MessageImpl &, Message::Type, size_t  );
//	void 	pushErrorTail( MessageImpl &, Message::Type, size_t);

	void 	copyTx2Rx( TxMessage &, RxMessage & );
	void 	readRx( RxMessage &message, Message::Type type, Instruction::Id id, byte seqCnt, size_t contentSize, byte value );
	void	writeTx( TxMessage &message, Message::Type type, Instruction::Id id, size_t contentSize, byte value );
};

#endif /* TEST_MESSAGEHANDLER_H_ */
