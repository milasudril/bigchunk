#ifdef __WAND__
target[name[writer.h] type[include]]
#endif

#ifndef CHUNKIO_WRITER_H
#define CHUNKIO_WRITER_H

#include <cstdint>
#include <cstddef>

namespace ChunkIO
	{
	struct Header;
	
	class Writer
		{
		public:
			virtual bool chunkIDWrite(const char* header_name)=0;
			virtual bool chunkSizeWrite(uintmax_t size)=0;
			virtual size_t dataWrite(const void* buffer,size_t buffer_size)=0;
		};
	};

#endif
