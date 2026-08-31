#include"../HashAllocator.h"
#include "StaticRootSignatureContainer.h"

using namespace render::dx12::container;

/// <summary>
/// ルートシグネチャー作成関数
/// </summary>
/// <param name="key">追加したい倫理側のキー</param>
/// <param name="device">DirectX12デバイスポインター</param>
/// <param name="desc">ルートシグネチャー設定</param>
/// <returns>作成の成否</returns>
[[nodiscard]] HRESULT StaticRootSignatureContainer::create_root_signature(const handle::RootSignatureKey& key, ID3D12Device* device, desc::RootSignatureDesc& desc) {

    //  ルートシグネチャー作成
    auto root = std::make_unique<object::RootSignature>();
    const auto hr = root->create_root_signature(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    return add_value(key, std::move(root)) ? S_OK : E_FAIL;
}