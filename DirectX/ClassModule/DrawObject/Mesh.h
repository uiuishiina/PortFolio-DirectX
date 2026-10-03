#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/VertexBuffer.h"
#include"../../ClassObject/GPUResource/IndexBuffer.h"

#include"DrawObjectBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// オブジェクト機能統合設定名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// メッシュ設定構造体
			/// </summary>
			/// <typeparam name="T">頂点データ型</typeparam>
			template<typename T>
			struct MeshDesc {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// 頂点データ配列
				/// </summary>
				std::vector<T> vertex_{};

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// インデックスデータ配列
				/// </summary>
				std::vector<UINT16> index_{};

				/// <summary>
				/// 描画トポロジー設定
				/// </summary>
				D3D_PRIMITIVE_TOPOLOGY topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			};
		}


		/// <summary>
		/// メッシュクラス
		/// </summary>
		class Mesh final : public DrawObjectBase
		{
			using Resource = Microsoft::WRL::ComPtr<ID3D12Resource>;
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Mesh() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~Mesh() = default;


			/* ===== 初期化関数 ===== */

			/// <summary>
			/// メッシュ作成関数
			/// </summary>
			/// <typeparam name="T">頂点データ型</typeparam>
			/// <param name="device_">Device参照</param>
			/// <param name="list_">コマンドリスト参照</param>
			/// <param name="upload_resources">Upload用GPU_Resource参照配列</param>
			/// <param name="desc">メッシュ設定構造体参照</param>
			/// <returns>作成の成否</returns>
			template<typename T>
			[[nodiscard]] HRESULT create_mesh(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				std::span<std::reference_wrapper<Resource>>& upload_resources,
				const desc::MeshDesc<T>& desc
			) {

				//	Upload用Resourceが足りないなら失敗
				if (upload_resources.size() < 2) {
					return E_INVALIDARG;
				}

				//	頂点バッファ作成
				auto hr = vertex_.create_vertex_buffer(
					device_,
					list_,
					upload_resources[0].get(),
					std::span<const T>{desc.vertex_}
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	インデクスバッファ作成
				hr = index_.create_index_buffer(
					device_,
					list_,
					upload_resources[1].get(),
					std::span<const UINT16>{desc.index_}
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	変数取得
				topology_ = desc.topology_;
				index_count = static_cast<UINT>(desc.index_.size());

				return hr;
			}


			/* ===== 実行関数 ===== */

			/// <summary>
			/// メッシュ描画関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			void draw(
				ID3D12GraphicsCommandList* list_
			) const noexcept override {

				//	VertexBuffer設定
				list_->IASetVertexBuffers(0, 1,&vertex_.get_vertex_buffer_view());

				//	IndexBuffer設定
				list_->IASetIndexBuffer(&index_.get_index_buffer_view());

				//	プリミティブトポロジー設定
				list_->IASetPrimitiveTopology(topology_);

				//	描画
				list_->DrawIndexedInstanced(index_count, 1, 0, 0, 0);

			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// 頂点バッファクラス
			/// </summary>
			ClassObject::VertexBuffer vertex_{};

			/// <summary>
			/// インデックスバッファクラス
			/// </summary>
			ClassObject::IndexBuffer index_{};

			/// <summary>
			/// インデックスカウント
			/// </summary>
			UINT index_count{};

			/// <summary>
			/// 描画トポロジー設定
			/// </summary>
			D3D_PRIMITIVE_TOPOLOGY topology_{};

		};

	}
}