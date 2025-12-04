#pragma once

//------  Root_signature.h  ------

#include"Device.h"

class RootSignature final
{
public:
	RootSignature() = default;

	//デストラクタ
	~RootSignature();

	//ルートシグネチャー作成
	[[nodiscard]] bool create(const Device& device)noexcept;

	//ルートシグネチャー取得
	[[nodiscard]] ID3D12RootSignature* get()const noexcept;

private:
	ID3D12RootSignature* RootSignature_{};
};