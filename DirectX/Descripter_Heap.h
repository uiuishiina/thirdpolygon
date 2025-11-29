#pragma once

//------  Descripter_Heap.h  ------

#include"Device.h"

class Descripter_Heap final
{
public:
	Descripter_Heap() = default;

	//デストラクタ
	~Descripter_Heap();

	//ディスクリプターヒープ作成
	[[nodiscard]] bool create(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false)noexcept;

	//ディスクリプターヒープ取得
	[[nodiscard]] ID3D12DescriptorHeap* get() const noexcept;

	//ディスクリプターヒープタイプを取得
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE getType()const noexcept;

private:
	ID3D12DescriptorHeap* heap_{};
	D3D12_DESCRIPTOR_HEAP_TYPE type_{};
};