#pragma once
#include"DrawObjectBase.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include<memory>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// 描画オブジェクト名前空間
		/// </summary>
		namespace drawobject {

			/// <summary>
			/// メッシュ設定構造体
			/// </summary>
			/// <typeparam name="T">頂点データ型</typeparam>
			template<typename T>
			struct MeshDesc {

				/* ========== メンバー変数 ========== */

				/// <summary>
				/// 頂点データ配列
				/// </summary>
				std::vector<T> vertex_data{};

				/// <summary>
				/// 頂点データインデックス配列
				/// </summary>
				std::vector<UINT> index_data{};

				/// <summary>
				/// 描画トポロジー設定
				/// </summary>
				D3D_PRIMITIVE_TOPOLOGY topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			};

			/// <summary>
			/// メッシュクラス
			/// </summary>
			class Mesh final : public DrawObjectBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				Mesh() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~Mesh() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// ポリゴン作成関数
				/// </summary>
				/// <details>
				/// ポリゴンデータに使用する型を設定
				/// </details>
				/// <typeparam name="T">メッシュ設定構造体の頂点データ型</typeparam>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="upload_resource">各Staticバッファ用書き込み先バッファインスタンス(ライフタイムは外部管理)</param>
				/// <param name="data">メッシュ設定構造体参照</param>
				/// <returns>作成の成否</returns>
				template<typename T>
				[[nodiscard]] HRESULT create_mesh(
					ID3D12Device* device,
					ID3D12GraphicsCommandList* list,
					std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& upload_resource,
					const MeshDesc<T>& data
				) {

					//	VertexBuffer作成
					vertex_buffer = std::make_unique<object::VertexBuffer>();
					auto hr = vertex_buffer->create_vertex_buffer(device, list, upload_resource[0], data.vertex_data);
					if (FAILED(hr)) {
						return hr;
					}

					//	IndexBuffer作成
					index_buffer = std::make_unique<object::IndexBuffer>();
					hr = index_buffer->create_index_buffer(device, list, upload_resource[1], data.index_data);
					if (FAILED(hr)) {
						return hr;
					}

					//	その他設定
					index_size = static_cast<UINT>(data.index_data.size());
					topology_ = data.topology_;

					return hr;
				}

				/* -- 描画関数 -- */

				/// <summary>
				/// ポリゴン描画関数
				/// </summary>
				/// <param name="list">描画用コマンドリスト参照</param>
				void draw(ID3D12GraphicsCommandList* list) const noexcept override;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// 頂点バッファクラスインスタンス
				/// </summary>
				std::unique_ptr<object::VertexBuffer> vertex_buffer{};

				/// <summary>
				/// インデックスバッファクラスインスタンス
				/// </summary>
				std::unique_ptr<object::IndexBuffer> index_buffer{};

				/// <summary>
				/// インデックス数保存変数
				/// </summary>
				UINT index_size{};

				/// <summary>
				/// トポロジー設定保存変数
				/// </summary>
				D3D_PRIMITIVE_TOPOLOGY topology_{};

			};
		}
	}
}