#pragma once

//-----  CommandQueue.h  ------

#include"DXGI.h"
#include<d3d12.h>

class Device final
{
public:
	Device() = default;

	//デストラクタ
	~Device();

	//デバイス作成
	[[nodiscard]] bool create(const DXGI& DXGI)noexcept;

	//デバイスを取得
	[[nodiscard]] ID3D12Device* get()const noexcept;

private:
	ID3D12Device* device_{};
};