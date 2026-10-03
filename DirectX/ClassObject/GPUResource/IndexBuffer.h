#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"StaticResourceBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// インデックスバッファクラス
		/// </summary>
		class IndexBuffer final : public StaticResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			IndexBuffer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~IndexBuffer() = default;


			/* ===== 初期化関数 ===== */

			/// <summary>
			/// インデックスバッファ作成関数
			/// </summary>
			/// <typeparam name="T">インデックスバッファデータ型</typeparam>
			/// <param name="device_">Device参照</param>
			/// <param name="list_">コマンドリスト参照</param>
			/// <param name="upload_resource">Upload用GPU_Resource参照</param>
			/// <param name="buffer_data">インデックスバッファデータ配列</param>
			/// <returns></returns>
			template<typename T>
			[[nodiscard]] HRESULT create_index_buffer(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource,
				std::span<const T> buffer_data
			) {

				//	変数取得
				buffer_size = static_cast<UINT64>(buffer_data.size() * sizeof(T));
				format_ = get_index_format<T>();;


				//	IndexBuffer用リソース設定作成
				desc::StaticResourceDesc desc{};

				//	バッファサイズをデータサイズ分用意
				desc.resource_desc = Helper::GPUResourceDescHelper::get_buffer_desc(buffer_size);

				//	初期データ作成
				desc.add_buffer_data(buffer_data);

				//	最終的なリソース設定を、読み取り専用で作成
				desc.final_state = D3D12_RESOURCE_STATE_GENERIC_READ;

				//	リソース作成
				return create_static_resource(device_, list_, upload_resource, desc);
			}


			/* ===== 取得関数 ===== */

			/// <summary>
			/// インデックスバッファビュー取得関数
			/// </summary>
			/// <returns>インデックスバッファビュー</returns>
			[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW& get_index_buffer_view()const noexcept {

				return index_buffer_view;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// インデックスバッファビュー
			/// </summary>
			D3D12_INDEX_BUFFER_VIEW	index_buffer_view{};

			/// <summary>
			/// バッファデータメモリサイズ
			/// </summary>
			UINT64 buffer_size{};

			/// <summary>
			/// インデックスバッファビューフォーマット\
			/// </summary>
			DXGI_FORMAT format_{};


			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化補助関数 ===== */

			/// <summary>
			/// 派生先別リソース作成関数
			/// </summary>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_resource_object() override {

				//	IndexBufferView作成
				index_buffer_view.BufferLocation = get_GPU_address();
				index_buffer_view.SizeInBytes = static_cast<UINT>(buffer_size);
				index_buffer_view.Format = format_;

				return S_OK;
			}


			/* ===== 取得関数 ===== */

			/// <summary>
			/// インデックスバッファ用フォーマット取得関数
			/// </summary>
			/// <typeparam name="T">インデックスバッファデータ型</typeparam>
			/// <returns>取得したフォーマット</returns>
			template<typename T>
			constexpr DXGI_FORMAT get_index_format() {

				if constexpr (std::is_same_v<T, UINT16>) {
					return DXGI_FORMAT_R16_UINT;
				}
				else if constexpr (std::is_same_v<T, UINT32>) {
					return DXGI_FORMAT_R32_UINT;
				}
				else {
					static_assert(sizeof(T) == 0, "Unsupported index_format type");
				}
			}

		};
	}
}