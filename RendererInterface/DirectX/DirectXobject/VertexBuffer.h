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
			/// 頂点バッファ派生クラス
			/// </summary>
			class VertexBuffer final : public StaticBufferResource
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				VertexBuffer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~VertexBuffer() = default;


				/* ========== Publicメンバー関数 ========== */
				
				/* -- 作成関数 -- */

				/// <summary>
				/// 頂点バッファ作成関数
				/// </summary>
				/// <typeparam name="T">頂点データ型</typeparam>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="upload_resource">Uploadリソース参照</param>
				/// <param name="buffer_data">頂点バッファに書き込むデータ型配列</param>
				/// <returns>作成の成否</returns>
				template<typename T>
				[[nodiscard]] HRESULT create_vertex_buffer(
					ID3D12Device* device,
					ID3D12GraphicsCommandList* list,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource,
					const std::vector<T>& buffer_data
				) {

					//	サイズを取得
					class_size = sizeof(T);
					buffer_size = static_cast<UINT64>(buffer_data.size() * class_size);

					//	リソース設定作成
					const auto desc = create_static_buffer_desc(buffer_data);

					//	リソース作成
					return create_static_buffer(device, list, upload_resource, desc);
				}

				/* -- 取得関数 -- */

				/// <summary>
				/// 頂点バッファビュー取得関数
				/// </summary>
				/// <returns>頂点バッファビュー参照</returns>
				[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			protected:
				/* ========== Protectedメンバー関数 ========== */

				using StaticBufferResource::create_static_buffer_desc;

				/* -- 作成補助関数 -- */

				/// <summary>
				/// 設定構造体作成関数
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
				/// ここでは頂点バッファビューを作成
				/// </details>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_resource_object() override;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// 頂点バッファビュー
				/// </summary>
				D3D12_VERTEX_BUFFER_VIEW	vertex_buffer_view{};

				/// <summary>
				/// バッファデータ全体のメモリサイズ保存変数
				/// </summary>
				UINT64 buffer_size{};

				/// <summary>
				/// バッファデータのクラス型のメモリサイズ保存変数
				/// </summary>
				UINT class_size{};

			};
		}
	}
}