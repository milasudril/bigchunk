#ifdef __WAND__
target[name[bigchunk_writer.h] type[include]]
dependency[bigchunk_writer.o]
#endif

#ifndef CHUNKIO_BIGCHUNK_WRITER_H
#define CHUNKIO_BIGCHUNK_WRITER_H

#include "writer.h"

namespace Herbs
	{
	class StreamOut;
	}

namespace ChunkIO
	{
	class BigchunkWriter:public Writer
		{
		public:
			BigchunkWriter(Herbs::StreamOut& dest);
			
			bool chunkIDWrite(const char* header_name);
			bool chunkSizeWrite(uintmax_t size);
			size_t dataWrite(const void* buffer,size_t buffer_size);
			
		private:
			Herbs::StreamOut & m_dest;
			uintmax_t header_size;
		};
	}

#endif
