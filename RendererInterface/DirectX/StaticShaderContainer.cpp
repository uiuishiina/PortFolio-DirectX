#include"HashAllocator.h"

#include "StaticShaderContainer.h"

///====================================================================
/// クラス登録
///====================================================================

StaticShaderContainer::StaticShaderContainer() {
    hash_allocator = std::make_unique<HashAllocator>();
}
StaticShaderContainer::~StaticShaderContainer() = default;

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
    auto hash = hash_allocator->get_hash(key_name);
    if (hash.has_value()) {
        return S_OK;
    }

    //  シェーダーコンパイル
    auto shader = std::make_unique<ShaderCompiler>();
    const auto hr = shader->compile_shader(path, entry_point_name, target_profile);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    hash = hash_allocator->allocate_hash(key_name);
    shader_map.emplace(hash.value(), std::move(shader));
    return S_OK;
}

//@brief	=== ハッシュキー取得関数 ===
//@param	key_name	登録したキーの名前
//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
[[nodiscard]] std::optional<UINT> StaticShaderContainer::get_shader_hash_key(const std::string& key_name)const noexcept {

    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return std::nullopt;
    }
    return hash.value();
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
    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return nullptr;
    }

    const auto it = shader_map.find(hash.value());
    if (it == shader_map.end()) {
        return nullptr;
    }
    return it->second->get_shader();
}