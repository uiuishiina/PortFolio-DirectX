#pragma once
#include<d3d12.h>
#include<wrl/client.h>

///====================================================================
/// PiplineState クラス
///====================================================================

//@brief	=== パイプラインステートクラス ===
class PiplineState final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================
	
	//コンストラクタ,デストラクタ
	PiplineState() = default;
	~PiplineState() = default;

	//コピー禁止,ムーブ禁止
	PiplineState(const PiplineState&) = delete;
	PiplineState& operator=(const PiplineState&) = delete;
	PiplineState(PiplineState&&) = delete;
	PiplineState& operator=(PiplineState&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@breif	=== パイプラインステート作成関数 ===
	//@return	作成の成否
	[[nodiscard]] HRESULT create_piplinestate();

	//@brief	=== パイプラインステート取得関数 ===
	//@return	パイプラインステートインスタンス
	[[nodiscard]] ID3D12PipelineState* get_pipline_state()const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	=== パイプラインステートインスタンス ===
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipline_state{};
};