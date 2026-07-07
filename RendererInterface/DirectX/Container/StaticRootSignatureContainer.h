#pragma once
#include"../DirectXobject/RootSignature.h"
#include<string>
#include<unordered_map>
#include<memory>
#include<optional>

///====================================================================
/// 前方宣言
///====================================================================

class HashAllocator;

///====================================================================
/// StaticRootSignatureContainer クラス
///====================================================================

//@brief	=== 初期作成ルートシグネチャーコンテナクラス ===
class StaticRootSignatureContainer final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	StaticRootSignatureContainer();
	~StaticRootSignatureContainer();

	//コピー禁止,ムーブ禁止
	StaticRootSignatureContainer(const StaticRootSignatureContainer&) = delete;
	StaticRootSignatureContainer& operator=(const StaticRootSignatureContainer&) = delete;
	StaticRootSignatureContainer(StaticRootSignatureContainer&&) = delete;
	StaticRootSignatureContainer& operator=(StaticRootSignatureContainer&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ルートシグネチャー作成関数 ===
	//@param	key_name	登録するキーの名前
	//@param	device	DirectX12 デバイス
	//@param	desc	ルートシグネチャー設定
	//@return	作成の成否
	[[nodiscard]] HRESULT create_root_signature(const std::string& key_name, ID3D12Device* device, RootSignatureDesc& desc);

	//@brief	=== ハッシュキー取得関数 ===
	//@param	key_name	登録したキーの名前
	//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
	[[nodiscard]] std::optional<UINT> get_root_signature_hash_key(const std::string& key_name)const noexcept;

	//@brief	=== ルートシグネチャー取得関数 ===
	//@param	key	ルートシグネチャーと紐づけたキー
	//@return	ルートシグネチャーインスタンス
	[[nodiscard]] ID3D12RootSignature* get_root_signature(UINT key)const noexcept;

	//@brief	=== ルートシグネチャー取得関数オーバーロード ===
	//@param	key_name	ルートシグネチャーと紐づけたキーの名前
	//@return	ルートシグネチャーインスタンス
	[[nodiscard]] ID3D12RootSignature* get_root_signature(const std::string& key_name)const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== ルートシグネチャー保存マップ ===
	//@details	作成できたルートシグネチャーを保存するmap
	std::unordered_map<UINT, std::unique_ptr<RootSignature>> root_map{};

	//@brief	== ハッシュアロケーターインスタンス ==
	//@details	シェーダーハッシュキー登録クラス
	std::unique_ptr<HashAllocator> hash_allocator{};
};