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
				[[nodiscard]] HRESULT create_index_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list,
					Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const std::vector<T>& buffer_data);

				//@brief	=== インデックスバッファビュー取得関数 ===
				//@return	インデックスバッファビュー参照
				[[nodiscard]] const D3D12_INDEX_BUFFER_VIEW* get_buffer_view()const noexcept;

			protected:
				///====================================================================
				/// Protected メンバー関数
				///====================================================================

				//@brief	=== 設定構造体作成仮想関数 ===
				//@param	data	初期設定データ構造体に設定する先頭ポインター
				//@param	size	初期設定データ構造体に設定するメモリサイズ
				//@return	作成した構造体
				[[nodiscard]] desc::StaticBufferCreateDesc create_static_buffer_desc(const void* data, UINT64 size) override;

				//@brief	=== 派生先別リソース作成仮想関数 ===
				//@details	基底クラスではS_OKを返す
				//@return	作成の成否
				[[nodiscard]] HRESULT create_resource_object() override;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== インデックスバッファビュー ==
				D3D12_INDEX_BUFFER_VIEW	index_buffer_view{};

				UINT buffer_size{};

				DXGI_FORMAT format_{};

				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	=== インデックスバッファ用フォーマット取得関数 ===
				template<typename T>
				constexpr DXGI_FORMAT get_index_format();
			};

			//@brief	=== インデックスバッファ作成関数 ===
			//@param	device	DirectX12 デバイス
			//@param	buffer_data	インデックスバッファに書き込むデータ型配列
			//@return	作成の成否
			template<typename T>
			[[nodiscard]] HRESULT IndexBuffer::create_index_buffer(ID3D12Device* device, ID3D12GraphicsCommandList* list,
				Microsoft::WRL::ComPtr<ID3D12Resource>& upload_resource, const std::vector<T>& buffer_data) {

				buffer_size = static_cast<UINT>(buffer_data.size() * sizeof(T));
				format_ = get_index_format<T>();;
				
				const auto desc = create_static_buffer_desc(buffer_data.data(), buffer_size);

				const auto hr = create_static_buffer(device, list, upload_resource, desc);
				if (FAILED(hr)) {
					return hr;
				}

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