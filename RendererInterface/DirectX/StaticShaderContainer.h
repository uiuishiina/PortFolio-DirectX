#pragma once
#include"DirectXobject/ShaderCompiler.h"
#include<unordered_map>
#include<memory>
#include<optional>

///====================================================================
/// 前方宣言
///====================================================================

class HashAllocator;

///====================================================================
/// StaticShaderContainer クラス
///====================================================================

//@breif	=== シェーダーコンテナクラス ===
class StaticShaderContainer final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	StaticShaderContainer();
	~StaticShaderContainer();

	//コピー禁止,ムーブ禁止
	StaticShaderContainer(const StaticShaderContainer&) = delete;
	StaticShaderContainer& operator=(const StaticShaderContainer&) = delete;
	StaticShaderContainer(StaticShaderContainer&&) = delete;
	StaticShaderContainer& operator=(StaticShaderContainer&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================
	
	//@brief	=== シェーダーコンパイル関数 ===
	//@param	key_name	登録するキーの名前
	//@param	path	登録するシェーダーパス
	//@param	entry_point_name	登録するシェーダーのエントリーポイントの名前
	//@param	target_profile	登録するシェーダーのターゲットプロファイル
	//@return	コンパイルの成否...登録してあるなら [ S_OK ] 
	[[nodiscard]] HRESULT compile_shader(const std::string& key_name, const std::wstring& path, const std::string& entry_point_name, const std::string& target_profile);

	//@brief	=== ハッシュキー取得関数 ===
	//@param	key_name	登録したキーの名前
	//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
	[[nodiscard]] std::optional<UINT> get_shader_hash_key(const std::string& key_name)const noexcept;

	//@brief	=== シェーダー取得関数 ===
	//@param	key	シェーダーと紐づけたキー
	//@return	シェーダーインスタンス
	[[nodiscard]] ID3DBlob* get_shader(UINT key)const noexcept;

	//@brief	=== シェーダー取得関数オーバーロード ===
	//@param	key_name	シェーダーと紐づけたキーの名前
	//@return	シェーダーインスタンス
	[[nodiscard]] ID3DBlob* get_shader(const std::string& key_name)const noexcept;
	
private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================
	
	//@brief	== シェーダー保存マップ ===
	//@details	コンパイルできたシェーダーを保存するmap
	std::unordered_map<UINT, std::unique_ptr<ShaderCompiler>> shader_map{};

	//@brief	== ハッシュアロケーターインスタンス ==
	//@details	シェーダーハッシュキー登録クラス
	std::unique_ptr<HashAllocator> hash_allocator{};
};