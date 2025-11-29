
//------  Fence.cpp  ------

#include"Fence.h"
#include<cassert>

//デストラクタ
Fence :: ~Fence() {
	if (Fence_) {
		Fence_->Release();
		Fence_ = nullptr;
	}
}

//フェンス作成
[[nodiscard]] bool Fence :: create(const Device& device)noexcept
{
	const auto hr = device.get()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence_));
	if (FAILED(hr)) {
		assert(false && "フェンスの作成に失敗");
		return false;
	}

	waitGPUEvent_ = CreateEvent(nullptr, false, false, "Wait_GPU");
	if (!waitGPUEvent_) {
		assert(false && "同期用イベントの作成に失敗");
		return false;
	}
	return true;
}

//待機関数
void Fence :: wait(UINT64 fencevalue)const noexcept
{
	if (!Fence_) {
		assert(false && "フェンスが未作成");
		return;
	}
	if (Fence_->GetCompletedValue() < fencevalue) {
		Fence_->SetEventOnCompletion(fencevalue, waitGPUEvent_);
		WaitForSingleObject(waitGPUEvent_, INFINITE);
	}
}

//フェンス取得
[[nodiscard]] ID3D12Fence* Fence :: get()const noexcept {
	if (!Fence_) {
		assert(false && "フェンスが未作成");
		return nullptr;
	}
	return Fence_;
}