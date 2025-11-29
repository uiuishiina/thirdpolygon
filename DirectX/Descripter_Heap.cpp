
//

#include"Descripter_Heap.h"
#include<cassert>

//デストラクタ
Descripter_Heap :: ~Descripter_Heap() {
	if (heap_) {
		heap_->Release();
		heap_ = nullptr;
	}
}

//ディスクリプターヒープ作成
[[nodiscard]] bool Descripter_Heap::create(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible)noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = type;
	desc.NumDescriptors = numDescriptors;
	desc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	type_ = type;

	const auto hr = device.get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap_));
	if (FAILED(hr)) {
		assert(false && "ディスクリプターヒープの作成に失敗");
		return false;
	}
	return true;
}

//ディスクリプターヒープの取得
[[nodiscard]] ID3D12DescriptorHeap* Descripter_Heap :: get() const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプターヒープが未作成");
		return nullptr;
	}
	return heap_;
}

//ディスクリプターヒープタイプの取得
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE Descripter_Heap :: getType()const noexcept {
	if (!heap_) {
		assert(false && "ディスクリプターヒープが未作成");
	}
	return type_;
}