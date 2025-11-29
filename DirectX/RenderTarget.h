#pragma once

//------  RenderTarget.h  ------

#include"Device.h"
#include"SwapChain.h"
#include"Descripter_Heap.h"
#include<vector>

class RenderTarget final
{
public:
	RenderTarget() = default;

	//デストラクタ
	~RenderTarget();

	//レンダーターゲット作成
	[[nodiscard]] bool create(const Device& device, const SwapChain& swapChain, const Descripter_Heap& heap) noexcept;

	//ディスクリプターハンドル取得
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle(const Device& device, const Descripter_Heap& heap, UINT index) const noexcept;

	//レンダーターゲット取得
	[[nodiscard]] ID3D12Resource* get(uint32_t index) const noexcept;

private:
	std::vector<ID3D12Resource*> RenderTargets_;
};