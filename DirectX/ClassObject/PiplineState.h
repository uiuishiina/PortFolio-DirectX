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

			/// <summary>
			/// コンストラクタ
			/// </summary>
			PiplineState() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~PiplineState() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// パイプラインステート作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="desc">パイプラインステート設定構造体</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_pipline(
				ID3D12Device* device,
				desc::PipelineStateDesc& desc
			);

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