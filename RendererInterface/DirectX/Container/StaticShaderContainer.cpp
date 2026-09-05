#include"../HashAllocator.h"
#include "StaticShaderContainer.h"

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// シェーダーコンパイル関数
/// </summary>
/// <param name="key">追加したい倫理側のキー</param>
/// <param name="path">シェーダー絶対パス</param>
/// <param name="entry_point_name">シェーダー開始関数名</param>
/// <param name="target_profile">シェーダータイプ</param>
/// <returns>コンパイルの成否</returns>
[[nodiscard]] HRESULT StaticShaderContainer::compile_shader(const handle::ShaderKey& key,
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