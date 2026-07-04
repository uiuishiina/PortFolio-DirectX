#pragma once
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

///====================================================================
/// PipelineStateDesc 構造体
///====================================================================

//@breif	=== パイプラインステート設定構造体 ===
struct PipelineStateDesc
{
	//@brief	== インプットレイアウト配列 ==
	std::vector<D3D12_INPUT_ELEMENT_DESC> input_elements{};

	//@brief	== ルートシグネチャー参照 ==
	ID3D12RootSignature* root_signature{};

	//	各種シェーダー参照
	ID3DBlob* vs_hlsl{};
	ID3DBlob* ps_hlsl{};
	ID3DBlob* gs_hlsl{};
	ID3DBlob* hs_hlsl{};
	ID3DBlob* ds_hlsl{};

	// 各種構造体設定
	D3D12_RASTERIZER_DESC    rasterizer_desc{};
	D3D12_BLEND_DESC         blend_desc{};
	D3D12_DEPTH_STENCIL_DESC depth_stencil_desc{};

	//@brief	== トポロジー設定 ==
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive_topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// レンダーターゲット設定
	UINT num_render_targets = 1;
	DXGI_FORMAT rtv_formats[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT] {
		DXGI_FORMAT_R8G8B8A8_UNORM
	};

	//@brief	== デプスステート設定 ==
	DXGI_FORMAT dsv_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 各種サンプラー設定
	UINT sample_count = 1;
	UINT sample_quality = 0;

	// 各種マスク設定
	UINT sample_mask = UINT_MAX;
	UINT node_mask = 0;

	//@brief	== パイプラインステートフラグ設定 ==
	D3D12_PIPELINE_STATE_FLAGS flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	///====================================================================
	/// 構造体設定
	///====================================================================
	
	//コンストラクタ
	PipelineStateDesc();
};

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
	[[nodiscard]] HRESULT create_piplinestate(ID3D12Device* device, PipelineStateDesc& desc);

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