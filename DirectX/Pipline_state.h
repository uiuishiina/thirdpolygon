#pragma once

//------  Pipline_state.h  ------

#include"Device.h"
#include"CompileShader.h"
#include"Root_signature.h"

class Pipline final
{
public:
	Pipline() = default;

	//デストラクタ
	~Pipline();

	//パイプラインステート作成
	[[nodiscard]] bool create(const Device& device, const CompileShader& Shader, const RootSignature& Root)noexcept;

	//パイプラインステート取得
	[[nodiscard]] ID3D12PipelineState* get()const noexcept;
private:
	ID3D12PipelineState* PiplineState_{};
};