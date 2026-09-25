#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Debug/DebugLogSystem.h"

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
			/// ルートシグネチャー設定構造体
			/// </summary>
			struct RootSignatureDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// ルートパラメーター設定配列
				/// </summary>
				std::vector<D3D12_ROOT_PARAMETER> parameters_;

				/// <summary>
				/// サンプラー設定配列
				/// </summary>
				std::vector<D3D12_STATIC_SAMPLER_DESC> samplers_;

				/// <summary>
				/// ルートシグネチャーフラグ
				/// </summary>
				D3D12_ROOT_SIGNATURE_FLAGS flags_;

			};
		}

		/// <summary>
		/// ルートシグネチャークラス
		/// </summary>
		class RootSignature final : HandyItems::others::NonCopyableBase 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			RootSignature() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~RootSignature() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// ルートシグネチャ作成関数
			/// </summary>
			/// <param name="device">Device参照</param>
			/// <param name="desc">ルートシグネチャー設定構造体参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_root_signature(
				ID3D12Device* device,
				desc::RootSignatureDesc& desc
			) {

				//	ルートシグネチャー設定
				D3D12_ROOT_SIGNATURE_DESC root_desc{};

				//	ルートパラメーラー設定
				root_desc.NumParameters = static_cast<UINT>(desc.parameters_.size());
				root_desc.pParameters = desc.parameters_.data();

				//	サンプラー設定
				root_desc.NumStaticSamplers = static_cast<UINT>(desc.samplers_.size());
				root_desc.pStaticSamplers = desc.samplers_.data();

				//	ルートシグネチャーフラグ設定
				root_desc.Flags = desc.flags_;

				//	ルートシグネチャーのシリアライズ
				Microsoft::WRL::ComPtr<ID3DBlob> serialized;
				Microsoft::WRL::ComPtr<ID3DBlob> error_blob;

				auto hr = D3D12SerializeRootSignature(
					&root_desc, 
					D3D_ROOT_SIGNATURE_VERSION_1, 
					&serialized, 
					&error_blob
				);
				if (FAILED(hr)) {
					if (error_blob) {
						DEBUG_ERROR_LOG(static_cast<const char*>(error_blob.Get()->GetBufferPointer()));
					}
					return hr;
				}

				//	ID3D12RootSignatureの作成
				return device->CreateRootSignature(
					0,
					serialized->GetBufferPointer(),
					serialized->GetBufferSize(), 
					IID_PPV_ARGS(&root_)
				);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ルートシグネチャー参照取得関数
			/// </summary>
			/// <returns>ルートシグネチャー参照</returns>
			[[nodiscard]] ID3D12RootSignature* get() const noexcept {

				return root_.Get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ルートシグネチャインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12RootSignature> root_{};

		};
	}
}