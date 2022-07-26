#pragma once
#include "BaseFileStream.h"
class BWFStream : public BaseFileStream
{
public:
	BWFStream(const wchar_t * _filePath);
	~BWFStream();
public:
	template<class T>
	void Write(T& buf)
	{
		BaseFileStream::Write(&buf, sizeof(T));
	}
};

