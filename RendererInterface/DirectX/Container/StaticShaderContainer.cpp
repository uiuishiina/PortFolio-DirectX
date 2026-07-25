#include"../HashAllocator.h"
#include "StaticShaderContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 実行時処理関数群
///====================================================================

//@brief	=== シェーダーコンパイル関数 ===
//@param	key_name	登録するキーの名前
//@param	path	登録するシェーダーパス
//@param	entry_point_name	登録するシェーダーのエントリーポイントの名前
//@param	target_profile	登録するシェーダーのターゲットプロファイル
//@return	コンパイルの成否
[[nodiscard]] HRESULT StaticShaderContainer::compile_shader(const std::string& key_name, 
    const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile)
{
    //  登録済みか確認
    auto hash = get_hash_key(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  シェーダーコンパイル
    auto shader = std::make_unique<object::ShaderCompiler>();
    const auto hr = shader->compile_shader(path, entry_point_name, target_profile);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    auto new_hash = allocate_hash(key_name);
    shader_map.emplace(new_hash, std::move(shader));
    return S_OK;
}

//@brief	=== シェーダー取得関数 ===
//@param	key	シェーダーと紐づけたキー
//@return	シェーダーインスタンス
[[nodiscard]] ID3DBlob* StaticShaderContainer::get_shader(UINT key)const noexcept {

    const auto it = shader_map.find(key);
    if (it == shader_map.end()) {
        return nullptr;
    }
    return it->second->get_shader();
}

//@brief	=== シェーダー取得関数オーバーロード ===
//@param	key_name	シェーダーと紐づけたキーの名前
//@return	シェーダーインスタンス
[[nodiscard]] ID3DBlob* StaticShaderContainer::get_shader(const std::string& key_name)const noexcept {

    //  キーを取得
    auto hash = get_hash_key(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    //  上の関数に処理を任せる
    return get_shader(hash.value());
}