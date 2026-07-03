#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<string>

///====================================================================
/// ShaderCompiler クラス
///====================================================================

//@brief	=== シェーダーコンパイラークラス ===
class ShaderCompiler final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	ShaderCompiler() = default;
	~ShaderCompiler() = default;

	//コピー禁止,ムーブ禁止
	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(ShaderCompiler&&) = delete;
	ShaderCompiler& operator=(ShaderCompiler&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== HLSLシェーダーコンパイル関数 ===
	//@param	path	HLSLシェーダーのファイル位置を示すpath
	//@param	entry_point_name	HLSLシェーダーのエントリーポイントの名前
	//@param	target_profile	HLSLシェーダーのターゲットプロファイル(バージョン)
	//@return	コンパイルの成否
	[[nodiscard]] HRESULT compile_shader(const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile);

	//@brief	=== HLSLシェーダー取得関数 ===
	//@return	HLSLシェーダーインスタンス
	[[nodiscard]] ID3DBlob* get_shader()const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== HLSLシェーダーインスタンス ==
	//@details	コンパイルしたシェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> shader_blob;
};