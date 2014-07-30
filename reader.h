#ifdef __WAND__
target[name[reader.h] type[include]]
#endif

#ifndef CHUNKIO_READER_H
#define CHUNKIO_READER_H

namespace Herbs
	{
	template<class T>
	class Stringbase;
	}
	
#include <cstddef>

namespace ChunkIO
	{
	class Reader
		{
		public:
			virtual bool headerRead(Herbs::Stringbase<char>& name)=0;
			virtual size_t dataRead(void* buffer,size_t buffer_size)=0;
			virtual bool skip()=0;
		};
	};

#endif
