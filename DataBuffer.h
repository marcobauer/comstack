
#ifndef DATABUFFER_H_
#define DATABUFFER_H_

#include "arch_types.h"

#if defined(UNITTEST)
#define BUFFER_SIZE 10
#else
#define BUFFER_SIZE 254
#endif

/*!
 * @class DataBuffer
 */
class DataBuffer {

public:

	DataBuffer();
	virtual ~DataBuffer(){}

	/*!
	 * @brief	Read a number of character from the buffer. The method returns a string;
	 * @note
	 * @param 	buf 		- Pointer to a buffer, which is used for the result string
	 * @param	buf_size 	- Number of character
	 * @return
	 */
	size_t pop( byte *buf, size_t buf_size );

	/*!
	 *	@brief Add a character to the buffer
	 */
	size_t push( byte value );

	/*!
	 * 	@brief Buffer will be cleared
	 */
	void clear();

	/*!
	 *	@brief Current size of the buffer
	 */
	uint16_t size();

#ifdef UNITTEST
	void print();
#endif

protected:
	byte data[BUFFER_SIZE+1]; // Addition one for termination string symbol
	size_t 	write_index, read_index;
	boolean write_ahead;

	void updateAHead();
};

#endif /* DATABUFFER_H_ */
