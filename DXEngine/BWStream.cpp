#include "BWStream.h"

BWFStream::BWFStream(const wchar_t * _filePath) : BaseFileStream(_filePath,L"wb")
{
}

BWFStream::~BWFStream()
{
}
