#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "TestDataBuffer.h"
#include "TestMessage.h"

int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( TestDataBuffer::suite() );
	runner.addTest( TestMessage::suite() );
	runner.run();
}
