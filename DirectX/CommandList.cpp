
//------  CommandList.cpp  ------

#include"CommandList.h"
#include<cassert>

//デストラクタ
CommandList :: ~CommandList() {
	if (CommandList_) {
		CommandList_->Release();
		CommandList_ = nullptr;
	}
}

//コマンドリスト作成
[[nodiscard]] bool CommandList :: create(const Device& device, const CommandAllocator& Allocator)noexcept
{
	const auto hr = device.get()->CreateCommandList(0, Allocator.getType(), Allocator.get(), nullptr, IID_PPV_ARGS(&CommandList_));
	if (FAILED(hr)) {
		assert(false && "コマンドリストの作成に失敗");
		return false;
	}
	CommandList_->Close();
	return true;
}

//
void CommandList :: reset(const CommandAllocator& Allocator) noexcept {
	if(!CommandList_) {
		assert(false && "コマンドリストが未作成です");
	}

	// コマンドリストをリセット
	CommandList_->Reset(Allocator.get(), nullptr);
}

//コマンドリスト取得
[[nodiscard]] ID3D12GraphicsCommandList* CommandList :: get()const noexcept {
	if (!CommandList_) {
		assert(false && "コマンドリスト未作成");
		return nullptr;
	}
	return CommandList_;
}