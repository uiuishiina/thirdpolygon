#pragma once

//------  DXGI.h  ------

#include<d3d12.h>
#include<dxgi1_4.h>

class DXGI final
{
public:
	DXGI() = default;

	//デストラクタ
	~DXGI();

	//DXGI作成
	[[nodiscard]] bool setDisplayAdapter()noexcept;

	//DXGIファクトリー取得
	[[nodiscard]] IDXGIFactory4* getFactory()const noexcept;

	//アダプター取得
	[[nodiscard]] IDXGIAdapter1* getAdapter()const noexcept;

private:
	IDXGIFactory4* dxgiFactory_{};  /// DXGIファクトリー
	IDXGIAdapter1* dxgiAdapter_{};  /// アダプター(GPU)
};