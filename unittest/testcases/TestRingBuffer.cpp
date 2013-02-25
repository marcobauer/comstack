
#include "TestRingBuffer.h"

#include <string.h>

void TestRingBuffer::testOverflow()
{
	RingBuffer buffer;

	write( BUFFER_SIZE/2, buffer, 0x55 );
	read( 15, buffer );

	write( BUFFER_SIZE/2+10, buffer, 0xAA );

	read( 30, buffer );

	write( 15, buffer, 0x44 );

	read( 5, buffer );

	read( 5, buffer );

	write( 5, buffer, 0x88 );

	read( BUFFER_SIZE, buffer );

	write( BUFFER_SIZE/2, buffer, 0x55 );
	buffer.save();

	for(int i=0; i<(BUFFER_SIZE/2)+1; i++)
	{
		if( i == (BUFFER_SIZE/2))
			CPPUNIT_ASSERT( buffer.push(0x55) == 0 );
		else
			CPPUNIT_ASSERT( buffer.push(0x55) );
	}

	buffer.print();

	buffer.restore();

	buffer.print();

	for(int i=0; i<(BUFFER_SIZE/2); i++)
	{
		CPPUNIT_ASSERT( buffer.push(0xAA) );
	}

	buffer.print();

}

void TestRingBuffer::testSize()
{
	RingBuffer buffer;

	CPPUNIT_ASSERT( buffer.size() == 0 );
	buffer.save();

	for(int i=0; i<(BUFFER_SIZE/2); i++)
		CPPUNIT_ASSERT( buffer.push(0x55) );

	CPPUNIT_ASSERT( buffer.size() == (BUFFER_SIZE/2) );
	buffer.print();

	for(int i=0; i<(BUFFER_SIZE/2); i++)
		CPPUNIT_ASSERT( buffer.push(0x55) );

	CPPUNIT_ASSERT( buffer.size() == BUFFER_SIZE );
	buffer.print();

	testBuffer[(BUFFER_SIZE/2)] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], (BUFFER_SIZE/2) ) == (BUFFER_SIZE/2) );
	CPPUNIT_ASSERT( buffer.size() == (BUFFER_SIZE/2) );
	buffer.print();

	testBuffer[10] = '\0';
	for(int i=0; i<10; i++)
		CPPUNIT_ASSERT( buffer.push(0x55) );

	buffer.print();

	CPPUNIT_ASSERT( buffer.size() == (BUFFER_SIZE/2)+10 );

	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], (BUFFER_SIZE/2)+10 ) == (BUFFER_SIZE/2)+10 );

	buffer.print();
	CPPUNIT_ASSERT( buffer.size() == 0 );
}

void TestRingBuffer::testGetAll()
{
	RingBuffer buffer;

	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') );
	CPPUNIT_ASSERT( buffer.push('1') );
	CPPUNIT_ASSERT( buffer.push('2') );
	CPPUNIT_ASSERT( buffer.push('3') );
	CPPUNIT_ASSERT( buffer.push('4') );
	CPPUNIT_ASSERT( buffer.push('5') );
	CPPUNIT_ASSERT( buffer.push('6') );
	CPPUNIT_ASSERT( buffer.push('7') );
	CPPUNIT_ASSERT( buffer.push('8') );
	CPPUNIT_ASSERT( buffer.push('9') );
	testBuffer[10] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == 10 );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "0123456789" ) == 0 );

	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') );
	CPPUNIT_ASSERT( buffer.push('1') );
	CPPUNIT_ASSERT( buffer.push('2') );
	CPPUNIT_ASSERT( buffer.push('3') );
	CPPUNIT_ASSERT( buffer.push('4') );
	testBuffer[5] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == 5 );
	CPPUNIT_ASSERT( strcmp( (const char*)&testBuffer[0], "01234" ) == 0 );
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 10 ) == -1 );
}

