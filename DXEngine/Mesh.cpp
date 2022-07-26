#include "Mesh.h"
#include"DxDevice.h"
#include"UtillMacor.h"
Mesh::Mesh(): m_VertexBuffer(nullptr), m_IndexBuffer(nullptr)
{
}


Mesh::~Mesh()
{
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_IndexBuffer);
}


bool Mesh::Create(void* vertexMem, const UINT vertexCount, const UINT vertexSize, const D3D11_USAGE vertexUsage, void* indexMem, const UINT indexCount, const UINT indexSize, const D3D11_USAGE indexUsage, DXGI_FORMAT indexFomet, D3D11_PRIMITIVE_TOPOLOGY drawMode)
{
	m_IndexFomet = indexFomet;
	m_DrawMode = drawMode;

	if (!CreateVertexBuffer(vertexMem, vertexCount, vertexSize, vertexUsage))
	{
		return false;
	}
	if (!CreateIndexBuffer(indexMem, indexCount, indexSize, indexUsage))
	{
		return false;
	}

	return true;
}

void Mesh::Update()
{
	unsigned int Offset = 0;

	DxDevice::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &m_VertexSize, &Offset);
	DxDevice::GetContext()->IASetIndexBuffer(m_IndexBuffer,m_IndexFomet, 0);
	DxDevice::GetContext()->IASetPrimitiveTopology(m_DrawMode);
}

void Mesh::Render()
{
	DxDevice::GetContext()->DrawIndexed(m_IndexCount, 0, 0);
}

bool Mesh::CreateVertexBuffer(void* vertexMem, const UINT vertexCount, const UINT vertexSize, const D3D11_USAGE _vertexUsage)
{
	m_VertexSize = vertexSize;
	m_VertexCount = vertexCount;

	D3D11_BUFFER_DESC vertexDes = {};
	vertexDes.ByteWidth = m_VertexCount * m_VertexSize;
	vertexDes.Usage = _vertexUsage;
	if (D3D11_USAGE_DYNAMIC == vertexDes.Usage)
	{
		vertexDes.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	vertexDes.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexSub = {};
	vertexSub.pSysMem = vertexMem;
	if (S_OK != DxDevice::GetDevice()->CreateBuffer(&vertexDes, &vertexSub, &m_VertexBuffer))
	{
		assert(false);
		return false;
	}
	return true;
}

bool Mesh::CreateIndexBuffer(void* indexMem, const UINT indexCount, const UINT indexSize, const D3D11_USAGE _indexUsage)
{

	m_IndexCount = indexCount;
	m_IndexSize = indexSize;

	D3D11_BUFFER_DESC indexDes = {};
	indexDes.ByteWidth = m_IndexCount * m_IndexSize;
	indexDes.Usage = _indexUsage;
	if (D3D11_USAGE_DYNAMIC == indexDes.Usage)
	{
		indexDes.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	indexDes.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexSub = {};
	indexSub.pSysMem = indexMem;

	if (S_OK != DxDevice::GetDevice()->CreateBuffer(&indexDes, &indexSub, &m_IndexBuffer))
	{
		assert(false);
		return false;
	}
	return true;
}