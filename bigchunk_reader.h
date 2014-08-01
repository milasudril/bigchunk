#ifdef __WAND__
target[name[bigchunk_reader.h] type[include]]
dependency[bigchunk_reader.o]
#endif

#ifndef CHUNKIO_BIGCHUNK_READER_H
#define CHUNKIO_BIGCHUNK_READER_H

#include "reader.h"
#include <cstdint>

namespace Herbs
	{
	class StreamIn;
	}

namespace ChunkIO
	{
	class BigchunkReader:public Reader
		{
		public:
			BigchunkReader(Herbs::StreamIn& source);
			bool headerRead(Herbs::Stringbase<char>& name);
			bool skip();
			size_t dataRead(void* buffer,size_t buffer_size);
	
		private:	
			Herbs::StreamIn& m_source;
			uint64_t header_size;
		};
	};

#endif
