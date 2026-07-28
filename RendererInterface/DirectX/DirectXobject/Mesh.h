#pragma once
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include<memory>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// メッシュ名前空間
		///====================================================================

		namespace mesh {

			///====================================================================
			/// MeshDesc 構造体
			///====================================================================

			//@brief	=== メッシュ設定構造体 ===
			template<typename T>
			struct MeshDesc
			{
				std::vector<T> vertex_data{};

				std::vector<UINT> index_data{};

				D3D_PRIMITIVE_TOPOLOGY topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			};

			///====================================================================
			/// Mesh クラス
			///====================================================================

			//@brief	=== メッシュクラス ===
			class Mesh final : public NonMovableBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				Mesh() = default;
				~Mesh() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== ポリゴン作成関数 ===
				//@details	ポリゴンデータに使用する型を設定
				//@param	device	DirectX12 デバイス
				//@param	data	データ配列
				//@return	作成の成否
				template<typename T>
				[[nodiscard]] HRESULT create_mesh(ID3D12Device* device, const MeshDesc<T>& data);

				//@breif	=== ポリゴン描画関数 ===
				//@param	list	描画用コマンドリスト参照
				void draw_mesh(ID3D12GraphicsCommandList* list) const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	=== 頂点バッファクラスインスタンス ===
				std::unique_ptr<object::VertexBuffer> vertex_buffer{};

				//@brief	=== インデックスバッファクラスインスタンス ===
				std::unique_ptr<object::IndexBuffer> index_buffer{};

				//@brief	== インデックス数保存変数 ==
				UINT index_size{};

				//@brief	== トポロジー設定保存変数 ==
				D3D_PRIMITIVE_TOPOLOGY topology_{};

			};

			//@brief	=== ポリゴン作成関数 ===
			//@details	ポリゴンデータに使用する型を設定
			//@param	device	DirectX12 デバイス
			//@param	data	データ配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT Mesh::create_mesh(ID3D12Device* device, const MeshDesc<T>& data) {

				vertex_buffer = std::make_unique<object::VertexBuffer>();
				auto hr = vertex_buffer->create_vertex_buffer(device,data.vertex_data);
				if (FAILED(hr)) {
					return hr;
				}

				index_buffer = std::make_unique<object::IndexBuffer>();
				hr = index_buffer->create_index_buffer(device, data.index_data);
				if (FAILED(hr)) {
					return hr;
				}

				index_size = static_cast<UINT>(data.index_data.size());
				topology_ = data.topology_;

				return hr;
			}
		};
	};
};