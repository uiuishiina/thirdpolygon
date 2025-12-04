
//------  Root_signature.cpp  ------

#include"Root_signature.h"
#include<cassert>

//デストラクタ
RootSignature :: ~RootSignature() {
	if (RootSignature_) {
		RootSignature_->Release();
		RootSignature_ = nullptr;
	}
}

////ルートシグネチャー作成
[[nodiscard]] bool RootSignature :: create(const Device& device)noexcept
{

	D3D12_ROOT_SIGNATURE_DESC Desc{};
	Desc.NumParameters		= 0;
	Desc.pParameters		= nullptr;
	Desc.NumStaticSamplers	= 0;
	Desc.pStaticSamplers	= nullptr;
	Desc.Flags				= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob* signature{};
	auto hr = D3D12SerializeRootSignature(
		&Desc,D3D_ROOT_SIGNATURE_VERSION_1,&signature,nullptr);
	if (FAILED(hr)) {
		assert(false && "ルートシグネチャーのシリアライズに失敗");
		return false;
	}

	hr = device.get()->CreateRootSignature(
		0, signature->GetBufferPointer(),
		signature->GetBufferSize(),
		IID_PPV_ARGS(&RootSignature_)
	);
	if (FAILED(hr)) {
		assert(false && "ルートシグネチャーの作成に失敗");
		return false;
	}
	if (signature) {
		signature->Release();
	}

	return true;
}

////ルートシグネチャー取得
[[nodiscard]] ID3D12RootSignature* RootSignature :: get()const noexcept	{
	if (!RootSignature_) {
		assert(false && "ルートシグネチャーが未作成");
		return nullptr;
	}
	return RootSignature_;
}