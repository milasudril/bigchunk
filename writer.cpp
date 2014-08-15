#ifdef __WAND__
target[name[writer.o] type[object]]
#endif

#include "writer.h"
#include <herbs/streamout/streamout.h>
#include <algorithm>

Bigchunk::Writer::Writer(Herbs::StreamOut& dest):
	m_dest(dest)
	{
	m_dest.write("BIGCHUNK",8);
	}

bool Bigchunk::Writer::chunkIDWrite(const char* header_name)
	{
	char buffer_out[8]={0,0,0,0, 0,0,0,0};
	auto ptr_out=buffer_out;
	while(*header_name && (ptr_out-buffer_out)!=8)
		{
		*ptr_out=*header_name;
		++ptr_out;
		++header_name;
		}
	return m_dest.write(buffer_out,8)==8;
	}

bool Bigchunk::Writer::chunkSizeWrite(uint64_t size)
	{
	header_size=size;
	uint64_t size_out=header_size;
	return m_dest.write(&size_out,sizeof(size_out))==sizeof(size_out);
	}

size_t Bigchunk::Writer::dataWrite(const void* buffer,size_t buffer_size)
	{
	auto n_bytes_write=std::min(header_size,uint64_t(buffer_size));
	auto res=m_dest.write(buffer,n_bytes_write);
	header_size-=res;
	return res;
	}
