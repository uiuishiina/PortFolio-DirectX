#pragma once
#include<dxgi1_6.h>
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// TextureResouce 基底クラス
///====================================================================

//@brief	=== 描画リソース基底クラス ===
class TextureResouce
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	TextureResouce() = default;
	virtual ~TextureResouce() = default;

	//コピー禁止,ムーブ禁止
	TextureResouce(const TextureResouce&) = delete;
	TextureResouce& operator=(const TextureResouce&) = delete;
	TextureResouce(TextureResouce&&) = delete;
	TextureResouce& operator=(TextureResouce&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================
	
	//@brief	=== リソースバリア遷移関数 ===
	//@param	list	描画用コマンドリスト
	//@param	next_state	遷移先バリアステート
	void  barrier_transition(ID3D12GraphicsCommandList* list, D3D12_RESOURCE_STATES next_state);

	//@breif	=== リソースインスタンス取得関数 ===
	//@return	リソースインスタンス
	[[nodiscard]] ID3D12Resource* get_resouce()const noexcept;
protected:

	//@brief	== リソースインスタンス ==
	Microsoft::WRL::ComPtr<ID3D12Resource> resouce_{};

	//@brief	== リソースステート ==
	D3D12_RESOURCE_STATES current_state = D3D12_RESOURCE_STATE_PRESENT;
};