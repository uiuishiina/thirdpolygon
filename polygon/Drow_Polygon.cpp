
//------  Drow_Polygon.cpp  ------

#include"Drow_Polygon.h"
#include<cassert>
#include<DirectXMath.h>

using namespace PG;

//デストラクタ
Drow_Polygon :: ~Drow_Polygon() {
	if (VertexBuffer_) {
		VertexBuffer_->Release();
		VertexBuffer_ = nullptr;
	}
	if (IndexBuffer_) {
		IndexBuffer_->Release();
		IndexBuffer_ = nullptr;
	}
}

[[nodiscard]] bool Drow_Polygon :: create(const Device& device, const PG::PoNum num)noexcept
{
	//
	if (!createVertexBuffer(device,num)) {
		assert(false && "頂点バッファの作成に失敗");
		return false;
	}

	if (!createIndexBuffer(device,num)) {
		assert(false && "インデックスバッファの作成に失敗");
		return false;
	}

	return true;
}

//
[[nodiscard]] void Drow_Polygon :: Draw(const CommandList& List)noexcept
{
	//
	List.get()->IASetVertexBuffers(0, 1, &VertexBufferView_);
	//
	List.get()->IASetIndexBuffer(&IndexBufferView_);
	//
	List.get()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//
	List.get()->DrawIndexedInstanced(3, 1, 0, 0, 0);
	
}

//
[[nodiscard]] bool Drow_Polygon :: createVertexBuffer(const Device& device, const PG::PoNum num)noexcept
{
	const auto VertexBufferSize = sizeof(VerT);

	D3D12_HEAP_PROPERTIES Propety{};
	Propety.Type					= D3D12_HEAP_TYPE_UPLOAD;
	Propety.CPUPageProperty			= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	Propety.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
	Propety.CreationNodeMask		= 1;
	Propety.VisibleNodeMask			= 1;

	D3D12_RESOURCE_DESC desc{};
	desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment			= 0;
	desc.Width				= VertexBufferSize;
	desc.Height				= 1;
	desc.DepthOrArraySize	= 1;
	desc.MipLevels			= 1;
	desc.Format				= DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count	= 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

	auto hr = device.get()->CreateCommittedResource(
		&Propety, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&VertexBuffer_)
	);
	if (FAILED(hr)) {
		assert(false && "頂点バッファの作成に失敗");
		return false;
	}

	Vertex* v{};
	hr = VertexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&v));
	if (FAILED(hr)) {
		assert(false && "頂点バッファのマップに失敗");
		return false;
	}

	memcpy_s(v, VertexBufferSize, VerT, VertexBufferSize);

	VertexBuffer_->Unmap(0, nullptr);

	VertexBufferView_.BufferLocation	= VertexBuffer_->GetGPUVirtualAddress();
	VertexBufferView_.SizeInBytes		= VertexBufferSize;
	VertexBufferView_.StrideInBytes		= sizeof(Vertex);
	return true;
}

//
[[nodiscard]] bool Drow_Polygon :: createIndexBuffer(const Device& device, const PG::PoNum num)noexcept
{
	const auto IndexBufferSize = sizeof(Index_);

	D3D12_HEAP_PROPERTIES Propety{};
	Propety.Type					= D3D12_HEAP_TYPE_UPLOAD;
	Propety.CPUPageProperty			= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	Propety.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
	Propety.CreationNodeMask		= 1;
	Propety.VisibleNodeMask			= 1;

	D3D12_RESOURCE_DESC desc{};
	desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment			= 0;
	desc.Width				= IndexBufferSize;
	desc.Height				= 1;
	desc.DepthOrArraySize	= 1;
	desc.MipLevels			= 1;
	desc.Format				= DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc.Count	= 1;
	desc.SampleDesc.Quality	= 0;
	desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

	auto hr = device.get()->CreateCommittedResource(
		&Propety, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&IndexBuffer_)
	);
	if (FAILED(hr)) {
		assert(false && "インデックスバッファの作成に失敗");
		return false;
	}

	uint16_t* T{};
	hr = IndexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&T));
	if (FAILED(hr)) {
		assert(false && "インデックスバッファのマップに失敗");
		return false;
	}

	memcpy_s(T, IndexBufferSize, Index_, IndexBufferSize);

	IndexBuffer_->Unmap(0, nullptr);

	IndexBufferView_.BufferLocation = IndexBuffer_->GetGPUVirtualAddress();
	IndexBufferView_.SizeInBytes = IndexBufferSize;
	IndexBufferView_.Format = DXGI_FORMAT_R16_UINT;

	return true;
}