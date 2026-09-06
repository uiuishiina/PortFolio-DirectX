#include"ShaderCompiler.h"

#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include"../../../Debug/DebugLogSystem.h"
#include<cassert>

using namespace render::dx12::object;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/* -- 作成関数 -- */

/// <summary>
/// HLSLシェーダーコンパイル関数
/// </summary>
/// <param name="path">コンパイルするHLSLシェーダーの絶対パス</param>
/// <param name="entry_point_name">HLSLシェーダーのエントリーポイントの名前</param>
/// <param name="target_profile">HLSLシェーダーのターゲットプロファイル(バージョン)</param>
/// <returns>コンパイルの成否</returns>
[[nodiscard]] HRESULT ShaderCompiler::compile_shader(
	const std::wstring& path,
	const std::string& entry_point_name, 
	const std::string& target_profile
) {

	//	デバッグ設定
	UINT compile_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	compile_flags |= D3DCOMPILE_DEBUG;
#endif

	//	シェーダーコンパイル
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob;
	const auto hr = D3DCompileFromFile(path.c_str(), nullptr, nullptr, entry_point_name.c_str(),
		target_profile.c_str(), compile_flags, 0, &shader_blob, &error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			DEBUG_ERROR_LOG(static_cast<const char*>(error_blob.Get()->GetBufferPointer()));
		}
	}
	return hr;
}

/* -- 取得関数 -- */

/// <summary>
/// HLSLシェーダー取得関数
/// </summary>
/// <returns>HLSLシェーダー参照</returns>
[[nodiscard]] ID3DBlob* ShaderCompiler::get_shader()const noexcept {
	assert(shader_blob && "シェーダー nullptr");
	return shader_blob.Get();
}