#include"../HashAllocator.h"

#include "StaticRootSignatureContainer.h"

///====================================================================
/// クラス設定
///====================================================================

//コンストラクタ,デストラクタ
StaticRootSignatureContainer::StaticRootSignatureContainer() {
    hash_allocator = std::make_unique<HashAllocator>();
}
StaticRootSignatureContainer::~StaticRootSignatureContainer() = default;

///====================================================================
/// 実行時処理関数群
///====================================================================

//@brief	=== ルートシグネチャー作成関数 ===
//@param	key_name	登録するキーの名前
//@param	device	DirectX12 デバイス
//@param	desc	ルートシグネチャー設定
//@return	作成の成否
[[nodiscard]] HRESULT StaticRootSignatureContainer::create_root_signature(const std::string& key_name, ID3D12Device* device, RootSignatureDesc& desc)
{
    //  登録済みか確認
    auto hash = hash_allocator->get_hash(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  ルートシグネチャー作成
    auto pipline = std::make_unique<RootSignature>();
    const auto hr = pipline->create_root_signature(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    hash = hash_allocator->allocate_hash(key_name);
    root_map.emplace(hash.value(), std::move(pipline));
    return S_OK;
}

//@brief	=== ハッシュキー取得関数 ===
//@param	key_name	登録したキーの名前
//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
[[nodiscard]] std::optional<UINT> StaticRootSignatureContainer::get_root_signature_hash_key(const std::string& key_name)const noexcept {

    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return std::nullopt;
    }
    return hash.value();
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
    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    const auto it = root_map.find(hash.value());
    if (it == root_map.end()) {
        return nullptr;
    }
    return it->second->get_root_signature();
}