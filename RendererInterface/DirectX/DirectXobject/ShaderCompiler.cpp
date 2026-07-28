#include"ShaderCompiler.h"

#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include"../../../Debug/DebugLogSystem.h"
#include<cassert>

using namespace render::dx12::object;

///====================================================================
/// 初期化時関数
///====================================================================

//@brief	=== HLSLシェーダーコンパイル関数 ===
//@param	path	HLSLシェーダーのファイル位置を示すpath
//@param	entry_point_name	HLSLシェーダーのエントリーポイントの名前
//@param	target_profile	HLSLシェーダーのターゲットプロファイル(バージョン)
//@return	コンパイルの成否
[[nodiscard]] HRESULT ShaderCompiler::compile_shader(const std::wstring& path,
	const std::string& entry_point_name, const std::string& target_profile) {

	UINT compile_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	compile_flags |= D3DCOMPILE_DEBUG;
#endif
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

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== HLSLシェーダー取得関数 ===
//@return	HLSLシェーダー参照
[[nodiscard]] ID3DBlob* ShaderCompiler::get_shader()const noexcept {
	assert(shader_blob && "シェーダー nullptr");
	return shader_blob.Get();
}