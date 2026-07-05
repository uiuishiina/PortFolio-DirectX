#include"HashAllocator.h"

#include "StaticPiplineStateContainer.h"

///====================================================================
/// クラス設定
///====================================================================

//コンストラクタ,デストラクタ
StaticPiplineStateContainer::StaticPiplineStateContainer() {
    hash_allocator = std::make_unique<HashAllocator>();
}
StaticPiplineStateContainer::~StaticPiplineStateContainer() = default;

///====================================================================
/// 実行時処理関数群
///====================================================================

//@brief	=== パイプラインステート作成関数 ===
//@param	key_name	登録するキーの名前
//@param	device	DirectX12 デバイス
//@param	desc	パイプラインステート設定
//@return	作成の成否
[[nodiscard]] HRESULT StaticPiplineStateContainer::create_pipline_state(const std::string& key_name, ID3D12Device* device, PipelineStateDesc& desc)
{
    //  登録済みか確認
    auto hash = hash_allocator->get_hash(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  パイプラインステート作成
    auto pipline = std::make_unique<PiplineState>();
    const auto hr = pipline->create_piplinestate(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    hash = hash_allocator->allocate_hash(key_name);
    pipline_map.emplace(hash.value(), std::move(pipline));
    return S_OK;
}

//@brief	=== ハッシュキー取得関数 ===
//@param	key_name	登録したキーの名前
//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
[[nodiscard]] std::optional<UINT> StaticPiplineStateContainer::get_pipline_state_hash_key(const std::string& key_name)const noexcept {

    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return std::nullopt;
    }
    return hash.value();
}

//@brief	=== パイプラインステート取得関数 ===
//@param	key	パイプラインステートと紐づけたキー
//@return	パイプラインステートインスタンス
[[nodiscard]] ID3D12PipelineState* StaticPiplineStateContainer::get_pipline_state(UINT key)const noexcept {

    const auto it = pipline_map.find(key);
    if (it == pipline_map.end()) {
        return nullptr;
    }
    return it->second->get_pipline_state();
}

//@brief	=== パイプラインステート取得関数オーバーロード ===
//@param	key_name	パイプラインステートと紐づけたキーの名前
//@return	パイプラインステートインスタンス
[[nodiscard]] ID3D12PipelineState* StaticPiplineStateContainer::get_pipline_state(const std::string& key_name)const noexcept {

    //  キーを取得
    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    const auto it = pipline_map.find(hash.value());
    if (it == pipline_map.end()) {
        return nullptr;
    }
    return it->second->get_pipline_state();
}