
//------  App.cpp  ------


//------  #include  ------
#include<cassert>
//------  window  ------
#include"../window/window.h"
//------  DirectX  ------
#include"../DirectX/DXGI.h"
#include"../DirectX/Device.h"
#include"../DirectX/CommandQueue.h"
#include"../DirectX/SwapChain.h"
#include"../DirectX/Descripter_Heap.h"
#include"../DirectX/RenderTarget.h"
#include"../DirectX/CommandAllocator.h"
#include"../DirectX/CommandList.h"
#include"../DirectX/Fence.h"
#include"../DirectX/Root_signature.h"
#include"../DirectX/CompileShader.h"
#include"../DirectX/Pipline_state.h"
//------  Polygon  ------
#include"../Polygon/Drow_Polygon.h"
//------ End.#include ------


namespace {
	constexpr std::string_view App_Name = "Draw_Polygon_App";
};

class App final
{
public:
	App() = default;
	~App() = default;

	//アプリケーション起動
	[[nodiscard]] bool Initialize(HINSTANCE instance)noexcept
	{
		//window作成
		if (!window_.crate(instance, 1280, 720, App_Name)) {
			assert(false && "ウィンドウの作成に失敗(App)");
			return false;
		}

		//
		if (!DXGI_.setDisplayAdapter()) {
			assert(false && "DXGIアダプターの設定に失敗(App)");
			return false;
		}

		//
		if (!Device_.create(DXGI_)) {
			assert(false && "デバイスの作成に失敗(App)");
			return false;
		}
		
		//
		if (!Queue_.create(Device_)) {
			assert(false && "コマンドキューの作成に失敗(App)");
			return false;
		}

		//
		if (!SwapChain_.create(DXGI_, Queue_, window_)) {
			assert(false && "スワップチェーンの作成に失敗(App)");
			return false;
		}

		//
		if (!Descripter_.create(Device_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, SwapChain_.getDesc().BufferCount)) {
			assert(false && "ディスクリプターヒープの作成に失敗(App)");
			return false;
		}

		//
		if (!RenderTarget_.create(Device_,SwapChain_,Descripter_)) {
			assert(false && "レンダーターゲットの作成に失敗(App)");
			return false;
		}

		//
		if (!Allocator_[0].create(Device_, D3D12_COMMAND_LIST_TYPE_DIRECT)) {
			assert(false && "コマンドアロケーターの作成に失敗(App)");
			return false;
		}
		if (!Allocator_[1].create(Device_, D3D12_COMMAND_LIST_TYPE_DIRECT)) {
			assert(false && "コマンドアロケーターの作成に失敗(App)");
			return false;
		}

		//
		if (!CommandList_.create(Device_, Allocator_[0])) {
			assert(false && "コマンドリストの作成に失敗(App)");
			return false;
		}

		//
		if (!Fence_.create(Device_)) {
			assert(false && "フェンスの作成に失敗(App)");
			return false;
		}

		//
		if (!Root_.create(Device_)) {
			assert(false && "ルートシグネチャーの作成に失敗(App)");
			return false;
		}

		//
		if (!Shader_.create(Device_)) {
			assert(false && "シェーダーの作成に失敗(App)");
			return false;
		}

		//
		if (!Pipline_.create(Device_, Shader_, Root_)) {
			assert(false&&"パイプラインステートの作成に失敗(App)");
			return false;
		}

		//
		if (!DrowPolygon_.createTriangle(Device_)) {
			assert(false && "三角形のポリゴンの作成に失敗(App)");
			return false;
		}

		//すべて成功ならtrue
		return true;
	}

	//ループ処理
	void Loop()noexcept {
		while (window_.messegeLoop()) {
			//現在のバックバッファインデックスを取得
			const auto BufferIndex = SwapChain_.get()->GetCurrentBackBufferIndex();

			if (FrameFenceValue_[BufferIndex] != 0) {
				Fence_.wait(FrameFenceValue_[BufferIndex]);
			}

			Allocator_[BufferIndex].Reset();
			CommandList_.reset(Allocator_[BufferIndex]);

			auto PtoRT = resourceBarrier(RenderTarget_.get(BufferIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
			CommandList_.get()->ResourceBarrier(1, &PtoRT);

			D3D12_CPU_DESCRIPTOR_HANDLE handle[] = { RenderTarget_.getDescriptorHandle(Device_,Descripter_,BufferIndex) };
			CommandList_.get()->OMSetRenderTargets(1, handle, false, nullptr);

			const float ClearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			CommandList_.get()->ClearRenderTargetView(handle[0], ClearColor, 0, nullptr);

			//
			// パイプラインステートの設定
				CommandList_.get()->SetPipelineState(Pipline_.get());
			// ルートシグネチャの設定
				CommandList_.get()->SetGraphicsRootSignature(Root_.get());

			// ビューポートの設定
			const auto [w, h] = window_.getSize();
			D3D12_VIEWPORT viewport{};
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;
			viewport.Width = static_cast<float>(w);
			viewport.Height = static_cast<float>(h);
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			CommandList_.get()->RSSetViewports(1, &viewport);

			// シザー矩形の設定
			D3D12_RECT scissorRect{};
			scissorRect.left = 0;
			scissorRect.top = 0;
			scissorRect.right = w;
			scissorRect.bottom = h;
			CommandList_.get()->RSSetScissorRects(1, &scissorRect);

			// ポリゴンの描画
			DrowPolygon_.Draw(CommandList_);


			//

			auto RTtoP = resourceBarrier(RenderTarget_.get(BufferIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
			CommandList_.get()->ResourceBarrier(1, &RTtoP);

			CommandList_.get()->Close();

			ID3D12CommandList* ppList[] = { CommandList_.get() };
			Queue_.get()->ExecuteCommandLists(_countof(ppList), ppList);

			SwapChain_.get()->Present(1, 0);

			Queue_.get()->Signal(Fence_.get(), nextFenceValue_);
			FrameFenceValue_[BufferIndex] = nextFenceValue_;
			nextFenceValue_++;
		}
	}

	D3D12_RESOURCE_BARRIER resourceBarrier(ID3D12Resource * resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = from;
		barrier.Transition.StateAfter = to;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		return barrier;
	}
private:
	window				window_{};		//ウィンドウクラスインスタンス
	DXGI				DXGI_{};		//DXGIインスタンス
	Device				Device_{};		//Deviceインスタンス
	CommandQueue		Queue_{};		//CommandQueueインスタンス
	SwapChain			SwapChain_{};	//SwapChianインスタンス
	Descripter_Heap		Descripter_{};	//Descripter_Heapインスタンス
	RenderTarget		RenderTarget_{};//RenderTargetインスタンス
	CommandAllocator	Allocator_[2]{};//CommandAllocatorインスタンス
	CommandList			CommandList_{};	//CommandListインスタンス

	Fence	Fence_{};				//Fenceインスタンス
	UINT64	FrameFenceValue_[2]{};	//現在フレームの値
	UINT	nextFenceValue_ = 1;		//次のフレームの値

	RootSignature	Root_{};		//ルートシグネチャーインスタンス
	CompileShader	Shader_{};		//コンパイルシェーダーインスタンス
	Pipline			Pipline_{};		//パイプラインステートインスタンス
	Drow_Polygon	DrowPolygon_{};	//ポリゴン描画インスタンス
};

//開始関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	App app;

	//アプリケーションの起動
	if (!app.Initialize(hInstance)) {
		assert(false && "アプリケーションの起動に失敗");
	}

	app.Loop();

	return 0;
}