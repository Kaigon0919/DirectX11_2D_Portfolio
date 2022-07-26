#include "BRStream.h"

BRStream::BRStream(const wchar_t * _filePath) : BaseFileStream(_filePath,L"rb")
{
}

BRStream::~BRStream()
{
}

void BRStream::Read(void * _buffer, int _bufferByteSize, int _readByteSize)
{
	BaseFileStream::Read(_buffer, _bufferByteSize, _readByteSize);
}

void BRStream::Seek(long _offset, int _flag)
{
	BaseFileStream::Seek(_offset, _flag);
}
void BRStream::ReOpen(const wchar_t* _filePath)
{
	BaseFileStream::ReOpen(_filePath, L"rb");
}
