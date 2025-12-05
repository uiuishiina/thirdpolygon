
//------  CompileShader.cpp  ------

#include"CompileShader.h"
#include<cassert>
#include<string>

#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

//
CompileShader :: ~CompileShader() {
	if (VertexShader_) {
		VertexShader_->Release();
		VertexShader_ = nullptr;
	}
	if (PixelShader_) {
		PixelShader_->Release();
		PixelShader_ = nullptr;
	}
}

//シェーダー作成
[[nodiscard]] bool CompileShader :: create(const Device& device)noexcept
{
	//
	const std::string FilePath = "Shader/VertexShader.hlsl";
	const std::wstring temp = std::wstring(FilePath.begin(), FilePath.end());

	ID3DBlob* error{};
	auto hr = D3DCompileFromFile(temp.data(), nullptr, nullptr, 
		"vs",//------  頂点シェーダーを返す関数の名前
		"vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VertexShader_, &error);
	if (FAILED(hr)) {
		char* p = static_cast<char*>(error->GetBufferPointer());
		assert(false && "頂点シェーダのコンパイルに失敗");
	}
	hr = D3DCompileFromFile(temp.data(), nullptr, nullptr,
		"ps", //------  ピクセルシェーダーを返す関数の名前
		"ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PixelShader_, &error);
	if (FAILED(hr)) {
		char* p = static_cast<char*>(error->GetBufferPointer());
		assert(false && "ピクセルシェーダのコンパイルに失敗");
	}
	if (error) {
		error->Release();
	}
	return true;
}

//頂点シェーダー取得
[[nodiscard]] ID3DBlob* CompileShader :: getVertexShader()const noexcept {
	if (!VertexShader_) {
		assert(false && "頂点シェーダーが未作成");
	}
	return VertexShader_;
}

//ピクセルシェーダー取得
[[nodiscard]] ID3DBlob* CompileShader :: getPixelShader()const noexcept	{
	if (!PixelShader_) {
		assert(false && "ピクセルシェーダーが未作成");
	}
	return PixelShader_;
}