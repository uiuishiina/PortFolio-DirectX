#pragma once
#include"StaticBufferResource.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// インデックスバッファ派生クラス
			/// </summary>
			class IndexBuffer final : public StaticBufferResource
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				IndexBuffer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~IndexBuffer() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// インデックスバッファ作成関数
				/// </summary>
				/// <typeparam name="T">インデックスバッファ用フォーマットに利用する型</typeparam>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="upload_resource">Uploadリソース参照</param>
				/// <param name="buffer_data">インデックスバッファに書き込むデータ型配列</param>
				/// <returns>作成の成否</returns>
				template<typename T>
				[[nodiscard]] HRESULT create_index_buffer(
					ID3D12Device* device,
					ID3D12GraphicsCommandList* list,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource,
					const std::vector<T>& buffer_data
				) {

					//	サイズとフォーマットを取得
					buffer_size = static_cast<UINT64>(buffer_data.size() * sizeof(T));
					format_ = get_index_format<T>();;

					//	リソース設定作成
					const auto desc = create_static_buffer_desc(buffer_data);

					//	リソース作成
					return create_static_buffer(device, list, upload_resource, desc);
				}

				/* -- 取得関数 -- */

				/// <summary>
				/// インデックスバッファビュー取得関数
				/// </summary>
				/// <returns>インデックスバッファビュー参照</returns>
				[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			protected:
				/* ========== Protectedメンバー関数 ========== */

				using StaticBufferResource::create_static_buffer_desc;

				/* -- 作成補助関数 -- */

				/// <summary>
				/// 設定構造体作成仮想関数
				/// </summary>
				/// <param name="data">初期設定データ構造体に設定する先頭ポインター</param>
				/// <param name="size">初期設定データ構造体に設定するメモリサイズ</param>
				/// <returns>作成した構造体</returns>
				[[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(
					const void* data, 
					UINT64 size
				) override;

				/// <summary>
				/// 派生先別リソース作成仮想関数
				/// </summary>
				/// <details>
				/// ここではインデックスバッファビューを作成
				/// </details>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_resource_object() override;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// インデックスバッファビュー
				/// </summary>
				D3D12_INDEX_BUFFER_VIEW	index_buffer_view{};

				/// <summary>
				/// バッファデータ全体のメモリサイズ保存変数
				/// </summary>
				UINT64 buffer_size{};

				/// <summary>
				/// インデックスバッファビューのフォーマット保存変数
				/// </summary>
				DXGI_FORMAT format_{};


				/* ========== Privateメンバー関数 ========== */

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
}