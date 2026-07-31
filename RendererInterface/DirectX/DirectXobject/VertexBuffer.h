#pragma once
#include"StaticBufferResource.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// DX12オブジェクトラッパークラス名前空間
		///====================================================================

		namespace object {

			///====================================================================
			/// VertexBuffer 派生クラス
			///====================================================================

			//@brief	=== 頂点バッファ派生クラス ===
			class VertexBuffer final : public StaticBufferResource
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				VertexBuffer() = default;
				~VertexBuffer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================
				
				//@brief	=== 頂点バッファ作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	buffer_data	頂点バッファに書き込むデータ型配列
				//@return	作成の成否
				template<typename T>
				[[nodiscard]] HRESULT create_vertex_buffer(ID3D12Device* device, const std::vector<T>& buffer_data);

				//@brief	=== 頂点バッファビュー取得関数 ===
				//@return	頂点バッファビュー参照
				[[nodiscard]] const D3D12_VERTEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 頂点バッファビュー ==
				D3D12_VERTEX_BUFFER_VIEW	vertex_buffer_view{};

				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	=== 頂点バッファ用GPUリソース設定作成 ===
				//@param	T_buffer_size	頂点バッファメモリサイズ
				//@return	作成した頂点バッファ用GPUリソース設定
				[[nodiscard]] desc::ResourceCreateDesc create_vertex_buffer_desc(UINT T_buffer_size);

			};

			//@brief	=== 頂点バッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	buffer_data	頂点バッファに書き込むデータ型配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT VertexBuffer::create_vertex_buffer(ID3D12Device* device, const std::vector<T>& buffer_data) {

				const UINT buffer_size = static_cast<UINT>(buffer_data.size() * sizeof(T));
				const auto desc = create_vertex_buffer_desc(buffer_size);

				auto hr = create_committed_resource(device, desc);
				if (FAILED(hr)) {
					return hr;
				}

				hr = copy_buffer(buffer_data);
				if (FAILED(hr)) {
					return hr;
				}

				vertex_buffer_view.BufferLocation = resource_->GetGPUVirtualAddress();
				vertex_buffer_view.StrideInBytes = sizeof(T);
				vertex_buffer_view.SizeInBytes = buffer_size;

				return hr;
			};
		};
	};
};