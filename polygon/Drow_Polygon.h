#pragma once

//------  Drow_Polygon.h  ------

#include"../DirectX/Device.h"
#include"../DirectX/CommandList.h"
#include<DirectXMath.h>
#include<vector>

//------  ポリゴンの構造体名前空間  ------
namespace PG {
	//------  ポリゴンの本体  ------
	struct  Vertex {
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;
	};
	//------  ポリゴンの種類分け用構造体  ------
	/*
	*/
	static Vertex VerT[] = {
		{ { 0, 0.5f, 0 }, { 1,	0,	0,	1 } },
	{ {		0.5f,	-0.5f,		0},	{	0,	1,	0,	1} },
	{ {		-0.5f,	-0.5f,		0},	{	0,	0,	1,	1} }
	};

	static uint16_t Index_[] = { 0,1,2 };


	enum PoNum {
		Triangle
	};
}


class Drow_Polygon final
{
public:
	Drow_Polygon() = default;

	//デストラクタ
	~Drow_Polygon();

	//ポリゴン生成
	[[nodiscard]] bool create(const Device& device,const PG::PoNum num)noexcept;

	//描画指示
	[[nodiscard]] void Draw(const CommandList& List)noexcept;

	[[nodiscard]] bool createTriangle(const Device& device)noexcept;

private:

	//頂点バッファ作成
	[[nodiscard]] bool createVertexBuffer(const Device& device, const PG::PoNum num)noexcept;

	//インデックスバッファ作成
	[[nodiscard]] bool createIndexBuffer(const Device& device, const PG::PoNum num)noexcept;

	//三角形作成
	

	ID3D12Resource* VertexBuffer_{};
	ID3D12Resource* IndexBuffer_{};

	D3D12_VERTEX_BUFFER_VIEW	VertexBufferView_{};
	D3D12_INDEX_BUFFER_VIEW		IndexBufferView_{};
};