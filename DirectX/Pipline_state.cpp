
//------  Pipline_state.cpp  ------

#include"Pipline_state.h"
#include<cassert>

//
Pipline :: ~Pipline() {
	if (!PiplineState_) {
		PiplineState_->Release();
		PiplineState_ = nullptr;
	}
}

//パイプラインステート作成
[[nodiscard]] bool Pipline :: create(const Device& device, const CompileShader& Shader, const RootSignature& Root)noexcept
{
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
		//頂点バッファのフォーマットに合わせる
		//R32G32B32はfloat3のことでありfloatは４バイトなので３２ビットのメモリサイズを表す
		{"POSITION", 0,    DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{   "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//ラスタライザステート
	//ポリゴンの塗りつぶし方やカリングなどの設定
	D3D12_RASTERIZER_DESC Desc{};
	Desc.FillMode				= D3D12_FILL_MODE_SOLID;
	Desc.CullMode				= D3D12_CULL_MODE_BACK;
	Desc.FrontCounterClockwise	= false;
	Desc.DepthBias				= D3D12_DEFAULT_DEPTH_BIAS;
	Desc.DepthBiasClamp			= D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	Desc.SlopeScaledDepthBias	= D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	Desc.DepthClipEnable		= true;
	Desc.MultisampleEnable		= false;
	Desc.AntialiasedLineEnable	= false;
	Desc.ForcedSampleCount		= 0;
	Desc.ConservativeRaster		= D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	//ブレンドステート
	//描画効果の合成を設定
	//ここでいろいろできそうそれぞれなんかありそう
	const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc = {
		FALSE,
		FALSE,
		D3D12_BLEND_ONE,
		D3D12_BLEND_ZERO,
		D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE,
		D3D12_BLEND_ZERO,
		D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL,
	};

	D3D12_BLEND_DESC BlendDesc{};
	BlendDesc.AlphaToCoverageEnable = false;//なんかアルファ値でできそう
	BlendDesc.IndependentBlendEnable = false;

	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		BlendDesc.RenderTarget[i] = defaultRenderTargetBlendDesc;
	}

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc{};
	psoDesc.InputLayout						= { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.pRootSignature					= Root.get();
	psoDesc.VS								= { Shader.getVertexShader()->GetBufferPointer(), Shader.getVertexShader()->GetBufferSize() };//頂点
	psoDesc.PS								= { Shader.getPixelShader()->GetBufferPointer(), Shader.getPixelShader()->GetBufferSize() };//ピクセル
	psoDesc.RasterizerState					= Desc;
	psoDesc.BlendState						= BlendDesc;
	psoDesc.DepthStencilState.DepthEnable	= false;
	psoDesc.DepthStencilState.StencilEnable = false;
	psoDesc.SampleMask						= UINT_MAX;
	psoDesc.PrimitiveTopologyType			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets				= 1;
	psoDesc.RTVFormats[0]					= DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count				= 1;

	const auto hr = device.get()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&PiplineState_));
	if (FAILED(hr)) {
		assert(false && "パイプラインステートの作成に失敗");
		return false;
	}
	return true;
}

//パイプラインステート取得
[[nodiscard]] ID3D12PipelineState* Pipline :: get()const noexcept {
	if (!PiplineState_) {
		assert(false && "パイプラインステート未作成");
		return nullptr;
	}
	return PiplineState_;
}