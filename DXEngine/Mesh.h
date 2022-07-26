#pragma once
#include <d3d11.h>

#include "Resource.h"



class Mesh : public Resource
{
public:
	Mesh();
	~Mesh();

public:

		DEFCREATOR(Mesh, std::wstring)
		DEFCREATORFUNC(void* vertexMem, const UINT vertexCount, const UINT vertexSize, const D3D11_USAGE vertexUsage, void* indexMem, UINT indexCount, UINT indexSize, const D3D11_USAGE indexUsage, DXGI_FORMAT indexFomet, D3D11_PRIMITIVE_TOPOLOGY drawMode = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		DEFCREATORFUNCPARA(vertexMem, vertexCount, vertexSize, vertexUsage, indexMem, indexCount, indexSize, indexUsage, indexFomet, drawMode)
		DEFCREATOREND
	

	private:
		// 정점버퍼(Vertex Buffer).
		ID3D11Buffer * m_VertexBuffer;
		UINT m_VertexSize;
		UINT m_VertexCount;

		// 색인버퍼(Index Buffer).
		ID3D11Buffer * m_IndexBuffer;
		UINT m_IndexSize;
		UINT m_IndexCount;
		DXGI_FORMAT m_IndexFomet;

		D3D11_PRIMITIVE_TOPOLOGY m_DrawMode;
	public:
		bool Create(void* vertexMem, const UINT vertexCount, const UINT vertexSize, const D3D11_USAGE vertexUsage, void* indexMem, UINT indexCount, UINT indexSize, const D3D11_USAGE indexUsage, DXGI_FORMAT indexFomet, D3D11_PRIMITIVE_TOPOLOGY drawMode = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	public:
		void Update();
		void Render();

	private:
		bool CreateVertexBuffer(void* vertexMem, const UINT vertexCount, const UINT vertexSize, const D3D11_USAGE vertexUsage);
		bool CreateIndexBuffer(void* indexMem, const UINT indexCount, const UINT indexSize, const D3D11_USAGE _indexUsage);
	};

