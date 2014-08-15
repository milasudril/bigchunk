#ifdef __WAND__
target[name[reader.h] type[include]]
dependency[reader.o]
#endif

#ifndef BIGCHUNK_READER_H
#define BIGCHUNK_READER_H

#include <cstdint>

namespace Herbs
	{
	class StreamIn;
	template<class T>
	class Stringbase;
	}

namespace Bigchunk
	{
	class Reader
		{
		public:
			Reader(Herbs::StreamIn& source);
			bool headerRead(Herbs::Stringbase<char>& name);
			bool skip();
			size_t dataRead(void* buffer,size_t buffer_size);
	
		private:	
			Herbs::StreamIn& m_source;
			uint64_t header_size;
		};
	};

#endif
