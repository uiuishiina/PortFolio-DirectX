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
[[nodiscard]] HRESULT StaticShaderContainer::compile_shader(const key::DefaultKey& key,
   const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile)
{
   
    //  シェーダーコンパイル
    auto shader = std::make_unique<object::ShaderCompiler>();
    const auto hr = shader->compile_shader(path, entry_point_name, target_profile);
    if (FAILED(hr)) {
        return hr;
    }

    //  mapに登録
    return add_value(key, std::move(shader)) ? S_OK : E_FAIL;
}