void TestRingBuffer::testAddGet()
{
	RingBuffer buffer;

	for(int i=0; i<BUFFER_SIZE; i++)
		CPPUNIT_ASSERT( buffer.push(0x55) );

	buffer.print();
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], BUFFER_SIZE ) == BUFFER_SIZE );
	buffer.print();

	printf("\n---> add: 0123456789");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('0') );
	CPPUNIT_ASSERT( buffer.push('1') );
	CPPUNIT_ASSERT( buffer.push('2') );
	CPPUNIT_ASSERT( buffer.push('3') );
	CPPUNIT_ASSERT( buffer.push('4') );
	CPPUNIT_ASSERT( buffer.push('5') );
	CPPUNIT_ASSERT( buffer.push('6') );
	CPPUNIT_ASSERT( buffer.push('7') );
	CPPUNIT_ASSERT( buffer.push('8') );
	CPPUNIT_ASSERT( buffer.push('9') );
	testBuffer[8] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 8 ) == 8 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "01234567") == 0 );

	printf("\n---> add: ABCD");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('A') );
	CPPUNIT_ASSERT( buffer.push('B') );
	CPPUNIT_ASSERT( buffer.push('C') );
	CPPUNIT_ASSERT( buffer.push('D') );
	buffer.print();
	testBuffer[5] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 5 ) == 5 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "89ABC") == 0 );

	printf("\n---> add: EFGHIJKLM");
	this->reset();
	CPPUNIT_ASSERT( buffer.push('E') );
	CPPUNIT_ASSERT( buffer.push('F') );
	CPPUNIT_ASSERT( buffer.push('G') );
	CPPUNIT_ASSERT( buffer.push('H') );
	CPPUNIT_ASSERT( buffer.push('I') );
	CPPUNIT_ASSERT( buffer.push('J') );
	CPPUNIT_ASSERT( buffer.push('K') );
	CPPUNIT_ASSERT( buffer.push('L') );
	CPPUNIT_ASSERT( buffer.push('M') );
	buffer.print();
	testBuffer[9] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 9 ) == 9 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "DEFGHIJKL") == 0 );

	this->reset();
	CPPUNIT_ASSERT( buffer.push('N') );
	CPPUNIT_ASSERT( buffer.push('O') );
	CPPUNIT_ASSERT( buffer.push('P') );
	CPPUNIT_ASSERT( buffer.push('Q') );
	CPPUNIT_ASSERT( buffer.push('R') );
	CPPUNIT_ASSERT( buffer.push('S') );
	CPPUNIT_ASSERT( buffer.push('T') );
	CPPUNIT_ASSERT( buffer.push('U') );
	CPPUNIT_ASSERT( buffer.push('V') );
	testBuffer[10] = '\0';
	CPPUNIT_ASSERT( buffer.pop( &testBuffer[0], 15 ) == 10 );
	CPPUNIT_ASSERT( strcmp((const char*)&testBuffer[0], "MNOPQRSTUV") == 0 );
}

void TestRingBuffer::testIterator()
{
	RingBuffer buffer;

	CPPUNIT_ASSERT( buffer.push(0xAA) );

	for(int i=0; i<BUFFER_SIZE/2; i++)
		CPPUNIT_ASSERT( buffer.push(0x55) );

	CPPUNIT_ASSERT( buffer.push(0xAA) );

	Iterator *iterator = buffer.iteratorHead();//( buffer.getHeadSaved(), buffer.getHead() );

	int i=0;
	uint16_t cnt = buffer.size();
	byte *data;

	while( (data = buffer.next()) ){
		if( (i == 0) || (i == cnt ) )
		{
			CPPUNIT_ASSERT( *data == 0xAA );
			printf("%02X", *data );
		}
		i++;
	}
	CPPUNIT_ASSERT( i == cnt );

}

void TestRingBuffer::reset()
{
	for(int i=0; i<BUFFER_SIZE; i++)
		this->testBuffer[i] = ' ';

	this->testBuffer[BUFFER_SIZE] = '\0';
}

void TestRingBuffer::print( size_t num )
{
	printf(" ");

	for(int i= 0; i< num; i++)
	{
		printf("%02d", i );
		if( i < (num-1) )
			printf(" ");
	}

	printf("\n");

	printf("[");

	for(int i= 0; i< num; i++)
	{
		printf("%02X", testBuffer[i] );
		if( i < (num-1) )
			printf("|");
	}

	printf("]\n");
}

void TestRingBuffer::write( size_t size, RingBuffer &buffer, byte data )
{
	for(int i=0; i<size; i++)
		CPPUNIT_ASSERT( buffer.push(data) );

	buffer.save();

	buffer.print();

}

void TestRingBuffer::read( size_t size, RingBuffer &buffer )
{
	size_t cnt = buffer.pop( &testBuffer[0], size );
	print(cnt);
	buffer.print();
}



