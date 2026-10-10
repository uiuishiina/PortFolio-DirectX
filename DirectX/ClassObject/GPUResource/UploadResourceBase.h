#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"GPUResourceBase.h"
#include"ResourceBarrier.h"

#include"../../Helpers/GPUResourceHelper.h"
#include"../../Helpers/GPUResourceDescHelper.h"
#include"../../Helpers/DescriptorHeapHandles.h"

//	その他
#include<span>
#include<cstddef>
#include<cstring>


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
			/// 動的GPUリソース設定構造体
			/// </summary>
			struct UploadResourceDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// MapSubResource番号
				/// </summary>
				UINT subresource_index{};

				/// <summary>
				/// CPU読み取り範囲設定構造体
				/// </summary>
				/// <details>
				/// SIZE_T Begin [ 読み取り開始位置 ]
				///	SIZE_T End	 [ 読み取り終了位置 ]
				/// </details>
				D3D12_RANGE read_range{ 0,0 };

				/// <summary>
				/// リソースサイズ
				/// </summary>
				UINT64 resource_size{};

			};
		}

		/// <summary>
		/// 動的GPUリソース基底クラス
		/// </summary>
		class UploadResourceBase : public GPUResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			UploadResourceBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~UploadResourceBase() {
				unmap_resource();
			}

		protected:
			/* ========== Protectedメンバー変数 ========== */

			/// <summary>
			/// マップ先ポインター
			/// </summary>
			void* mapped_{};

			/// <summary>
			/// MapSubResource番号
			/// </summary>
			UINT subresource_index{};

			/// <summary>
			/// リソースサイズ
			/// </summary>
			UINT64 resource_size{};

			/* ========== Protectedメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// 動的GPUリソース作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="desc">動的GPUリソース設定構造体参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_upload_resource(
				ID3D12Device* device_,
				const desc::UploadResourceDesc& desc
			) {

				if (desc.resource_size == 0) {
					return E_INVALIDARG;
				}

				desc::GPUResourceDesc resource_desc{};
				resource_desc.heap_properties = Helper::GPUResourceDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
				resource_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
				resource_desc.resource_desc = Helper::GPUResourceDescHelper::get_buffer_desc(desc.resource_size);

				auto hr = create_committed_resource(
					device_,
					resource_desc
				);
				if (FAILED(hr)) {
					rollback_resource();
					return hr;
				}

				hr = map_resource(desc);
				if (FAILED(hr)) {
					rollback_resource();
					return hr;
				}

				hr = create_resource_object(device_);
				if (FAILED(hr)) {
					rollback_resource();
				}

				return hr;
			}

			/* ===== 初期化補助関数 ===== */

			/// <summary>
			/// 派生先別リソース作成仮想関数
			/// </summary>
			/// <details>
			/// 基底クラスではS_OKを返す
			/// </details>
			/// <returns>作成の成否</returns>
			[[nodiscard]] virtual HRESULT create_resource_object(
				ID3D12Device* device_
			) { return S_OK; };

			/// <summary>
			/// ロールバック関数
			/// </summary>
			void rollback_resource() noexcept {

				unmap_resource();
				resource_.Reset();
				resource_size = 0;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// 動的GPUリソースMap関数
			/// </summary>
			/// <param name="desc"></param>
			/// <returns>マップの成否</returns>
			[[nodiscard]] HRESULT map_resource(
				const desc::UploadResourceDesc& desc
			) {

				subresource_index = desc.subresource_index;
				resource_size = desc.resource_size;
				mapped_ = nullptr;

				return resource_->Map(
					desc.subresource_index, 
					&desc.read_range, 
					&mapped_
				);
			}

			/// <summary>
			/// 動的GPUリソースUnmap関数
			/// </summary>
			void unmap_resource() {

				if (!mapped_) {
					return;
				}

				resource_->Unmap(subresource_index, nullptr);
				mapped_ = nullptr;
			}


			/* ===== Upload関数 ===== */

			/// <summary>
			/// Upload関数
			/// </summary>
			/// <param name="data">コピー元先頭ポインター</param>
			/// <param name="size">コピーサイズ</param>
			/// <param name="offset">コピーオフセット</param>
			/// <returns>Uploadの成否</returns>
			[[nodiscard]] bool upload_resource(
				const void* data,
				std::size_t size,
				std::size_t offset = 0
			) {

				//	memcpyできるかチェック
				if (
					!mapped_ ||
					!data ||
					size == 0 ||
					size > resource_size ||
					offset > resource_size ||
					size > resource_size - offset
					) {

					return false;
				}

				std::memcpy(
					static_cast<std::byte*>(mapped_) + offset,
					data,
					size
				);

				return true;
			}

			/// <summary>
			/// Upload関数オーバーロード
			/// </summary>
			/// <typeparam name="T">コピーするデータ型</typeparam>
			/// <param name="data">コピーするデータ</param>
			/// <returns>Uploadの成否</returns>
			template<typename T>
			[[nodiscard]] bool upload(
				const T& data
			) {

				if (sizeof(T) > resource_size) {
					return false;
				}

				return upload_resource(
					&data,
					sizeof(T)
				);
			}

			/// <summary>
			/// Upload関数オーバーロード
			/// </summary>
			/// <typeparam name="T">コピーするデータ型</typeparam>
			/// <param name="datas">コピーするデータ配列</param>
			/// <returns>Uploadの成否</returns>
			template<typename T>
			[[nodiscard]] bool upload(
				std::span<const T> datas
			) {

				if (
					datas.empty() ||
					datas.size_bytes() > resource_size
					) {

					return false;
				}

				return upload_resource(
					datas.data(),
					datas.size_bytes()
				);
			}


			/* ===== 取得関数 ===== */

			/// <summary>
			/// マップ先ポインター参照取得関数
			/// </summary>
			/// <typeparam name="T">キャストする型</typeparam>
			/// <returns>キャストしたマップ先ポインター参照</returns>
			template<typename T>
			T* get_mapped_cast() const noexcept {
				return static_cast<T*>(mapped_);
			}

		};
	}
}