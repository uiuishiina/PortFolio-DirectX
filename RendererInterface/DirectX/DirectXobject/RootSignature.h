#pragma once
#include"Others/NonCopyableBase.h"
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

/// <summary>
/// 描画機能名前空間
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
			/// ルートシグネチャ設定構造体
			/// </summary>
			struct RootSignatureDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// ルートパラメーター設定配列
				/// </summary>
				std::vector<D3D12_ROOT_PARAMETER> parameters_;

				/// <summary>
				/// サンプラー設定配列
				/// </summary>
				std::vector<D3D12_STATIC_SAMPLER_DESC> samplers_;

				/// <summary>
				/// パイプラインステートフラグ
				/// </summary>
				D3D12_ROOT_SIGNATURE_FLAGS flags_;

			};
		}

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// ルートシグネチャクラス
			/// </summary>
			class RootSignature final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				RootSignature() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~RootSignature() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// ルートシグネチャ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="desc">ルートシグネチャー設定構造体参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_root_signature(
					ID3D12Device* device, 
					desc::RootSignatureDesc& desc
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// ルートシグネチャ取得関数
				/// </summary>
				/// <returns>ルートシグネチャ参照</returns>
				[[nodiscard]] ID3D12RootSignature* get_root_signature() const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// ルートシグネチャインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12RootSignature> root_signature{};

			};
		}
	}
}