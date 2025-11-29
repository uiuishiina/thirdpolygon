#pragma once

//------  SwapChain.h  ------

#include"DXGI.h"
#include"CommandQueue.h"
#include"../window/window.h"

class SwapChain final
{
public:
	SwapChain() = default;

	//デストラクタ
	~SwapChain();

	//スワップチェーン作成
	[[nodiscard]] bool create(const DXGI& DXGI, const CommandQueue& Queue, const window& window)noexcept;

	//スワップチェーン取得
	[[nodiscard]] IDXGISwapChain3* get()const noexcept;

	//スワップチェーンのディスク取得
	[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc()const noexcept;
private:
	IDXGISwapChain3* SwapChain_{};
	DXGI_SWAP_CHAIN_DESC1 SwapDesc_{};
};
