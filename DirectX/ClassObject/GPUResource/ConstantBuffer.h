#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"UploadResourceBase.h"


/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// コンスタントバッファクラス
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template<typename T>
		class ConstantBuffer final : public UploadResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			ConstantBuffer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~ConstantBuffer() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// コンスタントバッファ作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="handles">紐づけるDescriptorHeapHandleの補助構造体</param>
			/// <param name="data">コンスタントバッファに書き込むデータ</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_constant_buffer(
				ID3D12Device* device_,
				Helper::DescriptorHeapHandles handles,
				const T& data
			) {

				handles_ = handles;

				desc::UploadResourceDesc desc{};
				
				desc.resource_size = (sizeof(T) + 255) & ~255;
				desc.read_range = { 0,0 };
				desc.subresource_index = 0;

				const auto hr = create_upload_resource(
					device_,
					desc
				);
				if (FAILED(hr)) {
					return hr;
				}

				if (!upload(data)) {
					rollback_resource();
					return E_FAIL;
				}

				return hr;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// データUpload関数
			/// </summary>
			/// <param name="data">Uploadするデータ</param>
			/// <returns>Uploadの成否</returns>
			bool upload_buffer(
				const T& data
			) {

				return upload(data);
			}

			/// <summary>
			/// コンスタントバッファセット関数
			/// </summary>
			/// <param name="register_index">セットするレジスター番号</param>
			/// <param name="list_">コマンドリスト参照</param>
			void set_constant_buffer(
				UINT register_index,
				ID3D12GraphicsCommandList* list_
			) {

				list_->SetGraphicsRootDescriptorTable(
					register_index,
					handles_.gpu_handle
				);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// ディスクリプターハンドル補助構造体取得関数
			/// </summary>
			/// <returns>取得したいディスクリプターハンドル補助構造体</returns>
			[[nodiscard]] Helper::DescriptorHeapHandles get_handles() const noexcept {

				return handles_;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ディスクリプターハンドル補助構造体
			/// </summary>
			Helper::DescriptorHeapHandles handles_{};

			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化補助関数 ===== */

			/// <summary>
			/// 派生先別リソース作成仮想関数
			/// </summary>
			/// <details>
			/// 基底クラスではS_OKを返す
			/// </details>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_resource_object(
				ID3D12Device* device_
			) override {

				D3D12_CONSTANT_BUFFER_VIEW_DESC Desc{};
				Desc.BufferLocation = resource_->GetGPUVirtualAddress();
				Desc.SizeInBytes = static_cast<UINT>(resource_size);

				device_->CreateConstantBufferView(
					&Desc, 
					handles_.cpu_handle
				);

				return S_OK;
			}

		};
	}
}