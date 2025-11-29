
//------  SwapChain.cpp  ------

#include"SwapChain.h"
#include<cassert>

//デストラクタ
SwapChain :: ~SwapChain() {
	if (SwapChain_) {
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}
}

//スワップチェーン作成
[[nodiscard]] bool SwapChain :: create(const DXGI& DXGI, const CommandQueue& Queue, const window& window)noexcept 
{
	const auto [w,h] = window.getSize();

	SwapDesc_.BufferCount		= 2;
	SwapDesc_.Width				= w;
	SwapDesc_.Height			= h;
	SwapDesc_.Format			= DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapDesc_.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapDesc_.SwapEffect		= DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapDesc_.SampleDesc.Count	= 1;

	IDXGISwapChain1* VSwapChain{};
	auto hr = DXGI.getFactory()->CreateSwapChainForHwnd(Queue.get(), window.getHandle(), &SwapDesc_, nullptr, nullptr, &VSwapChain);
	if (FAILED(hr)) {
		assert(false && "スワップチェーンの作成に失敗");
		return false;
	}

	hr = VSwapChain->QueryInterface(IID_PPV_ARGS(&SwapChain_));
	if (FAILED(hr)) {
		assert(false && "スワップチェーンのアップグレードに失敗");
		return false;
	}
	VSwapChain->Release();
	return true;
}

//スワップチェーンの取得
[[nodiscard]] IDXGISwapChain3* SwapChain::get()const noexcept{
	if (!SwapChain_) {
		assert(false && "スワップチェーンが未作成");
		return nullptr;
	}
	return SwapChain_;
}

//スワップチェーンのディスク取得
[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& SwapChain ::  getDesc()const noexcept {
	if (!SwapChain_) {
		assert(false && "スワップチェーンが未作成");
	}
	return SwapDesc_;
}