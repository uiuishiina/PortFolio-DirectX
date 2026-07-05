#pragma once
#include"DirectXobject/PiplineState.h"
#include<string>
#include<unordered_map>
#include<memory>
#include<optional>

///====================================================================
/// 前方宣言
///====================================================================

class HashAllocator;

///====================================================================
/// StaticPiplineStateContainer クラス
///====================================================================

//@brief	=== パイプラインステートコンテナクラス ===
class StaticPiplineStateContainer final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	StaticPiplineStateContainer();
	~StaticPiplineStateContainer();

	//コピー禁止,ムーブ禁止
	StaticPiplineStateContainer(const StaticPiplineStateContainer&) = delete;
	StaticPiplineStateContainer& operator=(const StaticPiplineStateContainer&) = delete;
	StaticPiplineStateContainer(StaticPiplineStateContainer&&) = delete;
	StaticPiplineStateContainer& operator=(StaticPiplineStateContainer&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== パイプラインステート作成関数 ===
	//@param	key_name	登録するキーの名前
	//@param	device	DirectX12 デバイス
	//@param	desc	パイプラインステート設定
	//@return	作成の成否
	[[nodiscard]] HRESULT create_pipline_state(const std::string& key_name, ID3D12Device* device, PipelineStateDesc& desc);

	//@brief	=== ハッシュキー取得関数 ===
	//@param	key_name	登録したキーの名前
	//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
	[[nodiscard]] std::optional<UINT> get_pipline_state_hash_key(const std::string& key_name)const noexcept;

	//@brief	=== パイプラインステート取得関数 ===
	//@param	key	パイプラインステートと紐づけたキー
	//@return	パイプラインステートインスタンス
	[[nodiscard]] ID3D12PipelineState* get_pipline_state(UINT key)const noexcept;

	//@brief	=== パイプラインステート取得関数オーバーロード ===
	//@param	key_name	パイプラインステートと紐づけたキーの名前
	//@return	パイプラインステートインスタンス
	[[nodiscard]] ID3D12PipelineState* get_pipline_state(const std::string& key_name)const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== パイプラインステート保存マップ ===
	//@details	作成できたパイプラインステートを保存するmap
	std::unordered_map<UINT, std::unique_ptr<PiplineState>> pipline_map{};

	//@brief	== ハッシュアロケーターインスタンス ==
	//@details	シェーダーハッシュキー登録クラス
	std::unique_ptr<HashAllocator> hash_allocator{};
};