#ifdef __WAND__
target[name[writer.h] type[include]]
dependency[writer.o]
#endif

#ifndef BIGCHUNK_WRITER_H
#define BIGCHUNK_WRITER_H

#include "writer.h"
#include <cstdint>
#include <cstddef>

namespace Herbs
	{
	class StreamOut;
	template<class T>
	class Stringbase;
	}

namespace Bigchunk
	{
	class Writer
		{
		public:
			Writer(Herbs::StreamOut& dest);

			bool chunkIDWrite(const char* header_name);
			bool chunkSizeWrite(uint64_t size);
			size_t dataWrite(const void* buffer,size_t buffer_size);

		private:
			Herbs::StreamOut & m_dest;
			uint64_t header_size;
		};
	}

#endif
