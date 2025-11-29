
//------  DXGI.h  ------

#include"DXGI.h"
#include<cassert>
#pragma comment(lib, "dxgi.lib")

//
DXGI :: ~DXGI(){
	if (dxgiFactory_) {
		dxgiFactory_->Release();
		dxgiFactory_ = nullptr;
	}
	if (dxgiAdapter_) {
		dxgiAdapter_->Release();
		dxgiAdapter_ = nullptr;
	}
}

//
[[nodiscard]] bool DXGI :: setDisplayAdapter()noexcept
{
#if _DEBUG
	// デバッグレイヤーをオン
	ID3D12Debug* debug;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
		debug->EnableDebugLayer();
		ID3D12Debug1* debugController1;
		if (SUCCEEDED(debug->QueryInterface(IID_PPV_ARGS(&debugController1))))
		{
			debugController1->SetEnableGPUBasedValidation(TRUE);
		}
	}
#endif
	UINT CreateFactoryFlags = 0;
#if _DEBUG
	// デバッグビルドではデバッグフラグを設定
	CreateFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	auto hr = CreateDXGIFactory2(CreateFactoryFlags, IID_PPV_ARGS(&dxgiFactory_));
	if (FAILED(hr)) {
		assert(false && "DXGIファクトリーの作成に失敗");
		return false;
	}

	auto Num = 0;
	IDXGIAdapter1* Adapter_{};

	while (dxgiFactory_->EnumAdapters1(Num, &Adapter_) != DXGI_ERROR_NOT_FOUND) {
		DXGI_ADAPTER_DESC1 desc{};
		Adapter_->GetDesc1(&desc);
		Num++;

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			Adapter_->Release();
			continue;
		}

		if (FAILED(D3D12CreateDevice(Adapter_, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
			Adapter_->Release();
			continue;
		}

		dxgiAdapter_ = Adapter_;
		break;
	}

	if (!dxgiAdapter_) {
		assert(false && "アダプターの取得に失敗");
		return false;
	}

	return true;
}

//
[[nodiscard]] IDXGIFactory4* DXGI :: getFactory()const noexcept {
	if (!dxgiFactory_) {
		assert(false && "DXGIファクトリーが未作成");
		return nullptr;
	}
	return dxgiFactory_;
}

//
[[nodiscard]] IDXGIAdapter1* DXGI :: getAdapter()const noexcept {
	if (!dxgiAdapter_) {
		assert(false && "アダプターが未設定");
		return nullptr;
	}
	return dxgiAdapter_;
}