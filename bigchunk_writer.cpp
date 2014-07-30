#ifdef __WAND__
target[name[bigchunk_writer.o] type[object]]
#endif

#include "bigchunk_writer.h"
#include <herbs/streamout/streamout.h>
#include <algorithm>

ChunkIO::BigchunkWriter::BigchunkWriter(Herbs::StreamOut& dest):
	m_dest(dest)
	{
	m_dest.write("BIGCHUNK",8);
	}

bool ChunkIO::BigchunkWriter::chunkIDWrite(const char* header_name)
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

bool ChunkIO::BigchunkWriter::chunkSizeWrite(uintmax_t size)
	{
	header_size=size;
	uint64_t size_out=header_size;
	return m_dest.write(&size_out,sizeof(size_out))==sizeof(size_out);
	}

size_t ChunkIO::BigchunkWriter::dataWrite(const void* buffer,size_t buffer_size)
	{
	auto n_bytes_write=std::min(header_size,buffer_size);
	auto res=m_dest.write(buffer,n_bytes_write);
	header_size-=res;
	return res;
	}
