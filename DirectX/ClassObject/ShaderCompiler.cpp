
/* ========== Includeファイル ========== */

#include "ShaderCompiler.h"

#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include"Debug/DebugLogSystem.h"

using namespace DirectX::ClassObject;

/* ========== Publicメンバー関数 ========== */

/* ===== 初期化関数 ===== */

/// <summary>
/// HLSLシェーダーコンパイル関数
/// </summary>
/// <param name="desc">HLSLシェーダー設定構造体参照</param>
/// <returns>コンパイルの成否</returns>
[[nodiscard]] HRESULT ShaderCompiler::compile_shader(
	desc::ShaderDesc& desc
) {

	//	デバッグ設定
	UINT compile_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	compile_flags |= D3DCOMPILE_DEBUG;
#endif

	//	シェーダーコンパイル
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob;

	const auto hr = D3DCompileFromFile(
		desc.path.c_str(),
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		desc.entry_point_name.c_str(),
		desc.target_profile.c_str(),
		compile_flags, 
		0,
		&shader_blob, 
		&error_blob
	);
	if (FAILED(hr)) {
		if (error_blob) {
			DEBUG_ERROR_LOG(static_cast<const char*>(error_blob.Get()->GetBufferPointer()));
		}
	}
	return hr;
}