#pragma once

//------  CommandList.h  ------

#include"Device.h"
#include"CommandAllocator.h"

class CommandList final
{
public:
	CommandList() = default;

	//デストラクタ
	~CommandList();

	//コマンドリスト作成
	[[nodiscard]] bool create(const Device& device, const CommandAllocator& Allocator)noexcept;

	//
	void reset(const CommandAllocator& Allocator) noexcept;

	//コマンドリストを取得
	[[nodiscard]] ID3D12GraphicsCommandList* get()const noexcept;
private:
	ID3D12GraphicsCommandList* CommandList_{};
};