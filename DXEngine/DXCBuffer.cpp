#include "DXCBuffer.h"

void DXCBuffer::VSSet()
{
	DxDevice::GetContext()->VSSetConstantBuffers(m_RegSlot, 1, &m_CBuffer);
}

void DXCBuffer::PSSet()
{
	DxDevice::GetContext()->PSSetConstantBuffers(m_RegSlot, 1, &m_CBuffer);
}
