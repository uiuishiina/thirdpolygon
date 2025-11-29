#pragma once

//-----  CommandQueue.h  ------

#include"Device.h"

class CommandQueue final
{
public:
	CommandQueue() = default;

	//デストラクタ
	~CommandQueue();

	//スワップチェーン作成
	[[nodiscard]] bool create(const Device& device)noexcept;

	//スワップチェーン取得
	[[nodiscard]] ID3D12CommandQueue* get()const noexcept;

private:
	ID3D12CommandQueue* CommandQueue_{};
};