#pragma once
#include<iostream>
class BaseFileStream
{
public:
	BaseFileStream(const wchar_t * _fileName, const wchar_t* _flag);
	~BaseFileStream();
private:
	FILE* m_File;
public:
	void Seek(long offset, int _flag = SEEK_CUR);
	void Write(void * _buffer, int _byteLength);
	void Read(void* _buffer, int _bufferSize, int _readSize);
	inline bool IsOpen()const
	{
		return m_File != nullptr;
	}
	void ReOpen(const wchar_t * _fileName, const wchar_t* _flag);
};

