
//------  Drow_Polygon.cpp  ------

#include"Drow_Polygon.h"
#include<cassert>
#include<DirectXMath.h>

namespace {
	//------  ポリゴンの構造体  ------
	struct  Vertex	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;
	};

	//------  使用するポリゴンの構造体  ------
	//三角形
	Vertex Triangle[] = {
		{	{	0.0f,	0.5f,	0.0f},	{	1.0f,	0.0f,	0.0f,	1.0f}	},
		{	{	0.5f,  -0.5f,	0.0f},	{	0.0f,	1.0f,	0.0f,	1.0f}	},
		{	{  -0.5f,  -0.5f,	0.0f},	{	0.0f,	0.0f,	1.0f,	1.0f}	}
	};
}


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

[[nodiscard]] bool Drow_Polygon :: create(const Device& device)noexcept
{
	//
	if (!createVertexBuffer(device)) {
		assert(false && "頂点バッファの作成に失敗");
		return false;
	}

	if (!createIndexBuffer(device)) {
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