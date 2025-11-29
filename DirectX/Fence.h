#pragma once

//------  Fence.h  ------

#include"Device.h"

class Fence final
{
public:
	Fence() = default;

	//デストラクタ
	~Fence();

	//フェンス作成
	[[nodiscard]] bool create(const Device& device)noexcept;

	//待機処理
	void wait(UINT64 fencevalue)const noexcept;

	//フェンス取得
	[[nodiscard]] ID3D12Fence* get()const noexcept;
private:
	ID3D12Fence* Fence_{};
	HANDLE waitGPUEvent_{};
};