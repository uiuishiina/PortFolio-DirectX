#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<d3d12.h>
#include<wrl/client.h>

//	その他
#include<vector>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DirectXオブジェクト設定構造体名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// パイプラインステート設定構造体
			/// </summary>
			struct PipelineStateDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// インプットレイアウト配列
				/// </summary>
				std::vector<D3D12_INPUT_ELEMENT_DESC> input_elements{};

				/// <summary>
				/// ルートシグネチャー参照
				/// </summary>
				ID3D12RootSignature* root_{};


				/* ===== 各種シェーダー参照 ===== */

				/// <summary>
				/// 頂点シェーダー参照
				/// </summary>
				ID3DBlob* vs_hlsl{};

				/// <summary>
				/// ピクセルシェーダー参照
				/// </summary>
				ID3DBlob* ps_hlsl{};

				/// <summary>
				/// ジオメトリシェーダー参照
				/// </summary>
				ID3DBlob* gs_hlsl{};

				/// <summary>
				/// ハルシェーダー参照
				/// </summary>
				ID3DBlob* hs_hlsl{};

				/// <summary>
				/// ドメインシェーダー参照
				/// </summary>
				ID3DBlob* ds_hlsl{};


				/* ===== 各種描画設定 ===== */

				/// <summary>
				/// ラスタライザ設定
				/// </summary>
				D3D12_RASTERIZER_DESC rasterizer_desc{};

				/// <summary>
				/// ブレンド設定
				/// </summary>
				D3D12_BLEND_DESC blend_desc{};

				/// <summary>
				/// デプス設定
				/// </summary>
				D3D12_DEPTH_STENCIL_DESC depth_stencil_desc{};

				/// <summary>
				/// トポロジー設定
				/// </summary>
				D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive_topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


				/* ===== 描画先設定 ===== */

				/// <summary>
				/// レンダーターゲット数設定
				/// </summary>
				UINT num_render_targets = 1;

				/// <summary>
				/// レンダーターゲットフォーマット設定
				/// </summary>
				DXGI_FORMAT rtv_formats[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT]{
					DXGI_FORMAT_R8G8B8A8_UNORM
				};

				/// <summary>
				/// デプスフォーマット設定
				/// </summary>
				DXGI_FORMAT dsv_format = DXGI_FORMAT_UNKNOWN;

				/// <summary>
				/// サンプラー数設定
				/// </summary>
				UINT sample_count = 1;

				/// <summary>
				/// サンプラークオリティー設定
				/// </summary>
				UINT sample_quality = 0;

				/// <summary>
				/// サンプルマスク設定
				/// </summary>
				UINT sample_mask = UINT_MAX;

				/// <summary>
				/// ノードマスク
				/// </summary>
				UINT node_mask = 0;

				/// <summary>
				/// パイプラインステートフラグ設定
				/// </summary>
				D3D12_PIPELINE_STATE_FLAGS flags = D3D12_PIPELINE_STATE_FLAG_NONE;

			};
		}

		/// <summary>
		/// パイプラインステートクラス
		/// </summary>
		class PiplineState final : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// パイプラインステート作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="desc">パイプラインステート設定構造体</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_pipline(
				ID3D12Device* device_,
				const desc::PipelineStateDesc& desc
			) {

				D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_desc{};

				// インプットレイアウト配列設定
				pipeline_desc.InputLayout = { desc.input_elements.data(), static_cast<UINT>(desc.input_elements.size()) };

				// ルートシグネチャー参照設定
				pipeline_desc.pRootSignature = desc.root_;

				// 各種シェーダー参照設定
				if (desc.vs_hlsl) {
					pipeline_desc.VS = { desc.vs_hlsl->GetBufferPointer(),desc.vs_hlsl->GetBufferSize() };
				}

				if (desc.ps_hlsl) {
					pipeline_desc.PS = { desc.ps_hlsl->GetBufferPointer(),desc.ps_hlsl->GetBufferSize() };
				}

				if (desc.gs_hlsl) {
					pipeline_desc.GS = { desc.gs_hlsl->GetBufferPointer(),desc.gs_hlsl->GetBufferSize() };
				}

				if (desc.hs_hlsl) {
					pipeline_desc.HS = { desc.hs_hlsl->GetBufferPointer(),desc.hs_hlsl->GetBufferSize() };
				}

				if (desc.ds_hlsl) {
					pipeline_desc.DS = { desc.ds_hlsl->GetBufferPointer(),desc.ds_hlsl->GetBufferSize() };
				}

				// 各種構造体設定
				pipeline_desc.RasterizerState = desc.rasterizer_desc;
				pipeline_desc.BlendState = desc.blend_desc;
				pipeline_desc.DepthStencilState = desc.depth_stencil_desc;

				// トポロジー設定
				pipeline_desc.PrimitiveTopologyType = desc.primitive_topology;

				// レンダーターゲット設定
				pipeline_desc.NumRenderTargets = desc.num_render_targets;
				for (UINT i = 0; i < desc.num_render_targets; ++i) {
					pipeline_desc.RTVFormats[i] = desc.rtv_formats[i];
				}

				//  デプスステート設定
				pipeline_desc.DSVFormat = desc.dsv_format;

				// 各種サンプラー設定
				pipeline_desc.SampleDesc.Count = desc.sample_count;
				pipeline_desc.SampleDesc.Quality = desc.sample_quality;

				// 各種マスク設定
				pipeline_desc.SampleMask = desc.sample_mask;
				pipeline_desc.NodeMask = desc.node_mask;

				//  パイプラインステートフラグ設定
				pipeline_desc.Flags = desc.flags;

				return device_->CreateGraphicsPipelineState(
					&pipeline_desc,
					IID_PPV_ARGS(&pipline_)
				);
			}

			/* ===== 追加関数 ===== */

			/// <summary>
			/// パイプラインステート参照取得関数
			/// </summary>
			/// <returns>パイプラインステート参照</returns>
			[[nodiscard]] ID3D12PipelineState* get() const noexcept {

				return pipline_.Get();
			}
	
		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// パイプラインステートインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12PipelineState> pipline_{};

		};
	}
}