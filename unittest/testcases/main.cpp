#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "TestRingBuffer.h"
#include "TestMessageImpl.h"
#include "TestMessageHandler.h"

int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;
//	runner.addTest( TestRingBuffer::suite() );
	runner.addTest( TestMessageImpl::suite() );
//	runner.addTest( TestMessageHandler::suite() );
	runner.run();
}
