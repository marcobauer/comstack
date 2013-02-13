
#include "TestDataBuffer.h"
#include <DataBuffer.h>
#include <string.h>

void TestDataBuffer::testOverflow()
{
	DataBuffer buffer;
	buffer.print();
	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	CPPUNIT_ASSERT( buffer.push('5') == 1 );
	CPPUNIT_ASSERT( buffer.push('6') == 1 );
	CPPUNIT_ASSERT( buffer.push('7') == 1 );
	CPPUNIT_ASSERT( buffer.push('8') == 1 );
	CPPUNIT_ASSERT( buffer.push('9') == 1 );

	printf("Size:%d\n", buffer.size() );
	buffer.print();
	CPPUNIT_ASSERT( buffer.push('A') == -1   );
	buffer.print();

	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	CPPUNIT_ASSERT( buffer.push('5') == 1 );
	CPPUNIT_ASSERT( buffer.push('6') == 1 );
	CPPUNIT_ASSERT( buffer.push('7') == 1 );
	CPPUNIT_ASSERT( buffer.push('8') == 1 );
	CPPUNIT_ASSERT( buffer.push('9') == 1 );
	CPPUNIT_ASSERT( buffer.push('A') ==-1 );
	buffer.print();
}

void TestDataBuffer::testSize()
{
	DataBuffer buffer;
	buffer.print();
	CPPUNIT_ASSERT( buffer.size() == 0 );
	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.size() == 3 );
	buffer.print();

	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	CPPUNIT_ASSERT( buffer.push('5') == 1 );
	CPPUNIT_ASSERT( buffer.push('6') == 1 );
	CPPUNIT_ASSERT( buffer.push('7') == 1 );
	CPPUNIT_ASSERT( buffer.push('8') == 1 );
	CPPUNIT_ASSERT( buffer.push('9') == 1 );
	CPPUNIT_ASSERT( buffer.size() == 10 );
	buffer.print();

	this->reset();
	testBuffer[4] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 4 ) == 4 );
	CPPUNIT_ASSERT( buffer.size() == 6 );
	buffer.print();
	this->print();

	this->reset();
	testBuffer[1] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 1 ) == 1 );
	CPPUNIT_ASSERT( buffer.size() == 5 );
	buffer.print();
	this->print();

	this->reset();
	testBuffer[1] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 1 ) == 1 );
	CPPUNIT_ASSERT( buffer.size() == 4 );
	buffer.print();
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.push('A') == 1 );
	CPPUNIT_ASSERT( buffer.push('B') == 1 );
	CPPUNIT_ASSERT( buffer.push('C') == 1 );
	testBuffer[4] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 4 ) == 4);
	CPPUNIT_ASSERT( buffer.size() == 3 );
	buffer.print();
	this->print();

	this->reset();
	testBuffer[3] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 3 ) == 3 );
	CPPUNIT_ASSERT( buffer.size() == 0 );
	buffer.print();
	this->print();
}

void TestDataBuffer::testGetAll()
{
	DataBuffer buffer;
	buffer.print();

	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	CPPUNIT_ASSERT( buffer.push('5') == 1 );
	CPPUNIT_ASSERT( buffer.push('6') == 1 );
	CPPUNIT_ASSERT( buffer.push('7') == 1 );
	CPPUNIT_ASSERT( buffer.push('8') == 1 );
	CPPUNIT_ASSERT( buffer.push('9') == 1 );
	testBuffer[10] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == 10 );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "0123456789" ) == 0 );
	this->print();

	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	testBuffer[5] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == 5 );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "01234" ) == 0 );
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == -1 );
}

void TestDataBuffer::testAddGet()
{
	DataBuffer buffer;
	buffer.print();

	printf("\n---> add: 0123456789");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') == 1 );
	CPPUNIT_ASSERT( buffer.push('1') == 1 );
	CPPUNIT_ASSERT( buffer.push('2') == 1 );
	CPPUNIT_ASSERT( buffer.push('3') == 1 );
	CPPUNIT_ASSERT( buffer.push('4') == 1 );
	CPPUNIT_ASSERT( buffer.push('5') == 1 );
	CPPUNIT_ASSERT( buffer.push('6') == 1 );
	CPPUNIT_ASSERT( buffer.push('7') == 1 );
	CPPUNIT_ASSERT( buffer.push('8') == 1 );
	CPPUNIT_ASSERT( buffer.push('9') == 1 );
	testBuffer[8] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 8 ) == 8 );
	buffer.print();
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "01234567") == 0 );
	this->print();
	buffer.print();

	printf("\n---> add: ABCD");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('A') == 1 );
	CPPUNIT_ASSERT( buffer.push('B') == 1 );
	CPPUNIT_ASSERT( buffer.push('C') == 1 );
	CPPUNIT_ASSERT( buffer.push('D') == 1 );
	buffer.print();
	testBuffer[5] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 5 ) == 5 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "89ABC") == 0 );
	this->print();
	buffer.print();

	printf("\n---> add: EFGHIJKLM");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('E') == 1 );
	CPPUNIT_ASSERT( buffer.push('F') == 1 );
	CPPUNIT_ASSERT( buffer.push('G') == 1 );
	CPPUNIT_ASSERT( buffer.push('H') == 1 );
	CPPUNIT_ASSERT( buffer.push('I') == 1 );
	CPPUNIT_ASSERT( buffer.push('J') == 1 );
	CPPUNIT_ASSERT( buffer.push('K') == 1 );
	CPPUNIT_ASSERT( buffer.push('L') == 1 );
	CPPUNIT_ASSERT( buffer.push('M') == 1 );
	buffer.print();
	testBuffer[9] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 9 ) == 9 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "DEFGHIJKL") == 0 );
	this->print();
	buffer.print();

	this->reset();
	CPPUNIT_ASSERT( buffer.push('N') == 1 );
	CPPUNIT_ASSERT( buffer.push('O') == 1 );
	CPPUNIT_ASSERT( buffer.push('P') == 1 );
	CPPUNIT_ASSERT( buffer.push('Q') == 1 );
	CPPUNIT_ASSERT( buffer.push('R') == 1 );
	CPPUNIT_ASSERT( buffer.push('S') == 1 );
	CPPUNIT_ASSERT( buffer.push('T') == 1 );
	CPPUNIT_ASSERT( buffer.push('U') == 1 );
	CPPUNIT_ASSERT( buffer.push('V') == 1 );
	testBuffer[10] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 15 ) == 10 );
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

