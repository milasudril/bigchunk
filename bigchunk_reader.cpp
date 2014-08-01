#ifdef __WAND__
target[name[bigchunk_reader.o] type[object]]
#endif

#include "bigchunk_reader.h"
#include <herbs/streamin/streamin.h>
#include <herbs/exceptionmissing/exceptionmissing.h>
#include <cstring>

ChunkIO::BigchunkReader::BigchunkReader(Herbs::StreamIn& source):
	m_source(source)
	{
	m_source.modeBufferedOn();
	auto n_eaten=m_source.offsetGet();
	char buffer_magic[8];
	unsigned int k=0;
	while(!m_source.eof() && k!=8)
		{
		buffer_magic[k]=m_source.byteGet();
		++k;
		}

	if(strncmp(buffer_magic,"BIGCHUNK",8) )
		{
		m_source.offsetRestore(n_eaten);
		m_source.modeBufferedOff();
		throw Herbs::ExceptionMissing(___FILE__,__LINE__);
		}
	m_source.modeBufferedOff();
	}

bool ChunkIO::BigchunkReader::headerRead(Herbs::Stringbase<char>& name)
	{
	name.clear();
	m_source.modeBufferedOn();
	unsigned int k=0;
	while(!m_source.eof() && k!=8)
		{
		auto b=m_source.byteGet();
		if(b!=0)
			{name.append(b);}
		++k;
		}
	if(k!=8)
		{
		m_source.modeBufferedOff();
		return 0;
		}

	uint64_t size;
	if(m_source.read(&size,sizeof(size))!=sizeof(size))
		{
		m_source.modeBufferedOff();
		return 0;
		}
	header_size=size;
	m_source.modeBufferedOff();
	return 1;
	}

bool ChunkIO::BigchunkReader::skip()
	{
	char buffer[4096];
	while(header_size!=0)
		{
		auto n_read=std::min(header_size,uint64_t(4096));
		auto ret=m_source.read(buffer,n_read);
		if(ret!=n_read)
			{return 0;}
		header_size-=ret;
		}
	return 1;
	}

size_t ChunkIO::BigchunkReader::dataRead(void* buffer,size_t buffer_size)
	{
	auto n_read=m_source.read(buffer,std::min(uint64_t(buffer_size),header_size));
	header_size-=n_read;
	return n_read;
	}
