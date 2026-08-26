#pragma once
#include"DrawObjectBase.h"
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
		/// 描画オブジェクト名前空間
		///====================================================================

		namespace drawobject {

			///====================================================================
			/// MeshDesc 構造体
			///====================================================================

			//@brief	=== メッシュ設定構造体 ===
			template<typename T>
			struct MeshDesc
			{
				//@brief	== 頂点データ配列 ==
				std::vector<T> vertex_data{};

				//@brief	== 頂点データインデックス配列 ==
				std::vector<UINT> index_data{};

				//@breif	== 描画トポロジー設定 ==
				D3D_PRIMITIVE_TOPOLOGY topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			};

			///====================================================================
			/// Mesh クラス
			///====================================================================

			//@brief	=== メッシュクラス ===
			class Mesh : public DrawObjectBase
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
				//@param	list	描画用コマンドリスト参照
				//@param	upload_resource 各Staticバッファ用書き込み先バッファインスタンス(ライフタイムは外部管理)
				//@param	data	データ配列
				//@return	作成の成否
				template<typename T>
				[[nodiscard]] HRESULT create_mesh(ID3D12Device* device, ID3D12GraphicsCommandList* list, std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& upload_resource, const MeshDesc<T>& data);

				//@breif	=== ポリゴン描画関数 ===
				//@param	list	描画用コマンドリスト参照
				void draw(ID3D12GraphicsCommandList* list) const noexcept override;

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
			//@param	list	描画用コマンドリスト参照
			//@param	upload_resource 各Staticバッファ用書き込み先バッファインスタンス(ライフタイムは外部管理)
			//@param	data	データ配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT Mesh::create_mesh(ID3D12Device* device, ID3D12GraphicsCommandList* list, std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& upload_resource, const MeshDesc<T>& data) {

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
			};
		};
	};
};