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
		/// 頂点バッファクラス
		/// </summary>
		class VertexBuffer final : public StaticResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			VertexBuffer() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~VertexBuffer() = default;


			/* ===== 初期化関数 ===== */

			/// <summary>
			/// 頂点バッファ作成関数
			/// </summary>
			/// <typeparam name="T">頂点バッファデータ型</typeparam>
			/// <param name="device_">Device参照</param>
			/// <param name="list_">コマンドリスト参照</param>
			/// <param name="upload_resource">Upload用GPU_Resource参照</param>
			/// <param name="buffer_data">頂点バッファデータ配列</param>
			/// <returns></returns>
			template<typename T>
			[[nodiscard]] HRESULT create_vertex_buffer(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource,
				std::span<const T> buffer_data
			) {

				//	サイズ取得
				class_size = sizeof(T);
				buffer_size = static_cast<UINT64>(buffer_data.size() * class_size);
				

				//	VerTexBuffer用リソース設定作成
				desc::StaticResourceDesc desc{};

				//	バッファをデータサイズ分用意
				desc.resource_desc = Helper::GPUResourceDescHelper::get_buffer_desc(buffer_data);

				//	初期データ作成
				desc.add_buffer_data(buffer_data);

				//	最終的なリソース設定を、読み取り専用で作成
				desc.final_state = D3D12_RESOURCE_STATE_GENERIC_READ;


				//	リソース作成
				return create_static_resource(device_, list_, upload_resource, desc);
			}


			/* ===== 取得関数 ===== */

			/// <summary>
			/// 頂点バッファビュー取得関数
			/// </summary>
			/// <returns>頂点バッファビュー</returns>
			[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW get_vertex_buffer_view()const noexcept {

				return vertex_buffer_view;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// 頂点バッファビュー
			/// </summary>
			D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view{};

			/// <summary>
			/// バッファデータメモリサイズ
			/// </summary>
			UINT64 buffer_size{};

			/// <summary>
			/// バッファデータ型メモリサイズ
			/// </summary>
			UINT class_size{};


			/* ========== Privateメンバー関数 ========== */

			/* ===== 初期化補助関数 ===== */

			/// <summary>
			/// 派生先別リソース作成関数
			/// </summary>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_resource_object() override {

				//	VertexBufferViweを作成
				vertex_buffer_view.BufferLocation = get_GPU_address();
				vertex_buffer_view.StrideInBytes = class_size;
				vertex_buffer_view.SizeInBytes = static_cast<UINT>(buffer_size);

				return S_OK;
			}

		};
	}
}