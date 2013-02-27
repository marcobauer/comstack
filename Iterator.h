
#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "arch_types.h"

class Iterator {

public:
	virtual ~Iterator(){};

	virtual byte* reset() 	= 0;
	virtual byte* next() 	= 0;
	virtual byte* prev() 	= 0;
};

#endif // BUFFERITERATOR_H_
