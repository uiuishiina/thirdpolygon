
//------  CommandQueuecpp  ------

#include"CommandQueue.h"
#include<cassert>

//
CommandQueue :: ~CommandQueue() {
	if (CommandQueue_) {
		CommandQueue_->Release();
		CommandQueue_ = nullptr;
	}
}

//コマンドキュー作成
[[nodiscard]] bool CommandQueue :: create(const Device& device)noexcept
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	const auto hr = device.get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&CommandQueue_));
	if (FAILED(hr)) {
		assert(false && "コマンドキューの作成に失敗");
		return false;
	}
	return true;
}

//コマンドキュー取得
[[nodiscard]] ID3D12CommandQueue* CommandQueue :: get()const noexcept {
	if (!CommandQueue_) {
		assert(false && "コマンドキューが未作成");
		return nullptr;
	}
	return CommandQueue_;
}