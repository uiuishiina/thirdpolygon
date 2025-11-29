
//------  RenderTarget.cpp  ------

#include"RenderTarget.h"
#include<cassert>

//デストラクタ
RenderTarget::~RenderTarget() {
    // レンダーターゲットリソースの解放
    for (auto& rt : RenderTargets_) {
        if (rt) {
            rt->Release();
            rt = nullptr;
        }
    }
    RenderTargets_.clear();
}

//
[[nodiscard]] bool RenderTarget :: create(const Device& device, const SwapChain& swapChain, const Descripter_Heap& heap) noexcept
{
    const auto& desc = swapChain.getDesc();
    
    RenderTargets_.resize(desc.BufferCount);

    auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

    auto heapType = heap.getType();
    assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターピープのタイプがRTVではありません");

    for (uint8_t i = 0; i < desc.BufferCount; i++ ) {
        const auto hr = swapChain.get()->GetBuffer(i, IID_PPV_ARGS(&RenderTargets_[i]));
        if (FAILED(hr)) {
            assert(false && "バックバッファの取得に失敗");
            return false;
        }

        device.get()->CreateRenderTargetView(RenderTargets_[i], nullptr, handle);

        handle.ptr += device.get()->GetDescriptorHandleIncrementSize(heapType);
    }
    return true;
}

//
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget :: getDescriptorHandle(const Device& device, const Descripter_Heap& heap, UINT index) const noexcept
{
    if (index >= RenderTargets_.size() || !RenderTargets_[index]) {
        assert(false && "レンダーターゲットサイズ異常");
    }

    auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

    auto heapType = heap.getType();
    assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターピープのタイプがRTVではありません");

    handle.ptr += (index * device.get()->GetDescriptorHandleIncrementSize(heapType));
    return handle;
}

//
[[nodiscard]] ID3D12Resource* RenderTarget :: get(uint32_t index) const noexcept {
    if (!RenderTargets_[index]) {
        assert(false && "レンダーターゲットサイズ異常(get)");
        return nullptr;
    }
    if (index >= RenderTargets_.size() ) {
        assert(false && "レンダーターゲットサイズ異常(get)");
        return nullptr;
    }
    return RenderTargets_[index];
}