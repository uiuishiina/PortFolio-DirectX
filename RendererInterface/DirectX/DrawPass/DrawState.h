#pragma once
#include"../DrawResouces.h"
#include"Others/NonCopyableBase.h"
#include<vector>
#include<functional>

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクト設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// 描画設定補助構造体
			/// </summary>
			struct DrawStateDesc {

				/// <summary>
				/// ルートシグネチャークラス参照
				/// </summary>
				ID3D12RootSignature* root_signature{};

				/// <summary>
				/// パイプラインステートクラス参照
				/// </summary>
				ID3D12PipelineState* pipline_state{};

				/// <summary>
				/// ビューポート設定
				/// </summary>
				D3D12_VIEWPORT viewport_{};

				/// <summary>
				/// シザー短径設定
				/// </summary>
				D3D12_RECT	rect_{};

			};
		}

		/// <summary>
		/// 描画設定名前空間
		/// </summary>
		namespace state {

			/// <summary>
			/// 描画設定クラス
			/// </summary>
			class Drawstate final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				Drawstate() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~Drawstate() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画設定作成関数
				/// </summary>
				/// <param name="desc">描画設定補助構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] bool creaate_draw_state(desc::DrawStateDesc& desc);

				/// <summary>
				/// 描画パス実行時バインド関数
				/// </summary>
				/// <param name="resouce">描画リソース構造体参照</param>
				void apply(resources::DrawResources& resouce);

			private:
				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// ルートシグネチャー参照
				/// </summary>
				ID3D12RootSignature* root_signature{};

				/// <summary>
				/// パイプラインステート参照
				/// </summary>
				ID3D12PipelineState* pipeline_state{};

				/// <summary>
				/// ビューポート
				/// </summary>
				D3D12_VIEWPORT viewport_{};

				/// <summary>
				/// シーザー短形
				/// </summary>
				D3D12_RECT	rect_{};

			};
		}
	}
}