#pragma once
#include"NonMovable.h"
#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

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

			DXGI_FORMAT	format_ = DXGI_FORMAT_R32_UINT;
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

			//@brief	== 頂点バッファインスタンス ==
			Microsoft::WRL::ComPtr<ID3D12Resource>		vertex_buffer;

			//@brief	== インデックスバッファインスタンス ==
			Microsoft::WRL::ComPtr<ID3D12Resource>		index_buffer;

			//@brief	== 頂点バッファビュー ==
			D3D12_VERTEX_BUFFER_VIEW	vertex_buffer_view{};

			//@brief	== インデックスバッファビュー ==
			D3D12_INDEX_BUFFER_VIEW		index_buffer_view{};

			//@brief	== インデックス数保存変数 ==
			UINT index_size{};

			//@brief	== トポロジー設定保存変数 ==
			D3D_PRIMITIVE_TOPOLOGY topology_{};

			///====================================================================
			/// Private メンバー関数
			///====================================================================

			//@brief	=== 頂点バッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	T_memory_size	データ型サイズ
			//@return	作成の成否
			[[nodiscard]] HRESULT create_vertex_buffer(ID3D12Device* device, UINT T_buffer_size, UINT T_memory_size);

			//@brief	=== インデックスバッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	T_data_size	データ配列サイズ
			//@return	作成の成否
			[[nodiscard]] HRESULT create_index_buffer(ID3D12Device* device, UINT T_data_size, DXGI_FORMAT format);
		};


		//@brief	=== ポリゴン作成関数 ===
		//@details	ポリゴンデータに使用する型を設定
		//@param	device	DirectX12 デバイス
		//@param	data	データ配列
		//@return	作成の成否
		template<typename T>
		[[nodiscard]] HRESULT Mesh::create_mesh(ID3D12Device* device, const MeshDesc<T>& data) {

			//	メモリ量計算
			const auto memory_size = sizeof(T);
			const UINT buffer_size = static_cast<UINT>(data.vertex_data.size() * sizeof(T));

			//	頂点バッファ作成
			auto hr = create_vertex_buffer(device, buffer_size, memory_size);
			if (FAILED(hr)) {
				return hr;
			}

			//	頂点バッファマップ
			void* mapped = nullptr;
			hr = vertex_buffer->Map(0, nullptr, &mapped);
			if (FAILED(hr)) {
				return hr;
			}
			memcpy(mapped, data.vertex_data.data(), buffer_size);
			vertex_buffer->Unmap(0, nullptr);

			//	メモリ量計算
			const UINT index_count = static_cast<UINT>(data.index_data.size());
			const UINT index_buffer_size = index_count * ((data.format_ == DXGI_FORMAT_R32_UINT) ? 4 : 2);

			//	インデックスバッファ作成
			hr = create_index_buffer(device, index_buffer_size, data.format_);
			if (FAILED(hr)) {
				return hr;
			}

			//	インデックスバッファマップ
			mapped = nullptr;
			hr = index_buffer->Map(0, nullptr, &mapped);
			if (FAILED(hr)) {
				return hr;
			}
			memcpy(mapped, data.index_data.data(), data.index_data.size() * sizeof(data.index_data[0]));
			index_buffer->Unmap(0, nullptr);

			index_size = index_count;
			topology_ = data.topology_;
			return S_OK;
		};
	};
};