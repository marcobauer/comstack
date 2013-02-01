
#include "TestDataBuffer.h"
#include <DataBuffer.h>
#include <string.h>

void TestDataBuffer::testOverflow()
{
	DataBuffer buffer;
	buffer.print();
	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('5') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('6') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('7') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('8') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('9') == DataBuffer::successful );

	printf("Size:%d\n", buffer.size() );
	buffer.print();
	CPPUNIT_ASSERT( buffer.add('A') == DataBuffer::overflow   );
	buffer.print();

	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('5') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('6') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('7') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('8') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('9') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('A') == DataBuffer::overflow   );
	buffer.print();
}

void TestDataBuffer::testSize()
{
	DataBuffer buffer;
	buffer.print();
	CPPUNIT_ASSERT( buffer.size() == 0 );
	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 3 );
	buffer.print();

	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('5') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('6') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('7') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('8') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('9') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 10 );
	buffer.print();

	this->reset();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 4 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 6 );
	buffer.print();
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 1 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 5 );
	buffer.print();
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 1 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 4 );
	buffer.print();
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.add('A') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('B') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('C') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 4 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 3 );
	buffer.print();
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 3 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.size() == 0 );
	buffer.print();
	this->print();
}

void TestDataBuffer::testGetAll()
{
	DataBuffer buffer;
	buffer.print();

	this->reset();
	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('5') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('6') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('7') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('8') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('9') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 10 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "0123456789" ) == 0 );
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 10 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "01234" ) == 0 );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 10 ) == DataBuffer::empty );
}

void TestDataBuffer::testAddGet()
{
	DataBuffer buffer;
	buffer.print();

	printf("\n---> add: 0123456789");
	this->reset();
	CPPUNIT_ASSERT( buffer.add('0') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('1') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('2') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('3') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('4') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('5') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('6') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('7') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('8') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('9') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 8 ) == DataBuffer::successful );
	buffer.print();
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "01234567") == 0 );
	this->print();
	buffer.print();

	printf("\n---> add: ABCD");
	this->reset();
	CPPUNIT_ASSERT( buffer.add('A') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('B') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('C') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('D') == DataBuffer::successful );
	buffer.print();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 5 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "89ABC") == 0 );
	this->print();
	buffer.print();

	printf("\n---> add: EFGHIJKLM");
	this->reset();
	CPPUNIT_ASSERT( buffer.add('E') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('F') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('G') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('H') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('I') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('J') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('K') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('L') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('M') == DataBuffer::successful );
	buffer.print();
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 9 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "DEFGHIJKL") == 0 );
	this->print();
	buffer.print();

	this->reset();
	CPPUNIT_ASSERT( buffer.add('N') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('O') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('P') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('Q') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('R') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('S') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('T') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('U') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.add('V') == DataBuffer::successful );
	CPPUNIT_ASSERT( buffer.get( &testBuffer[0], 15 ) == DataBuffer::successful );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "MNOPQRSTUV") == 0 );
	buffer.print();
	this->print();
}

void TestDataBuffer::reset()
{
	for(int i=0; i<TST_BUF_SIZE; i++)
		this->testBuffer[i] = ' ';

	this->testBuffer[TST_BUF_SIZE] = '\0';
}

void TestDataBuffer::print()
{
	printf("\nTest-Buffer: [%s]", this->testBuffer);
}

