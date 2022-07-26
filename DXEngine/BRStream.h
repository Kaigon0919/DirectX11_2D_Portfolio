#pragma once
#include "BaseFileStream.h"
class BRStream : protected BaseFileStream
{
public:
	BRStream(const wchar_t* _filePath );
	~BRStream();

public:	
	void Read(void* _buffer, int _bufferByteSize, int _readByteSize);
	void Seek(long _offset, int _Mode = SEEK_CUR);
	inline bool IsOpen()const
	{
		return BaseFileStream::IsOpen();
	}
	void ReOpen(const wchar_t* _filePath);
public:
	template<class T>
	void Read(T& buf)
	{
		BaseFileStream::Read(&buf, sizeof(T), sizeof(T));
	}
};

