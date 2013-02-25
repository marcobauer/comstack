
#ifndef DATABUFFER_H_
#define DATABUFFER_H_

#include "arch_types.h"
#include "abstract/Iterator.h"

namespace ComStack {

/*!
 * @class RingBuffer
 */
class RingBuffer : public Iterator{

public:

	enum PtrName{
		head 		= 0,
		head_old 	= 1,
		tail 		= 2,
		tail_old 	= 3,
		num_of_ptr 	= 4
	};

	RingBuffer();
	virtual ~RingBuffer(){}

	Iterator* iterator( byte *, size_t  );
	Iterator* iterator( byte *, byte * );
	Iterator* iteratorHead();
	Iterator* iteratorTail();

	byte*  	reset();
	byte* 	next();
	byte* 	prev();

	size_t 	pop( byte *buf, size_t buf_size );
	boolean push( byte );
	boolean push( byte, byte );

	size_t 	indexOf( byte* );
	size_t 	indexOf( byte *ptr, size_t offset );
	byte	valueOf( byte *ptr, size_t );

	byte* 	pointer( RingBuffer::PtrName, size_t );
	byte*	pointer( byte* , size_t );

	size_t 	size();
	size_t 	free();

	size_t 	save();
	void 	clear();
	void 	remove(byte*);
	void 	remove(size_t);
	void 	restore();

	byte*  	find( Iterator *, byte, size_t & );
	size_t 	trim( byte *, byte *, byte );

#ifdef UNITTEST
	void print();
#endif

#ifndef UNITTEST
private:
#endif

	byte 	data[BUFFER_SIZE+1]; // Addition one for termination string symbol
	size_t 	index[num_of_ptr];
	byte 	*iterator_begin, *iterator_end, *iterator_ptr;
	boolean iterator_active;
	size_t	dataload, old_dataload;
};

}  // namespace ComStack

#endif /* DATABUFFER_H_ */
