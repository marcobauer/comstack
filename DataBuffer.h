
#ifndef DATABUFFER_H_
#define DATABUFFER_H_

#include "arch_types.h"

#if defined(UNITTEST)
#define BUFFER_SIZE 10
#else
#define BUFFER_SIZE 512
#endif

/*!
 * @class DataBuffer
 */
class DataBuffer {

public:

	enum Result {
		overflow 	= 0x01, //!< Buffer overflow occus; @note Buffer reset was done
		successful	= 0x02,	//!< Buffer access successful
		empty		= 0x03	//!< Ring-Buffer is empty
	};

	DataBuffer();
	virtual ~DataBuffer(){}

	/*!
	 * @brief	Read a number of character from the buffer. The method returns a string;
	 * @note
	 * @param 	buf 		- Pointer to a buffer, which is used for the result string
	 * @param	buf_size 	- Number of character
	 * @return
	 */
	DataBuffer::Result get( uint8_t *buf, size_t buf_size );

	/*!
	 *	@brief Add a character to the buffer
	 */
	DataBuffer::Result add( uint8_t value );

	/*!
	 * 	@brief Buffer will be cleared
	 */
	void reset();

	/*!
	 *	@brief Current size of the buffer
	 */
	uint16_t size();

#ifdef UNITTEST
	void print();
#endif

protected:
	char data[BUFFER_SIZE+1]; // Addition one for termination string symbol
	uint8_t write_index, read_index;
	boolean write_ahead;

	void updateAHead();
};

#endif /* DATABUFFER_H_ */
