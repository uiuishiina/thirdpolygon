#pragma once

//------  CompileShader.h  ------

#include"Device.h"

class CompileShader final
{
public:
	CompileShader() = default;

	//デストラクタ
	~CompileShader();

	//シェーダー作成
	[[nodiscard]] bool create(const Device& device)noexcept;

	//頂点シェーダー取得
	[[nodiscard]] ID3DBlob* getVertexShader()const noexcept;

	//ピクセルシェーダー取得
	[[nodiscard]] ID3DBlob* getPixelShader()const noexcept;

private:
	ID3DBlob* VertexShader_{};
	ID3DBlob* PixelShader_{};
};