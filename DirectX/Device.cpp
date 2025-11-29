
//------  Device.cpp  ------

#include"Device.h"
#include<cassert>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

//デストラクタ
Device :: ~Device() {
	if (device_) {
		device_->Release();
		device_ = nullptr;
	}
}

//デバイス作成
[[nodiscard]] bool Device :: create(const DXGI& DXGI)noexcept
{
	const auto hr = D3D12CreateDevice(DXGI.getAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
	if (FAILED(hr)){
		assert(false && "デバイスの作成に失敗");
		return false;
	}
	return true;
}

//デバイスのポインターを返す
[[nodiscard]] ID3D12Device* Device :: get()const noexcept
{
	if (!device_) {
		assert(false && "デバイスが未作成");
	}
	return device_;
}