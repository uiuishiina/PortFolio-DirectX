#include"../HashAllocator.h"
#include "StaticRootSignatureContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数群
///====================================================================

//@brief	=== ルートシグネチャー作成関数 ===
//@param	key_name	登録するキーの名前
//@param	device	DirectX12 デバイス
//@param	desc	ルートシグネチャー設定
//@return	作成の成否
[[nodiscard]] HRESULT StaticRootSignatureContainer::create_root_signature(const std::string& key_name, ID3D12Device* device, desc::RootSignatureDesc& desc)
{
    //  登録済みか確認
    auto hash = get_hash_key(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  ルートシグネチャー作成
    auto pipline = std::make_unique<object::RootSignature>();
    const auto hr = pipline->create_root_signature(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    auto new_hash = allocate_hash(key_name);
    root_map.emplace(new_hash, std::move(pipline));
    return S_OK;
}


//@brief	=== ルートシグネチャー取得関数 ===
//@param	key	ルートシグネチャー紐づけたキー
//@return	ルートシグネチャーインスタンス
[[nodiscard]] ID3D12RootSignature* StaticRootSignatureContainer::get_root_signature(UINT key)const noexcept {

    const auto it = root_map.find(key);
    if (it == root_map.end()) {
        return nullptr;
    }
    return it->second->get_root_signature();
}

//@brief	=== ルートシグネチャー取得関数オーバーロード ===
//@param	key_name	ルートシグネチャー紐づけたキーの名前
//@return	ルートシグネチャーインスタンス
[[nodiscard]] ID3D12RootSignature* StaticRootSignatureContainer::get_root_signature(const std::string& key_name)const noexcept {

    //  キーを取得
    auto hash = get_hash_key(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    //  上の関数に処理を任せる
    return get_root_signature(hash.value());
}