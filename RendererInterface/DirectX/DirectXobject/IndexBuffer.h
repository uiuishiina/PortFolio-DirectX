#pragma once
#include"BufferResource.h"

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
			/// IndexBuffer 派生クラス
			///====================================================================

			//@brief	=== インデックスバッファ派生クラス ===
			class IndexBuffer final : public StaticBufferResource
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				IndexBuffer() = default;
				~IndexBuffer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== インデックスバッファ作成関数 ===
				//@param	device	DirectX12 デバイス
				//@param	buffer_data	インデックスバッファに書き込むデータ型配列
				//@return	作成の成否
				template<typename T>
				[[nodiscard]] HRESULT create_index_buffer(ID3D12Device* device, const std::vector<T>& buffer_data);

				//@brief	=== インデックスバッファビュー取得関数 ===
				//@return	インデックスバッファビュー参照
				[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== インデックスバッファビュー ==
				D3D12_INDEX_BUFFER_VIEW	index_buffer_view{};

				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	=== インデックスバッファ用GPUリソース設定作成 ===
				//@param	T_buffer_size	インデックスバッファメモリサイズ
				//@return	作成したインデックスバッファ用GPUリソース設定
				[[nodiscard]] desc::ResourceCreateDesc create_index_buffer_desc(UINT T_buffer_size);

				//@brief	=== インデックスバッファ用フォーマット取得関数 ===
				template<typename T>
				constexpr DXGI_FORMAT get_index_format();
			};

			//@brief	=== インデックスバッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	buffer_data	インデックスバッファに書き込むデータ型配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT IndexBuffer::create_index_buffer(ID3D12Device* device, const std::vector<T>& buffer_data) {

				const UINT buffer_size = static_cast<UINT>(buffer_data.size() * sizeof(T));
				const auto desc = create_index_buffer_desc(buffer_size);

				auto hr = create_committed_resource(device, desc);
				if (FAILED(hr)) {
					return hr;
				}

				hr = copy_buffer(buffer_data);
				if (FAILED(hr)) {
					return hr;
				}

				index_buffer_view.BufferLocation = resource_->GetGPUVirtualAddress();
				index_buffer_view.SizeInBytes = buffer_size;
				index_buffer_view.Format = get_index_format<T>();

				return hr;
			};

			//@brief	=== インデックスバッファ用フォーマット取得関数 ===
			//@details	データ型から変換した、フォーマットを返す関数
			//@return	インデックスフォーマット
			template<typename T>
			constexpr DXGI_FORMAT IndexBuffer::get_index_format() {
				if constexpr (std::is_same_v<T, UINT16>) {
					return DXGI_FORMAT_R16_UINT;
				}
				else if constexpr (std::is_same_v<T, UINT32>) {
					return DXGI_FORMAT_R32_UINT;
				}
				else {
					static_assert(sizeof(T) == 0, "Unsupported index_format type");
				}
			};
		};
	};
};