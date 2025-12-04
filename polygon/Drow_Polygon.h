#pragma once

//------  Drow_Polygon.h  ------

#include"../DirectX/Device.h"
#include"../DirectX/CommandList.h"


class Drow_Polygon final
{
public:
	Drow_Polygon() = default;

	//デストラクタ
	~Drow_Polygon();

	//ポリゴン生成
	[[nodiscard]] bool create(const Device& device)noexcept;

	//描画指示
	[[nodiscard]] void Draw(const CommandList& List)noexcept;

private:

	//頂点バッファ作成
	[[nodiscard]] bool createVertexBuffer(const Device& device)noexcept;

	//インデックスバッファ作成
	[[nodiscard]] bool createIndexBuffer(const Device& device)noexcept;

	ID3D12Resource* VertexBuffer_{};
	ID3D12Resource* IndexBuffer_{};

	D3D12_VERTEX_BUFFER_VIEW	VertexBufferView_{};
	D3D12_INDEX_BUFFER_VIEW		IndexBufferView_{};
};