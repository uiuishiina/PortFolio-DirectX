#include "StaticPiplineStateContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数群
///====================================================================

/* ==================== 作成関数 ==================== */

//@brief	=== パイプラインステート作成関数 ===
//@param	key_name	登録するキーの名前
//@param	device	DirectX12 デバイス
//@param	desc	パイプラインステート設定
//@return	作成の成否
[[nodiscard]] HRESULT StaticPiplineStateContainer::create_pipline_state(const std::string& key_name, ID3D12Device* device, desc::PipelineStateDesc& desc)
{
    //  登録済みか確認
    auto hash = get_hash_key(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  パイプラインステート作成
    auto pipline = std::make_unique<object::PipelineState>();
    const auto hr = pipline->create_piplinestate(device, desc);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    auto new_hash = allocate_hash(key_name);
    pipline_map.emplace(new_hash, std::move(pipline));
    return hr;
}

/* ==================== 取得関数 ==================== */

//@brief	=== パイプラインステート取得関数 ===
//@param	key	パイプラインステートと紐づけたキー
//@return	パイプラインステート参照
[[nodiscard]] ID3D12PipelineState* StaticPiplineStateContainer::get_pipline_state(UINT key)const noexcept {

    const auto it = pipline_map.find(key);
    if (it == pipline_map.end()) {
        return nullptr;
    }
    return it->second->get_pipline_state();
}

//@brief	=== パイプラインステート取得関数オーバーロード ===
//@param	key_name	パイプラインステートと紐づけたキーの名前
//@return	パイプラインステート参照
[[nodiscard]] ID3D12PipelineState* StaticPiplineStateContainer::get_pipline_state(const std::string& key_name)const noexcept {

    //  キーを取得
    auto hash = get_hash_key(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    //  上の関数に処理を任せる
    return get_pipline_state(hash.value());
}