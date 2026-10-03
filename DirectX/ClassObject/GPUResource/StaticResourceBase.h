#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"GPUResourceBase.h"
#include"ResourceBarrier.h"

#include"../../Helpers/GPUResourceHelper.h"
#include"../../Helpers/GPUResourceDescHelper.h"

//	その他
#include<vector>
#include<span>

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
			/// 静的リソース設定構造体
			/// </summary>
			struct StaticResourceDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// リソース設定
				/// </summary>
				D3D12_RESOURCE_DESC resource_desc{};

				/// <summary>
				/// リソースステート設定
				/// </summary>
				D3D12_RESOURCE_STATES final_state{ D3D12_RESOURCE_STATE_COMMON };

				/// <summary>
				/// 初期化データ設定配列
				/// </summary>
				/// <details>
				/// D3D12_SUBRESOURCE_DATA {
				///		const void	*pData;		= データ先頭ポインター
				///		LONG_PTR	RowPitch;	= データ一行分のメモリサイズ
				///		LONG_PTR	SlicePitch;	= データ全体のメモリサイズ
				/// }
				/// </details>
				std::vector<D3D12_SUBRESOURCE_DATA> data_{};

				/* ========== Publicメンバー関数 ========== */

				/* ===== Buffer用関数 ===== */

				/// <summary>
				/// Bufferデータ追加関数
				/// </summary>
				/// <param name="data">データ先頭ポインター</param>
				/// <param name="size">データ全体のメモリサイズ</param>
				void add_buffer_data(
					const void* data,
					UINT64 size
				) {

					data_.push_back({
						data,
						static_cast<LONG_PTR>(size),
						static_cast<LONG_PTR>(size)
					});
				}
				
				/// <summary>
				/// Bufferデータ追加関数オーバーロード
				/// </summary>
				/// <typeparam name="T">追加するデータ型</typeparam>
				/// <param name="span">追加するデータ配列</param>
				template<typename T>
				void add_buffer_data(
					std::span<const T> span
				) {

					data_.push_back({
						span.data(),
						static_cast<LONG_PTR>(span.size_bytes()),
						static_cast<LONG_PTR>(span.size_bytes())
					});
				}

				/* ===== Texture用関数 ===== */

				/// <summary>
				/// Textureデータ追加関数
				/// </summary>
				/// <param name="data">データ先頭ポインター</param>
				/// <param name="row_pitch">データ一行分のメモリサイズ</param>
				/// <param name="slice_pitch">データ全体のメモリサイズ</param>
				void add_texture_data(
					const void* data,
					LONG_PTR row_pitch,
					LONG_PTR slice_pitch
				) {

					data_.push_back({
						data,
						row_pitch,
						slice_pitch
					});
				}

			};
		}

		/// <summary>
		/// 静的GPUリソース基底クラス
		/// </summary>
		class StaticResourceBase : public GPUResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			StaticResourceBase() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~StaticResourceBase() = default;

		protected:
			/* ========== Protectedメンバー変数 ========== */

			/// <summary>
			/// リソースバリア管理クラス
			/// </summary>
			ResourceBarrier barrier_{ D3D12_RESOURCE_STATE_COPY_DEST };

			/* ========== Protectedメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// 静的GPUリソース作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="list_">コマンドリスト参照</param>
			/// <param name="upload_resource">Upload用GPU_Resource参照</param>
			/// <param name="desc">静的リソース設定構造体参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_static_resource(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource,
				const desc::StaticResourceDesc& desc
			) {

				//	データがないなら作成しない
				if (desc.data_.empty()) {
					return E_INVALIDARG;
				}

				//	Default_Resource作成
				auto hr = create_default_resource(
					device_, 
					desc
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	サイズ計算
				const auto num_subresources = static_cast<UINT>(desc.data_.size());
				const auto upload_size = Helper::GPUResourceHelper::get_required_intermediate_size(
					resource_.Get(),
					0,
					num_subresources
				);

				//	Upload_Resource作成
				hr = create_upload_resource(
					device_, 
					upload_size, 
					upload_resource
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	データコピー...	0ならコピーできていない事になるためエラー
				if (0 == Helper::GPUResourceHelper::update_subresource(
					list_,
					resource_.Get(),
					upload_resource.Get(),
					0,
					0,
					num_subresources,
					desc.data_.data()
				)) {

					return E_FAIL;
				}

				//	リソースバリア遷移
				barrier_transition(
					list_,
					desc.final_state
				);

				//	派生クラス固有処理
				return create_resource_object();
			}

			/* ===== 初期化補助関数 ===== */

			/// <summary>
			/// 派生先別リソース作成仮想関数
			/// </summary>
			/// <details>
			/// 基底クラスではS_OKを返す
			/// </details>
			/// <returns>作成の成否</returns>
			[[nodiscard]] virtual HRESULT create_resource_object() { return S_OK; };

		private:
			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// Default用GPUResource作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="desc">静的リソース設定構造体参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_default_resource(
				ID3D12Device* device_,
				const desc::StaticResourceDesc& desc
			) {

				desc::GPUResourceDesc create_desc{};

				create_desc.heap_properties = Helper::GPUResourceDescHelper::get_heap_properties(D3D12_HEAP_TYPE_DEFAULT);
				create_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
				create_desc.resource_desc = desc.resource_desc;
				create_desc.initial_state = D3D12_RESOURCE_STATE_COMMON;

				return create_committed_resource(
					device_,
					create_desc
				);
			}

			/// <summary>
			/// Upload用Resource作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="upload_size">Upload用Resourceサイズ</param>
			/// <param name="upload_resource">Upload用GPU_Resource参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_upload_resource(
				ID3D12Device* device_,
				UINT64 upload_size,
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource
			) {

				desc::GPUResourceDesc create_desc{};

				create_desc.heap_properties = Helper::GPUResourceDescHelper::get_heap_properties(D3D12_HEAP_TYPE_UPLOAD);
				create_desc.heap_flags = D3D12_HEAP_FLAG_NONE;
				create_desc.resource_desc = Helper::GPUResourceDescHelper::get_buffer_desc(upload_size);
				create_desc.initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;	//	コピーするために読み取り専用にしておく

				return create_committed_resource(
					device_,
					create_desc,
					upload_resource
				);
			}
			
			/// <summary>
			/// リソースバリア遷移関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			/// <param name="next_state">遷移先リソースステート</param>
			void barrier_transition(
				ID3D12GraphicsCommandList* list_,
				D3D12_RESOURCE_STATES next_state
			) {

				//	リソースバリア遷移
				barrier_.barrier_transition(
					list_,
					resource_.Get(),
					next_state
				);
			}

		};
	}
}