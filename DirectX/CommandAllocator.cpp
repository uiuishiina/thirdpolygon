
//------  CommandAllocator.cpp  ------

#include"CommandAllocator.h"
#include<cassert>

//デストラクタ
CommandAllocator :: ~CommandAllocator() {
	if (CommandAllocator_) {
		CommandAllocator_->Release();
		CommandAllocator_ = nullptr;
	}
}

//コマンドアロケーター作成
[[nodiscard]] bool CommandAllocator :: create(const Device& device, const D3D12_COMMAND_LIST_TYPE type)noexcept
{
	type_ = type;

	const auto hr = device.get()->CreateCommandAllocator(type_, IID_PPV_ARGS(&CommandAllocator_));
	if (FAILED(hr)) {
		assert(false && "コマンドアロケーターの作成に失敗");
		return false;
	}
	return true;
}

//コマンドアロケーターリセット
void CommandAllocator :: Reset() {
	if (!CommandAllocator_) {
		assert(false && "コマンドアロケーターが未作成");
	}
	CommandAllocator_->Reset();
}

//コマンドアロケーター取得
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator :: get()const noexcept {
	if (!CommandAllocator_) {
		assert(false && "コマンドアロケーターが未作成");
		return nullptr;
	}
	return CommandAllocator_;
}

//コマンドアロケーターのタイプ取得
[[nodiscard]] D3D12_COMMAND_LIST_TYPE CommandAllocator :: getType()const noexcept {
	if (!CommandAllocator_) {
		assert(false && "コマンドアロケーターが未作成");
	}
	return type_;
}